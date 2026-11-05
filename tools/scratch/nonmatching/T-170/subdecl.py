#!/usr/bin/env python3
"""Brute-force subsets of the draft's local declarations to find frame 0x20."""
import importlib.util, sys, tempfile, re, itertools, difflib, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = sys.argv[1]
base = Path(sys.argv[2]).read_text()
outdir = Path(sys.argv[2]).parent

m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{\n', base, re.M)
body_start = m.end()
decl_end = base.index('\n\n', body_start)
DECL = base[body_start:decl_end]
LINES = [l for l in DECL.splitlines() if l.strip() and not l.strip().startswith('/*')]
print('locals:', len(LINES))
TARGET = [cm.canon(x) for x in cm.target_raw(fn)]
TARGET = [x for x in TARGET if not x.startswith(('dlabel', 'enddlabel'))]


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


TM = [M(x) for x in TARGET]


def score(keep, tag):
    txt = base[:body_start] + '\n'.join(keep) + base[decl_end:]
    p = outdir / f's_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 9999, 999, f'{tag:26s} ERROR')
    fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    fr = int(fr.group(1)) if fr else 0
    sm = difflib.SequenceMatcher(None, [M(x) for x in mine], TM, autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad2, fr, f'{tag:26s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} rdiff={bad2:3d} frame=0x{fr:x}')


jobs = []
for n in (0, 1, 2, 3):
    for combo in itertools.combinations(range(len(LINES)), n):
        keep = [l for i, l in enumerate(LINES) if i not in combo]
        jobs.append((keep, 'rm' + ''.join(str(c) for c in combo)))
with concurrent.futures.ThreadPoolExecutor(max_workers=10) as pool:
    rows = list(pool.map(lambda j: score(*j), jobs))
rows.sort()
for r in rows[:25]:
    print(r[3])
