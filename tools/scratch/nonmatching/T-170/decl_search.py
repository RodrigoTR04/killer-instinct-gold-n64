#!/usr/bin/env python3
"""23C0: reorder declaration block, minimize frame + words."""
import importlib.util, sys, tempfile, re, difflib, itertools, random, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801C23C0'
D = json.load(open(ROOT/'tools/scratch/nonmatching/T-170/decl23.json'))
BASE, DECLS, ORDER = D['base'], D['decls'], D['order']
import re as _re
def _key(l):
    m = _re.search(r'(\w+)\s*(\[|;|=)', l.strip())
    return m.group(1)
LINES = {_key(l): l for l in DECLS.splitlines(True)}


def score(txt, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'f_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        frv = int(fr.group(1)) if fr else 0
    except Exception as e:
        return (9999, 9999, f'{tag:10s} ERROR {str(e)[-60:]}')
    return (frv, r['words'], f'{tag:10s} frame={frv} w={r["words"]:4d} {r["compiled"]}/{r["original"]}')


def build(order):
    return BASE.replace(DECLS, ''.join(LINES[k] for k in order), 1)


if __name__ == '__main__':
    results = []
    best = None
    rnd = random.Random(11)
    seen = set()
    def ev(order):
        key = tuple(order)
        if key in seen:
            return None
        seen.add(key)
        res = score(build(order), str(len(results)))
        results.append((res[0], res[1], list(order), res[2]))
        print(res[2], flush=True)
        return res

    ev(ORDER)
    cur = list(ORDER)
    cur_score = None
    # hill-climb on (frame, words)
    for step in range(400):
        cand = list(cur)
        i, j = rnd.randrange(len(cand)), rnd.randrange(len(cand))
        cand[i], cand[j] = cand[j], cand[i]
        r = ev(cand)
        if r is None:
            continue
        key = (r[0], r[1])
        if cur_score is None or key < cur_score:
            cur, cur_score = cand, key
    results.sort(key=lambda x: (x[0], x[1]))
    print('\nBEST:')
    for fr, w, order, line in results[:6]:
        print(line, order)
