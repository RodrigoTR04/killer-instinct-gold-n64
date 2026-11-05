#!/usr/bin/env python3
"""wrapclimb.py FN DRAFT OUT [iters] — hill-climb the SET of statements wrapped in
`do { } while (0);` against the official word count. Adds/removes one wrap at a time.
"""
import importlib.util, re, sys, random
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
fn, draft, out = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
iters = int(sys.argv[4]) if len(sys.argv) > 4 else 300
random.seed(int(sys.argv[5]) if len(sys.argv) > 5 else 3)

src = draft.read_text()
m = re.search(r'\b' + re.escape(fn) + r'\([^)]*\)\s*\{\n', src)
head_end = m.end()
rest = src[head_end:]
depth, end = 1, None
for i, ch in enumerate(rest):
    if ch == '{': depth += 1
    elif ch == '}':
        depth -= 1
        if depth == 0: end = i; break
body, tail = rest[:end], rest[end:]
lines = body.split('\n')

DECL = re.compile(r'^\s*(?:[A-Za-z_]\w*\s+)+\**\w+\s*(?:\[\w*\])?\s*(?:=|;)')
CTRL = ('if','for','while','do','else','switch','case','default','return','goto','{','}')
cands = []
for i, ln in enumerate(lines):
    s = ln.strip()
    if not s.endswith(';'): continue
    first = s.split()[0].rstrip('(')
    if first in CTRL: continue
    if DECL.match(ln): continue
    if '{' in s or '}' in s: continue
    cands.append(i)

TMP = Path('/tmp/wrapclimb.c')
def build(chosen):
    o = lines[:]
    for i in sorted(chosen, reverse=True):
        ln = o[i]
        ind = ln[:len(ln)-len(ln.lstrip())]
        o[i:i+1] = [f'{ind}do {{', f'{ind}    {ln.strip()}', f'{ind}}} while (0);']
    return src[:head_end] + '\n'.join(o) + tail

def score(chosen):
    TMP.write_text(build(chosen))
    try: return dict(screen.measure(fn, TMP))['words']
    except Exception: return 10**6

cur, best = [], score([])
print(f'{fn}: {len(cands)} statements, start {best}', flush=True)
out.write_text(build(cur))
for it in range(iters):
    c = cur[:]
    if random.random() < 0.7 or not c:
        # add a candidate not present
        pool = [x for x in cands if x not in c]
        if not pool: continue
        c.append(random.choice(pool))
    else:
        c.remove(random.choice(c))
    s = score(c)
    if s < best:
        best, cur = s, c
        out.write_text(build(cur))
        print(f'improved {best} wraps={sorted(cur)}', flush=True)
        if best == 0: break
print('final', best, 'wraps', sorted(cur), flush=True)
out.write_text(build(cur))
