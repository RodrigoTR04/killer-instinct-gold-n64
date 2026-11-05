#!/usr/bin/env python3
"""func_8001346C: split the palette copy loop into the target's two-cursor form."""
from pathlib import Path
OUT = Path('/tmp/v1346c')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346b/a.c').read_text()

# target: two separate source cursors a (AC98) and b (ACB0), two dest cursors
# 0xAC8E and 0xAC92, all advanced inside one loop; loop count in a0.
V = {}
V['loopsrc'] = BASE.replace('''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }''', '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            *(D_8004AC8E + i) = *(a + i);
            *(D_8004AC92 + i) = *(b + i);
        }''')

V['ptrloop'] = BASE.replace('''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }''', '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        {
            u8 *src = a, *dst = D_8004AC8E;
            u8 *src2 = b, *dst2 = D_8004AC92;
            for (i = 0; i != 3; i++) {
                *dst++ = *src++;
                *dst2++ = *src2++;
            }
        }''')

V['unroll'] = BASE.replace('''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }''', '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        D_8004AC8E[0] = a[0]; D_8004AC92[0] = b[0];
        D_8004AC8E[1] = a[1]; D_8004AC92[1] = b[1];
        D_8004AC8E[2] = a[2]; D_8004AC92[2] = b[2];''')

# same three, but the clear loop also converted
CLEAR_OLD = '''        a = D_8004AC92; b = D_8004AC8E;
        do { *a++ = 0; *b++ = 0; } while (a != D_8004AC92 + 3);'''
for k in list(V):
    V[k + '_cf'] = V[k].replace(CLEAR_OLD, '''        a = D_8004AC92; b = D_8004AC8E;
        for (i = 0; i != 3; i++) { *(D_8004AC92 + i) = 0; *(D_8004AC8E + i) = 0; }''')

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
