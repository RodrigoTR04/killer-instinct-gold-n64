import importlib.util, concurrent.futures, re, tempfile, subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)

HDR = '''f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
'''
BODY = '''            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32)((f64)amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
'''
TAIL = '''    return (f32)((f64)amount * 1.5);
}
'''
LOOPS = {
 'L0': lambda b: f'''    for (i = 0; i <= count; i++) {{
        if (arg1[i].z >= 6) {{
{b}        }}
    }}
''',
 'L1': lambda b: f'''    for (i = count; i >= 0; i--) {{
        if (arg1[i].z >= 6) {{
{b}        }}
    }}
''',
 'L2': lambda b: f'''    i = count + 1;
    while (i--) {{
        if (arg1[i].z >= 6) {{
{b}        }}
    }}
''',
 'L3': lambda b: f'''    for (i = 0; i < count + 1; i++) {{
        if (arg1[i].z >= 6) {{
{b}        }}
    }}
''',
 'L4': lambda b: f'''    i = 0;
    do {{
        if (arg1[i].z >= 6) {{
{b}        }}
    }} while (i++ < count);
''',
 'L5': lambda b: f'''    for (i = -1; i < count; i++) {{
        if (arg1[i + 1].z >= 6) {{
{b}        }}
    }}
''',
}
# unrolled pointer walk: i as element counter, separate pointers
PTRBODY = '''            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            d->y = (s->y * scale) >> 8;
            d->z = (s32)((f64)amount * 0.5);
            d->x = ((s->x * scale) >> 8) + (s32)(ratio * distance);
'''
PTRLOOPS = {
 'P0': f'''    {{ T169Vertex *s = arg1; T169Vertex *d = arg0; s32 n = count + 1;
    while (n--) {{
        if (s->z >= 6) {{
{PTRBODY}        }}
        s++; d++;
    }} }}
''',
 'P1': f'''    {{ T169Vertex *s = arg1; T169Vertex *d = arg0;
    for (i = 0; i <= count; i++, s++, d++) {{
        if (s->z >= 6) {{
{PTRBODY}        }}
    }} }}
''',
 'P2': f'''    {{ T169Vertex *s = arg1; T169Vertex *d = arg0;
    for (i = count; i >= 0; i--, s++, d++) {{
        if (s->z >= 6) {{
{PTRBODY}        }}
    }} }}
''',
}
out = Path('tools/scratch/nonmatching/T-169/aloo'); out.mkdir(exist_ok=True)
paths=[]
for k, f in LOOPS.items():
    p = out/f'{k}.c'; p.write_text(HDR + f(BODY) + TAIL); paths.append(p)
for k, t in PTRLOOPS.items():
    p = out/f'{k}.c'; p.write_text(HDR + t + TAIL); paths.append(p)
def run(p):
    source, tu = cm.build_source('func_801B1A7C', p, False)
    with tempfile.TemporaryDirectory() as td:
        try:
            o = cm.compile_source(source, Path(td)/'c.c')
        except SystemExit:
            return (p.name, 'ERR', '')
        pairs = cm.draft_raw(o, 'func_801B1A7C')
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    masks = [m for m in mine if re.match(r'andi \w+,\w+,\d+$', m)]
    return (p.name, len(mine), masks)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in pool.map(run, paths): print(r)
