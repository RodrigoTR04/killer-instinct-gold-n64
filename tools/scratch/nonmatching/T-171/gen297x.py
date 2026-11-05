#!/usr/bin/env python3
"""func_800297A4: the header is written through the *indexed* slot while the scan
pointer p is kept only for the timer test; the target copies v1 into a1
(`or a1, v1, zero`) right after the scan, which is the index being handed to the
slot expression."""
from pathlib import Path
OUT = Path('/tmp/v297x')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
#define E ((T171Burst *) D_80061D60)
'''

SCANS = {
# x1: p for the scan, i for the header (no reset of p when i == 4)
'x1': '''    p = E;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) i = 0;
    E[i].z = z;
    E[i].x = x;
    E[i].y = y;
    E[i].timer = 0;
    E[i].limit = life;
    E[i].kind = kind;
''',
# x2: same but p is recomputed after
'x2': '''    p = E;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) i = 0;
    p = E + i;
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
''',
# x3: no p at all, timer read through E[i]
'x3': '''    i = 0;
    while (E[i].timer >= 0) {
        i++;
        if (i >= 4) break;
    }
    if (i == 4) i = 0;
    E[i].z = z;
    E[i].x = x;
    E[i].y = y;
    E[i].timer = 0;
    E[i].limit = life;
    E[i].kind = kind;
''',
}

BODY = '''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
            E[i].axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            E[i].axisY[j] = 0.0f;
            E[i].axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            E[i].flags[j] = 0;
        } else if (j < 8) {
            E[i].axisX[j] = 0.0f;
            E[i].axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            E[i].axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            E[i].flags[j] = 0;
        } else {
            E[i].axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            E[i].axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            E[i].axisZ[j] = 0.0f;
            E[i].flags[j] = 1;
        }
        E[i].velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        E[i].position[j] = (float) (u32) (func_800326F0() & 15);
        E[i].age[j] = 0;
        E[i].duration[j] = life - (func_800326F0() & 7);
    }
}
'''

for k, scan in SCANS.items():
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += '    T171Burst *p;\n    s32 i, j, angle;\n' + scan + BODY
    (OUT / f'{k}.c').write_text(src)
print(len(SCANS))
