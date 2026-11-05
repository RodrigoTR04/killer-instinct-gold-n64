#!/usr/bin/env python3
"""func_800297A4: header through p, body arrays through D_80061D60[i].

The target keeps BOTH: v0 is the loop pointer used for x/y/z/timer/limit/kind,
and a0 = D_80061D60 + i*320 is recomputed for the array cursors. So the source
must mention the indexed form for the arrays while the header uses the pointer.
"""
from pathlib import Path
OUT = Path('/tmp/v297o')
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
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = E;
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

def body(cursors):
    decl = ''.join(f'    {d}\n' for d in cursors[0])
    init = ''.join(f'    {d}\n' for d in cursors[1])
    use = cursors[2]
    return decl, init, f'''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {{
        if (j < 4) {{
            {use['ax']}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {use['ay']}[j] = 0.0f;
            {use['az']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {use['fl']}[j] = 0;
        }} else if (j < 8) {{
            {use['ax']}[j] = 0.0f;
            {use['ay']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            {use['az']}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {use['fl']}[j] = 0;
        }} else {{
            {use['ax']}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {use['ay']}[j] = (float) (u32) (97 - (func_800326F0() & 15));
            {use['az']}[j] = 0.0f;
            {use['fl']}[j] = 1;
        }}
        {use['vel']}[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        {use['pos']}[j] = (float) (u32) (func_800326F0() & 15);
        {use['age']}[j] = 0;
        {use['dur']}[j] = life - (func_800326F0() & 7);
    }}
}}
'''

CASES = {
# o1: axis/vel/pos through E[i], age/dur through p, flags through p
'o1': ([], [], {'ax': 'E[i].axisX', 'ay': 'E[i].axisY', 'az': 'E[i].axisZ', 'fl': 'p->flags',
                'vel': 'E[i].velocity', 'pos': 'E[i].position', 'age': 'p->age', 'dur': 'p->duration'}),
# o2: everything through E[i]
'o2': ([], [], {'ax': 'E[i].axisX', 'ay': 'E[i].axisY', 'az': 'E[i].axisZ', 'fl': 'E[i].flags',
                'vel': 'E[i].velocity', 'pos': 'E[i].position', 'age': 'E[i].age', 'dur': 'E[i].duration'}),
# o3: q = &E[i], arrays through q, header through p
'o3': (['T171Burst *q;'], ['q = &E[i];'],
       {'ax': 'q->axisX', 'ay': 'q->axisY', 'az': 'q->axisZ', 'fl': 'q->flags',
        'vel': 'q->velocity', 'pos': 'q->position', 'age': 'q->age', 'dur': 'q->duration'}),
# o4: axis through E[i], rest through p (target's s0/s3/s5 are all off a0 though)
'o4': ([], [], {'ax': 'E[i].axisX', 'ay': 'E[i].axisY', 'az': 'E[i].axisZ', 'fl': 'p->flags',
                'vel': 'p->velocity', 'pos': 'p->position', 'age': 'p->age', 'dur': 'p->duration'}),
}

for k, (decl, init, use) in CASES.items():
    d, i_, b = body((decl, init, use))
    src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
    src += '    T171Burst *p;\n    s32 i, j, angle;\n' + d
    src += SCAN + i_ + b
    (OUT / f'{k}.c').write_text(src)
print(len(CASES))
