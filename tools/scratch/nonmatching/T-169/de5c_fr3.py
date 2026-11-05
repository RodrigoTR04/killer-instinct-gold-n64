import importlib.util, concurrent.futures, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)

base = Path('tools/scratch/nonmatching/T-169/fr/v3_nospan.c').read_text()
out = Path('tools/scratch/nonmatching/T-169/fr3'); out.mkdir(exist_ok=True)

DECL = '''    s32 mx;
    s32 my;
    s32 dx;
    s32 dx0;
    s32 dy;
    s32 dyb;
    s32 rx;
    s32 ry;
    u32 areaW;
    u32 areaH;
    T022Sprite *sprite;
'''
# variants: keep span locals but compute lazily at the compare site
V = {
 'a_spans':   DECL,
 'b_nospan':  DECL.replace('    s32 dx0;\n', '    s32 dx0;\n'),
}
# variant: restore spanX/spanY as *locals assigned where first used* (they are
# genuinely reused: once in the compare, once in the call)
def withspans(decl):
    return decl
paths = []
# candidate 1: spans reintroduced but only as expressions bound once, used twice
p1 = base.replace('''    if (arg1 != 0) {
        if (bx2 + dx >= x2) {
            rx = bx2 + dx;
        }
        if (by2 + dyb >= y2) {
            ry = by2 + dyb;
        }
    }''', '''    if (arg1 != 0) {
        s32 spanX = bx2 + dx;
        s32 spanY = by2 + dyb;
        if (spanX >= x2) {
            rx = spanX;
        }
        if (spanY >= y2) {
            ry = spanY;
        }
    }''').replace('((ry - (by2 + dyb)) << 16) | dyb', '((ry - y2) << 16) | dyb')
p = out/'c1.c'; p.write_text(p1); paths.append(p)

def info(path):
    r = dict(screen.measure('func_8001DE5C', path))
    source, tu = cm.build_source('func_8001DE5C', path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, 'func_8001DE5C')
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    fr = next((-int(m.split(',')[-1]) for m in mine if m.startswith('addiu sp,sp,-')), 0)
    return r['words'], r['compiled'], fr, len(mine)
for p in paths: print(p.name, info(p))
print('target frame 104 (0x68), target instr 150')
