#!/usr/bin/env python3
"""func_800297A4: block boundaries that do NOT extend live ranges.

The tail `do/while` pushed the frame from 0x48 to 0x68. Put the blocks on the
header stores, which IDO can schedule freely and which are dead immediately.
The target's schedule shows the header stores happening *after* the scan and
*before* the loop, with `a0 = base + i*320` derived in between.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297ad')
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
'''

STORES = {
'z':  ('    p->z = z;\n', '    do { p->z = z; } while (0);\n'),
'x':  ('    p->x = x;\n', '    do { p->x = x; } while (0);\n'),
'y':  ('    p->y = y;\n', '    do { p->y = y; } while (0);\n'),
'tm': ('    p->timer = 0;\n', '    do { p->timer = 0; } while (0);\n'),
'li': ('    p->limit = life;\n', '    do { p->limit = life; } while (0);\n'),
'kd': ('    p->kind = kind;\n', '    do { p->kind = kind; } while (0);\n'),
'dur': ('''        p->age[j] = 0;
        p->duration[j] = life - (func_800326F0() & 7);''',
        '''        p->age[j] = 0;
        do { p->duration[j] = life - (func_800326F0() & 7); } while (0);'''),
}

HDR = '''    p->z = z;
    p->x = x;
    p->y = y;
    p->timer = 0;
    p->limit = life;
    p->kind = kind;
'''

BODY = '''    angle = 0;
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

n = 0
for r in (1, 2, 3):
    for combo in itertools.combinations(['z','x','y','tm','li','kd'], r):
        h = HDR
        ok = True
        for c in combo:
            old, new = STORES[c]
            if old not in h:
                ok = False; break
            h = h.replace(old, new)
        if not ok: continue
        src = HEAD + 'void func_800297A4(float x, float y, float z, s32 speed, s32 life, s32 kind) {\n'
        src += '    T171Burst *p;\n    s32 i, j, angle;\n' + SCAN + h + BODY
        (OUT / f'{"".join(combo)}.c').write_text(src)
        n += 1
print(n)
