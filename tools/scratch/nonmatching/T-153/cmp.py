#!/usr/bin/env python3
"""Readable instruction-level diff of a draft against the original splat assembly.

Both sides are canonicalized: relocations folded to symbol names, immediates
to integers, registers to names without `$`, and branch targets to `LBL`.
So every remaining line difference is a real codegen difference.
"""
import argparse
import difflib
import importlib.util
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'

ALIASES = {'or': 'move'}


def owner(function):
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(function) + r'\.s)"\)', text)
        if m:
            return tu, text, m
    raise SystemExit(f'no owner for {function}')


def build_source(function, draft, prefix=False):
    tu, text, m = owner(function)
    source = text[:m.start()] + draft.read_text() + ('' if prefix else text[m.end():])
    if prefix:
        source = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', source)
    return source, tu


def compile_source(source, path):
    path.write_text(source)
    o = path.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', str(o), str(path)]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        print(r.stderr[-8000:], file=sys.stderr)
        raise SystemExit(1)
    return o


RELOC = re.compile(r'^\s*[0-9a-f]+:\s+(R_MIPS_\w+)\s+(\S+)(?:\s*\+?\s*(-?\w+))?$')


def draft_raw(o, function):
    text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                          capture_output=True, text=True).stdout
    lines = text.splitlines()
    start = None
    for i, line in enumerate(lines):
        if re.match(r'^[0-9a-f]{8} <' + re.escape(function) + r'>:$', line):
            start = i
            break
    if start is None:
        raise SystemExit('function not found in object')
    out = []
    for line in lines[start + 1:]:
        if re.match(r'^[0-9a-f]{8} <', line):
            break
        r = RELOC.match(line)
        if r and out:
            out[-1][2].append((r.group(1), r.group(2), r.group(3)))
            continue
        m = re.match(r'\s*([0-9a-f]+):\t(.*?)(?:\s*#.*)?$', line)
        if m:
            out.append([int(m.group(1), 16), m.group(2).strip(), []])
            continue
    return out


def apply_relocs(ins, rels):
    if not rels:
        return ins
    kinds = {k for k, _, _ in rels}
    sym = rels[0][1]
    add = rels[0][2]
    if 'R_MIPS_26' in kinds:
        return re.sub(r'\b(jal|j)\s+.*$', lambda m: f'{m.group(1)} {sym}', ins)
    if 'R_MIPS_HI16' in kinds:
        return re.sub(r'(lui\s+\w+),\s*(?:0x0|0)\b', lambda m: f'{m.group(1)},%hi({sym})', ins)
    if 'R_MIPS_LO16' in kinds:
        if re.search(r'(?<=,)\s*-?0\(', ins):
            return re.sub(r'(?<=,)\s*-?0\(', f'%lo({sym})(', ins, count=1)
        return re.sub(r',\s*-?0$', f',%lo({sym})', ins)
    return ins


def target_raw(function):
    tu, text, m = owner(function)
    out = []
    for line in (ROOT / m.group(1)).read_text().splitlines():
        line = re.sub(r'/\*[^*]*\*/', ' ', line).split('#')[0].strip()
        if not line:
            continue
        mnem = line.split()[0]
        if mnem.startswith('.') or mnem in ('glabel', 'endlabel', 'nonmatching', '}', '{'):
            continue
        out.append(line)
    return out


OFFSET = re.compile(r'^(-?)(0x[0-9A-Fa-f]+|-?\d+)\((\w+)\)$')


def imm(token):
    token = re.sub(r'\s+', '', token.strip())
    if token in ('zero', '$zero', '$0'):
        return 'zero'
    off = OFFSET.match(token)
    if off:
        sign, value, reg = off.groups()
        n = int(value, 16) if value.startswith('0x') else int(value)
        return f'{sign}{n}({reg})'
    hexshift = re.fullmatch(r'\(?(0x[0-9A-Fa-f]+)>>16\)?', token)
    if hexshift:
        return str(int(hexshift.group(1), 16) >> 16)
    hexmask = re.fullmatch(r'\(?(0x[0-9A-Fa-f]+)&(0[xX][0-9A-Fa-f]+)\)?', token)
    if hexmask:
        v = int(hexmask.group(1), 16) & int(hexmask.group(2), 16)
        return str(v - (1 << 32) if v & 0x80000000 else v)
    if re.fullmatch(r'-?0x[0-9A-Fa-f]+', token):
        return str(int(token, 16))
    if re.fullmatch(r'-?\d+', token):
        return str(int(token))
    return token


