#!/usr/bin/env python3
"""func_8001346C: block-scope the branch bodies, the shape the target's
`bnez`-into-.L80013534 shows."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1346q')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346j/ip_p_s32.c').read_text()

OLD = """    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    switch (mode) {"""
assert OLD in BASE

V = {
# q1: palette index in its own block
'q1': """    palette = part->flags & 0xF0;
    if (palette >= 16) {
        do { palette = (palette - 16) >> 4; } while (0);
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    switch (mode) {""",
# q2: mode mask in its own block, switch after
'q2': """    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
        func_8001BB64(arg0);
    }
    do { mode = part->flags & 15; } while (0);
    switch (mode) {""",
# q3: the whole palette arm wrapped
'q3': """    palette = part->flags & 0xF0;
    do { if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
        func_8001BB64(arg0);
    } } while (0);
    mode = part->flags & 15;
    switch (mode) {""",
# q4: the copy loop body wrapped
'q4': """    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { do { *d1++ = a[i]; *d2++ = b[i]; } while (0); } }
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    switch (mode) {""",
}
for k, v in V.items():
    (OUT / f'{k}.c').write_text(BASE.replace(OLD, v))
print(len(V))
