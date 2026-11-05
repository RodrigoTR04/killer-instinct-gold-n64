"""Pairwise do{}while(0) wraps at block boundaries in func_8002E150."""
import itertools
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

SRC = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
lines = SRC.split('\n')

cands = []
for i, line in enumerate(lines):
    s = line.strip()
    if not s.endswith(';') or s.startswith(('extern', '#', 'return', 'double func')):
        continue
    if 'while (0)' in s:
        continue
    cands.append(i)

v = {'base': SRC}
for i, j in itertools.combinations(cands, 2):
    out = list(lines)
    for k in (i, j):
        s = out[k].strip()
        ind = out[k][:len(out[k]) - len(out[k].lstrip())]
        out[k] = f'{ind}do {{ {s} }} while (0);'
    v[f'{i}+{j}'] = '\n'.join(out)
print(len(v), 'variants', flush=True)
detail.run('func_8002E150', v, jobs=16)
