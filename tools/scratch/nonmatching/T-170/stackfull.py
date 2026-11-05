#!/usr/bin/env python3
"""Full stack-offset map (all offsets) for target vs draft, plus frame."""
import importlib.util, sys, tempfile, re
from collections import Counter
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn = sys.argv[1]


def sl(lines):
    c = Counter()
    for l in lines:
        m = re.match(r'^(\w+) [\w,]+?,\s*(-?\d+)\(sp\)$', l)
        if m:
            c[(m.group(1), int(m.group(2)))] += 1
    return c


th = [cm.canon(t) for t in cm.target_raw(fn)]
th = [t for t in th if not t.startswith(('dlabel', 'enddlabel'))]
a = sl(th)
for d in sys.argv[2:]:
    p = Path(d)
    src, tu = cm.build_source(fn, p, False)
    with tempfile.TemporaryDirectory() as dd:
        o = cm.compile_source(src, Path(dd)/'c.c')
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    b = sl(mine)
    fa = re.search(r'addiu sp,sp,-(\d+)', ' '.join(th))
    fb = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    print(f'== {p.name}  frame {fa.group(1) if fa else "?"} -> {fb.group(1) if fb else "?"}  instr {len(th)} -> {len(mine)}')
    for k in sorted(set(a) | set(b), key=lambda k: k[1]):
        if a[k] != b[k]:
            print(f'   {k[0]:6s} {k[1]:4d} (0x{k[1]:02x})  target={a[k]} draft={b[k]}')
