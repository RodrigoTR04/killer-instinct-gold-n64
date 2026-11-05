import importlib.util, sys, tempfile, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn, draft = sys.argv[1], Path(sys.argv[2])
src, tu = cm.build_source(fn, draft, False)
with tempfile.TemporaryDirectory() as d:
    o = cm.compile_source(src, Path(d)/'c.c'); pairs = cm.draft_raw(o, fn)
mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel','enddlabel'))]
def slots(lines):
    out = {}
    for l in lines:
        m = re.search(r'(\w+) (\w+),(\d+)\(sp\)$', l)
        if m: out.setdefault(int(m.group(3)), []).append(l)
    return out
a, b = slots(theirs), slots(mine)
for k in sorted(set(a)|set(b)):
    print(f'0x{k:02X}: T={len(a.get(k,[]))} D={len(b.get(k,[]))}   {a.get(k,[""])[0]:34s} | {b.get(k,[""])[0]}')
