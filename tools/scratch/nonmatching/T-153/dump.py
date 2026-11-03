#!/usr/bin/env python3
"""Compile one draft inside its owning TU and diff its asm against the target.

Uses the same compiler invocation as tools/permuter/screen.py. The target
function's bytes are extracted from build/segments/<area>.bin into a small
binary object that objdump can disassemble at the original address.
"""
import argparse
import difflib
import importlib.util
import json
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

OBJDUMP = ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'
BASES = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}


def build_source(function, draft, prefix=False):
    owners = []
    for tu in (ROOT / 'src').glob('*/*.c'):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(function) + r'\.s"\)', text)
        if m:
            owners.append((tu, text, m))
    tu, text, m = owners[0]
    candidate = draft.read_text()
    source = text[:m.start()] + candidate + ('' if prefix else text[m.end():])
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


def blocks(objdump_text):
    out = {}
    for b in re.split(r'\n(?=[0-9a-f]{8} <)', objdump_text):
        head = b.split('\n', 1)[0]
        m = re.match(r'([0-9a-f]{8}) <([^>]+)>:', head)
        if m:
            out[m.group(2)] = b.split('\n')
    return out


def norm(lines, strip_addr=True):
    res = []
    for line in lines[1:]:
        line = line.split('#')[0].rstrip()
        if not line.strip():
            continue
        if strip_addr:
            m = re.match(r'\s*([0-9a-f]+):\s*(.*)', line)
            if m:
                line = '\t' + m.group(2)
        res.append(line)
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft')
    ap.add_argument('--prefix', action='store_true')
    args = ap.parse_args()
    draft = Path(args.draft)
    if not draft.is_absolute():
        draft = ROOT / draft
    source, tu = build_source(args.function, draft, args.prefix)
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == args.function)
    base = BASES[row['area']]
    off = int(args.function[5:], 16) - base
    blob = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[off:off + row['bytes']]
    with tempfile.TemporaryDirectory(prefix='kig-dump-') as d:
        path = Path(d) / 'candidate.c'
        o = compile_source(source, path)
        cand_text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                                   capture_output=True, text=True).stdout
        target = Path(d) / 'target.bin'
        target.write_bytes(blob)
        tgt_text = subprocess.run([str(OBJDUMP), '-D', '-b', 'binary', '-m', 'mips:isa32',
                                   '-EB', '--adjust-vma', hex(int(args.function[5:], 16)),
                                   '--no-show-raw-insn', str(target)],
                                  capture_output=True, text=True).stdout
    cb = blocks(cand_text).get(args.function)
    if cb is None:
        print('candidate function not found in object; symbols:', list(blocks(cand_text)), file=sys.stderr)
        raise SystemExit(1)
    tb = blocks(tgt_text)
    tname = next(iter(tb))
    a = norm(cb)
    b = norm(tb[tname])
    diff = list(difflib.unified_diff(b, a, fromfile='target', tofile='draft', lineterm='', n=2))
    if not diff:
        print(f'{args.function}: IDENTICAL ({len(a)} instructions)')
    else:
        print('\n'.join(diff))
    print(f'\n# {args.function}: target {len(b)} instr, draft {len(a)} instr, tu {tu.relative_to(ROOT)}')


if __name__ == '__main__':
    main()
