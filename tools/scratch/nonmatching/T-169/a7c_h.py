import importlib.util, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

HEAD = '''f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
'''
TAIL = '''    return (f32)((f64)amount * onePointFive);
}
'''
V = {
'h0': '''    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    f64 half = 0.5;
    f64 onePointFive = 1.5;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * half);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
'h1': '''    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    f32 radiusScale = 256.0f;
    f64 half = 0.5;
    f64 onePointFive = 1.5;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * radiusScale) + radiusScale);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * half);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
'h2': '''    f64 onePointFive = 1.5;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    f64 half = 0.5;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * half);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
'h3': '''    f64 half = 0.5;
    f64 onePointFive = 1.5;
    f32 halfBack = half;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * half);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
}
out = Path('tools/scratch/nonmatching/T-169/agen'); out.mkdir(exist_ok=True)
paths=[]
for k,v in V.items():
    p = out/f'{k}.c'; p.write_text(HEAD+v+TAIL); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name+' ERR '+str(e)[:80])
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
