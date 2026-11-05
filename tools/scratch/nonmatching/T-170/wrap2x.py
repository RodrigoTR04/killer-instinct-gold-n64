#!/usr/bin/env python3
"""Pair-wise do{...}while(0) wrap scan using the wrap3 lexer spans.

Scans every pair of statement spans in a window around the tail of the function
(the block the single-wrap scan liked) plus a few structural triples, and
reports the official words / size / frame for each so a schedule win is visible.
"""
import importlib.util, sys, tempfile, re, itertools, json, concurrent.futures
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
draft = Path(sys.argv[2])
lo = int(sys.argv[3]) if len(sys.argv) > 3 else 0
hi = int(sys.argv[4]) if len(sys.argv) > 4 else 10 ** 9
outdir = draft.parent
text = draft.read_text()

m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^\n]*\)\s*\{?\s*\n', text, re.M)
fstart = text.index('{', m.start())
depth = 0
for j in range(fstart, len(text)):
    if text[j] == '{':
        depth += 1
    elif text[j] == '}':
        depth -= 1
        if depth == 0:
            break
fend = j
body_off = fstart + 1
body = text[body_off:fend]

LEX = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d+(?:[\w.]*)|>>=|<<=|\+\+|--|->|&&|\|\||==|!=|<=|>=|<<|>>|\+=|-=|\*=|/=|%=|&=|\|=|\^=|[^\s]', re.S)


def scan(s):
    spans = []
    pd = 0
    bd = 0
    bstart = {0: 0}
    stack = []
    i = 0
    n = len(s)
    while i < n:
        ch = s[i]
        if ch in '"\'':
            q = ch
            i += 1
            while i < n and s[i] != q:
                i += 2 if s[i] == '\\' else 1
            i += 1
            continue
        if ch == '/' and i + 1 < n and s[i + 1] == '*':
            i = s.index('*/', i) + 2
            continue
        if ch == '/' and i + 1 < n and s[i + 1] == '/':
            i = s.index('\n', i)
            continue
        if ch == '(':
            pd += 1
        elif ch == ')':
            pd -= 1
        elif ch == '{':
            bd += 1
            stack.append(i)
            bstart[bd] = i + 1
        elif ch == '}':
            o = stack.pop() if stack else None
            if o is not None and s[o + 1:i].strip():
                spans.append((o + 1, i))
            bd -= 1
            bstart[bd] = i
        elif ch == ';' and pd == 0:
            st = bstart.get(bd, 0)
            if s[st:i + 1].strip():
                spans.append((st, i + 1))
            bstart[bd] = i + 1
        i += 1
    return spans


ALLSPANS = scan(body)
CANDS = [(a, b) for a, b in ALLSPANS if lo <= a <= hi]
# remap pair indices onto ALLSPANS so wrap indices stay valid
_OFF = [i for i, (a, b) in enumerate(ALLSPANS) if lo <= a <= hi]
print(f'{len(CANDS)} spans in window', flush=True)


def apply_wraps(idx_list):
    spans = sorted((ALLSPANS[_OFF[k]] for k in idx_list), reverse=True)
    out = body
    for a, b in spans:
        out = out[:a] + ' do { ' + out[a:b] + ' } while (0); ' + out[b:]
    return text[:body_off] + out + text[fend:]


def score(src, tag):
    p = outdir / f'p_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        s, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(s, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        frv = int(fr.group(1)) if fr else 0
        return (r['words'], r['compiled'], frv, f'{tag:12s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame=0x{frv:x}')
    except Exception as e:
        return (99999, 0, 0, f'{tag:12s} ERR {str(e)[-50:]}')


if __name__ == '__main__':
    jobs = []
    for a, b in itertools.combinations(range(len(CANDS)), 2):
        jobs.append(([a, b], f'{a}_{b}'))
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: score(apply_wraps(j[0]), j[1]), jobs))
    rows.sort()
    for r in rows[:14]:
        print(r[3])
