#!/usr/bin/env python3
"""func_801B0668: compare the global byte directly at each decision point.

Motivation: for func_801C1990, writing the test as the global rather than a
saved local register made IDO re-read the byte and emit the target's
`andi`/`bne` pair. Try the same here: no `state` local at all, every test and
store through D_801D2FC0.
"""
from pathlib import Path
OUT = Path('/tmp/v0668e')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

OLD_ELSE = """    state = D_801D2FC0;
    height = 0.0f; if ((state & 0x7F) == 1)
    {
      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40); state = D_801D2FC0;
      D_801D2FC0 = state | 3; } else
      if ((state >= 3) && (state < 128))
    {
      state++;
      D_801D2FC0 = state;
      if (state >= 21)
      {
        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
        D_801D2FC0 = 0x82;
      }
    } }"""
assert OLD_ELSE in BASE

VARIANTS = {
# e1: no local at all
'e1': """    height = 0.0f;
    if ((D_801D2FC0 & 0x7F) == 1)
    {
      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40);
      D_801D2FC0 |= 3;
    }
    else if (D_801D2FC0 >= 3 && D_801D2FC0 < 128)
    {
      D_801D2FC0++;
      if (D_801D2FC0 >= 21)
      {
        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
        D_801D2FC0 = 0x82;
      }
    } }""",
# e2: local only for the OR/3 arm
'e2': """    state = D_801D2FC0;
    height = 0.0f;
    if ((state & 0x7F) == 1)
    {
      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40);
      D_801D2FC0 |= 3;
    }
    else if (D_801D2FC0 >= 3 && D_801D2FC0 < 128)
    {
      D_801D2FC0++;
      if (D_801D2FC0 >= 21)
      {
        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
        D_801D2FC0 = 0x82;
      }
    } }""",
# e3: no local, window test on the masked value
'e3': """    height = 0.0f;
    if ((D_801D2FC0 & 0x7F) == 1)
    {
      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40);
      D_801D2FC0 |= 3;
    }
    else if ((D_801D2FC0 & 0x7F) >= 3 && D_801D2FC0 < 128)
    {
      D_801D2FC0++;
      if ((D_801D2FC0 & 0x7F) >= 21)
      {
        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
        D_801D2FC0 = 0x82;
      }
    } }""",
# e4: local kept for +1 only, everything else global
'e4': """    height = 0.0f;
    if ((D_801D2FC0 & 0x7F) == 1)
    {
      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40);
      D_801D2FC0 |= 3;
    }
    else if (D_801D2FC0 >= 3 && D_801D2FC0 < 128)
    {
      state = D_801D2FC0 + 1;
      D_801D2FC0 = state;
      if (state >= 21)
      {
        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
        D_801D2FC0 = 0x82;
      }
    } }""",
}

for k, v in VARIANTS.items():
    (OUT / f'{k}.c').write_text(BASE.replace(OLD_ELSE, v))
print(len(VARIANTS))
