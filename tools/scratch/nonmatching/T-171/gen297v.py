#!/usr/bin/env python3
"""func_800297A4: a second struct view so the body base is computed once.

The target computes the base twice - `v0` for the scan pointer (used for the
six header stores) and a fresh `t9`+`i*320` in `a0` for the array cursors. Give
the body its own typed view over D_80061D60 so the two derivations are separate
source expressions.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297v')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

TYPES = '''typedef struct {
    float axisX[12], axisY[12], axisZ[12], velocity[12], position[12], x, y, z;
    s16 age[12], duration[12], timer, limit, kind;
    u8 flags[12], pad[2];
} T171Burst;
typedef T171Burst T171Slots[4];
#define SLOTS ((T171Slots *) D_80061D60)
'''

SCAN = '''    p = SLOTS[0];
    i = 0;
    while (p->timer >= 0) {
        i++;
        if (i >= 4) break;
        p++;
    }
    if (i == 4) p = SLOTS[0];
    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

def body(arrays, cursors):
    d = ''.join('    ' + c + '\n' for c in cursors[0])
    ini = ''.join('    ' + c + '\n' for c in cursors[1])
    ax, ay, az, vel, pos, age, dur, fl = arrays
    b = f'''    angle = 0;
    for (j = 0; j < 12; j++, angle += 90) {{
        if (j < 4) {{
            {ax}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {ay}[j] = 0.0f;
            {az}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {fl}[j] = 0;
        }} else if (j < 8) {{
            {ax}[j] = 0.0f;
            {ay}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 570);
            {az}[j] = (float) (u32) (7 - (func_800326F0() & 15));
            {fl}[j] = 0;
        }} else {{
            {ax}[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);
            {ay}[j] = (float) (u32) (97 - (func_800326F0() & 15));
            {az}[j] = 0.0f;
            {fl}[j] = 1;
        }}
        {vel}[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);
        {pos}[j] = (float) (u32) (func_800326F0() & 15);
        {age}[j] = 0;
        {dur}[j] = life - (func_800326F0() & 7);
    }}
}}
'''
    return d, ini, b

CURS = (
    (['s16 *dur;', 'u8 *fl;'], ['dur = p->duration;', 'fl = p->flags;']),
    ([], []),
)

# arrays via the indexed slot view, or via p
IDX = ('SLOTS[i]->axisX', 'SLOTS[i]->axisY', 'SLOTS[i]->axisZ',
       'SLOTS[i]->velocity', 'SLOTS[i]->position', 'SLOTS[i]->age',
       'SLOTS[i]->duration', 'SLOTS[i]->flags')
P_ = ('p->axisX', 'p->axisY', 'p->axisZ', 'p->velocity', 'p->position',
      'p->age', 'p->duration', 'p->flags')

n = 0
for arr in (IDX, P_):
    for curs, (d, ini) in zip(('none', 'durfl'), CURS):
        dd, ii, bb = body(arr, (d, ini))
        # when cursors are used, override the two arrays
        if curs == 'durfl':
            bb = bb.replace(IDX[6], 'dur[j]').replace('p->duration', 'dur[j]')
            bb = bb.replace(IDX[7], 'fl[j]').replace('p->flags', 'fl[j]')
        src = TYPES + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
        src += '    T171Burst *p;\n    s32 i, j, angle;\n' + dd + SCAN + ii + bb
        (OUT / f'{"idx" if arr is IDX else "ptr"}_{curs}.c').write_text(src)
        n += 1
print(n)
