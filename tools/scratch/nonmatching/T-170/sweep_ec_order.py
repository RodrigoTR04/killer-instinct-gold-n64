#!/usr/bin/env python3
"""01EC: with alpha as s32[1] (a real memory object), sweep declaration order to
land the alpha spill on sp+0x64 and the float spill on sp+0x60."""
import importlib.util, sys, tempfile, re, difflib, itertools, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801B01EC'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'func_801B01EC.c').read_text()


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


TARGET = [cm.canon(x) for x in cm.target_raw(fn)]
TARGET = [x for x in TARGET if not x.startswith(('dlabel', 'enddlabel'))]
TM = [M(x) for x in TARGET]

DECLS = ["    u8 lookat[0x40];", "    T164Gfx01EC *g;", "    s32 result;",
         "    f32 angle;", "    f32 rise;", "    s32 alpha[1];", "    u32 elapsed;"]


def variants():
    for perm in itertools.permutations(range(len(DECLS))):
        yield perm


def score(perm, tag):
    decls = '\n'.join(DECLS[i] for i in perm)
    v = BASE
    for d in DECLS:
        v = v.replace(d, '', 1)
    v = v.replace('s32 func_801B01EC(T164Gfx01EC **arg0, s32 arg1, u8 *arg2, u32 arg3) {\n',
                  's32 func_801B01EC(T164Gfx01EC **arg0, s32 arg1, u8 *arg2, u32 arg3) {\n' + decls + '\n', 1)
    v = v.replace('alpha = 0xFF;', 'alpha[0] = 0xFF;')
    v = v.replace('alpha = (s32) func_801AFA80', 'alpha[0] = (s32) func_801AFA80')
    v = v.replace('    alpha &= 0xFF;', '    alpha[0] &= 0xFF;')
    v = v.replace('(alpha << 24) | (alpha << 16) | (alpha << 8)',
                  '(alpha[0] << 24) | (alpha[0] << 16) | (alpha[0] << 8)')
    p = outdir / f'd_{tag}.c'
    p.write_text(v)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as dd:
            o = cm.compile_source(src, Path(dd)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception:
        return (9999, 9999, '')
    sm = difflib.SequenceMatcher(None, [M(x) for x in mine], TM, autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad2, f'{tag:16s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} rdiff={bad2:3d}')


if __name__ == '__main__':
    jobs = [(''.join(map(str, p)), p) for p in variants()]
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: score(j[1], j[0]), jobs))
    rows.sort()
    for r in rows[:12]:
        print(r[2])
