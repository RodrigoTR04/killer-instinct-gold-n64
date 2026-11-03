#!/usr/bin/env python3
"""Hill-climb the order of the leading declaration lines. usage: declhill.py fn draft out [full]"""
import sys, re, itertools, random
sys.path.insert(0, '.')
import lib
fn, draft, out = sys.argv[1:4]
prefix = not (len(sys.argv) > 4 and sys.argv[4] == 'full')
src = open(draft).read()
m = re.search(r'\b' + fn + r'\([^)]*\)\s*\{\n', src)
i0 = m.end()
lines = src[i0:].split('\n')
decl = []
for ln in lines:
    if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$', ln) and not re.match(r'^\s+(return|goto|break)', ln):
        decl.append(ln)
    else:
        break
n = len(decl); rest = '\n'.join(lines[n:])
print('decls', n)
def build(o): return src[:i0] + '\n'.join(decl[k] for k in o) + '\n' + rest
cur = tuple(range(n))
def sc(os_):
    return lib.run(fn, [build(o) for o in os_], prefix)
best = sc([cur])[0]; print('start', best)
seen = {cur}
while True:
    cands = []
    for i in range(n):
        for j in range(n):
            if i == j: continue
            o = list(cur); x = o.pop(i); o.insert(j, x); o = tuple(o)
            if o not in seen: cands.append(o); seen.add(o)
    res = sc(cands)
    bb = None
    for o, r in zip(cands, res):
        if r and (bb is None or (r[0], r[1]) < (bb[0][0], bb[0][1])): bb = (r, o)
    if bb and (bb[0][0], bb[0][1]) < (best[0], best[1]):
        best, cur = bb[0], bb[1]; print('improved', best, [decl[k].strip() for k in cur], flush=True)
        open(out, 'w').write(build(cur))
    else:
        break
print('final', best)
