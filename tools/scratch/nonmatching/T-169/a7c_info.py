import sys, importlib.util, re, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT/'tools/scratch/nonmatching/T-155'))
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)
fn = sys.argv[1]
for d in sys.argv[2:]:
    path = Path(d)
    r = dict(screen.measure(fn, path))
    source, tu = cm.build_source(fn, path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    mask = [m for m in mine if re.match(r'andi \w+,\w+,\d+$', m)]
    nmul = sum(1 for m in mine if m.startswith('multu'))
    print(f'{d}: words={r["words"]} bytes={r["compiled"]} ninstr={len(mine)} masks={mask} multu={nmul}')
