#!/usr/bin/env python3
"""Line-layout search that starts from a draft's own layout.
usage: layout.py fn draft out [seconds] [full]
Splits the function body into atoms (statements/braces) and searches over, for each atom boundary,
'same line' vs 'new line' (plateau moves allowed). Score = lib exact word diff (lower is better)."""
import sys, re, random, time
sys.path.insert(0, 'tools/scratch/nonmatching/T-155')
import lib
fn, draft, out = sys.argv[1:4]
secs = int(sys.argv[4]) if len(sys.argv) > 4 else 600
prefix = not (len(sys.argv) > 5 and sys.argv[5] == 'full')
src = open(draft).read()
m = re.search(r'\b' + fn + r'\([^)]*\)\s*\{', src)
head, body = src[:m.end()], src[m.end():]
body = body.rstrip()
assert body.endswith('}')
body = body[:-1]
# atoms with the line number they started on
atoms, lines, cur, depth, ln = [], [], '', 0, 0
start_ln = 0
for ch in body:
    if not cur.strip() and ch == '\n':
        ln += 1
        continue
    if not cur.strip():
        start_ln = ln
    cur += ch
    if ch == '\n':
        ln += 1
    if ch == '(':
        depth += 1
    elif ch == ')':
        depth -= 1
    elif depth == 0 and ch in ';{}':
        atoms.append(re.sub(r'\s+', ' ', cur.strip()))
        lines.append(start_ln)
        cur = ''
if cur.strip():
    atoms.append(re.sub(r'\s+', ' ', cur.strip())); lines.append(start_ln)
# declarations stay one per line (first atoms until a non-declaration)
nd = 0
for a in atoms:
    if re.match(r'^(?:[A-Za-z_]\w*\s+)+[\*\w\[\], =&\.]+;$', a) and '(' not in a.split('=')[0]:
        nd += 1
    else:
        break
init = [lines[i] == lines[i - 1] for i in range(1, len(atoms))]
def build(joins):
    parts, ind = [], 1
    for i, a in enumerate(atoms):
        if a.startswith('}'):
            ind = max(1, ind - 1)
        if i > 0 and joins[i - 1] and i > nd:
            parts[-1] += ' ' + a
        else:
            parts.append('    ' * ind + a)
        if a.endswith('{'):
            ind += 1
    return head + '\n' + '\n'.join(parts) + '\n}\n'
n = len(atoms) - 1
def sc(cs):
    return lib.run(fn, [build(c) for c in cs], prefix)
cur = list(init)
best = sc([cur])[0]
print('start', best, 'atoms', len(atoms), flush=True)
open(out, 'w').write(build(cur))
rr = random.Random(7)
t0 = time.time()
seen = {tuple(cur)}
while time.time() - t0 < secs:
    cands = []
    for _ in range(100):
        c = list(cur)
        for k in rr.sample(range(nd, n), rr.choice([1, 1, 2, 3])):
            c[k] = not c[k]
        if tuple(c) not in seen:
            seen.add(tuple(c)); cands.append(c)
    res = sc(cands)
    for c, r in zip(cands, res):
        if r and (r[1] <= best[1]):
            if r[1] < best[1]:
                print('best', r, flush=True)
                open(out, 'w').write(build(c))
            best, cur = r, c
            break
print('final', best)
