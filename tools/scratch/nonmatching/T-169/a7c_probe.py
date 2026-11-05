import importlib.util, concurrent.futures, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

HEAD = '''f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;

f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
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
B = {
 # baseline
 'v0': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
 # scale as s32 local
 'v1': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            s32 sc;
            ratio = amount / radius;
            sc = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * sc) >> 8;
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = ((arg1[i].x * sc) >> 8) + (s32)(ratio * distance);
        }
    }
''',
 # z before x/y stores
 'v2': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
 # y,x into temps then store
 'v3': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            s32 nx, ny;
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            ny = (arg1[i].y * scale) >> 8;
            nx = (arg1[i].x * scale) >> 8;
            arg0[i].y = ny;
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = nx + (s32)(ratio * distance);
        }
    }
''',
 # amount used as f64 local
 'v4': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)(amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
 # no z store (control)
 'v5': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
 # one multu only (control)
 'v6': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = (s32)(ratio * distance);
        }
    }
''',
 # 64-bit shift style
 'v7': '''    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (s16)((arg1[i].y * scale) / 256);
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = (s16)(((arg1[i].x * scale) / 256) + (s32)(ratio * distance));
        }
    }
''',
 # count local copy
 'v8': '''    for (i = 0; i <= count; i++) {
        T169Vertex *s = arg1 + i;
        T169Vertex *d = arg0 + i;
        if (s->z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            d->y = (s->y * scale) >> 8;
            d->z = (s32)((f64)amount * 0.5);
            d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
''',
}
out = Path('tools/scratch/nonmatching/T-169/agen'); out.mkdir(exist_ok=True)
paths=[]
for k,v in B.items():
    p = out/f'q_{k}.c'; p.write_text(HEAD+v+TAIL); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name+' ERR '+str(e)[:60])
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
