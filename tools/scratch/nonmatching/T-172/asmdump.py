"""Dump a draft's own disassembly for one function (canonical lines from cmp.py)."""
import importlib.util, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cmp = importlib.util.module_from_spec(spec); spec.loader.exec_module(cmp)
fn, draft = sys.argv[1], Path(sys.argv[2])
if not draft.is_absolute(): draft = ROOT / draft
source, tu = cmp.build_source(fn, draft)
with tempfile.TemporaryDirectory() as d:
    o = cmp.compile_source(source, Path(d) / 'c.c')
    pairs = cmp.draft_raw(o, fn)
for _, ins, rels in pairs:
    print(cmp.canon(cmp.apply_relocs(ins, rels)))
