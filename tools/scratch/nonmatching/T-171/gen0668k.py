#!/usr/bin/env python3
"""func_801B0668: force `bc1f` + nop instead of `bc1fl` with the load.

IDO emits `bc1fl` + `lbu` when the load is hoisted into the delay slot. The
target has `bc1f` + `nop` and the load *after* the branch, i.e. the load must
depend on the branch being taken - which happens when the branch target's block
starts with a *statement* that uses the byte, or when the branch is an early
`continue`/`return` shape. Try guards and early exits.
"""
from pathlib import Path
OUT = Path('/tmp/v0668k')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

OLD = """  if (height > 0.0f)
  { if (height <= 60.0f)
    {
      height = 120.0 - ((cosf((height * D_802928C0) * 0.75) * 60.0f) / D_802928C8);
    }
    height -= 35.0f; if (height <= 200.0f)
"""
assert OLD in BASE

V = {}
# k1: early-out form (guard clause)
V['k1'] = BASE.replace(OLD, """  if (!(height > 0.0f)) goto tail;
  if (height <= 60.0f)
  {
    height = 120.0 - ((cosf((height * D_802928C0) * 0.75) * 60.0f) / D_802928C8);
  }
  height -= 35.0f;
  if (height <= 200.0f)
""")
V['k1'] = V['k1'].replace("""  }
  guScale(arg2, D_802928D0, D_802928D0, 1.0f);""",
"""  }
tail:
  guScale(arg2, D_802928D0, D_802928D0, 1.0f);""")
# need the else body moved before tail; simpler: nested positive form
V['k2'] = BASE.replace(OLD, """  if (height > 0.0f)
  {
    if (height <= 60.0f)
    {
      height = 120.0 - ((cosf((height * D_802928C0) * 0.75) * 60.0f) / D_802928C8);
    }
    height -= 35.0f;
    if (height <= 200.0f)
""")
# k3: compare with 0.0f on the right (target c.lt.s $f4, $f0 = 0 < height)
V['k3'] = BASE.replace('  if (height > 0.0f)', '  if (0.0f < height)')
V['k4'] = BASE.replace('  if (height > 0.0f)', '  if (height >= 0.0001f)')

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
