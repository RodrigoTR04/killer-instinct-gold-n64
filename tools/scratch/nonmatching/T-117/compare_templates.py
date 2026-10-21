#!/usr/bin/env python3
"""Instruction-by-instruction original-image diffs; run after make extract."""
from pathlib import Path
import difflib
import json
import struct
import rabbitizer
ROOT = Path(__file__).resolve().parents[4]
rows = {r['function']: r for r in json.loads((ROOT / 'tools/progress/original-functions.json').read_text()).values()}
def instructions(name):
    row = rows[name]
    base = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}[row['area']]
    offset = int(name[5:], 16) - base
    data = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[offset:offset + row['bytes']]
    return [rabbitizer.Instruction(w).disassemble() + '\n' for w in struct.unpack('>' + 'I' * (len(data) // 4), data)]
if __name__ == '__main__':
    pairs = [('func_801BA674', 'func_801BB258'), ('func_801B2EF4', 'func_801B3B84'), ('func_8001AD04', 'func_8001B134')]
    result = []
    for left, right in pairs:
        result.extend(difflib.unified_diff(instructions(left), instructions(right), fromfile=left, tofile=right, n=4))
    (Path(__file__).parent / 'template-diffs.txt').write_text(''.join(result))
