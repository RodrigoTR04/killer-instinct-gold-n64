#!/usr/bin/env python3
"""func_800297A4: body addressed through D_80061D60[i] (target recomputes base)."""
from pathlib import Path
OUT = Path('/tmp/v297h')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
#define E ((T171Burst *) D_80061D60)
'''

def body(base):
    return '''        if (j < 4) {
            {b}axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {b}axisY[j] = 0.0f;
            {b}axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {b}flags[j] = 0;
        } else if (j < 8) {
            {b}axisX[j] = 0.0f;
            {b}axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            {b}axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {b}flags[j] = 0;
        } else {
            {b}axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {b}axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            {b}axisZ[j] = 0.0f;
            {b}flags[j] = 1;
        }
        {b}velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        {b}position[j] = (float) (u32) (func_800326F0() & 15);
        {b}age[j] = 0;
        {b}duration[j] = life - (func_800326F0() & 7);
    }
}
'''.replace('{b}', base)

SEARCH = '''    p = E;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) { p = E; i = 0; }
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

CASES = {
'idx': ('    T171Burst *p;\n    s32 i, j, angle;\n', 'E[i].'),
'q': ('    T171Burst *p;\n    s32 i, j, angle;\n    T171Burst *q;\n', 'q->'),
}
for k, (decls, base) in CASES.items():
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += decls + SEARCH
    if k == 'q':
        src += '    q = &E[i];\n'
    src += '    angle = 0;\n    for (j = 0; j < 12; j++, angle += 90) {\n' + body(base)
    (OUT / f'{k}.c').write_text(src)
print(len(CASES))
