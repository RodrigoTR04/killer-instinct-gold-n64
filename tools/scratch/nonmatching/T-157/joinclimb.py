#!/usr/bin/env python3
"""joinclimb.py fn draft.c --from 'regex' --to 'regex' [--header H] [--rounds N] [--out f]
Hill-climb which consecutive source lines (inside the line range matched by --from..--to) are joined onto one line.
Single-statement lines only are meant to be joined; lines ending in '{' or starting with '}' are never joined.
Objective: (exact LCS diff, reg-masked LCS diff)."""
import argparse, concurrent.futures as cf, importlib.util, random, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--from', dest='frm', required=True); ap.add_argument('--to', required=True)
    ap.add_argument('--header', default='#include "common.h"\n')
    ap.add_argument('--rounds', type=int, default=3); ap.add_argument('-j', type=int, default=8)
    ap.add_argument('--out', default=None); ap.add_argument('--key', default='exact', choices=['exact', 'reg', 'p'])
    a = ap.parse_args()
    lines = Path(a.draft).read_text().split('\n')
    lo = next(i for i, l in enumerate(lines) if re.search(a.frm, l))
    hi = next(i for i, l in enumerate(lines) if i > lo and re.search(a.to, l))
    # candidate join points: line i (lo < i <= hi) joins onto previous line
    cand = [i for i in range(lo + 1, hi + 1)
            if not lines[i].rstrip().endswith('{') and not lines[i].lstrip().startswith('}')
            and not lines[i - 1].rstrip().endswith('{') and not lines[i - 1].lstrip().startswith('}')
            and not lines[i - 1].lstrip().startswith('#') and not lines[i].lstrip().startswith('#')
            and lines[i].strip() and lines[i - 1].strip()]
    def build(joined):
        out = []
        for i, l in enumerate(lines):
            if i in joined and out:
                out[-1] = out[-1].rstrip() + ' ' + l.strip()
            else:
                out.append(l)
        return '\n'.join(out)
    def ev(joined):
        sc = fast.score(a.function, build(joined), a.header)
        return sc
    K = (lambda s: (s[1], s[0])) if a.key == 'exact' else ((lambda s: (s[4], s[1])) if a.key == 'p' else (lambda s: (s[0], s[1])))
    cur = frozenset(); best = ev(cur); print('start', best, len(cand), 'candidates', flush=True)
    for r in range(a.rounds):
        changed = False
        for i in cand:
            pass
        trial = [cur ^ {i} for i in cand]
        with cf.ThreadPoolExecutor(a.j) as ex:
            res = list(zip(trial, ex.map(ev, trial)))
        res = [(K(s), j, s) for j, s in res if s]
        res.sort(key=lambda t: t[0])
        for k, j, s in res:
            if k < K(best):
                best, cur, changed = s, j, True
                print('round', r, 'improved', best, sorted(cur), flush=True)
            break
        if not changed:
            break
    if a.out:
        Path(a.out).write_text(build(cur))
    print('final', best, sorted(cur))

if __name__ == '__main__':
    main()
