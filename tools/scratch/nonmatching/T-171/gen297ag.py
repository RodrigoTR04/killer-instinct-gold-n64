#!/usr/bin/env python3
"""func_800297A4: blocks on the scan loop and header, on top of the 148 base."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297ag')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_800297A4.c').read_text()

CAND = {
# wrap the scan's i++ (first statement of the loop body)
's1': ('    while (p->timer >= 0) {\n        i++;\n', '    while (p->timer >= 0) {\n        do { i++; } while (0);\n'),
# wrap p++
's2': ('        if (i >= 4) break;\n        p++;\n', '        if (i >= 4) break;\n        do { p++; } while (0);\n'),
# wrap each header store
's3': ('    p->z = z;\n', '    do { p->z = z; } while (0);\n'),
's4': ('    p->x = x;\n', '    do { p->x = x; } while (0);\n'),
's5': ('    p->y = y;\n', '    do { p->y = y; } while (0);\n'),
's6': ('    p->timer = 0;\n', '    do { p->timer = 0; } while (0);\n'),
's7': ('    p->limit = life;\n', '    do { p->limit = life; } while (0);\n'),
's8': ('    p->kind = kind;\n', '    do { p->kind = kind; } while (0);\n'),
# wrap the reset
's9': ('    if (i == 4) p = (T171Burst *) D_80061D60;\n',
       '    if (i == 4) { p = (T171Burst *) D_80061D60; }\n'),
}

n = 0
keys = list(CAND)
for r in (1, 2, 3):
    for combo in itertools.combinations(keys, r):
        t = BASE
        ok = True
        for c in combo:
            old, new = CAND[c]
            if old not in t:
                ok = False; break
            t = t.replace(old, new, 1)
        if not ok: continue
        (OUT / f'{"".join(combo)}.c').write_text(t)
        n += 1
print(n)
