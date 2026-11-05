#!/usr/bin/env python3
"""23C0: shrink the frame 0x98 -> 0x70 by removing named locals / restructuring."""
import importlib.util, sys, tempfile, re, difflib, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
fn = 'func_801C23C0'
T = None


def target():
    global T
    if T is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        T = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return T


def score(txt, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'n_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 9999, tag, f'{tag:20s} ERROR {str(e)[-90:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    frame = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    fr = frame.group(1) if frame else '?'
    return (r['words'], bad, tag, f'{tag:20s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} frame={fr} diff={bad:3d}')


BASE = (ROOT / 'tools/scratch/nonmatching/T-170/func_801C23C0.c').read_text()
if __name__ == '__main__':
    variants = json.loads(Path(sys.argv[1]).read_text())
    res = []
    for name, pairs in variants.items():
        s = BASE
        ok = True
        for a, b in pairs:
            if a not in s:
                print(f'SKIP {name}: {a[:50]!r}')
                ok = False
                break
            s = s.replace(a, b)
        if not ok:
            continue
        res.append(score(s, name))
    for w, b, t, line in sorted(res):
        print(line, flush=True)
