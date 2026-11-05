#!/usr/bin/env python3
"""func_801BCB70: match the target's s4 (left) / s5 (x0f*4 truncated) split.

Target:
  s4 = left (0x158 arg home), s5 = trunc(x0f * 4), s3 = uls
  E4 w0 = (0xE4<<24) | MAX(trunc(x1c*4),0)<<12 | MAX(trunc(y1c*4),0)
  E4 w1 = MAX(xl,0)<<12 | MAX(yl,0)      (note: no <<24 term beyond 0)
and the F4/F3 words reuse t4 (ult<<2) and t2/t3.
The draft reuses one register for both, so introduce xl4/yl4 named ints.
"""
from pathlib import Path
OUT = Path('/tmp/vbcb70n')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801BCB70.c').read_text()

E4_OLD = """                        yl = (s32) (fy * 4.0f); GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX((s32) (x1c * 4.0f), 0), 12, 12) | _SHIFTL(MAX((s32) (y1c * 4.0f), 0), 0, 12),
                                  _SHIFTL(0, 24, 3) | _SHIFTL(MAX(xl, 0), 12, 12) | _SHIFTL(MAX(yl, 0), 0, 12));"""
assert E4_OLD in BASE

V = {}
# n1: xl4/yl4 as named s32 locals, then the command
V['n1'] = BASE.replace(E4_OLD,
"""                        yl = (s32) (fy * 4.0f);
                        { s32 xl4 = (s32) (x1c * 4.0f);
                          s32 yl4 = (s32) (y1c * 4.0f);
                          GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX(xl4, 0), 12, 12) | _SHIFTL(MAX(yl4, 0), 0, 12),
                                        _SHIFTL(0, 24, 3) | _SHIFTL(MAX(xl, 0), 12, 12) | _SHIFTL(MAX(yl, 0), 0, 12)); }""")
# n2: clamp the truncation to named s32s at declaration level
V['n2'] = BASE.replace(E4_OLD,
"""                        yl = (s32) (fy * 4.0f);
                        xl = MAX(xl, 0);
                        yl = MAX(yl, 0);
                        { s32 x1q = MAX((s32) (x1c * 4.0f), 0);
                          s32 y1q = MAX((s32) (y1c * 4.0f), 0);
                          GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(x1q, 12, 12) | _SHIFTL(y1q, 0, 12),
                                        _SHIFTL(0, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12)); }""")
# n3: yl computed before xl-block, xl not clobbered
V['n3'] = BASE.replace(E4_OLD,
"""                        { s32 x1q = (s32) (x1c * 4.0f), y1q = (s32) (y1c * 4.0f);
                          yl = (s32) (fy * 4.0f);
                          GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX(x1q, 0), 12, 12) | _SHIFTL(MAX(y1q, 0), 0, 12),
                                        _SHIFTL(0, 24, 3) | _SHIFTL(MAX(xl, 0), 12, 12) | _SHIFTL(MAX(yl, 0), 0, 12)); }""")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
