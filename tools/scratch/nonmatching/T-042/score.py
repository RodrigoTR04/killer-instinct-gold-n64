#!/usr/bin/env python3
"""Compare a boot C function against US V1.0 using IDO 5.3 -O2 -mips2.

Relocation-masked diagnostics are an iteration aid. A full linked ROM rebuild
is required for matching status. Pass the complete owning TU when unreachable
code alignment depends on preceding functions (notably func_80001F2C).
"""
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[4]


def score(source, name, disassemble=False):
    spec = importlib.util.spec_from_file_location(
        'compare', ROOT / 'tools/scratch/flagprobe/compare.py')
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    rows = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(row for row in rows.values()
               if row['area'] == 'boot' and row['function'] == name)
    offset = int(row['rom'], 16)
    original = (ROOT / 'baserom.us.z64').read_bytes()[offset:offset + row['bytes']]
    with tempfile.TemporaryDirectory(prefix='kig-T042-') as directory:
        cfile, obj = Path(directory) / 'probe.c', Path(directory) / 'probe.o'
        cfile.write_text('#include "common.h"\n' + source)
        subprocess.run([
            str(ROOT / 'tools/ext/ido/5.3/cc'), '-c', '-G', '0', '-non_shared',
            '-Xcpluscomm', '-Wab,-r4300_mul', '-O2', '-mips2', '-32',
            '-I' + str(ROOT / 'include'), str(cfile), '-o', str(obj)],
            cwd=ROOT, check=True, capture_output=True)
        code, masks, _ = compare.elf_function(obj, name)
        words = struct.unpack('>' + str(len(code) // 4) + 'I', code)
        target = struct.unpack('>' + str(len(original) // 4) + 'I', original)
        different = [i for i, (a, b) in enumerate(zip(words, target))
                     if (a & masks[i]) != (b & masks[i])]
        if disassemble:
            subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'),
                            '-dr', str(obj)], check=True)
        return dict(function=name, differing_words=len(different), size=len(code),
                    target=len(original), offsets=[hex(i * 4) for i in different],
                    match=len(code) == len(original) and not different)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('--function', help='defaults to source filename stem')
    parser.add_argument('--disassemble', action='store_true')
    args = parser.parse_args()
    print(json.dumps(score(args.source.read_text(), args.function or args.source.stem,
                           args.disassemble), indent=2))
