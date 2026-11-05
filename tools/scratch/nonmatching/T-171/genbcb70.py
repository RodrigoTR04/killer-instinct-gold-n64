#!/usr/bin/env python3
"""func_801BCB70: honest forms of the 480 clamp."""
from pathlib import Path
OUT = Path('/tmp/vbcb70')
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
              y1c = 480.0f;
            }
""",
'b': """            y1c = (y1f < 480.0f) ? y1f : 480.0f;
""",
'c': """            y1c = MIN(y1f, 480.0f);
""",
'd': """            y1c = 480.0f;
            if (y1f < 480.0f)
            {
              y1c = y1f;
            }
""",
'e': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1f = 480.0f;
            }
            y1c = y1f;
""",
'f': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
              y1f = y1c;
            }
""",
'g': """            if (y1f < 480.0f)
            {
              y1c = y1f;
            }
            else
            {
              y1c = 480.0f;
            }
""",
'h': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              x1c = 640.0f;
              y1c = 480.0f;
            }
""",
'i': """            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              y1f = 480.0f;
              y1c = y1f;
            }
""",
}

for k, v in FORMS.items():
    (OUT / f'{k}.c').write_text(base.replace(OLD, v))
print(len(FORMS))
