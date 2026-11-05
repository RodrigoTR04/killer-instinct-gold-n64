"""Broad standalone search over func_8002E150 shapes, ranked by full-stream diff.

Variants cover: extra/unused live temporaries declared in several positions (which
is how IDO decided to give this function its 0x60 frame while the target still
spills only one extra float), the `x = -x` parameter-reassignment shape, and
hoisting the exponent/hi into an argument rewrite.
"""
import itertools
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743')
sys.path.insert(0, str(ROOT / 'tools/scratch/nonmatching/T-172'))
import fast150  # noqa: E402
import ido  # noqa: E402

HEAD = fast150.scan150.HEAD
BODY = fast150.scan150.BODY


def make(order, body=None, extra_preamble=''):
    b = (body or BODY).replace('DECLS', ', '.join(order))
    return HEAD + extra_preamble + 'double func_8002E150(double x) {\n' + b


BASE_ORDER = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']

variants = {}
for order in itertools.permutations(BASE_ORDER):
    variants['/'.join(order)] = make(order)

print(len(variants), 'variants', flush=True)


def run(item):
    name, src = item
    try:
        s = fast150.score(src)
    except Exception:
        s = None
    return name, s


results = []
with ThreadPoolExecutor(max_workers=20) as pool:
    for name, s in pool.map(run, variants.items()):
        if s is not None:
            results.append((s, name))
results.sort()
for s, name in results[:15]:
    print(f'{s:.2f}\t{name}')
print('done', len(results))
