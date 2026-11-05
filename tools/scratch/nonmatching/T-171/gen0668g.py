#!/usr/bin/env python3
"""func_801B0668: split the sine/cosine and matrix temporaries into their own
names, matching the target's f24/f26/f28/f30 double-register set."""
from pathlib import Path
OUT = Path('/tmp/v0668g')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

# Variants of the tail, where the FP temp order actually differs.
TAIL_OLD = """  guScale(arg2, D_802928D0, D_802928D0, 1.0f);
  guTranslate(arg2 + 0x40, (f32) (((((f64) (-height)) + 50.0) - D_802928D8) - 8.0), 8.0f, 170.0f);
  temp_f2 = (f64) arg3 * D_802928E0;
  sine = sinf((f32) (temp_f2 / 2));
  guLookAtReflect(&sp60, &D_802C8760, sine * 60.0f, cosf((f32) temp_f2) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
"""
assert TAIL_OLD in BASE

V = {
# g1: translate y split into named pieces (target: neg, +50, -D8, -8 in double)
'g1': """  guScale(arg2, D_802928D0, D_802928D0, 1.0f);
  { f64 ty = (f64) (-height);
    ty = ty + 50.0;
    ty = ty - D_802928D8;
    ty = ty - 8.0;
    guTranslate(arg2 + 0x40, (f32) ty, 8.0f, 170.0f); }
  temp_f2 = (f64) arg3 * D_802928E0;
  sine = sinf((f32) (temp_f2 / 2));
  guLookAtReflect(&sp60, &D_802C8760, sine * 60.0f, cosf((f32) temp_f2) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
""",
# g2: separate the angle and the cosine into named doubles
'g2': """  { f64 angle = (f64) arg3 * D_802928E0;
    guScale(arg2, D_802928D0, D_802928D0, 1.0f);
    guTranslate(arg2 + 0x40, (f32) (((((f64) (-height)) + 50.0) - D_802928D8) - 8.0), 8.0f, 170.0f);
    sine = sinf((f32) (angle / 2));
    guLookAtReflect(&sp60, &D_802C8760, sine * 60.0f, cosf((f32) angle) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); }
""",
# g3: sine and cosine into two named f32 locals
'g3': """  guScale(arg2, D_802928D0, D_802928D0, 1.0f);
  guTranslate(arg2 + 0x40, (f32) (((((f64) (-height)) + 50.0) - D_802928D8) - 8.0), 8.0f, 170.0f);
  temp_f2 = (f64) arg3 * D_802928E0;
  { f32 s = sinf((f32) (temp_f2 / 2));
    f32 c = cosf((f32) temp_f2);
    guLookAtReflect(&sp60, &D_802C8760, s * 60.0f, c * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); }
""",
# g4: half angle as its own double
'g4': """  guScale(arg2, D_802928D0, D_802928D0, 1.0f);
  guTranslate(arg2 + 0x40, (f32) (((((f64) (-height)) + 50.0) - D_802928D8) - 8.0), 8.0f, 170.0f);
  temp_f2 = (f64) arg3 * D_802928E0;
  { f64 half = temp_f2 / 2;
    sine = sinf((f32) half); }
  guLookAtReflect(&sp60, &D_802C8760, sine * 60.0f, cosf((f32) temp_f2) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
""",
}

for k, v in V.items():
    (OUT / f'{k}.c').write_text(BASE.replace(TAIL_OLD, v))
print(len(V))
