#!/usr/bin/env python3
"""func_801B0668: do/while block boundaries (the lever that took 801BCB70
220->63 and 800297A4 178->148)."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v0668m')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

SITES = {
's1': ('        func_8002F6F4(D_80066C40, 0x135, &D_8004A258);\n        D_801D2FC0 |= 1;\n',
       '        do { func_8002F6F4(D_80066C40, 0x135, &D_8004A258);\n             D_801D2FC0 |= 1; } while (0);\n'),
's2': ('    { D_801D2FC0 &= 0x80;\n    }\n',
       '    do { D_801D2FC0 &= 0x80; } while (0);\n'),
's3': ('      func_801ADAD4(40); state = D_801D2FC0;\n      D_801D2FC0 = state | 3; }\n',
       '      func_801ADAD4(40);\n      do { state = D_801D2FC0;\n           D_801D2FC0 = state | 3; } while (0); }\n'),
's4': ('      state++;\n      D_801D2FC0 = state;\n',
       '      do { state++;\n           D_801D2FC0 = state; } while (0);\n'),
's5': ('        func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);\n        D_801D2FC0 = 0x82;\n',
       '        do { func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);\n             D_801D2FC0 = 0x82; } while (0);\n'),
's6': ('      height = 120.0 - ((cosf((height * D_802928C0) * 0.75) * 60.0f) / D_802928C8);\n',
       '      do { height = 120.0 - ((cosf((height * D_802928C0) * 0.75) * 60.0f) / D_802928C8); } while (0);\n'),
's7': ('    height -= 35.0f; if (height <= 200.0f)\n',
       '    height -= 35.0f;\n    do { if (height <= 200.0f)\n'),
's8': ('  func_801C35AC(arg0, ((s32) (((u32) arg3) >> 1)) % 360);\n',
       '  do { func_801C35AC(arg0, ((s32) (((u32) arg3) >> 1)) % 360); } while (0);\n'),
}
CLOSE_S7 = ('    else\n    { D_801D2FC0 &= 0x80;\n    }\n', '    else\n    { D_801D2FC0 &= 0x80;\n    } } while (0);\n')

n = 0
for r in (1, 2, 3):
    for combo in itertools.combinations(['s1','s2','s3','s4','s5','s6','s8'], r):
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
