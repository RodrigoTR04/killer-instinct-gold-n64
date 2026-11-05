#!/usr/bin/env python3
"""wrap2.py FN DRAFT — wrap every *simple statement* (any nesting) in
`do { stmt; } while (0);`, one at a time, and report official counts.

Wrapped statements are always real code. Declarations are never wrapped.
"""
import argparse, concurrent.futures as cf, importlib.util, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
OUT = Path('/tmp/wrap2')

ap = argparse.ArgumentParser()
ap.add_argument('function'); ap.add_argument('draft')
ap.add_argument('--combos', type=int, default=0)
a = ap.parse_args()
fn = a.function
src = Path(a.draft).read_text()
m = re.search(r'\b' + re.escape(fn) + r'\([^)]*\)\s*\{\n', src)
head_end = m.end()
rest = src[head_end:]
depth, end = 1, None
for i, ch in enumerate(rest):
    if ch == '{': depth += 1
    elif ch == '}':
        depth -= 1
        if depth == 0:
            end = i; break
body, tail = rest[:end], rest[end:]
lines = body.split('\n')

# find candidate simple statements: a line ending in ';' whose first token is not
# a control keyword and which is not a declaration
DECL = re.compile(r'^\s*(?:[A-Za-z_]\w*\s+)+\**\w+\s*(?:\[\w*\])?\s*(?:=|;)')
CTRL = ('if', 'for', 'while', 'do', 'else', 'switch', 'case', 'default', 'return', 'goto', '{', '}')
cands = []
for i, ln in enumerate(lines):
    s = ln.strip()
    if not s.endswith(';'): continue
    first = s.split()[0].rstrip('(')
    if first in CTRL: continue
    if DECL.match(ln): continue
    if '{' in s or '}' in s: continue
    cands.append(i)
print(f'{fn}: {len(cands)} candidate statements', flush=True)
OUT.mkdir(exist_ok=True)

def build(chosen):
    out = lines[:]
    for i in sorted(chosen, reverse=True):
        ln = out[i]
        indent = ln[:len(ln) - len(ln.lstrip())]
        out[i:i+1] = [f'{indent}do {{', f'{indent}    {ln.strip()}', f'{indent}}} while (0);']
    return src[:head_end] + '\n'.join(out) + tail

def score(name, text):
    p = OUT / name; p.write_text(text)
    try:
        r = dict(screen.measure(fn, p)); return (r['words'], r['compiled'], name)
    except Exception:
        return (10**6, 0, name)

tasks = [(f's{i}.c', build([i])) for i in cands]
if a.combos:
    import random; random.seed(11)
    for k in range(a.combos):
        n = random.choice([2, 2, 2, 3])
        ch = tuple(sorted(random.sample(cands, min(n, len(cands)))))
        tasks.append((f'c{k}_' + '_'.join(map(str, ch)) + '.c', build(ch)))
with cf.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(lambda t: score(*t), tasks))
base = score('base.c', src)
print('baseline', base[0], flush=True)
for w, b, n in res:
    if w < base[0]:
        print(f'BETTER {w} {b}B {n}', flush=True)
print('--- top 8 ---')
for r in res[:8]: print(r)
