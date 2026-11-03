#!/usr/bin/env python3
"""gen6.py fn draft.c [--n N] [--seed S] [--out f] [--limit L] : random dependency-respecting orders of the pre-switch statement group
(from 'div = ' line to the 'switch' line) + hoistable sCo/mnX lines moved into the group. Score = reg-masked LCS on first L instrs."""
import argparse, concurrent.futures as cf, difflib, importlib.util, random, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
IDENT = re.compile(r'[A-Za-z_]\w*')
def lhs(l):
    m = re.match(r'^\s*(?:if \(.*\) \{ )?(\w+) = ', l)
    s = l.strip()
    names = set(re.findall(r'(?:^|;\s*|\{\s*)(\w+) = ', s))
    return names
def ids(l): return set(IDENT.findall(l))
def dep(a, b):  # a before b originally; must keep order?
    la, lb = lhs(a), lhs(b)
    return bool(la & ids(b)) or bool(lb & ids(a)) or bool(la & lb)
def main():
    ap = argparse.ArgumentParser(); ap.add_argument('fn'); ap.add_argument('draft')
    ap.add_argument('--n', type=int, default=120); ap.add_argument('--seed', type=int, default=1); ap.add_argument('--out')
    ap.add_argument('--limit', type=int, default=240); ap.add_argument('-j', type=int, default=8)
    ap.add_argument('--move', default='sCo,mnX')
    a = ap.parse_args()
    lines = Path(a.draft).read_text().split('\n')
    s = next(i for i, l in enumerate(lines) if l.strip().startswith('div = 0x100000'))
    e = next(i for i, l in enumerate(lines) if l.strip().startswith('switch (fmt)'))
    grp = lines[s:e]
    extra = []
    rest = []
    for i, l in enumerate(lines):
        if i >= e and any(re.match(r'\s*%s = ' % m, l) for m in a.move.split(',') if m):
            extra.append(l)
        else:
            rest.append(l)
    # rebuild with the extras appended to the group
    base = lines[:s] + grp + extra
    # recompute rest after group
    after = [l for i, l in enumerate(lines) if i >= e and l not in extra]
    items = grp + extra
    rnd = random.Random(a.seed)
    def build(order): return '\n'.join(lines[:s] + order + after)
    def valid_swap(o, i):  # swap adjacent i,i+1
        return not dep(o[i], o[i + 1])
    tgt = fast.target(a.fn)[:a.limit]
    tgtm = [fast.M(x) for x in tgt]
    def ev(order):
        raw = fast.compile_raw(a.fn, build(order))
        if raw is None: return None
        d = [fast.M(x) for x in raw][:a.limit + 20]
        sm = difflib.SequenceMatcher(None, tgtm, d, autojunk=False)
        pre = sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
        sc = fast.score(a.fn, build(order))
        return (pre, sc)
    orders = [list(items)]
    seen = {tuple(items)}
    while len(orders) < a.n:
        o = list(orders[rnd.randrange(len(orders))])
        for _ in range(rnd.randint(1, 4)):
            i = rnd.randrange(len(o) - 1)
            if valid_swap(o, i): o[i], o[i + 1] = o[i + 1], o[i]
        if tuple(o) in seen: continue
        seen.add(tuple(o)); orders.append(o)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(zip(orders, ex.map(ev, orders)))
    res = [(r, o) for o, r in res if r]
    res.sort(key=lambda t: t[0][0])
    print('base', res and [r for r, o in res if o == orders[0]])
    for r, o in res[:6]:
        print(r)
    if a.out and res:
        Path(a.out).write_text(build(res[0][1]))
if __name__ == '__main__':
    main()
