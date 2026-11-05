#!/usr/bin/env python3
"""func_801BCB70: the user's specific restructuring ideas.

1. one clamp as a ternary, the other as an if
2. the multu/mflo product (cellW * run) in a named local computed before the commands
3. different F4 word expression orders
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/vbcb70h')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

CLAMPS_OLD = """                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
"""
assert CLAMPS_OLD in BASE

CLAMPS = {
'c1': """                        y1f = cellH * (f32) run + fy;
                        x1c = (x1f < 640.0f) ? x1f : 640.0f;
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
""",
'c2': """                        y1f = cellH * (f32) run + fy;
                        x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = (y1f < 480.0f) ? y1f : 480.0f;
""",
'c3': """                        y1f = cellH * (f32) run + fy;
                        x1c = (x1f < 640.0f) ? x1f : 640.0f;
                        y1c = (y1f < 480.0f) ? y1f : 480.0f;
""",
'c4': """                        y1f = cellH * (f32) run + fy;
                        x1c = x1f;
                        y1c = y1f;
                        if (!(x1f < 640.0f)) x1c = 640.0f;
                        if (!(y1f < 480.0f)) y1c = 480.0f;
""",
}

# product local before the commands
PROD_OLD = """                        lrt = (x + cellW * run < (right - 1)) ? x + cellW * run : (right - 1);"""
PROD_NEW = """                        { u32 width = cellW * run;
                        lrt = (x + width < (right - 1)) ? x + width : (right - 1);"""

TAIL_RESTORE = """                    }
                    x += cellW * run; fy += cellH * (f32) run;
                    col += run;"""

n = 0
for ck, clamps in CLAMPS.items():
    (OUT / f'{ck}.c').write_text(BASE.replace(CLAMPS_OLD, clamps))
    n += 1

# c5: product in a local, plus the clamp split
# apply the width local by rewriting lrt/x += and closing the brace
for ck, clamps in CLAMPS.items():
    t = BASE.replace(CLAMPS_OLD, clamps)
    t = t.replace(PROD_OLD, PROD_NEW)
    t = t.replace("                    }\n                    x += cellW * run; fy += cellH * (f32) run;",
                  "                    }\n                    x += width; fy += cellH * (f32) run; }\n                    fy = fy;")
    (OUT / f'{ck}_width.c').write_text(t)
    n += 1
print(n)
