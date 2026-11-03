#!/usr/bin/env python3
"""Generic honest-mutation hill climb: decl order, line joins, local types.
usage: autosearch.py fn draft out secs [full]"""
import sys, re, random, time, copy
sys.path.insert(0, '.')
import lib
fn, draft, out, secs = sys.argv[1:5]; secs = int(secs)
prefix = not (len(sys.argv) > 5 and sys.argv[5] == 'full')
src = open(draft).read()
m = re.search(r'\b' + fn + r'\s*\([^)]*\)\s*\{\n', src)
head, body = src[:m.end()], src[m.end():]
lines = body.rstrip('\n').split('\n')
assert lines[-1].strip() == '}', repr(lines[-1])
lines = lines[:-1]
DECL = re.compile(r'^(\s+)((?:unsigned |signed )?(?:[A-Za-z_]\w*))(\s+\**)(\w+)(\[\w*\])?( = [^;(]+)?;$')
nd = 0
for ln in lines:
    if DECL.match(ln): nd += 1
    elif ln.strip() == '': nd += 1
    else: break
decls = [l for l in lines[:nd] if l.strip()]
rest = lines[nd:]
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
TYPES = {'s32': ['s32', 'u32'], 'u32': ['s32', 'u32'], 'u8': ['u8', 's8', 'u32'], 's8': ['u8', 's8'], 's16': ['s16', 'u16', 's32'], 'u16': ['s16', 'u16', 'u32'], 'int': ['s32', 'u32']}
def build(st):
    order, joins, types = st
    dl = []
    for k in order:
        l = decls[k]
        mt = DECL.match(l)
        ty = types.get(k)
        if mt and ty: l = f"{mt.group(1)}{ty}{mt.group(3)}{mt.group(4)}{mt.group(5) or ''}{mt.group(6) or ''};"
        dl.append(l)
    parts = []; ind = 1
    for i, a in enumerate(atoms):
        if a.startswith('}'): ind = max(0, ind - 1)
        if i > 0 and joins[i-1]: parts[-1] += ' ' + a
        else: parts.append('    ' * ind + a)
        if a.endswith('{'): ind += 1
    return head + '\n'.join(dl + parts) + '\n}\n'
n = len(atoms) - 1
cur = (list(range(len(decls))), [False] * n, {})
# try to use original formatting as start: all-false joins is normalized; score both and keep better start
def sc(states): return lib.run(fn, [build(s) for s in states], prefix)
best = sc([cur])[0]; print('start', best, flush=True)
rr = random.Random(11)
def mutate(st):
    order, joins, types = copy.deepcopy(st)
    for _ in range(rr.choice([1, 1, 2, 3])):
        k = rr.random()
        if k < 0.35 and n:
            i = rr.randrange(n); joins[i] = not joins[i]
        elif k < 0.7 and len(order) > 1:
            i = rr.randrange(len(order)); j = rr.randrange(len(order)); x = order.pop(i); order.insert(j, x)
        else:
            cands = [i for i, l in enumerate(decls) if DECL.match(l) and DECL.match(l).group(2) in TYPES]
            if cands:
                i = rr.choice(cands); ty0 = DECL.match(decls[i]).group(2)
                types[i] = rr.choice(TYPES[ty0])
    return (order, joins, types)
t0 = time.time()
while time.time() - t0 < secs:
    cands = [mutate(cur) for _ in range(42)]
    res = sc(cands)
    bi = None
    for c, r in zip(cands, res):
        if r and (bi is None or (r[1], r[0]) < (bi[0][1], bi[0][0])): bi = (r, c)
    if bi and (bi[0][1], bi[0][0]) <= (best[1], best[0]):
        if (bi[0][1], bi[0][0]) < (best[1], best[0]):
            print('best', bi[0], round(time.time() - t0), flush=True)
            open(out, 'w').write(build(bi[1]))
        best, cur = bi
    if best[1] == 0: break
print('final', best)
