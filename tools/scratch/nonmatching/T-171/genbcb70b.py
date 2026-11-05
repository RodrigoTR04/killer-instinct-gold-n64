#!/usr/bin/env python3
"""func_801BCB70: replace the empty block with an honest block-scoped statement."""
from pathlib import Path
OUT = Path('/tmp/vbcb70b')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

base = Path('/tmp/bcb70.c').read_text()
OLD = """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              if (1)
              {
              }
              y1c = 480.0f;
            }
"""
assert OLD in base

FORMS = {
'a': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              f32 clamp = 480.0f;
              y1c = clamp;
            }
""",
'b': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              f32 clamp;
              clamp = 480.0f;
              y1c = clamp;
            }
""",
'c': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
              x1f = x1c;
            }
""",
'd': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
              y1f = y1c;
            }
""",
'e': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
              absDx = dx;
            }
""",
'f': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              i = i;
              y1c = 480.0f;
            }
""",
'g': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              yl = (s32) (fy * 4.0f);
              y1c = 480.0f;
            }
""",
'h': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
              yl = (s32) (y1c * 4.0f);
            }
""",
'i': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              yl = (s32) (fy * 4.0f);
              y1c = 480.0f;
              xl = (s32) (x0f * 4.0f);
            }
""",
}

for k, v in FORMS.items():
    (OUT / f'{k}.c').write_text(base.replace(OLD, v))
print(len(FORMS))
