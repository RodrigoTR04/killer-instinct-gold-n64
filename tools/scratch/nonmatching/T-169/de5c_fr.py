import importlib.util, itertools, concurrent.futures, re, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)

base = Path('tools/scratch/nonmatching/T-169/de5c_base.c').read_text()
out = Path('tools/scratch/nonmatching/T-169/fr'); out.mkdir(exist_ok=True)

def frame(path):
    source, tu = cm.build_source('func_8001DE5C', path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, 'func_8001DE5C')
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    for m in mine:
        if m.startswith('addiu sp,sp,-'):
            return -int(m.split(',')[-1]), len(mine)
    return 0, len(mine)

paths = [Path('tools/scratch/nonmatching/T-169/de5c_base.c')]
print('base', frame(paths[0]))
