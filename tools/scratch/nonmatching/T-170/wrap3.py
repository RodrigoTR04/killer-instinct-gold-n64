#!/usr/bin/env python3
"""Robust do{...}while(0) wrap scanner (lexer-based, nesting aware)."""
import importlib.util, sys, tempfile, re, json, itertools
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
    """Return list of (start,end) statement/block spans relative to s."""
    spans = []
    pd = 0
    bd = 0
    bstart = {}          # brace depth -> index right after last terminator
    bstart[0] = 0
    i = 0
    n = len(s)
    brace_stack = []
    while i < n:
        ch = s[i]
        if ch in '"\'':
            q = ch
            i += 1
            while i < n and s[i] != q:
                i += 2 if s[i] == '\\' else 1
            i += 1
            continue
        if ch == '/' and i + 1 < n and s[i+1] == '*':
            i = s.index('*/', i) + 2
            continue
        if ch == '/' and i + 1 < n and s[i+1] == '/':
            i = s.index('\n', i)
            continue
        if ch == '(':
            pd += 1
        elif ch == ')':
            pd -= 1
        elif ch == '{':
            open_at = i
            bd += 1
            bstart[bd] = i + 1
            brace_stack.append(open_at)
        elif ch == '}':
            close_at = i
            open_at = brace_stack.pop() if brace_stack else None
            # inner block content as a wrap candidate
            if open_at is not None:
                inner = s[open_at+1:close_at]
                if inner.strip():
                    spans.append((open_at+1, close_at, 'blk'))
            bd -= 1
            bstart[bd] = close_at
            # don't reset if followed by 'else'
        elif ch == ';' and pd == 0:
            st = bstart.get(bd, 0)
            seg = s[st:i+1]
            if seg.strip():
                spans.append((st, i + 1, 'stmt'))
            bstart[bd] = i + 1
        i += 1
    return spans


cands = scan(body)
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
        return (99999, 0, 0, f'{tag:8s} ERR {str(e)[-58:]}')


def apply_wraps(idx_list):
    """Apply wraps from the highest offset down so offsets stay valid."""
    spans = [(cands[k][0], cands[k][1]) for k in sorted(idx_list, reverse=True)]
    out = body
    for a, b in spans:
        out = out[:a] + ' do { ' + out[a:b] + ' } while (0); ' + out[b:]
    return text[:body_off] + out + text[fend:]


base_res = score(text, 'base')
print(base_res[3], flush=True)
results = []
for idx, (a, b, kind) in enumerate(cands):
    seg = body[a:b].strip()
    if not seg or seg.endswith(':') :
        continue
    if re.match(r'^(s32|f32|u8|u32|f64|struct|Frontend\w+|T\d+\w*)\s+\w', seg) and '=' not in seg:
        continue
    src = apply_wraps([idx])
    r = score(src, f'{kind[0]}{idx}')
    results.append((r[0], idx, r[3], kind, a, b))
    print(r[3], flush=True)

results.sort()
print('\nBEST:')
for w, idx, line, kind, a, b in results[:10]:
    print(line, repr(body[a:b].strip()[:70]))
json.dump([(w, i, k) for w, i, _, k, _, _ in results], open(outdir / f'{outpre}res.json', 'w'))
