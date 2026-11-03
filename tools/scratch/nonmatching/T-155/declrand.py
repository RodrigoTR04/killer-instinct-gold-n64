#!/usr/bin/env python3
"""Random declaration-order search. usage: declrand.py fn draft out N [seed] [full]"""
import sys, re, random
sys.path.insert(0, '.')
import lib
fn, draft, out, N = sys.argv[1:5]; N = int(N)
seed = int(sys.argv[5]) if len(sys.argv) > 5 else 1
prefix = not (len(sys.argv) > 6 and sys.argv[6] == 'full')
src = open(draft).read()
m = re.search(r'\b' + fn + r'\([^)]*\)\s*\{\n', src)
i0 = m.end()
lines = src[i0:].split('\n')
decl = []
for ln in lines:
    if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$', ln) and not re.match(r'^\s+(return|goto|break)', ln):
        decl.append(ln)
    elif ln.strip() == '' and not decl: continue
    else: break
n = len(decl); rest = '\n'.join(lines[n:])
rnd = random.Random(seed)
def build(o): return src[:i0] + '\n'.join(decl[k] for k in o) + '\n' + rest
orders = [tuple(range(n))]
for _ in range(N - 1):
    o = list(range(n)); rnd.shuffle(o); orders.append(tuple(o))
res = lib.run(fn, [build(o) for o in orders], prefix)
ranked = sorted([(r, o) for r, o in zip(res, orders) if r], key=lambda t: (t[0][1], t[0][0]))
print('base', res[0])
for r, o in ranked[:5]: print(r, [decl[k].strip() for k in o])
open(out, 'w').write(build(ranked[0][1]))
