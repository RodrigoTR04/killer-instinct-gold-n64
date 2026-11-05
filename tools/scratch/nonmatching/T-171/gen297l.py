#!/usr/bin/env python3
"""func_800297A4: mixed addressing - axis/velocity/position through p, age/duration
and flags through their own cursors (the target keeps s5 = 2*index for s16 and
s3 = index for u8, so those two arrays are addressed off a separate cursor)."""
from pathlib import Path
OUT = Path('/tmp/v297l')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

SCAN = {
'p': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (i < 4 && p->timer >= 0) { i++; p++; }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
'brk': '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
''',
}

def body(cur):
    return '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
    age = p->age; dur = p->duration; flags = p->flags;
    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->axisY[j] = 0.0f;
            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            flags[j] = 0;
        } else if (j < 8) {
            p->axisX[j] = 0.0f;
            p->axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            p->axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            flags[j] = 0;
        } else {
            p->axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            p->axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            p->axisZ[j] = 0.0f;
            flags[j] = 1;
        }
        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        p->position[j] = (float) (u32) (func_800326F0() & 15);
        age[j] = 0;
        dur[j] = life - (func_800326F0() & 7);
    }
}
'''

for k, scan in SCAN.items():
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += '    T171Burst *p;\n    s32 i, j, angle;\n    s16 *age, *dur;\n    u8 *flags;\n'
    src += scan + '    angle = 0;\n' + body(None)
    (OUT / f'{k}.c').write_text(src)
print(len(SCAN))
