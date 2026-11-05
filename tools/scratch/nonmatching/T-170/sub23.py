#!/usr/bin/env python3
"""23C0: drop unused / redundant locals to shrink the 0x98 frame toward 0x70."""
import importlib.util, sys, tempfile, re, itertools, difflib, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801C23C0'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'func_801C23C0.c').read_text()
TARGET = [cm.canon(x) for x in cm.target_raw(fn)]
TARGET = [x for x in TARGET if not x.startswith(('dlabel', 'enddlabel'))]


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


TM = [M(x) for x in TARGET]

m = re.search(r'^u8 func_801C23C0\([^\n]*\{\n', BASE, re.M)
body_start = m.end()
decl_end = BASE.index('    var_f0 = (f32)', body_start)
DECL = BASE[body_start:decl_end]
LINES = [l for l in DECL.splitlines() if l.strip()]
body = BASE[decl_end:]


def score(keep, tag):
    txt = BASE[:body_start] + '\n'.join(keep) + body
    p = outdir / f'z_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception:
        return (9999, 9999, 0, '')
    fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    fr = int(fr.group(1)) if fr else 0
    sm = difflib.SequenceMatcher(None, [M(x) for x in mine], TM, autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad2, fr, f'{tag:20s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} rdiff={bad2:3d} frame=0x{fr:x}')


if __name__ == '__main__':
    print('locals', len(LINES))
    jobs = []
    for n in (1, 2, 3):
        for combo in itertools.combinations(range(len(LINES)), n):
            keep = [l for i, l in enumerate(LINES) if i not in combo]
            jobs.append((keep, 'r' + ''.join(map(str, combo))))
    print('jobs', len(jobs))
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: score(*j), jobs))
    rows.sort()
    for r in rows[:20]:
        print(r[3])
