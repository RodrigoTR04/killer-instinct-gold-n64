#!/usr/bin/env python3
"""dstack.py fn draft.c [--iters N] [-j J] [--seed S] [--out f] [--header H]
Declaration-order search whose objective is the stack-slot mismatch: sum over sp-relative offsets of
|target refs - draft refs| (per distinct slot), tie-broken by the exact LCS.  Moves: swap / move one declaration."""
import argparse, concurrent.futures as cf, importlib.util, random, re, sys
from collections import Counter
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
SP = re.compile(r'(\d+)\(sp\)$')
DECL = re.compile(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$')

def slots(lines):
    c = Counter()
    for l in lines:
        m = SP.search(l)
        if m and int(m.group(1)) >= 0x10: c[int(m.group(1))] += 1
    return c

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--iters', type=int, default=60); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    ap.add_argument('--header', default='#include "common.h"\n')
    a = ap.parse_args()
    src = Path(a.draft).read_text()
    m = re.search(r'\b' + a.function + r'\([^)]*\)\s*\{\n', src)
    i0 = m.end(); lines = src[i0:].split('\n')
    decl = []
    for ln in lines:
        if DECL.match(ln): decl.append(ln)
        else: break
    n = len(decl); rest = '\n'.join(lines[n:])
    tgt = slots(fast.target(a.function))
    def build(o): return src[:i0] + '\n'.join(decl[k] for k in o) + '\n' + rest
    def ev(o):
        raw = fast.compile_raw(a.function, build(o), a.header)
        if raw is None: return None
        d = slots(raw)
        mism = sum(abs(tgt[k] - d[k]) for k in set(tgt) | set(d))
        return (mism, fast.lcsdiff(fast.target(a.function), raw))
    rnd = random.Random(a.seed); cur = tuple(range(n)); best = ev(cur); print('start', best, flush=True)
    for it in range(a.iters):
        cands = []
        for _ in range(a.j):
            o = list(cur)
            if rnd.random() < 0.5:
                i, j = rnd.sample(range(n), 2); o[i], o[j] = o[j], o[i]
            else:
                i = rnd.randrange(n); j = rnd.randrange(n); v = o.pop(i); o.insert(j, v)
            cands.append(tuple(o))
        with cf.ThreadPoolExecutor(a.j) as ex:
            res = [(s, o) for o, s in zip(cands, ex.map(ev, cands)) if s]
        if not res: continue
        res.sort(key=lambda r: r[0])
        s, o = res[0]
        if s <= best:
            if s < best: print(it, 'improved', s, flush=True)
            best, cur = s, o
            if a.out: Path(a.out).write_text(build(cur))
    print('final', best)

if __name__ == '__main__':
    main()
