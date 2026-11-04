#!/usr/bin/env python3
"""Hill-climb statement-atom line joins with lib scoring (prefix compile by default).
usage: joinhill.py fn draft out [full]"""
import sys, re, random
sys.path.insert(0, 'tools/scratch/nonmatching/T-155')
import lib
fn, draft, out = sys.argv[1:4]
prefix = False if (len(sys.argv) > 4 and sys.argv[4] == 'full') else True
src = open(draft).read()
m = re.search(r'\b' + fn + r'\([^)]*\)\s*\{\n', src)
head, body = src[:m.end()], src[m.end():]
lines = body.rstrip('\n').split('\n')
assert lines[-1].strip() == '}', lines[-1]
lines = lines[:-1]
# keep leading declaration lines intact
nd = 0
for ln in lines:
    if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$', ln): nd += 1
    elif ln.strip() == '': nd += 1
    else: break
decls, rest = lines[:nd], lines[nd:]
def atoms_of(text):
    atoms, cur, depth = [], '', 0
    for ch in text:
        cur += ch
        if ch == '(': depth += 1
        elif ch == ')': depth -= 1
        elif depth == 0 and ch in ';{}':
            atoms.append(cur.strip()); cur = ''
    if cur.strip(): atoms.append(cur.strip())
    return [a for a in atoms if a]
atoms = atoms_of(' '.join(l.strip() for l in rest))
def build(joins):
    parts = []
    ind = 0
    for i, a in enumerate(atoms):
        if a.startswith('}'): ind = max(0, ind - 1)
        if i > 0 and joins[i-1]:
            parts[-1] += ' ' + a
        else:
            parts.append('    ' * (ind + 1) + a)
        ind += a.count('{') - (a.count('}') if not a.startswith('}') else a.count('}') - 1 + 0) if False else 0
        if a.endswith('{'): ind += 1
    return head + '\n'.join(decls + parts) + '\n}\n'
n = len(atoms) - 1
def sc(cs): return lib.run(fn, [build(c) for c in cs], prefix)
cur = [False] * n
best = sc([cur])[0]; print('start', best, 'atoms', len(atoms), flush=True)
rr = random.Random(5)
while True:
    cands = []
    for i in range(n):
        c = list(cur); c[i] = not c[i]; cands.append(c)
    for _ in range(120):
        c = list(cur)
        for k in rr.sample(range(n), 2 if rr.random() < 0.6 else 3): c[k] = not c[k]
        cands.append(c)
    res = sc(cands)
    bi = None
    for c, r in zip(cands, res):
        if r and (bi is None or (r[0], r[1]) < (bi[0][0], bi[0][1])): bi = (r, c)
    if bi and (bi[0][0], bi[0][1]) < (best[0], best[1]):
        best, cur = bi; print('best', best, 'joins', sum(cur), flush=True)
        open(out, 'w').write(build(cur))
    else: break
print('final', best)
