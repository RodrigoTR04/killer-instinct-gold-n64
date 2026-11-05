#!/usr/bin/env python3
"""23C0: find a declaration set that yields the target 0x70 frame."""
import importlib.util, sys, tempfile, re, itertools, json, random
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801C23C0'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = Path('/tmp/c23_base.c').read_text()
DECLS = """    f32 temp_f10;
    s32 var_v1;
    f32 velocity[3];
    u8 temp_v0_4;
    s32 temp_f16;
    f32 temp_f14;
    u8 temp_v0_3;
    f32 temp_f12;
    f32 position[3];
    f32 sp4C;
    FrontendGfxWords *temp_v0;
    f32 temp_f12_2;
    f32 sp54;
    f32 sp50;
    f32 var_f0;
    u8 sp4B;
    FrontendGfxWords *temp_v0_2;
    f32 var_f14;
    s32 sp3C;
"""
assert DECLS in BASE
import re as _re
def key(l):
    return _re.search(r'(\w+)\s*(\[|;|=)', l.strip()).group(1)
LINES = {key(l): l for l in DECLS.splitlines(True)}


def score(src, tag):
    p = outdir / f'p23_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        return (int(fr.group(1)) if fr else 0, r['words'], r['compiled'], len(mine))
    except Exception as e:
        return (0, 99999, 0, 0)


if __name__ == '__main__':
    mode = sys.argv[1]
    res = []
    if mode == 'drop':
        # drop one local at a time (must still compile: only drop unused-ish ones by replacement)
        for k in LINES:
            if k in ('position', 'velocity', 'sp4B'):
                continue
            src = BASE.replace(DECLS, ''.join(LINES[x] for x in LINES if x != k), 1)
            res.append((*score(src, k), f'drop_{k}'))
    elif mode == 'size':
        # change velocity/position array sizes
        for nv in (3, 4, 6):
            for np_ in (3, 4, 6):
                d = DECLS.replace('f32 velocity[3];', f'f32 velocity[{nv}];').replace('f32 position[3];', f'f32 position[{np_}];')
                src = BASE.replace(DECLS, d, 1)
                res.append((*score(src, f'v{nv}p{np_}'), f'v{nv}p{np_}'))
    for fr, w, comp, n_, tag in sorted(res, key=lambda x: (x[0] != 112, x[1])):
        print(f'{tag:16s} frame={fr} w={w} {comp} n={n_}')
