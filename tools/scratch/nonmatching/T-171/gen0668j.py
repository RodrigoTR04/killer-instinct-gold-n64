#!/usr/bin/env python3
"""func_801B0668: split each state read-modify-write into two statements with a
block-scoped temporary, which is what makes IDO materialise the address twice."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v0668j')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

SITES = {
# 1: if (!(D_801D2FC0 & 0x7F)) { ...; D_801D2FC0 |= 1; }
's1': ("""      if (!(D_801D2FC0 & 0x7F))
      {
        func_8002F6F4(D_80066C40, 0x135, &D_8004A258);
        D_801D2FC0 |= 1;
      }""",
"""      if (!(D_801D2FC0 & 0x7F))
      {
        u8 st = D_801D2FC0;
        func_8002F6F4(D_80066C40, 0x135, &D_8004A258);
        D_801D2FC0 = st | 1;
      }"""),
# 2: else { D_801D2FC0 &= 0x80; }
's2': ("""    else
    { D_801D2FC0 &= 0x80;
    }""",
"""    else
    { u8 st = D_801D2FC0;
      D_801D2FC0 = st & 0x80;
    }"""),
# 3: the ==1 arm
's3': ("""      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40); state = D_801D2FC0;
      D_801D2FC0 = state | 3; }""",
"""      func_8002F6F4(D_80066C40, 11, &D_8004A258);
      func_801ADAD4(40);
      { u8 st = D_801D2FC0;
        D_801D2FC0 = st | 3; } }"""),
# 4: the increment arm
's4': ("""      state++;
      D_801D2FC0 = state;
      if (state >= 21)""",
"""      { u8 st = D_801D2FC0 + 1;
        D_801D2FC0 = st;
        if (st >= 21)"""),
}

base1 = BASE
for r in (1, 2, 3, 4):
    for combo in itertools.combinations(SITES, r):
        t = base1
        for c in combo:
            old, new = SITES[c]
            if old in t:
                t = t.replace(old, new)
        tag = ''.join(c[1] for c in combo)
        (OUT / f's{tag}.c').write_text(t)
print(len(list(OUT.glob('*.c'))))
