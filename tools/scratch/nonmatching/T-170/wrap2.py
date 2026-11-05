#!/usr/bin/env python3
"""Wrap a single statement in do { ... } while (0) at ANY nesting depth.

Enumerates every simple statement (ending in ';' at paren-depth 0) and every
compound block whose parent is an if/else/for/while, then scores each wrap.
"""
import importlib.util, sys, tempfile, re, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
draft = Path(sys.argv[2])
outpre = sys.argv[3]
start_at = int(sys.argv[4]) if len(sys.argv) > 4 else 0
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

def candidates(s):
    """Yield (start, end, kind) spans within s for statements to wrap."""
    out = []
    i, n = 0, len(s)
    while i < n:
        ch = s[i]
        if ch in '"\'':
            q = ch
            i += 1
            while i < n and s[i] != q:
                i += 2 if s[i] == '\\' else 1
            i += 1
            continue
        if ch == '{':
            d = 0
            k = i
            while k < n:
                if s[k] == '{': d += 1
                elif s[k] == '}':
                    d -= 1
                    if d == 0: break
                k += 1
            # block body candidate (contents only)
            inner = s[i+1:k]
            if inner.strip() and not inner.strip().startswith('return'):
                out.append((i+1, k, 'block'))
            i = k + 1
            continue
        i += 1
    # simple statements: scan for ';' at paren depth 0 outside braces (we already descend)
    # do a second pass tracking paren depth only
    pd = 0
    stmt = None
    for i, ch in enumerate(s):
        if ch in '"\'':
            continue
        if ch == '(':
            pd += 1
        elif ch == ')':
            pd -= 1
        elif ch == ';' and pd == 0:
            # statement starts after last ; { } at this level
            j = (stmt if stmt is not None else 0)
            seg = s[j:i+1].strip()
            if seg and not seg.startswith(('return', 'do ')) and 'for (' not in seg:
                out.append((j, i+1, 'stmt'))
            stmt = i + 1
        elif ch in '{}=;' and pd == 0:
            stmt = i + 1
    return out

body = text[fstart+1:fend]
cands = candidates(body)
print(f'{len(cands)} candidates', flush=True)

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
        frv = int(fr.group(1)) if fr else 0
        return (r['words'], r['compiled'], frv, f'{tag:8s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={frv}')
    except Exception as e:
        return (99999, 0, 0, f'{tag:8s} ERROR {str(e)[-70:]}')

base_res = score(text, 'base')
print(base_res[3], flush=True)
results = []
for idx, (a, b, kind) in enumerate(cands):
    if idx < start_at:
        continue
    aa, bb = fstart + 1 + a, fstart + 1 + b
    seg = text[aa:bb]
    if not seg.strip():
        continue
    new = text[:aa] + ' do { ' + seg + ' } while (0); ' + text[bb:]
    r = score(new, f'{kind[0]}{idx}')
    results.append((r[0], idx, r[3]))
    print(r[3], flush=True)
results.sort()
print('\nBEST:')
for w, idx, line in results[:8]:
    print(line)
