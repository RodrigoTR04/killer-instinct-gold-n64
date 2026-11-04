import sys, importlib.util, tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
spec=importlib.util.spec_from_file_location('cmpm',ROOT/'tools/scratch/nonmatching/T-155/cmp.py'); cm=importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn,draft=sys.argv[1],Path(sys.argv[2])
src,tu=cm.build_source(fn,draft,False)
with tempfile.TemporaryDirectory() as d:
    o=cm.compile_source(src,Path(d)/'c.c'); pairs=cm.draft_raw(o,fn)
for i,(a,ins,r) in enumerate(pairs): print(f'{i:3d} {a:04x} {cm.canon(cm.apply_relocs(ins,r))}')
