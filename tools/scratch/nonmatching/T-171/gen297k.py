#!/usr/bin/env python3
"""func_800297A4: scan by pointer, then address the body by the counter.

The target walks v0 += 320 while counting v1, then *recomputes* the element
address as (i*5)<<6 - IDO's multiply-by-320 - so the body must be written as
D_80061D60[i].field, not p->field.
"""
from pathlib import Path
OUT = Path('/tmp/v297k')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
#define E ((T171Burst *) D_80061D60)
'''

SCAN = '''    p = E;
    i = 0;
    while (i < 4 && p->timer >= 0) { i++; p++; }
    if (i == 4) { p = E; i = 0; }
'''

def body(i_expr):
    b = f'E[{i_expr}].'
    return '''    {b}z = z;
    {b}x = x;
    {b}y = y;
    {b}timer = 0;
    {b}limit = life;
    {b}kind = kind;
    for (j = 0; j < 12; j++, angle += 90) {
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
'''.replace('{b}', b)

for key, iexpr in (('i', 'i'), ('k', 'k')):
    decl = '    T171Burst *p;\n    s32 i, j, angle;\n' + ('    s32 k;\n' if key == 'k' else '')
    scan = SCAN + ('    k = i;\n' if key == 'k' else '')
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += decl + scan + '    angle = 0;\n' + body(iexpr)
    (OUT / f'{key}.c').write_text(src)
print(2)
