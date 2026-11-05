#!/usr/bin/env python3
"""func_801BCB70: move the y1c clamp in the source (IDO sank it in the draft)."""
from pathlib import Path
OUT = Path('/tmp/vbcb70i')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

CL_OLD = """                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
"""
assert CL_OLD in BASE

# the E4 command line
E4 = """                        yl = (s32) (fy * 4.0f); GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX((s32) (x1c * 4.0f), 0), 12, 12) | _SHIFTL(MAX((s32) (y1c * 4.0f), 0), 0, 12),"""
assert E4 in BASE

V = {}
# i1: y1f computed early, clamp right before E4
V['i1'] = BASE.replace(CL_OLD,
"""                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
""").replace(E4,
"""                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
""" + E4)

# i2: y1c into its own block right where the target has it (before the F5)
V['i2'] = BASE.replace(CL_OLD,
"""                        y1f = cellH * (f32) run + fy;
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
                        x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
""")

# i3: both clamps as separate blocks, x first (explicit braces around each)
V['i3'] = BASE.replace(CL_OLD,
"""                        y1f = cellH * (f32) run + fy;
                        { x1c = x1f;
                          if (!(x1f < 640.0f)) { x1c = 640.0f; } }
                        { y1c = y1f;
                          if (!(y1f < 480.0f)) { y1c = 480.0f; } }
""")

# i4: clamp with else arm
V['i4'] = BASE.replace(CL_OLD,
"""                        y1f = cellH * (f32) run + fy;
                        x1c = x1f;
                        y1c = y1f;
                        if (x1f < 640.0f) { x1c = x1f; } else { x1c = 640.0f; }
                        if (y1f < 480.0f) { y1c = y1f; } else { y1c = 480.0f; }
""")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
