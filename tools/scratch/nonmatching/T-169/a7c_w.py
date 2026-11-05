import importlib.util, concurrent.futures
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
'w0': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        for (i = 0; i <= count; i++) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
            s++;
            d++;
        }
    }
''',
'w1': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        for (i = 0; i <= count; i++, s++, d++) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
        }
    }
''',
'w2': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        s32 n = count + 1;
        for (i = 0; i < n; i++) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
            s++;
            d++;
        }
    }
''',
'w3': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        for (i = 0; i <= count; i++, s = (T169Vertex *)((u8 *)s + 16), d = (T169Vertex *)((u8 *)d + 16)) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
        }
    }
''',
'w4': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        for (i = 0; i <= count; i++) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
            s++;
            d++;
        }
        arg0 = d;
        arg1 = s;
    }
''',
'w5': '''    {
        T169Vertex *s = arg1;
        T169Vertex *d = arg0;
        for (i = 0; i <= count; i++) {
            if (s->z >= 6) {
                ratio = amount / radius;
                scale = (s32)((ratio * 256.0f) + 256.0f);
                d->y = (s->y * scale) >> 8;
                d->z = (s32)((f64)amount * 0.5);
                d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
            }
            s = s + 1;
            d = d + 1;
        }
    }
''',
}
out = Path('tools/scratch/nonmatching/T-169/agen'); out.mkdir(exist_ok=True)
paths=[]
for k,v in B.items():
    p = out/f'{k}.c'; p.write_text(HEAD+v+TAIL); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name+' ERR '+str(e)[:60])
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
