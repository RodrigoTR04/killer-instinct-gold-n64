#!/usr/bin/env python3
"""func_800297A4: cursor locals for the three element widths, matching the target's
s0 (f32 stride 4), s5 (s16 stride 2) and s3 (u8 stride 1) cursors."""
from pathlib import Path
OUT = Path('/tmp/v297j')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

SEARCH = '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (i < 4 && p->timer >= 0) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    f = p->axisX; a = p->age; fl = p->flags;
    angle = 0;
    for (j = 0; j < 12; j++, angle += 90, f++, a++, fl++) {
        if (j < 4) {
            f[0] = (float) (u32) (7 - (func_800326F0() & 15));
            f[12] = 0.0f;
            f[24] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            fl[0] = 0;
        } else if (j < 8) {
            f[0] = 0.0f;
            f[12] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            f[24] = (float) (u32) (7 - (func_800326F0() & 15));
            fl[0] = 0;
        } else {
            f[0] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            f[12] = (float) (u32) (97 - (func_800326F0() & 15));
            f[24] = 0.0f;
            fl[0] = 1;
        }
        f[36] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        f[48] = (float) (u32) (func_800326F0() & 15);
        a[0] = 0;
        a[12] = life - (func_800326F0() & 7);
    }
}
'''

src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
src += '    T171Burst *p;\n    s32 i, j, angle;\n    float *f;\n    s16 *a;\n    u8 *fl;\n'
src += SEARCH
(OUT / 'a.c').write_text(src)

# variant: separate pointers, all from p and indexed by j
src2 = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
src2 += '    T171Burst *p;\n    s32 i, j, angle;\n    float *ax, *ay, *az, *vel, *pos;\n    s16 *age, *dur;\n    u8 *flags;\n'
src2 += '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (i < 4 && p->timer >= 0) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    ax = p->axisX; ay = p->axisY; az = p->axisZ;
    vel = p->velocity; pos = p->position;
    age = p->age; dur = p->duration; flags = p->flags;
    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
            ax[j] = (float) (u32) (7 - (func_800326F0() & 15));
            ay[j] = 0.0f;
            az[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            flags[j] = 0;
        } else if (j < 8) {
            ax[j] = 0.0f;
            ay[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            az[j] = (float) (u32) (7 - (func_800326F0() & 15));
            flags[j] = 0;
        } else {
            ax[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            ay[j] = (float) (u32) (97 - (func_800326F0() & 15));
            az[j] = 0.0f;
            flags[j] = 1;
        }
        vel[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        pos[j] = (float) (u32) (func_800326F0() & 15);
        age[j] = 0;
        dur[j] = life - (func_800326F0() & 7);
    }
}
'''
(OUT / 'b.c').write_text(src2)
print(2)
