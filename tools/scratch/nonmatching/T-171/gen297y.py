#!/usr/bin/env python3
"""func_800297A4: same 195 instructions as the target; the gap is where the
base address and the timer load land relative to the register saves.

Target: addiu sp / sdc1 f20 / lui v0,hi / mtc1 a2,f20 / sw ra ... / addiu v0,lo /
or v1,zero,zero / lh t6,0x12C(v0) / bltzl

So the lui(hi) is emitted early but the addiu(lo) only after the saves. Try
initialising p in its declaration (the initialiser is the first statement) vs
assigning it later.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297y')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

DECLS = {
'd1': '    T171Burst *p = (T171Burst *) D_80061D60;\n    s32 i = 0, j, angle = 0;\n',
'd2': '    T171Burst *p;\n    s32 i, j, angle;\n',
'd3': '    s32 i, j, angle;\n    T171Burst *p = (T171Burst *) D_80061D60;\n',
'd4': '    T171Burst *p;\n    s32 i = 0;\n    s32 j;\n    s32 angle;\n',
}

PRE = {
'p1': '',
'p2': '    p = (T171Burst *) D_80061D60;\n    i = 0;\n',
'p3': '    i = 0;\n    p = (T171Burst *) D_80061D60;\n',
}

SCAN = '''    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

BODY = '''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->axisY[j] = 0.0f;
            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            p->flags[j] = 0;
        } else if (j < 8) {
            p->axisX[j] = 0.0f;
            p->axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            p->axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->flags[j] = 0;
        } else {
            p->axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            p->axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            p->axisZ[j] = 0.0f;
            p->flags[j] = 1;
        }
        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        p->position[j] = (float) (u32) (func_800326F0() & 15);
        p->age[j] = 0;
        p->duration[j] = life - (func_800326F0() & 7);
    }
}
'''

n = 0
for dk, d in DECLS.items():
    for pk, pre in PRE.items():
        if dk in ('d1', 'd3') and pk != 'p1':
            continue
        src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
        src += d + pre + SCAN + BODY
        (OUT / f'{dk}_{pk}.c').write_text(src)
        n += 1
print(n)
