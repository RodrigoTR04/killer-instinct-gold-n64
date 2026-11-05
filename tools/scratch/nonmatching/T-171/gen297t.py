#!/usr/bin/env python3
"""func_800297A4: keep the exact 780 B size while separating a cursor.

The 160-word form is 792 B (12 too many). Find the cheapest cursor that does not
grow the frame: the target keeps the axis base in one register and steps it, so
try cursors that are derived once and indexed, with the header still on p.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297t')
OUT.mkdir(exist_ok=True)
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
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

def build(use_fl_cursor, use_dur_cursor, fl_from_p):
    decls = '    T171Burst *p;\n    s32 i, j, angle;\n'
    init = ''
    if use_dur_cursor: decls += '    s16 *dur;\n'
    if use_fl_cursor: decls += '    u8 *fl;\n'
    if use_dur_cursor: init += '    dur = p->duration;\n'
    if use_fl_cursor: init += '    fl = p->flags;\n'
    FL = 'fl' if use_fl_cursor else 'p->flags'
    DU = 'dur' if use_dur_cursor else 'p->duration'
    body = f'''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {{
        if (j < 4) {{
            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));
            p->axisY[j] = 0.0f;
            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {FL}[j] = 0;
        }} else if (j < 8) {{
            p->axisX[j] = 0.0f;
            p->axisY[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            p->axisZ[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {FL}[j] = 0;
        }} else {{
            p->axisX[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            p->axisY[j] = (float) (u32) (97 - (func_800326F0() & 15));
            p->axisZ[j] = 0.0f;
            {FL}[j] = 1;
        }}
        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        p->position[j] = (float) (u32) (func_800326F0() & 15);
        p->age[j] = 0;
        {DU}[j] = life - (func_800326F0() & 7);
    }}
}}
'''
    return (HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
            + decls + SCAN + init + body)

for a in (False, True):
    for b in (False, True):
        (OUT / f'fl{int(a)}_dur{int(b)}.c').write_text(build(a, b, False))
print(4)
