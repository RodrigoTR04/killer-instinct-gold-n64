#!/usr/bin/env python3
"""T-169 1B1A7C: the target is a hand-unrolled 4-wide loop (stride 4, four
explicit copies, remainder loop). Write the body out four times at stride 4 --
no for-loop unrolling involved -- and see whether IDO then keeps div.s per copy.
"""
import concurrent.futures as cf
import importlib.util
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/b1u'
OUT.mkdir(exist_ok=True)

PRE = '''typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
'''

# one copy of the per-vertex work, at element offset `k`
def copy(k, ivar='i'):
    idx = f'{ivar} + {k}' if k else ivar
    return f'''        if (arg1[{idx}].z >= 6) {{
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[{idx}].y = (arg1[{idx}].y * scale) >> 8;
            arg0[{idx}].z = (s32) ((f64) amount * 0.5);
            arg0[{idx}].x = ((arg1[{idx}].x * scale) >> 8) + (s32) (ratio * distance);
        }}
'''


def build_stride4():
    body = ''.join(copy(k) for k in range(4))
    return PRE + f'''f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {{
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    s32 n;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i + 3 <= count; i += 4) {{
{body}    }}
    for (; i <= count; i++) {{
        if (arg1[i].z >= 6) {{
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32) ((f64) amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32) (ratio * distance);
        }}
    }}
    return (f32) ((f64) amount * 1.5);
}}
'''


def build_pointer_stride4():
    one = '''        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
'''
    body = ''.join(one for _ in range(4))
    return PRE + f'''f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {{
    T169Vertex *dst = arg0v;
    T169Vertex *src = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i + 3 <= count; i += 4) {{
{body}    }}
    for (; i <= count; i++) {{
        if (src->z >= 6) {{
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }}
        src++; dst++;
    }}
    return (f32) ((f64) amount * 1.5);
}}
'''


def score(p):
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], r['original'], p.name)
    except Exception as e:
        return (10**6, 0, 0, p.name + ' ' + str(e)[:90])


variants = {'stride4': build_stride4(), 'ptr_stride4': build_pointer_stride4()}
paths = []
for n, t in variants.items():
    p = OUT / f'{n}.c'
    p.write_text(t)
    paths.append(p)
with cf.ThreadPoolExecutor(2) as pool:
    for row in sorted(pool.map(score, paths)):
        print(row)
