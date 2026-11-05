#!/usr/bin/env python3
"""func_801B0668: read the state global for the tests instead of a saved local."""
from pathlib import Path
OUT = Path('/tmp/v0668c')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

V = {}
# v1: outer 0x7F test reads the global, inner test also reads it
V['v1'] = BASE.replace("""      if (!(D_801D2FC0 & 0x7F))""", """      if (!(D_801D2FC0 & 0x7F))""")
# v2: `state` loaded once but the else-if chain re-reads the global
V['v2'] = BASE.replace("""    state = D_801D2FC0;
    height = 0.0f; if ((state & 0x7F) == 1)""", """    height = 0.0f; state = D_801D2FC0;
    if ((D_801D2FC0 & 0x7F) == 1)""")
# v3: the 3..128 window tested on the global, increment through it
V['v3'] = BASE.replace("""      if ((state >= 3) && (state < 128))
    {
      state++;
      D_801D2FC0 = state;
      if (state >= 21)
      {""", """      if ((D_801D2FC0 >= 3) && (D_801D2FC0 < 128))
    {
      D_801D2FC0 = state + 1;
      if (D_801D2FC0 >= 21)
      {""")
# v4: only the >= 21 test moved to the global
V['v4'] = BASE.replace("""      state++;
      D_801D2FC0 = state;
      if (state >= 21)""", """      state++;
      D_801D2FC0 = state;
      if (D_801D2FC0 >= 21)""")
# v5: `state` only used for the decrement arithmetic, tests on the global
V['v5'] = BASE.replace("""    if ((state & 0x7F) == 1)""", """    if ((D_801D2FC0 & 0x7F) == 1)""").replace(
    """      if ((state >= 3) && (state < 128))""",
    """      if ((D_801D2FC0 >= 3) && (D_801D2FC0 < 128))""")
# v6: `state` local only for +1 arithmetic, stored then compared via the store
V['v6'] = BASE.replace("""      if ((state >= 3) && (state < 128))""",
    """      if ((state >= 3) && (state < 128))""").replace(
    """      state++;
      D_801D2FC0 = state;
      if (state >= 21)""", """      D_801D2FC0 = state + 1;
      if (D_801D2FC0 >= 21)""")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
