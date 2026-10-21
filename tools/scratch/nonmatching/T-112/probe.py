#!/usr/bin/env python3
"""Measure an rendering draft in its complete TU with the production game flags.

Run after make extract. No source files or build outputs are modified.
Usage: .venv/bin/python tools/scratch/nonmatching/T-112/probe.py [function] [draft]
"""
from pathlib import Path
import importlib.util
import json
import re
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('compare', ROOT / 'tools/scratch/flagprobe/compare.py')
compare = importlib.util.module_from_spec(spec)
spec.loader.exec_module(compare)
rows = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())


def measure(function, draft=None):
    source = next(p for p in (ROOT / 'src/main').glob('*.c')
                  if f'/{function}.s")' in p.read_text())
    if draft is None:
        draft = next((ROOT / 'tools/scratch/nonmatching').glob(f'T-*/{function}.c'))
    text = source.read_text().replace(
        f'#pragma GLOBAL_ASM("asm/nonmatchings/main/{source.stem}/{function}.s")',
        Path(draft).read_text())
    with tempfile.TemporaryDirectory(prefix='kig-t112-') as directory:
        c = Path(directory) / 'probe.c'
        obj = Path(directory) / 'probe.o'
        c.write_text(text)
        result = subprocess.run([
            str(ROOT / '.venv/bin/python'), str(ROOT / 'tools/ext/asm-processor/build.py'),
            str(ROOT / 'tools/ext/ido/5.3/cc'), '--',
            str(ROOT / 'tools/ext/binutils/bin/mips64-elf-as'),
            '-EB', '-mips3', '-32', '-G', '0', '-I', 'include', '--',
            '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul',
            '-O2', '-mips2', '-32', '-Iinclude', '-o', str(obj), str(c)
        ], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise RuntimeError(result.stderr)
        code, masks, _ = compare.elf_function(obj, function)
    row = next(r for r in rows.values() if r['function'] == function)
    offset = int(row['vram'], 16) - 0x8000F960
    original = (ROOT / 'build/segments/main.bin').read_bytes()[offset:offset + row['bytes']]
    words = struct.unpack(f'>{len(code)//4}I', code)
    target = struct.unpack(f'>{len(original)//4}I', original)
    differences = [i*4 for i in range(max(len(words), len(target)))
                   if i >= len(words) or i >= len(target)
                   or words[i] & masks[i] != target[i] & masks[i]]
    return {'function': function, 'tu': source.name, 'words': len(differences),
            'bytes': len(code), 'target_bytes': len(original), 'offsets': differences}


if __name__ == '__main__':
    names = sys.argv[1:2] or ['func_800300DC', 'func_80030220', 'func_8002DDD4',
                             'func_8002D9C4', 'func_8002FB80', 'func_8002FDA0',
                             'func_80030440', 'func_8002E150', 'func_800306B8',
                             'func_8002BBD0']
    print(json.dumps([measure(name, sys.argv[2] if len(sys.argv) > 2 else None)
                      for name in names], indent=2))
