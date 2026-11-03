#!/usr/bin/env python3
"""Readable instruction-level diff of a draft against the original splat assembly.

Both sides are canonicalized: relocations folded to symbol names, immediates
to integers, registers to names without `$`, and branch targets to `LBL`.
So every remaining line difference is a real codegen difference.
"""
import argparse
import os
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


LEAD = Path("/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-6960f82c")
BASEREV = '62c5c59'
def owner(function):
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(function) + r'\.s)"\)', text)
        if m:
            return tu, text, m
    # matched in this worktree: fall back to the starting commit's TU text
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        rel = tu.relative_to(ROOT)
        r = subprocess.run(['git', '-C', str(ROOT), 'show', f'{BASEREV}:{rel}'], capture_output=True, text=True)
        if r.returncode:
            continue
        m = re.search(r'#pragma GLOBAL_ASM\("([^"]*/' + re.escape(function) + r'\.s)"\)', r.stdout)
        if m:
            return tu, r.stdout, m
    raise SystemExit(f'no owner for {function}')


def build_source(function, draft, prefix=False):
    prefix = prefix or bool(os.environ.get('PREFIX'))
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
    return fix_addends(out)


def fix_addends(pairs):
    """REL relocs keep the addend in the immediate: fold it into the reloc so `sym+N` canonicalizes like splat's absolute names."""
    pairs = [[a, i, [list(r) for r in rels]] for a, i, rels in pairs]
    for k, (_, ins, rels) in enumerate(pairs):
        for rel in rels:
            if rel[0] != 'R_MIPS_LO16':
                continue
            m = re.search(r',\s*(-?\d+)(?:\(\w+\))?$', ins)
            n = int(m.group(1)) if m else 0
            if not n:
                continue
            total = n
            for j in range(k - 1, -1, -1):
                hr = [r for r in pairs[j][2] if r[0] == 'R_MIPS_HI16' and r[1] == rel[1]]
                if hr:
                    hm = re.search(r'lui\s+\w+,\s*(0x[0-9a-f]+|\d+)', pairs[j][1])
                    h = int(hm.group(1), 0) if hm else 0
                    total = (h << 16) + n
                    hr[0][2] = str(total)
                    break
            rel[2] = str(total)
            pairs[k][1] = re.sub(r'(-?\d+)(\(\w+\))?$', lambda mm: '0' + (mm.group(2) or ''), ins)
    return pairs


def apply_relocs(ins, rels):
    if not rels:
        return ins
    kinds = {k for k, _, _ in rels}
    sym = rels[0][1]
    add = rels[0][2]
    if add and re.fullmatch(r'-?\d+', add) and int(add) != 0:
        sym = f'{sym}+{add}'
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
    sp = ROOT / m.group(1)
    if not sp.exists(): sp = LEAD / m.group(1)
    for line in sp.read_text().splitlines():
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


def absaddr(line):
    def f(m):
        kind, name, add = m.group(1), m.group(2), m.group(3)
        mm = re.fullmatch(r'(?:D|func|jtbl|L)_([0-9A-Fa-f]{8})', name)
        if not mm:
            return m.group(0)
        a = int(mm.group(1), 16) + (int(add.replace('+', '').strip(), 0) if add else 0)
        return f'%{kind}({a:#x})'
    return re.sub(r'%(hi|lo)\((\w+)(\s*[+-]\s*(?:0x[0-9a-fA-F]+|\d+))?\)', f, line)


def canon(line):
    line = absaddr(line)
    line = re.sub(r'\bs8\b', 'fp', line)
    if os.environ.get('RONORM'):
        line = re.sub(r'%hi\((?:\.rodata|0x8029[0-9a-f]{4})\)', '%hi(RO)', line)
        line = re.sub(r'%lo\(0x8029[0-9a-f]{4}\)\(', 'RO(', line)
        line = re.sub(r'^((?:l|s)[wd]c1 \w+,)\d+\(at\)$', r'\1RO(at)', line)
    line = re.sub(r'\$', '', line)
    line = re.sub(r'0x80000000 >> 16', '0x8000', line)
    m = re.match(r'(\S+)\s*(.*)$', line)
    mnem, rest = m.group(1), m.group(2)
    compact = rest.replace(' ', '')
    if mnem == 'move':
        mnem = 'or'
        dst, src = compact.split(',', 1)
        rest = f'{dst},{src},zero'
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
    import os
    mask = bool(os.environ.get('REGMASK'))
    def M(x):
        return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x) if mask else x
    mine = [canon(apply_relocs(i, r)) for _, i, r in pairs]
    theirs = [canon(t) for t in target_raw(args.function)]
    theirs = [t for t in theirs if not t.startswith(('dlabel','enddlabel'))]
    mine = [M(x) for x in mine]; theirs = [M(x) for x in theirs]
    print(f'# {args.function}  target {len(theirs)} instr / draft {len(mine)} instr  ({tu.relative_to(ROOT)})')
    diff = list(difflib.unified_diff(theirs, mine, fromfile='target', tofile='draft',
                                     lineterm='', n=args.context))
    if os.environ.get('STACK'):
        from collections import Counter
        def sl(lines):
            c = Counter()
            for l in lines:
                m = re.match(r'(sw|lw|sb|lbu|swc1|lwc1|sh|lhu) \S+?,(-?\d+)\(sp\)$', l.replace('R,R','x')) if False else re.match(r'(sw|lw|sb|lbu|swc1|lwc1|sh|lhu) (\w+),(\d+)\(sp\)$', l)
                if m and int(m.group(3)) >= 0x10:
                    c[int(m.group(3))] += 1
            return c
        a, b = sl(theirs), sl(mine)
        for k in sorted(set(a) | set(b)):
            print(f'{k:4d} (0x{k:x})  target={a[k]} draft={b[k]}')
        return
    if os.environ.get('COUNT'):
        sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
        bad = sum(max(i2-i1, j2-j1) for t,i1,i2,j1,j2 in sm.get_opcodes() if t != 'equal')
        print(f'{args.draft}: lines target={len(theirs)} draft={len(mine)} diffwords={bad}')
        return
    print('\n'.join(diff) if diff else 'IDENTICAL')


if __name__ == '__main__':
    main()
