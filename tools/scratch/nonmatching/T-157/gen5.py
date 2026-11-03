#!/usr/bin/env python3
"""gen5.py : sample statement orders of the explicit preheader items for func_801BCB70.
Items are explicit statements before the run loop; random topological orders under data dependencies.
usage: gen5.py [--n N] [--seed S] [-j J] [--out f]"""
import argparse, concurrent.futures as cf, importlib.util, random, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
BASE = (ROOT / 'tools/scratch/nonmatching/T-157/w/hx_1111.c').read_text()
I = ' ' * 24
lines = BASE.split('\n')
# locate the contiguous explicit block: from 'div = ' to the line before 'while ((mask'
a = next(i for i, l in enumerate(lines) if l.strip().startswith('div = 0x100000'))
b = next(i for i, l in enumerate(lines) if l.strip().startswith('while ((mask'))
block = [l for l in lines[a:b]]
names = []
for l in block:
    m = re.match(r'\s*(\w+) = ', l)
    names.append(m.group(1) if m else None)
print(names)
deps = {
    'div': [], 'x0f': [], 'x1f': ['x0f'], 'xl': ['x0f'], 'hx': ['xl', 'div'], 'spB': ['div'], 't6c': [], 'w0': [],
    'pos': [], 'end': [], 'lrs': [], 'uls': [], 'lrt': [],
}
def valid(order):
    pos = {n: i for i, n in enumerate(order)}
    return all(pos[d] < pos[n] for n in order for d in deps.get(n, []) if d in pos)
def build(order):
    d = dict(zip(names, block))
    return '\n'.join(lines[:a] + [d[n] for n in order] + lines[b:])
def main():
    ap = argparse.ArgumentParser(); ap.add_argument('--n', type=int, default=120); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None); ap.add_argument('--prefix', default='')
    ar = ap.parse_args()
    rnd = random.Random(ar.seed)
    orders = [list(names)]
    seen = {tuple(names)}
    pre = [x for x in ar.prefix.split(',') if x]
    while len(orders) < ar.n:
        rest = [n for n in names if n not in pre]; rnd.shuffle(rest)
        o = pre + rest
        if not valid(o) or tuple(o) in seen: continue
        seen.add(tuple(o)); orders.append(o)
    ev = lambda o: fast.score('func_801BCB70', build(o))
    with cf.ThreadPoolExecutor(ar.j) as ex:
        res = list(zip(orders, ex.map(ev, orders)))
    res = [(s, o) for o, s in res if s and s[2] >= 400]
    res.sort(key=lambda r: (r[0][4], r[0][1]))
    for s, o in res[:6]:
        print(s, ' '.join(o))
    if ar.out and res:
        Path(ar.out).write_text(build(res[0][1]))
main()
