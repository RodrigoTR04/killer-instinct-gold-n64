#!/usr/bin/env python3
"""Hill-climb per-site statement order/joins for adjacent line pairs matching PAIR regex.
usage: sitehill.py fn draft out [full] ; env PAIR (regex for a line, default cmd->w[01] assignments)"""
import sys, re, os
sys.path.insert(0, '.')
import lib
fn, draft, out = sys.argv[1:4]
prefix = not (len(sys.argv) > 4 and sys.argv[4] == 'full')
LINE = re.compile(os.environ.get('PAIR', r'^\s*\w+->w[01] = [^;]*;$'))
lines = open(draft).read().split('\n')
pairs = []
i = 0
while i < len(lines) - 1:
    if LINE.match(lines[i]) and LINE.match(lines[i+1]) and lines[i].split('->')[1][1] != lines[i+1].split('->')[1][1]:
        pairs.append(i); i += 2
    else: i += 1
print('pairs', len(pairs))
# state per pair: (swap, join)
def build(state):
    out_ = []; i = 0; k = 0
    pi = {p: idx for idx, p in enumerate(pairs)}
    while i < len(lines):
        if i in pi:
            sw, jn = state[pi[i]]
            a, b = lines[i], lines[i+1]
            if sw: a, b = b, a
            if jn: out_.append(a + ' ' + b.strip())
            else: out_ += [a, b]
            i += 2
        else:
            out_.append(lines[i]); i += 1
    return '\n'.join(out_)
cur = tuple((0, 0) for _ in pairs)
def sc(states): return lib.run(fn, [build(s) for s in states], prefix)
best = sc([cur])[0]; print('start', best)
seen = {cur}
while True:
    cands = []
    for k in range(len(pairs)):
        for opt in [(0,0),(1,0),(0,1),(1,1)]:
            if opt == cur[k]: continue
            s = list(cur); s[k] = opt; s = tuple(s)
            if s not in seen: cands.append(s); seen.add(s)
    res = sc(cands)
    bb = None
    for s, r in zip(cands, res):
        if r and (bb is None or (r[0], r[1]) < (bb[0][0], bb[0][1])): bb = (r, s)
    if bb and (bb[0][0], bb[0][1]) < (best[0], best[1]):
        best, cur = bb[0], bb[1]; print('improved', best, flush=True)
        open(out, 'w').write(build(cur))
    else: break
print('final', best, cur)
