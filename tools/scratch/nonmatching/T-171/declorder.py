#!/usr/bin/env python3
"""Declaration-order search: shuffles the local declaration block of a draft.

usage: declorder.py FUNCTION DRAFT OUTDIR N [SEED]

Splits the draft at the function-local declaration run (the contiguous block of
simple `type name;` / `type a, b;` lines right after the opening brace), then
tries N random permutations of those lines. Each candidate is written to
OUTDIR/<i>.c and measured with screen.measure; the best counts are printed.
"""
import concurrent.futures, importlib.util, itertools, random, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

def split_decls(text):
    lines = text.splitlines(keepends=True)
    start = None
    for i, l in enumerate(lines):
        if l.rstrip().endswith('{'):
            start = i + 1
            break
    end = start
    while end < len(lines) and re.match(r'^\s+[A-Za-z_][\w ]*\**[A-Za-z_]\w*(\[[^\]]*\])?(\s*=\s*[^;]+)?;\s*$', lines[end]):
        end += 1
    return lines, start, end

def main():
    fn, draft, outdir = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
    n = int(sys.argv[4]) if len(sys.argv) > 4 else 60
    seed = int(sys.argv[5]) if len(sys.argv) > 5 else 0
    outdir.mkdir(parents=True, exist_ok=True)
    for f in outdir.glob('*.c'): f.unlink()
    text = draft.read_text() if draft.is_absolute() else (ROOT / draft).read_text()
    lines, start, end = split_decls(text)
    decls = lines[start:end]
    if len(decls) < 2:
        print('no declaration run found'); return
    rng = random.Random(seed)
    seen, cands = set(), []
    for _ in range(n * 4):
        p = decls[:]
        rng.shuffle(p)
        k = tuple(p)
        if k in seen: continue
        seen.add(k); cands.append(p)
        if len(cands) >= n: break
    paths = []
    for i, p in enumerate(cands):
        q = outdir / f'd{i:03d}.c'
        q.write_text(''.join(lines[:start] + p + lines[end:]))
        paths.append((i, q))

    def run(item):
        i, q = item
        try:
            r = screen.measure(fn, q)
            return (r['words'], r['compiled'], i, str(q))
        except Exception:
            return (9999, 0, i, str(q))

    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        res = sorted(pool.map(run, paths))
    for words, comp, i, q in res[:6]:
        print(f'{words:>6} {comp:>6}B  {q}')

main()
