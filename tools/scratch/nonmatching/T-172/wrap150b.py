"""Wrap each statement of func_8002E150 in do{...}while(0) at the 99-word draft."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

SRC = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
lines = SRC.split('\n')

variants = {'base': SRC}
for i, line in enumerate(lines):
    s = line.strip()
    if not s.endswith(';') or s.startswith(('extern', '#', 'return', 'double func')):
        continue
    indent = line[:len(line) - len(line.lstrip())]
    variants[f'{i}:{s[:26]}'] = '\n'.join(
        lines[:i] + [f'{indent}do {{ {s} }} while (0);'] + lines[i + 1:])

out = detail.run('func_8002E150', variants, jobs=12)
