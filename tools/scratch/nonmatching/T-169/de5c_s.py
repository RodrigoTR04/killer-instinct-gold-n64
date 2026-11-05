import importlib.util, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-162/func_8001DE5C.c').read_text()
i = base.index('    struct {')
j = base.index('    if (arg1 != 0) {')
STRUCT = '''    struct {
        s32 x;
        s32 y;
        s32 x2;
        s32 y2;
    } b;
'''
scal = '''    s32 mx;
    s32 my;
    s32 dx;
    s32 dx0;
    s32 dy;
    s32 dyb;
    s32 spanX;
    s32 spanY;
    s32 rx;
    s32 ry;
    u32 areaW;
    u32 areaH;
    T022Sprite *sprite;
'''
pre = base[:i]; post = base[j:]
VAR = {
 # struct first (current)
 's0': STRUCT + scal,
 # struct last
 's1': scal + STRUCT,
 # struct after half the scalars
 's2': '''    s32 mx;
    s32 my;
    s32 dx;
    s32 dx0;
''' + STRUCT + '''    s32 dy;
    s32 dyb;
    s32 spanX;
    s32 spanY;
    s32 rx;
    s32 ry;
    u32 areaW;
    u32 areaH;
    T022Sprite *sprite;
''',
 # struct after 3
 's3': '''    s32 mx;
    s32 my;
    s32 dx;
''' + STRUCT + '''    s32 dx0;
    s32 dy;
    s32 dyb;
    s32 spanX;
    s32 spanY;
    s32 rx;
    s32 ry;
    u32 areaW;
    u32 areaH;
    T022Sprite *sprite;
''',
}
out = Path('tools/scratch/nonmatching/T-169/ds'); out.mkdir(exist_ok=True)
paths = []
for k, v in VAR.items():
    p = out/f'{k}.c'
    p.write_text(pre + v + post)
    paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001DE5C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(4) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
