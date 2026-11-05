#!/usr/bin/env python3
"""Greedy wrap-combination search: wrap sets of statements one at a time."""
import importlib.util, sys, tempfile, re, json, itertools, random
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
draft = Path(sys.argv[2])
outpre = sys.argv[3]
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
text = draft.read_text()

m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', text, re.M)
fstart = text.index('{', m.start())
depth = 0
for j in range(fstart, len(text)):
    if text[j] == '{': depth += 1
    elif text[j] == '}':
        depth -= 1
        if depth == 0: break
fend = j
body_off = fstart + 1
body = text[body_off:fend]


def scan(s):
    spans = []
    pd = 0
    bstart = {0: 0}
    bd = 0
    i, n = 0, len(s)
    stack = []
    while i < n:
        ch = s[i]
        if ch in '"\'':
            q = ch
            i += 1
            while i < n and s[i] != q:
                i += 2 if s[i] == '\\' else 1
            i += 1
            continue
        if ch == '/' and i+1 < n and s[i+1] == '*':
            i = s.index('*/', i) + 2
            continue
        if ch == '/' and i+1 < n and s[i+1] == '/':
            i = s.index('\n', i)
            continue
        if ch == '(': pd += 1
        elif ch == ')': pd -= 1
        elif ch == '{':
            bd += 1; bstart[bd] = i+1; stack.append(i)
        elif ch == '}':
            o = stack.pop() if stack else None
            if o is not None:
                inner = s[o+1:i]
                if inner.strip(): spans.append((o+1, i, 'blk'))
            bd -= 1; bstart[bd] = i
        elif ch == ';' and pd == 0:
            st = bstart.get(bd, 0)
            if s[st:i+1].strip(): spans.append((st, i+1, 'stmt'))
            bstart[bd] = i+1
        i += 1
    return spans


CANDS = scan(body)
DECL = re.compile(r'^(s32|f32|u8|u32|f64|struct|Frontend\w+|T\d+\w*)\s+\S')
usable = [i for i, (a, b, k) in enumerate(CANDS)
          if body[a:b].strip() and not DECL.match(body[a:b].strip())
          and not body[a:b].strip().startswith('return')]


def apply(idx_list):
    spans = [(CANDS[k][0], CANDS[k][1]) for k in sorted(idx_list, reverse=True)]
    out = body
    for a, b in spans:
        out = out[:a] + ' do { ' + out[a:b] + ' } while (0); ' + out[b:]
    return text[:body_off] + out + text[fend:]


def score(src, tag):
    p = outdir / f'{outpre}{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        return (r['words'], int(fr.group(1)) if fr else 0, f'{tag:10s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={int(fr.group(1)) if fr else 0}')
    except Exception as e:
        return (99999, 0, f'{tag:10s} ERR {str(e)[-55:]}')


best = score(text, 'base')
print(best[2], flush=True)
cur = []
for round_ in range(6):
    results = []
    for i in usable:
        r = score(apply(cur + [i]), f'r{round_}i{i}')
        results.append((r[0], i, r[2]))
    results.sort()
    print(f'--- round {round_} best: {results[0][2]}', flush=True)
    if results[0][0] < best[0]:
        best = (results[0][0], 0, results[0][2])
        cur.append(results[0][1])
        print(f'   accepted wrap {results[0][1]}: {body[CANDS[results[0][1]][0]:CANDS[results[0][1]][1]].strip()[:60]!r}', flush=True)
    else:
        break
print('WRAPS:')
for i in cur:
    a, b, k = CANDS[i]
    print(f'  {i} {k} {body[a:b].strip()[:70]!r}')
(outdir / f'{outpre}best.c').write_text(apply(cur))
print('done')
