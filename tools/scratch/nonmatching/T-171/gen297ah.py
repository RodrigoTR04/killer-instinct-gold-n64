#!/usr/bin/env python3
"""func_800297A4: the target's actual loop shape.

Disassembly shows: s2 = angle stepping 90 compared against 1080; s4 = a doubled
index stepping 2 used only for `j < 8` / `j < 16`; s0 = a float cursor stepping
4 bytes; s5 = an s16 cursor stepping 2; s3 = a u8 cursor stepping 1.
So the arrays are walked by cursors and the branch counter is 2*j.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297ah')
OUT.mkdir(Exists_ok=True) if False else OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
'''

SCAN = '''    p = (T171Burst *) D_80061D60;
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = (T171Burst *) D_80061D60;
'''

HDR = '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

def body(axis, age, fl, counter, close_style):
    return f'''    angle = 0;
    for ({counter}, angle = 0; angle < 1080; {counter}, angle += 90) {{
        if ({counter} < 8) {{
            {axis}[0] = (float) (u32) (7 - (func_800326F0() & 15));
            {axis}[12] = 0.0f;
            {axis}[24] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {fl}[0] = 0;
        }} else if ({counter} < 16) {{
            {axis}[0] = 0.0f;
            {axis}[12] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            {axis}[24] = (float) (u32) (7 - (func_800326F0() & 15));
            {fl}[0] = 0;
        }} else {{
            {axis}[0] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {axis}[12] = (float) (u32) (97 - (func_800326F0() & 15));
            {axis}[24] = 0.0f;
            {fl}[0] = 1;
        }}
        {axis}[36] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        {axis}[48] = (float) (u32) (func_800326F0() & 15);
        {age}[0] = 0;
        {age}[12] = life - (func_800326F0() & 7);
        {close_style}
    }}
}}
'''

CASES = {
# a1: cursors incremented in the for header
'a1': ('    T171Burst *p;\n    float *f;\n    s16 *a;\n    u8 *fl;\n    s32 i, j, angle;\n',
       '    f = p->axisX; a = p->age; fl = p->flags;\n',
       'f', 'a', 'fl', 'j += 2',
       'f++; a++; fl++;'),
# a2: cursors incremented in the body
'a2': ('    T171Burst *p;\n    float *f;\n    s16 *a;\n    u8 *fl;\n    s32 i, j, angle;\n',
       '    f = p->axisX; a = p->age; fl = p->flags;\n',
       'f', 'a', 'fl', 'j += 2',
       'f++; a++; fl++;'),
}

for k, (decls, init, ax, ag, fl, counter, incr) in CASES.items():
    if k == 'a1':
        b = body(ax, ag, fl, counter, incr)
    else:
        b = body(ax, ag, fl, counter, incr + ' ')
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += decls + SCAN + HDR + init + b
    (OUT / f'{k}.c').write_text(src)
print(len(CASES))
