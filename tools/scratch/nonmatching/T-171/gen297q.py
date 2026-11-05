#!/usr/bin/env python3
"""func_800297A4: the 160-word form plus one more independent cursor."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297q')
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

ARR = {
 'age': ('s16 *age;', 'p->age', 'age'),
 'dur': ('s16 *dur;', 'p->duration', 'dur'),
 'fl':  ('u8 *fl;',   'p->flags',  'fl'),
 'vel': ('float *vel;', 'p->velocity', 'vel'),
 'pos': ('float *pos;', 'p->position', 'pos'),
 'ax':  ('float *ax;', 'p->axisX', 'ax'),
 'ay':  ('float *ay;', 'p->axisY', 'ay'),
 'az':  ('float *az;', 'p->axisZ', 'az'),
}

def build(sel):
    decls = ['    T171Burst *p;', '    s32 i, j, angle;']
    inits = []
    for k in sel:
        d, src, name = ARR[k]
        decls.append('    ' + d)
        inits.append(f'    {name} = {src};')
    b = {k: (ARR[k][2] if k in sel else ARR[k][1]) for k in ARR}
    body = SCAN + '\n'.join(inits) + '\n    angle = 0;\n'
    body += f'''    for (j = 0; j < 12; j++, angle += 90) {{
        if (j < 4) {{
            {b['ax']}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {b['ay']}[j] = 0.0f;
            {b['az']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {b['fl']}[j] = 0;
        }} else if (j < 8) {{
            {b['ax']}[j] = 0.0f;
            {b['ay']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            {b['az']}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {b['fl']}[j] = 0;
        }} else {{
            {b['ax']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {b['ay']}[j] = (float) (u32) (97 - (func_800326F0() & 15));
            {b['az']}[j] = 0.0f;
            {b['fl']}[j] = 1;
        }}
        {b['vel']}[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        {b['pos']}[j] = (float) (u32) (func_800326F0() & 15);
        {b['age']}[j] = 0;
        {b['dur']}[j] = life - (func_800326F0() & 7);
    }}
}}
'''
    return (HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
            + '\n'.join(decls) + '\n' + body)

n = 0
for r in (2, 3, 4):
    for sel in itertools.combinations(ARR, r):
        (OUT / ('_'.join(sel) + '.c')).write_text(build(sel))
        n += 1
print(n)
