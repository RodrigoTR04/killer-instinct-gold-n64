#!/usr/bin/env python3
"""func_8001346C: six float arrays each get their own cursor (target uses one
base for all six, indexed by a4/at, so try both a shared base and six cursors)."""
from pathlib import Path
OUT = Path('/tmp/v1346f')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-166/func_8001346C.c').read_text()

OLD = "        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);"
assert OLD in BASE

V = {}
V['base'] = BASE
# f1: one float* base, six offsets (target has ONE lui/addu base reused)
V['f1'] = BASE.replace(OLD,
  "        { f32 *q = &D_8004A740[palette];\n"
  "          func_8001C5AC(arg0, i, part->display, 0, 0, q[0], q[0x30], q[0x60], q[0xC0], q[0x120], q[0x180], 0); }")
# f2: cursor per array
V['f2'] = BASE.replace(OLD,
  "        { f32 *a = &D_8004A740[palette], *b = &D_8004A7A0; \n"
  "          func_8001C5AC(arg0, i, part->display, 0, 0, a[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0); }")
# f3: scalar locals for the six floats, computed before the call
V['f3'] = BASE.replace(OLD,
  "        { f32 c0 = D_8004A740[palette], c1 = (&D_8004A7A0)[palette], c2 = D_8004A800[palette];\n"
  "          f32 c3 = D_8004A860[palette], c4 = D_8004A8C0[palette], c5 = D_8004A920[palette];\n"
  "          func_8001C5AC(arg0, i, part->display, 0, 0, c0, c1, c2, c3, c4, c5, 0); }")
# f4: a single s32 offset local reused
V['f4'] = BASE.replace(OLD,
  "        { s32 k = part->transform;\n"
  "          func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[k], (&D_8004A7A0)[k], D_8004A800[k], D_8004A860[k], D_8004A8C0[k], D_8004A920[k], 0); }")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
