#!/usr/bin/env python3
"""func_800297A4: 160-word form, reduce one local so the frame returns to 0x48."""
from pathlib import Path
OUT = Path('/tmp/v297u')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

BODY = '''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->axisY[j] = 0.0f;
            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            fl[j] = 0;
        } else if (j < 8) {
            p->axisX[j] = 0.0f;
            p->axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            p->axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            fl[j] = 0;
        } else {
            p->axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            p->axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            p->axisZ[j] = 0.0f;
            fl[j] = 1;
        }
        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        p->position[j] = (float) (u32) (func_800326F0() & 15);
        p->age[j] = 0;
        dur[j] = life - (func_800326F0() & 7);
    }
}
'''

HDR = '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    dur = p->duration;
    fl = p->flags;
'''

V = {}
# u1: reuse i as j (i is dead after the scan)
V['u1'] = ('''    T171Burst *p;
    s32 i, angle;
    s16 *dur;
    u8 *fl;
    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''' + HDR).replace('j', 'j')
V['u1'] = V['u1']
# build u1 by using `i` in place of `j` in the body
u1_body = BODY.replace('j', 'i')
V['u1'] = ('''    T171Burst *p;
    s32 i, angle;
    s16 *dur;
    u8 *fl;
    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''' + HDR + u1_body)
# u2: angle only, one counter
V['u2'] = ('''    T171Burst *p;
    s32 i, angle;
    s16 *dur;
    u8 *fl;
    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''' + HDR + BODY.replace('for (j = 0; j < 12; j++, angle += 90)', 'for (j = 0; j < 12; angle += 90, j++)'))
# u3: no fl cursor, dur only, plus a j counter
V['u3'] = ('''    T171Burst *p;
    s32 i, j, angle;
    s16 *dur;
    u8 *fl;
    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''' + HDR + BODY)

for k, body in V.items():
    (OUT / f'{k}.c').write_text(HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n' + body)
print(len(V))
