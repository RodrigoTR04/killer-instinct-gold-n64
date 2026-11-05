#!/usr/bin/env python3
"""BB7B4 variant batch: official words + register-masked diffwords."""
import importlib.util, sys, tempfile, re, difflib
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801BB7B4'
TARGET = None


def target():
    global TARGET
    if TARGET is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        TARGET = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return TARGET


def M(x):
    return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)


def score(txt, tag, outdir):
    p = outdir / f'v_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        src, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(src, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 9999, f'{tag:20s} ERROR {str(e)[-120:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    sm2 = difflib.SequenceMatcher(None, [M(x) for x in th], [M(x) for x in mine], autojunk=False)
    bad2 = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm2.get_opcodes() if t != 'equal')
    fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    frt = re.search(r'addiu sp,sp,-(\d+)', ' '.join(th))
    return (r['words'], bad, f'{tag:20s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} diff={bad:3d} rdiff={bad2:3d} frame={fr.group(1) if fr else "?"}/{"?" if frt is None else frt.group(1)}')


if __name__ == '__main__':
    base = Path(sys.argv[1])
    variants = eval(Path(sys.argv[2]).read_text())
    outdir = base.parent
    B = base.read_text()
    rows = []
    for name, (a, b) in variants.items():
        assert a in B, f'{name}: pattern not found'
        rows.append(score(B.replace(a, b, 1), name, outdir))
    rows.sort()
    for r in rows:
        print(r[2])
