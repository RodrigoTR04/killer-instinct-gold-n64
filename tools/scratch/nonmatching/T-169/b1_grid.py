#!/usr/bin/env python3
"""T-169 1B1A7C: build real candidates in the owning TU; 872 B / 218 instrs is
the target. Pointer walk gives 4x unroll; now find the body that keeps div.s
inside the unrolled copies (target has 5 div.s)."""
import concurrent.futures as cf
import importlib.util
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/b1g'
OUT.mkdir(exist_ok=True)

PRE = '''typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
extern f32 D_802937C0;
'''

HEAD = '''f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
'''

V = {}

V['a_ratio_in'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['a_ratio_in_zfirst'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['a_ratio_in_zlast'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
            arg0->z = (s32) ((f64) amount * 0.5);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['b_radius_global'] = '''    radius = D_802937C0;
    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['b_radius_inloop'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / D_802937C0;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['c_inline'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            arg0->y = (arg1->y * (s16) (s32) (((amount / radius) * 256.0f) + 256.0f)) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * (s16) (s32) (((amount / radius) * 256.0f) + 256.0f)) >> 8) + (s32) ((amount / radius) * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['d_scale_in_ratio_out'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            arg0->y = (arg1->y * (s16) (s32) ((ratio * 256.0f) + 256.0f)) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * (s16) (s32) ((ratio * 256.0f) + 256.0f)) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['e_two_temps'] = '''    {
    s32 sy;
    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            sy = (arg1->y * scale) >> 8;
            arg0->y = sy;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    }
    return (f32) ((f64) amount * 1.5);
}'''

V['f_alias'] = '''    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = *(s16 *) &arg1->y * scale / 256;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = (*(s16 *) &arg1->x * scale / 256) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}'''


def build(name):
    p = OUT / f'{name}.c'
    p.write_text(PRE + HEAD + V[name])
    return p


def score(p):
    try:
        r = dict(screen.measure('func_801B1A7C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:70])


paths = [build(n) for n in V]
with cf.ThreadPoolExecutor(8) as pool:
    for r in sorted(pool.map(score, paths)):
        print(r)
