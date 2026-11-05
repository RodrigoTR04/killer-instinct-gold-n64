#!/usr/bin/env python3
"""func_8001346C: palette-copy loop bound and store order, on the s32 skeleton."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1346m')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346j/ip_p_s32.c').read_text()

COPY_OLD = """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
"""
assert COPY_OLD in BASE

COPIES = {
# bound by pointer end
'e1': """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92, *e = D_8004AC8E + 3;
          do { *d1++ = a[i]; *d2++ = b[i]; i++; } while (d1 != e); }
""",
'e2': """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *s1 = a, *d1 = D_8004AC8E, *s2 = b, *d2 = D_8004AC92, *e = D_8004AC8E + 3;
          do { *d1++ = *s1++; *d2++ = *s2++; } while (d1 != e); }
""",
'e3': """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i < 3; i++) { d1[i] = a[i]; d2[i] = b[i]; } }
""",
# store order flipped: AC92 first
'e4': """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d2++ = b[i]; *d1++ = a[i]; } }
""",
# no d1/d2, direct pointer arithmetic on the arrays
'e5': """        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) { *(D_8004AC92 + i) = b[i]; *(D_8004AC8E + i) = a[i]; }
""",
}

n = 0
for k, c in COPIES.items():
    (OUT / f'{k}.c').write_text(BASE.replace(COPY_OLD, c))
    n += 1
print(n)
