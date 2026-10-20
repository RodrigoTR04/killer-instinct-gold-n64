#!/usr/bin/env python3
"""Compile an overlay draft at the normal flags and count ELF-relocation-masked words.

Usage: .venv/bin/python tools/scratch/nonmatching/T-044/compare.py draft.c
This is a screening aid; only the full linked build proves matching.
"""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('flagprobe', ROOT / 'tools/scratch/flagprobe/compare.py')
compare = importlib.util.module_from_spec(spec)
spec.loader.exec_module(compare)
rows = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
rows = {r['function']: r for r in rows.values() if r['area'] == 'ovl_7DF8'}
image = (ROOT / 'build/segments/ovl_7DF8.bin').read_bytes()
for argument in sys.argv[1:]:
    draft = Path(argument)
    name = draft.stem
    with tempfile.TemporaryDirectory(prefix='kig-T044-') as directory:
        source, obj = Path(directory) / 'draft.c', Path(directory) / 'draft.o'
        source.write_text('#include "common.h"\n' + draft.read_text())
        subprocess.run([str(ROOT / 'tools/ext/ido/5.3/cc'), '-c', '-G', '0',
                        '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul', '-O2',
                        '-mips2', '-32', '-I' + str(ROOT / 'include'), str(source),
                        '-o', str(obj)], check=True, cwd=ROOT)
        code, masks, _ = compare.elf_function(obj, name)
    offset = int(name[5:], 16) - 0x801ABB20
    target = image[offset:offset + rows[name]['bytes']]
    words = struct.unpack('>' + str(len(code) // 4) + 'I', code)
    baseline = struct.unpack('>' + str(len(target) // 4) + 'I', target)
    different = sum((a & masks[i]) != (b & masks[i])
                    for i, (a, b) in enumerate(zip(words, baseline)))
    print(f'{name}: {different} differing words; {len(code)}/{len(target)} bytes')