def canon(line):
    line = re.sub(r'\$', '', line)
    line = re.sub(r'0x80000000 >> 16', '0x8000', line)
    m = re.match(r'(\S+)\s*(.*)$', line)
    mnem, rest = m.group(1), m.group(2)
    compact = rest.replace(' ', '')
    if mnem == 'move':
        mnem = 'or'
        dst, src = compact.split(',', 1)
        rest = f'{dst},zero,{src}'
    if mnem in ('addu', 'addiu', 'sll', 'sra', 'srl', 'sw', 'lw', 'sb', 'lbu', 'lhu', 'sh',
                'lwc1', 'swc1', 'sdc1', 'ldc1', 'addi', 'andi', 'ori', 'slt', 'sltu',
                'subu', 'mult', 'multu', 'div', 'jalr', 'lui', 'break', 'li', 'or',
                'lh', 'lhu', 'lb', 'sh', 'sd', 'ld', 'movn', 'movz', 'negu', 'nor',
                'xor', 'xori', 'slti', 'sltiu', 'lwl', 'lwr', 'swl', 'swr'):
        parts = [p.strip() for p in rest.split(',')]
        parts = [imm(p) for p in parts]
        if mnem == 'li':
            mnem = 'addiu'
            if len(parts) == 2:
                parts = [parts[0], 'zero', parts[1]]
        rest = ','.join(parts)
    if re.match(r'b', mnem) or mnem in ('j', 'jal', 'jr', 'jalr'):
        parts = [p.strip() for p in rest.split(',')]
        parts = [imm(p) for p in parts]
        targets = [i for i, p in enumerate(parts[-1:])]
        parts[-1] = 'LBL'
        rest = ','.join(parts)
    if mnem in ('sdc1', 'ldc1', 'lwc1', 'swc1', 'mtc1', 'mfc1', 'ctc1', 'cvt.s.w', 'cvt.d.s',
                'cvt.d.w', 'cvt.s.d', 'trunc.w.s', 'c.le.s', 'c.lt.s', 'c.eq.s', 'c.le.d',
                'c.lt.d', 'mov.s', 'mov.d', 'neg.s', 'add.s', 'sub.s', 'mul.s', 'div.s',
                'add.d', 'sub.d', 'mul.d', 'div.d', 'sqrt.s'):
        parts = [re.sub(r'\s+', '', p) for p in rest.split(',')]
        return f'{mnem} ' + ','.join(imm(p) for p in parts)
    rest = re.sub(r'\s+', '', rest)
    if mnem in ('beqzl', 'bnezl'):
        mnem, rest = {'beqzl': 'beql', 'bnezl': 'bnel'}[mnem], rest.replace(',', ',zero,', 1)
    return f'{mnem} {rest}' if rest else mnem


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft')
    ap.add_argument('--prefix', action='store_true')
    ap.add_argument('--context', type=int, default=2)
    args = ap.parse_args()
    draft = Path(args.draft)
    if not draft.is_absolute():
        draft = ROOT / draft
    source, tu = build_source(args.function, draft, args.prefix)
    with tempfile.TemporaryDirectory(prefix='kig-dump-') as d:
        path = Path(d) / 'candidate.c'
        o = compile_source(source, path)
        pairs = draft_raw(o, args.function)
    mine = [canon(apply_relocs(i, r)) for _, i, r in pairs]
    theirs = [canon(t) for t in target_raw(args.function)]
    print(f'# {args.function}  target {len(theirs)} instr / draft {len(mine)} instr  ({tu.relative_to(ROOT)})')
    diff = list(difflib.unified_diff(theirs, mine, fromfile='target', tofile='draft',
                                     lineterm='', n=args.context))
    print('\n'.join(diff) if diff else 'IDENTICAL')


if __name__ == '__main__':
    main()
