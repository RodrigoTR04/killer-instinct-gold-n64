#!/usr/bin/env python3
"""Word-exact diff: report only the instructions whose masked words differ.

Uses the same compiler path and relocation masks as tools/permuter/screen.py,
so the set printed here is exactly what the score counts.
"""
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


def build(function, draft, prefix=False):
    owners = []
    for tu in sorted((ROOT / 'src').glob('*/*.c')):
        text = tu.read_text()
        m = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(function) + r'\.s"\)', text)
        if m:
            owners.append((tu, text, m))
    tu, text, m = owners[0]
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
        print(r.stderr[-6000:], file=sys.stderr)
        raise SystemExit(1)
    return o


def instructions(o, function):
    text = subprocess.run([str(OBJDUMP), '-dr', '--no-show-raw-insn', str(o)],
                          capture_output=True, text=True).stdout
    out, started = [], False
    for line in text.splitlines():
        if re.match(r'^[0-9a-f]{8} <' + re.escape(function) + r'>:$', line):
            started = True
            continue
        if started and re.match(r'^[0-9a-f]{8} <', line):
            break
        if not started:
            continue
        m = re.match(r'\s*[0-9a-f]+:\t(.*?)(?:\s*#.*)?$', line)
        if m:
            out.append(m.group(1).strip())
    return out


def target_bytes(function):
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == function)
    off = int(function[5:], 16) - BASES[row['area']]
    blob = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()
    return blob[off:off + row['bytes']]


def main():
    function, draft = sys.argv[1], Path(sys.argv[2])
    prefix = '--prefix' in sys.argv
    if not draft.is_absolute():
        draft = ROOT / draft
    source, tu = build(function, draft, prefix)
    with tempfile.TemporaryDirectory(prefix='kig-word-') as d:
        o = compile_source(source, Path(d) / 'c.c')
        code, masks, _ = screen.elf.elf_function(o, function)
    target = target_bytes(function)
    a = struct.unpack('>' + 'I' * (len(code) // 4), code)
    b = struct.unpack('>' + 'I' * (len(target) // 4), target)
    lines = instructions.__wrapped__ if hasattr(instructions, '__wrapped__') else None
    with tempfile.TemporaryDirectory(prefix='kig-word2-') as d:
        o = compile_source(source, Path(d) / 'c.c')
        mine = instructions(o, function)
    diff = [(i, b[i] if i < len(b) else None, a[i] if i < len(a) else None)
            for i in range(max(len(a), len(b))) if i >= len(a) or i >= len(b)
            or (a[i] & masks[i]) != (b[i] & masks[i])]
    print(f'# {function}  target {len(b)} words / draft {len(a)}  -> {len(diff)} differing  ({tu.relative_to(ROOT)})')
    for i, t, c in diff:
        tv = f'{t:08x}' if t is not None else '--------'
        cv = f'{c:08x}' if c is not None else '--------'
        print(f'{i:4d}  target {tv}   draft {cv}   | {mine[i] if i < len(mine) else ""}')


if __name__ == '__main__':
    main()
