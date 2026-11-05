import importlib.util, itertools, concurrent.futures, tempfile, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-169/de5c_base.c').read_text()
out = Path('tools/scratch/nonmatching/T-169/fr'); out.mkdir(exist_ok=True)

def info(path):
    r = dict(screen.measure('func_8001DE5C', path))
    source, tu = cm.build_source('func_8001DE5C', path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, 'func_8001DE5C')
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    fr = next((-int(m.split(',')[-1]) for m in mine if m.startswith('addiu sp,sp,-')), 0)
    return r['words'], r['compiled'], fr, len(mine)

# Candidate rewrites that remove one live-across-call value
V = {}
V['v0_base'] = base
# y2 computed late (already), try removing spanY by folding into ry directly
V['v1_fold'] = base.replace('''    spanX = bx2 + dx;''', '''    spanX = bx2 + dx;''')
# write the final call args from x2/y2 instead of keeping spanY
V['v2_nospany'] = (base.replace('    s32 spanY;\n', '')
    .replace('    spanY = by2 + dyb;\n', '')
    .replace('''        if (spanY >= y2) {
            ry = spanY;
        }''', '''        if (by2 + dyb >= y2) {
            ry = by2 + dyb;
        }''')
    .replace('((ry - spanY) << 16) | dyb', '((ry - (by2 + dyb)) << 16) | dyb'))
# drop spanX too
V['v3_nospan'] = (V['v2_nospany'].replace('    s32 spanX;\n', '')
    .replace('    spanX = bx2 + dx;\n', '')
    .replace('''        if (spanX >= x2) {
            rx = spanX;
        }''', '''        if (bx2 + dx >= x2) {
            rx = bx2 + dx;
        }'''))
for k, v in V.items():
    p = out/f'{k}.c'; p.write_text(v)
for k in V:
    p = out/f'{k}.c'
    print(k, info(p))
