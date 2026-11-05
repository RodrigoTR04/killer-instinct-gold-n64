#!/usr/bin/env python3
"""Wrap each top-level statement (one at a time) in do { ... } while (0);

Usage: wrap.py FUNCTION DRAFT OUTPREFIX
Reports words/bytes/frame/n for each single-statement wrap.
"""
import importlib.util, sys, tempfile, re, difflib, json
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

# Find function body span
m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', text, re.M)
start = text.index('{', m.start())
depth = 0
for j in range(start, len(text)):
    if text[j] == '{':
        depth += 1
    elif text[j] == '}':
        depth -= 1
        if depth == 0:
            break
body_start, body_end = start, j

# Collect statement spans at brace-depth 1 (top level of function): simple statements ending in ; or \n
def stmt_spans(body, base):
    """Yield (abs_start, abs_end) for statements at relative depth 1."""
    spans = []
    i = 0
    depth = 0
    n = len(body)
    stmt_start = None
    while i < n:
        ch = body[i]
        if ch == '{':
            if depth == 1 and stmt_start is None:
                # block statement: find matching close
                d = 0
                k = i
                while k < n:
                    if body[k] == '{': d += 1
                    elif body[k] == '}':
                        d -= 1
                        if d == 0: break
                    k += 1
                # include trailing if/else? skip; only plain blocks
                spans.append((base + i, base + k + 1))
                i = k + 1
                continue
            depth += 1
        elif ch == '}':
            depth -= 1
        elif depth == 1 and stmt_start is None and not ch.isspace():
            stmt_start = i
        if depth == 1 and ch == ';' and stmt_start is not None:
            spans.append((base + stmt_start, base + i + 1))
            stmt_start = None
        i += 1
    return spans

body = text[body_start+1:body_end]
spans = stmt_spans(body, body_start+1)
# Also: identify "if (...) { ... }" and "else {...}" headers to wrap the body inside branches

def score(src, tag, frame_only=False):
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
        return (r['words'], frv, len(mine), r['compiled'], f'{tag:6s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={frv} n={len(mine)}')
    except Exception as e:
        return (99999, 0, 0, 0, f'{tag:6s} ERROR {str(e)[-80:]}')

base_res = score(text, 'base')
print(base_res[4], flush=True)
results = []
for idx, (a, b) in enumerate(spans):
    seg = text[a:b]
    if seg.strip().startswith('return'):
        continue
    new = text[:a] + 'do { ' + seg.strip() + ' } while (0);' + text[b:]
    r = score(new, f'w{idx}')
    results.append((r[0], idx, r[4], new))
    print(r[4], flush=True)
results.sort()
print('\nBEST:')
for w, idx, line, src in results[:5]:
    print(line)
