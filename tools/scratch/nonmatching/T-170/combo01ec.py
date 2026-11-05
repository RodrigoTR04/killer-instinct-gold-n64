#!/usr/bin/env python3
"""Combination search for 01EC: wrap position x alpha form x decl order."""
import importlib.util, sys, tempfile, re, itertools, json
from pathlib import Path
import concurrent.futures
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

fn = 'func_801B01EC'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'func_801B01EC.c').read_text()

COLOR_INLINE = "    g->w0 = 0xFB000000;\n    alpha &= 0xFF;\n    g->w1 = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;"
COLOR_MASK = "    g->w0 = 0xFB000000;\n    g->w1 = ((alpha & 0xFF) << 24) | ((alpha & 0xFF) << 16) | ((alpha & 0xFF) << 8) | 0xFF;"
WRAPS = [
  ("", ""),
  ("    g->w0 = 0x03820010;", "    do { g->w0 = 0x03820010; } while (0);"),
  ("    g->w0 = 0xFA000000;", "    do { g->w0 = 0xFA000000; } while (0);"),
  ("    g->w0 = 0xFB000000;", "    do { g->w0 = 0xFB000000; } while (0);"),
  ("    g->w0 = 0x06000000;", "    do { g->w0 = 0x06000000; } while (0);"),
  ("    g->w0 = 0x03840010;", "    do { g->w0 = 0x03840010; } while (0);"),
  ("    alpha = 0xFF;", "    do { alpha = 0xFF; } while (0);"),
  ("            D_802C8750 += 1;", "            do { D_802C8750 += 1; } while (0);"),
]


def score(src, tag):
    p = outdir / f'cb_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        return (r['words'], r['compiled'], tag)
    except Exception as e:
        return (99999, 0, tag)
    finally:
        p.unlink(missing_ok=True)


if __name__ == '__main__':
    jobs = []
    for cname, (cfrom, cto) in (('i', (COLOR_INLINE, COLOR_INLINE)), ('m', (COLOR_INLINE, COLOR_MASK))):
        for wname, (wfrom, wto) in enumerate(WRAPS):
            src = BASE if cfrom == cto else BASE.replace(cfrom, cto)
            if wfrom:
                if wfrom not in src:
                    continue
                src = src.replace(wfrom, wto, 1)
            jobs.append((f'{cname}{wname}', src))
    # plus two-wrap combos on the draw list
    for i, j in itertools.combinations(range(1, 6), 2):
        src = BASE
        for k in (i, j):
            a, b = WRAPS[k]
            src = src.replace(a, b, 1)
        jobs.append((f'w{i}{j}', src))
    res = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=10) as ex:
        for r in ex.map(lambda t: score(t[1], t[0]), jobs):
            res.append(r)
    for w, comp, tag in sorted(res)[:10]:
        print(f'{tag:6s} w={w:4d} {comp}')
