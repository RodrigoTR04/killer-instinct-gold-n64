#!/usr/bin/env python3
"""BB7B4: sweep forms of the (arg0+1) byte computation; score positionally."""
import importlib.util, sys, tempfile, re, difflib, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801BB7B4'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'bb7b4_c3.c').read_text()
TARGET = [cm.canon(x) for x in cm.target_raw(fn)]
TARGET = [x for x in TARGET if not x.startswith(('dlabel', 'enddlabel'))]


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


TM = [M(x) for x in TARGET]

DECL = """    s32 mask;
    u8 next;
"""
DECL_MAP = {
    'u8': DECL,
    's32': """    s32 mask;
    s32 next;
""",
    'u32': """    s32 mask;
    u32 next;
""",
    's8': """    s32 mask;
    s8 next;
""",
}
SIGS = {
    'u8': 'void func_801BB7B4(u8 arg0) {',
    's32': 'void func_801BB7B4(s32 arg0) {',
    'u32': 'void func_801BB7B4(u32 arg0) {',
}
EXPR = [
    'next = arg0 + 1;',
    'next = (arg0 + 1) & 0xFF;',
    'next = (u8) (arg0 + 1);',
    'next = arg0; next += 1;',
    'next = arg0; next = next + 1;',
    'next = arg0 + 1; next = (u8) next;',
    'next = arg0; next += 1; next = (u8) next;',
    'next = arg0 + 1; next &= 0xFF;',
]


def score(txt, tag):
    p = outdir / f'n_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 9999, '')
    sm = difflib.SequenceMatcher(None, [M(x) for x in mine], TM, autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad2, f'{tag:26s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} rdiff={bad2:3d}')


jobs = []
for at, sig in SIGS.items():
    for nt, d in DECL_MAP.items():
        for e in EXPR:
            t = BASE.replace('void func_801BB7B4(u8 arg0) {', sig, 1)
            t = t.replace(DECL, d, 1)
            t = t.replace('next = (arg0 + 1) & 0xFF;', e, 1)
            jobs.append((t, f'{at}_{nt}_{EXPR.index(e)}'))
with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
    rows = list(pool.map(lambda j: score(*j), jobs))
rows.sort()
for r in rows[:16]:
    print(r[2])
