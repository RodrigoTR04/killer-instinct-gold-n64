#!/usr/bin/env python3
"""func_800297A4: exhaustive loop-shape enumeration for the scan.

Target:
    lh   t6, 0x12C(v0)
    bltzl t6, LOUT           ; branch-likely + delay slot
    addiu at, zero, 4
    addiu v1, v1, 1
    slti  at, v1, 4
    bnez  at, LOOP
    addiu v0, v0, 0x140
    addiu at, zero, 4
LOUT:
    bne   v1, at, ...
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297z')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

SCANS = {
'l01': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l02': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0 && i < 4) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l03': '''    p = (T171Burst *) D_80061D60;
    for (i = 0; i < 4; i++, p++) if (p->timer < 0) break;
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l04': '''    p = (T171Burst *) D_80061D60;
    for (i = 0; i < 4; i++) { if (p->timer < 0) break; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l05': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    do {
        if (p->timer < 0) break;
        i++;
        p++;
    } while (i != 4);
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l06': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (1) {
        if (p->timer < 0) break;
        if (++i == 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l07': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    for (; p->timer >= 0; p++) {
        if (++i == 4) break;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l08': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        p++;
        if (++i == 4) break;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l09': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i = i + 1;
        if (i > 3) break;
        p = p + 1;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l10': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i < 4) p++;
        else break;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l11': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i != 4) { p++; continue; }
        break;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'l12': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (i < 4) {
        if (p->timer < 0) break;
        i++;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
}

BODY = '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    angle = 0;
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

for k, scan in SCANS.items():
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += '    T171Burst *p;\n    s32 i, j, angle;\n' + scan + BODY
    (OUT / f'{k}.c').write_text(src)
print(len(SCANS))
