#!/usr/bin/env python3
"""func_800297A4: broad search of do/while block placements on the 148 base.

Every assignment in the body becomes a candidate: wrap it in a single-iteration
loop. Search all combos of up to 3 candidates.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297ae')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_800297A4.c').read_text()

# every single statement line in the body that ends with ';'
import re
lines = BASE.splitlines(keepends=True)
cands = []
for i, l in enumerate(lines):
    s = l.strip()
    if s.endswith(';') and not s.startswith(('return', 'typedef', 'extern', '#')) and 'p->' in s or \
       (s.endswith(';') and s.startswith(('p->velocity', 'p->position', 'p->age', 'p->duration'))):
        cands.append(i)

def wrapped(line):
    s = line.strip()
    indent = line[:len(line) - len(line.lstrip())]
    return f'{indent}do {{ {s} }} while (0);\n'

n = 0
for r in (1, 2, 3):
    for combo in itertools.combinations(cands, r):
        out = list(lines)
        for i in combo:
            out[i] = wrapped(lines[i])
        (OUT / ('b' + '_'.join(str(i) for i in combo) + '.c')).write_text(''.join(out))
        n += 1
print(n, 'cands', len(cands))
