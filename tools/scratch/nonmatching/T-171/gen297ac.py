#!/usr/bin/env python3
"""func_800297A4: stack more do/while block boundaries on the 148-word base."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297ac')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_800297A4.c').read_text()

SITES = {
's1': ('        p->age[j] = 0;\n', '        do { p->age[j] = 0; } while (0);\n'),
's2': ('        p->position[j] = (float) (u32) (func_800326F0() & 15);\n',
       '        do { p->position[j] = (float) (u32) (func_800326F0() & 15); } while (0);\n'),
's3': ('        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);\n',
       '        do { p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed); } while (0);\n'),
's4': ('    angle = 0;\n', '    do { angle = 0; } while (0);\n'),
's5': ('            p->flags[j] = 0;\n        } else if (j < 8) {',
       '            p->flags[j] = 0;\n        } else if (j < 8) {'),
's6': ('    if (i == 4) p = (T171Burst *) D_80061D60;\n',
       '    if (i == 4) { p = (T171Burst *) D_80061D60; }\n'),
's7': ('        if (j < 4) {\n', '        do { if (j < 4) {\n'),
}

n = 0
for r in (1, 2):
    for combo in itertools.combinations(['s1','s2','s3','s4','s6','s7'], r):
        t = BASE
        ok = True
        for c in combo:
            old, new = SITES[c]
            if old not in t:
                ok = False; break
            t = t.replace(old, new, 1)
        if not ok: continue
        if 's7' in combo:
            # close the extra loop before the body's closing brace
            t = t.replace("""        p->duration[j] = life - (func_800326F0() & 7);
    }
}""", """        p->duration[j] = life - (func_800326F0() & 7);
    } } while (0);
}""")
        (OUT / f'{"".join(combo)}.c').write_text(t)
        n += 1
print(n)
