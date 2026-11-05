#!/usr/bin/env python3
"""func_800297A4: hoist angle-30 / angle-570 into block-scoped locals."""
from pathlib import Path
OUT = Path('/tmp/v297f')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

SEARCH = {
'w': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (i < 4 && p->timer >= 0) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'tf': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0 && i < 4) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'idx': '''    i = 0;
    while (i < 4 && ((T171Burst *) D_80061D60)[i].timer >= 0) i++;
    if (i == 4) i = 0;
    p = (T171Burst *) D_80061D60 + i;
''',
}

BODY = '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    for (j = 0; j < 12; j++, angle += 90) {
        s32 base = angle - 30;
        if (j < 4) {
            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->axisY[j] = 0.0f;
            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + base);
            p->flags[j] = 0;
        } else if (j < 8) {
            p->axisX[j] = 0.0f;
            p->axisY[j] = (float) (u32) ((func_800326F0() & 63) + (angle - 570));
            p->axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->flags[j] = 0;
        } else {
            p->axisX[j] = (float) (u32) ((func_800326F0() & 63) + base);
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

for k, search in SEARCH.items():
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += '    T171Burst *p;\n    s32 i, j, angle;\n'
    src += search + '    angle = 0;\n' + BODY
    (OUT / f'{k}.c').write_text(src)
print(len(SEARCH))
