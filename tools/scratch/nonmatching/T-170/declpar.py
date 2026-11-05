#!/usr/bin/env python3
"""Parallel declaration-order search for a draft function."""
import importlib.util, sys, tempfile, re, json, itertools
from pathlib import Path
import concurrent.futures
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
draftp = Path(sys.argv[2])
decls_file = Path(sys.argv[3])
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = draftp.read_text()
DECLS = decls_file.read_text()
assert DECLS in BASE, 'decl block not found'


def key(l):
    return re.search(r'(\w+)\s*(\[|;|=)', l.strip()).group(1)


LINES = {key(l): l for l in DECLS.splitlines(True)}
KEYS = list(LINES)


def score(order):
    src = BASE.replace(DECLS, ''.join(LINES[k] for k in order), 1)
    tag = 'p' + '_'.join(o[:3] for o in order)
    p = outdir / 'dtmp' / f'{tag}.c'
    p.parent.mkdir(exist_ok=True)
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        s1 = any(re.match(r'sw s1,', x) for x in mine)
        return (r['words'], int(fr.group(1)) if fr else 0, int(s1), r['compiled'], order)
    except Exception:
        return (99999, 0, 0, 0, order)
    finally:
        p.unlink(missing_ok=True)


if __name__ == '__main__':
    orders = [list(o) for o in itertools.permutations(KEYS)]
    res = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=10) as ex:
        for i, r in enumerate(ex.map(score, orders)):
            res.append(r)
            if (i + 1) % 48 == 0:
                print(f'{i+1}/{len(orders)} best={min(res)[:4]}', flush=True)
    res.sort()
    print('\nTOP:')
    for w, fr, s1, comp, order in res[:10]:
        print(f'w={w:4d} frame={fr} s1={s1} {comp}  {order}')
