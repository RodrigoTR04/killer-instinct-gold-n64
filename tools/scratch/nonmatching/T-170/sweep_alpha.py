#!/usr/bin/env python3
"""01EC: make alpha live in the sp+0x64 stack slot instead of a saved register."""
import importlib.util, sys, tempfile, re, difflib, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801B01EC'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'func_801B01EC.c').read_text()
TARGET = [cm.canon(x) for x in cm.target_raw(fn)]
TARGET = [x for x in TARGET if not x.startswith(('dlabel', 'enddlabel'))]


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


TM = [M(x) for x in TARGET]

ORIG_DECL = """    s32 alpha;
"""
ORIG_INIT = """    alpha = 0xFF;"""
ORIG_ASSIGN = """        alpha = (s32) func_801AFA80(255.0f, 2.0f, (s32) arg3, 0x78);"""
ORIG_TAIL = """    g->w0 = 0xFB000000;
    alpha &= 0xFF;
    g->w1 = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;"""

TYPES = {'s32': 's32', 'u8': 'u8', 'u32': 'u32', 's8': 's8', 'volatile_s32': 'volatile s32'}
TAILS = {
    'and': """    g->w0 = 0xFB000000;
    alpha &= 0xFF;
    g->w1 = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;""",
    'chained': """    g->w0 = 0xFB000000;
    g->w1 = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;""",
    'mask_expr': """    g->w0 = 0xFB000000;
    g->w1 = ((alpha & 0xFF) << 24) | ((alpha & 0xFF) << 16) | ((alpha & 0xFF) << 8) | 0xFF;""",
    'u8var': """    g->w0 = 0xFB000000;
    g->w1 = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;""",
}
INITS = {
    'ff': '    alpha = 0xFF;',
    'after_test': None,
}


def score(txt, tag):
    p = outdir / f'a_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception:
        return (9999, 9999, f'{tag:26s} ERROR')
    sm = difflib.SequenceMatcher(None, [M(x) for x in mine], TM, autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    s64 = sum(1 for x in mine if re.search(r',(100|196|188)\(sp\)', x))
    return (r['words'], bad2, f'{tag:26s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} rdiff={bad2:3d}')


jobs = []
for tn, t in TYPES.items():
    for tailn, tail in TAILS.items():
        if tailn == 'u8var' and not tn.startswith('u8'):
            continue
        txt = BASE.replace(ORIG_DECL, f'    {t} alpha;\n', 1).replace(ORIG_TAIL, tail, 1)
        jobs.append((txt, f'{tn}_{tailn}'))
with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
    rows = list(pool.map(lambda j: score(*j), jobs))
rows.sort()
for r in rows[:20]:
    print(r[2])
