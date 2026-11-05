#!/usr/bin/env python3
"""func_801BCB70: expression-level variants of the four clamps."""
from pathlib import Path
OUT = Path('/tmp/vbcb70g')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

PAIRS = {
# (old, new)
'x1': (
"""                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
""",
"""                        y1f = cellH * (f32) run + fy;
                        x1c = (x1f < 640.0f) ? x1f : 640.0f;
"""),
'y1': (
"""                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
""",
"""                        y1c = (y1f < 480.0f) ? y1f : 480.0f;
"""),
'both': (
"""                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
""",
"""                        y1f = cellH * (f32) run + fy;
                        x1c = (x1f < 640.0f) ? x1f : 640.0f;
                        y1c = (y1f < 480.0f) ? y1f : 480.0f;
"""),
'minmacro': (
"""                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
""",
"""                        y1f = cellH * (f32) run + fy;
                        x1c = MIN(x1f, 640.0f);
                        y1c = MIN(y1f, 480.0f);
"""),
'uls': (
"""if (pos != 0) { uls = pos; } else { uls = 0; }""",
"""uls = (pos != 0) ? pos : 0;"""),
'ult': (
"""ult = MAX(x - 1, 0);""",
"""ult = (x - 1) > 0 ? (x - 1) : 0;"""),
}

for k, (old, new) in PAIRS.items():
    if old not in BASE:
        print('MISSING', k)
        continue
    (OUT / f'{k}.c').write_text(BASE.replace(old, new))
print('ok')
