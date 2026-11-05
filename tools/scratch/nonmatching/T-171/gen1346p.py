#!/usr/bin/env python3
"""func_8001346C: do/while block boundaries (the lever that took
func_801BCB70 220->63 and func_800297A4 178->148)."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1346p')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346j/ip_p_s32.c').read_text()

SITES = {
's1': ('            g->value = (u32)part->display;\n',
       '            do { g->value = (u32)part->display; } while (0);\n'),
's2': ('        D_8004A984 = 0;\n',
       '        do { D_8004A984 = 0; } while (0);\n'),
's3': ('            g->command = 0x06000000;\n',
       '            do { g->command = 0x06000000; } while (0);\n'),
's4': ('        a = D_8004AC92; b = D_8004AC8E;\n',
       '        do { a = D_8004AC92; b = D_8004AC8E; } while (0);\n'),
's5': ('          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }\n',
       '          do { for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } } while (0); }\n'),
's6': ('        func_8001BB64(arg0);\n    }\n    mode = part->flags & 15;',
       '        do { func_8001BB64(arg0); } while (0);\n    }\n    mode = part->flags & 15;'),
's7': ('    mode = part->flags & 15;\n', '    do { mode = part->flags & 15; } while (0);\n'),
's8': ('        if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1;\n',
       '        do { if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1; } while (0);\n'),
's9': ('    if ((part->flags & 0xF0) >= 16) {\n        a = D_8004AC92;',
       '    do { if ((part->flags & 0xF0) >= 16) {\n        a = D_8004AC92;'),
}

CLOSE_S9 = ('        func_8001BB64(arg0);\n    }\n}\n', '        func_8001BB64(arg0);\n    } } while (0);\n}\n')

n = 0
for r in (1, 2, 3):
    for combo in itertools.combinations(['s1','s2','s3','s4','s6','s7','s8'], r):
        t = BASE
        ok = True
        for c in combo:
            old, new = SITES[c]
            if old not in t:
                ok = False; break
            t = t.replace(old, new, 1)
        if not ok: continue
        (OUT / f'{"".join(combo)}.c').write_text(t)
        n += 1
print(n)
