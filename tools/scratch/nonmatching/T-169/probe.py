"""probe.py FN DRAFT : print draft instruction stream positions a..b (masked regs off)."""
import sys, importlib.util, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn = sys.argv[1]; lo, hi = int(sys.argv[2]), int(sys.argv[3])
for d in sys.argv[4:]:
    p = Path(d)
    source, tu = cm.build_source(fn, p, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    print('==', p.name, len(mine))
    for i in range(lo, min(hi, len(mine))):
        print(f'{i:4d} {mine[i]}')
