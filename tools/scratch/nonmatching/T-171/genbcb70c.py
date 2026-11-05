#!/usr/bin/env python3
"""func_801BCB70: honest forms that create a block boundary at the y1c clamp."""
from pathlib import Path
OUT = Path('/tmp/vbcb70c')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

base = Path('/tmp/bcb70.c').read_text()
OLD = """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              if (1)
              {
              }
              y1c = 480.0f;
            }
"""
assert OLD in base
HEAD_PART = base.split(OLD)[0]
TAIL_PART = base.split(OLD)[1]

FORMS = {
# a nested bare scope
'scope': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              {
                y1c = 480.0f;
              }
            }
""",
# do/while(0)
'dowhile': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            y1c = y1f;
            if (!(y1f < 480.0f))
            do
            {
              y1c = 480.0f;
            }
            while (0);
""",
# both clamps in one shared block
'both': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            y1c = y1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            if (!(y1f < 480.0f))
            {
              y1c = 480.0f;
            }
""",
# clamp via a nested if that also stores x1c
'nest': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            y1c = y1f;
            if (y1f >= 480.0f)
            {
              y1c = 480.0f;
            }
""",
# clamp written with an explicit else
'else': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            if (y1f < 480.0f)
            {
              y1c = y1f;
            }
            else
            {
              y1c = 480.0f;
            }
""",
# y1c clamp expressed as MIN against the literal written the other way
'min': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
            y1c = y1f;
            if (480.0f < y1f)
            {
              y1c = 480.0f;
            }
""",
# both clamps through one predicate chain
'chain': """            y1f = (cellH * ((f32) run)) + fy;
            x1c = x1f;
            y1c = y1f;
            if (!(x1f < 640.0f)) x1c = 640.0f;
            if (!(y1f < 480.0f)) y1c = 480.0f;
""",
# x1c clamp after the y1c clamp (source order swap), y1c nested
'swapnest': """            y1f = (cellH * ((f32) run)) + fy;
            y1c = y1f;
            if (!(y1f < 480.0f))
            {
              {
                y1c = 480.0f;
              }
            }
            x1c = x1f;
            if (!(x1f < 640.0f))
            {
              x1c = 640.0f;
            }
""",
}

for k, v in FORMS.items():
    (OUT / f'{k}.c').write_text(HEAD_PART + v + TAIL_PART)
print(len(FORMS))
