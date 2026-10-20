#!/usr/bin/env python3
"""Compare saved boot drafts under six IDO 5.3 configurations.

Run from the repository root with .venv/bin/python. Relocation masking is only
an iteration aid; a match still requires the complete linked ROM verification.
"""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent


def main():
    spec = importlib.util.spec_from_file_location(
        'flagprobe', ROOT / 'tools/scratch/flagprobe/compare.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    inventory = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    rows = {r['function']: r for r in inventory.values() if r['area'] == 'boot'}
    rom = (ROOT / 'baserom.us.z64').read_bytes()
    results = {}
    with tempfile.TemporaryDirectory(prefix='kig-T038-') as directory:
        source, obj = Path(directory) / 'draft.c', Path(directory) / 'draft.o'
        for draft in sorted(HERE.glob('*.c'), key=lambda p: rows[p.stem]['bytes']):
            name = draft.stem
            row = rows[name]
            offset = int(row['rom'], 16)
            original = rom[offset:offset + row['bytes']]
            source.write_text('#include "common.h"\n' + draft.read_text())
            configurations = {}
            for opt, isa in [('O2', 'mips2'), ('O1', 'mips2'), ('O1', 'mips1'),
                             ('O2', 'mips1'), ('O2', 'mips3'), ('O1', 'mips3')]:
                subprocess.run([
                    str(ROOT / 'tools/ext/ido/5.3/cc'), '-c', '-G', '0',
                    '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul',
                    '-' + opt, '-' + isa, '-32', '-I' + str(ROOT / 'include'),
                    str(source), '-o', str(obj)], check=True, cwd=ROOT,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                code, masks, _ = compare.elf_function(obj, name)
                words = struct.unpack('>' + str(len(code) // 4) + 'I', code)
                target = struct.unpack('>' + str(len(original) // 4) + 'I', original)
                different = sum((a & masks[i]) != (b & masks[i])
                                for i, (a, b) in enumerate(zip(words, target)))
                configurations[opt + ' ' + isa] = dict(
                    size=len(code), target=len(original), differing_words=different,
                    match=len(code) == len(original) and different == 0)
            results[name] = configurations
    print(json.dumps(results, indent=2))


if __name__ == '__main__':
    main()
