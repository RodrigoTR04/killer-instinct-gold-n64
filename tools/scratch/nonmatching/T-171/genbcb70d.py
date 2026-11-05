#!/usr/bin/env python3
"""func_801BCB70: give the mask its own cursor (target keeps s0 = mask, v1 = col*2)."""
from pathlib import Path
OUT = Path('/tmp/vbcb70d')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

OLD = """                    run = 1;
                    if (mask[col] & bit) {"""
assert OLD in BASE

V = {}
V['base'] = BASE
V['m1'] = BASE.replace("""                    run = 1;
                    if (mask[col] & bit) {""",
"""                    run = 1;
                    m = mask + col;
                    if (m[0] & bit) {""").replace(
"""                        while ((mask[col + run] & bit) && run < 5) {""",
"""                        while ((m[run] & bit) && run < 5) {""")
V['m2'] = V['m1'].replace("    u16 *mask", "    u16 *mask")
# add the declaration
for k in ('m1', 'm2'):
    t = V[k].replace("    T157Gfx *g;\n", "    T157Gfx *g;\n    u16 *m;\n")
    V[k] = t

# n: col cursor
V['c1'] = BASE.replace("""                do {
                    run = 1;
                    if (mask[col] & bit) {""",
"""                do {
                    run = 1;
                    m = mask + col;
                    if (m[0] & bit) {""").replace(
"""                        while ((mask[col + run] & bit) && run < 5) {""",
"""                        while ((m[run] & bit) && run < 5) {""")
V['c1'] = V['c1'].replace("    T157Gfx *g;\n", "    T157Gfx *g;\n    u16 *m;\n")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
