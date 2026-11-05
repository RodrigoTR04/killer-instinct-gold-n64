#!/usr/bin/env python3
import importlib.util, sys, tempfile, re
from collections import Counter, defaultdict
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn = sys.argv[1]
def sl(lines):
    c = defaultdict(list)
    for l in lines:
        m = re.match(r'^(\w+) [\w,]+?,\s*(-?\d+)\(sp\)$', l)
        if m: c[int(m.group(2))].append(m.group(1))
    return c
th = [cm.canon(t) for t in cm.target_raw(fn)]
th = [t for t in th if not t.startswith(('dlabel','enddlabel'))]
a = sl(th)
p = Path(sys.argv[2])
src, tu = cm.build_source(fn, p, False)
with tempfile.TemporaryDirectory() as dd:
    o = cm.compile_source(src, Path(dd)/'c.c')
    pairs = cm.draft_raw(o, fn)
mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
b = sl(mine)
fa = re.search(r'addiu sp,sp,-(\d+)', ' '.join(th)); fb = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
print(f'frame {fa.group(1)} -> {fb.group(1)}')
for k in sorted(set(a)|set(b)):
    t = ','.join(a.get(k,[])) or '-'; d = ','.join(b.get(k,[])) or '-'
    mark = '' if t == d else '   <<<'
    print(f'0x{k:02x} {k:4d}  target={t:22s} draft={d}{mark}')
