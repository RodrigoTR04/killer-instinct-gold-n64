#!/usr/bin/env python3
"""sweep.py fn draft.c --from REGEX --to REGEX [--out f] [--rounds N] [--key p|reg|exact] : coordinate descent over statement positions
within the line range [from, to) (each simple statement line may move to any position in range if dependency-safe)."""
import argparse, concurrent.futures as cf, importlib.util, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
IDENT = re.compile(r'[A-Za-z_]\w*')
def lhs(l):
    s = l.strip()
    return set(re.findall(r'(?:^|;\s*|\{\s*)(\w+) = ', s)) | set(re.findall(r'(?:^|;\s*|\{\s*)(\w+) \+?= ', s))
def ids(l): return set(IDENT.findall(l))
def dep(a, b): return bool(lhs(a) & ids(b)) or bool(lhs(b) & ids(a)) or bool(lhs(a) & lhs(b))
def main():
    ap = argparse.ArgumentParser(); ap.add_argument('fn'); ap.add_argument('draft')
    ap.add_argument('--from', dest='frm', required=True); ap.add_argument('--to', required=True)
    ap.add_argument('--out'); ap.add_argument('--rounds', type=int, default=2); ap.add_argument('-j', type=int, default=8)
    ap.add_argument('--key', default='p')
    a = ap.parse_args()
    lines = Path(a.draft).read_text().split('\n')
    s = next(i for i, l in enumerate(lines) if re.search(a.frm, l))
    e = next(i for i, l in enumerate(lines) if i > s and re.search(a.to, l))
    K = {'p': lambda x: (x[4], x[1]), 'reg': lambda x: (x[0], x[1]), 'exact': lambda x: (x[1], x[0])}[a.key]
    def mk(grp): return '\n'.join(lines[:s] + grp + lines[e:])
    grp = list(lines[s:e])
    simple = lambda l: l.strip().endswith(';') and l.count('{') == l.count('}') and not l.strip().startswith('#')
    cur = fast.score(a.fn, mk(grp)); print('start', cur, flush=True)
    for r in range(a.rounds):
        improved = False
        for idx in range(len(grp)):
            l = grp[idx]
            if not simple(l): continue
            cands = []
            for p in range(len(grp)):
                if p == idx: continue
                g = list(grp); g.pop(idx); g.insert(p, l)
                # dependency check: statements crossed must be independent of l
                lo, hi = (idx, p) if p > idx else (p, idx)
                crossed = [grp[k] for k in range(lo, hi + 1) if k != idx]
                if any(dep(l, c) for c in crossed): continue
                cands.append(g)
            if not cands: continue
            with cf.ThreadPoolExecutor(a.j) as ex:
                res = [(K(sc), g, sc) for g, sc in zip(cands, ex.map(lambda g: fast.score(a.fn, mk(g)), cands)) if sc and sc[2] >= 400]
            if not res: continue
            res.sort(key=lambda t: t[0])
            if res[0][0] < K(cur):
                cur = res[0][2]; grp = res[0][1]; improved = True
                print(f'round {r} moved "{l.strip()[:40]}" -> {cur}', flush=True)
                if a.out: Path(a.out).write_text(mk(grp))
        if not improved: break
    print('final', cur)
    if a.out: Path(a.out).write_text(mk(grp))
main()
