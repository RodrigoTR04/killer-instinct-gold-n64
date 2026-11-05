import importlib.util, itertools, concurrent.futures, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

HEAD = '''f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
'''
TAIL = '''    return (f32)((f64)amount * 1.5);
}
'''
LOOPC = {
 'l0': 'for (i = 0; i <= count; i++) {',
 'l1': 'for (i = 0; count >= i; i++) {',
 'l2': 'for (i = count; i >= 0; i--) {',
 'l3': 'for (i = 0; i < count + 1; i++) {',
}
COND = {'c0': 'arg1[i].z >= 6', 'c1': 'arg1[i].z > 5', 'c2': '6 <= arg1[i].z'}
SCALE = {'s0': 'scale = (s32)((ratio * 256.0f) + 256.0f);', 's1': 'scale = (s16)((ratio * 256.0f) + 256.0f);'}
Y = {'y0': 'arg0[i].y = (arg1[i].y * scale) >> 8;', 'y1': 'arg0[i].y = (s16)((arg1[i].y * scale) >> 8);'}
Z = {'z0': 'arg0[i].z = (s32)((f64)amount * 0.5);', 'z1': 'arg0[i].z = (s16)((f64)amount * 0.5);', 'z2': 'arg0[i].z = (s32)(amount * 0.5);'}
X = {'x0': 'arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);',
     'x1': 'arg0[i].x = (arg1[i].x * scale >> 8) + (s32)(ratio * distance);',
     'x2': 'arg0[i].x = (s16)(((arg1[i].x * scale) >> 8) + (s32)(ratio * distance));'}
ORDS = {'o0': ('y','z','x'), 'o1': ('x','y','z'), 'o2': ('z','y','x')}
def body(lc, cd, sc, y, z, x, od):
    parts = {'y': '            '+y, 'z': '            '+z, 'x': '            '+x}
    lines = ['    '+lc, '        if ('+cd+') {', '            ratio = amount / radius;', '            '+sc]
    lines += [parts[k] for k in od]
    lines += ['        }', '    }']
    return '\n'.join(lines)+'\n'
out = Path('tools/scratch/nonmatching/T-169/abf'); out.mkdir(exist_ok=True)
paths = []
for lc, cd, sc, y, z, x, od in itertools.product(LOOPC, COND, SCALE, Y, Z, X, ORDS):
    txt = HEAD + body(LOOPC[lc], COND[cd], SCALE[sc], Y[y], Z[z], X[x], ORDS[od]) + TAIL
    n = f'{lc}{cd}{sc}{y}{z}{x}{"".join(ORDS[od])}.c'
    p = out/n; p.write_text(txt); paths.append((p, (lc,cd,sc,y,z,x,od)))
print('n', len(paths))
def run(item):
    p, key = item
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], p.name, key)
    except Exception:
        return (9999, 0, p.name, key)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:14]: print(r)
