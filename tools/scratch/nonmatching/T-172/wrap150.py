"""Wrap each statement in func_8002E150 in do{...}while(0), one at a time."""
import re
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

SRC = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
lines = SRC.split('\n')

variants = {'base': SRC}
for i, line in enumerate(lines):
    stripped = line.strip()
    if not stripped.endswith(';') or stripped.startswith(('extern', '#', 'return', 'double func')):
        continue
    if i + 1 < len(lines) and lines[i + 1].strip().startswith(('else', 'while')):
        continue
    indent = line[:len(line) - len(line.lstrip())]
    wrapped = f'{indent}do {{ {stripped} }} while (0);'
    new = lines[:i] + [wrapped] + lines[i + 1:]
    variants[f'w{i}:{stripped[:28]}'] = '\n'.join(new)

out = detail.run('func_8002E150', variants, jobs=12)
