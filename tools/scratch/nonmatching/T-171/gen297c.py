#!/usr/bin/env python3
"""func_800297A4: search-loop shapes; body via pointer or index."""
from pathlib import Path
OUT = Path('/tmp/v297c')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'):
    f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
#define P ((T171Burst *) D_80061D60)
'''

SEARCH = {
'dowhile': '''    p = P;
    do {
        if (p->timer < 0) break;
        i++;
        p++;
    } while (i < 4);
    if (i == 4) { p = P; i = 0; }
''',
'dowhile2': '''    p = P;
    do {
        i++;
        if (p->timer < 0) break;
        p++;
    } while (i < 4);
    if (i == 4) { p = P; i = 0; }
''',
'wbreak3': '''    p = P;
    i = 0;
    while (1) {
        if (p->timer < 0) break;
        i++;
        if (i == 4) break;
        p++;
    }
    if (i == 4) { p = P; i = 0; }
''',
}

def body(base):
    return '''    for (j = 0; j < 12; j++, angle += 90) {
        if (j < 4) {
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

for sname, search in SEARCH.items():
    for bname, base in (('p', 'p->'), ('idx', 'P[i].')):
        src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
        src += '    T171Burst *p;\n    s32 i, j, angle;\n    angle = 0;\n    i = 0;\n'
        src += search
        src += '    p->z = z;\n    p->x = x;\n    p->y = y;\n    p->timer = 0;\n    p->limit = life;\n    p->kind = kind;\n'
        src += body(base)
        (OUT / f'{sname}_{bname}.c').write_text(src)
print('ok')
