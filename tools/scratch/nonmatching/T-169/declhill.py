#!/usr/bin/env python3
"""declhill.py FN DRAFT OUT [full] - hill-climb the leading declaration order.

Uses the official `screen.measure` word count on the full owning TU, so only
honest C reordering is searched. Each step tries every single-declaration move.
"""
import importlib.util
import random
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def score(fn, path):
    try:
        r = dict(screen.measure(fn, path))
        return r['words'], r['compiled']
    except Exception:
        return 9999, 0


def main():
    fn, draft, out = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
    src = draft.read_text()
    m = re.search(r'\b' + re.escape(fn) + r'\([^)]*\)\s*\{\n', src)
    head_end = m.end()
    lines = src[head_end:].split('\n')
    decl = []
    for ln in lines:
        if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$', ln) and not re.match(r'^\s+(return|goto|break)', ln):
            decl.append(ln)
        else:
            break
    n = len(decl)
    rest = '\n'.join(lines[n:])
    print('decls', n, flush=True)

    def build(order):
        return src[:head_end] + '\n'.join(decl[k] for k in order) + '\n' + rest

    tmp = Path('/tmp/declhill_candidate.c')
    best_order = tuple(range(n))
    tmp.write_text(build(best_order))
    best = score(fn, tmp)
    print('start', best, flush=True)
    seen = {best_order}
    improved = True
    while improved:
        improved = False
        candidates = []
        for i in range(n):
            for j in range(n):
                if i == j:
                    continue
                o = list(best_order)
                x = o.pop(i)
                o.insert(j, x)
                o = tuple(o)
                if o not in seen:
                    seen.add(o)
                    candidates.append(o)
        for o in candidates:
            tmp.write_text(build(o))
            s = score(fn, tmp)
            if s < best:
                best, best_order = s, o
                out.write_text(build(o))
                print('improved', best, [decl[k].strip() for k in o], flush=True)
                improved = True
                break
    print('final', best, flush=True)
    out.write_text(build(best_order))


main()
