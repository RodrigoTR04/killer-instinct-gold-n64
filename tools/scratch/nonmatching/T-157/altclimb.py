#!/usr/bin/env python3
"""altclimb.py fn draft.c alts.txt [--header H] [-j J] [--out f]
alts.txt: blocks separated by blank lines; each block is a set of mutually exclusive alternative texts, one per line
(first line = text currently present in the draft; others are replacements; use \\n not needed - single-line substrings).
Greedy coordinate climb (steepest) over all blocks, objective (exact LCS, reg-masked)."""
import argparse, concurrent.futures as cf, importlib.util
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
ap = argparse.ArgumentParser(); ap.add_argument('function'); ap.add_argument('draft'); ap.add_argument('alts')
ap.add_argument('--header', default='#include "common.h"\n'); ap.add_argument('-j', type=int, default=8)
ap.add_argument('--out', default=None); ap.add_argument('--key', default='exact', choices=['exact', 'reg'])
a = ap.parse_args()
text = Path(a.draft).read_text()
blocks = [[l for l in b.split('\n') if l.strip()] for b in Path(a.alts).read_text().split('\n\n') if b.strip()]
cur = [0] * len(blocks)
for bi, b in enumerate(blocks):
    if b[0] not in text: print('WARNING: base alt not found:', b[0])
def build(sel):
    t = text
    for bi, b in enumerate(blocks):
        if sel[bi] != 0 and b[0] in t:
            t = t.replace(b[0], b[sel[bi]], 1)
    return t
K = (lambda s: (s[1], s[0])) if a.key == 'exact' else (lambda s: (s[0], s[1]))
ev = lambda sel: fast.score(a.function, build(sel), a.header)
best = ev(cur); print('start', best, flush=True)
for rnd in range(6):
    trials = [(bi, k) for bi, b in enumerate(blocks) for k in range(len(b)) if k != cur[bi]]
    sels = []
    for bi, k in trials:
        s = list(cur); s[bi] = k; sels.append(s)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(zip(trials, sels, ex.map(ev, sels)))
    res = [(K(sc), t, s, sc) for t, s, sc in res if sc]
    res.sort(key=lambda r: r[0])
    if res and res[0][0] < K(best):
        k, t, s, sc = res[0]
        cur, best = s, sc
        print('round', rnd, 'take', blocks[t[0]][t[1]], '->', best, flush=True)
    else:
        break
print('final', best, cur)
if a.out: Path(a.out).write_text(build(cur))
