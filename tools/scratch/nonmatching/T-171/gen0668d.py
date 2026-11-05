#!/usr/bin/env python3
"""func_801B0668: stop IDO from speculating the D_801D2FC0 load."""
from pathlib import Path
OUT = Path('/tmp/v0668d')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

TESTS = {
'q1': '      if (!(D_801D2FC0 & 0x7F))\n',
'q2': '      if ((D_801D2FC0 & 0x7F) == 0)\n',
'q3': '      if ((D_801D2FC0 & 0x7F) != 0) {} else\n',
'q4': '      if (!(D_801D2FC0 & 0x7f) )\n',
}
ORs = {
'o1': '        D_801D2FC0 |= 1;\n',
'o2': '        D_801D2FC0 = D_801D2FC0 | 1;\n',
'o3': '        D_801D2FC0 += 1;\n',
}
ELSES = {
'e1': '    { D_801D2FC0 &= 0x80;\n    }\n',
'e2': '    { D_801D2FC0 = D_801D2FC0 & 0x80;\n    }\n',
'e3': '    { state = D_801D2FC0; D_801D2FC0 = state & 0x80;\n    }\n',
}

OLD = """      if (!(D_801D2FC0 & 0x7F))
      {
        func_8002F6F4(D_80066C40, 0x135, &D_8004A258);
        D_801D2FC0 |= 1;
      }
    }
    else
    { D_801D2FC0 &= 0x80;
    }
"""
assert OLD in BASE

n = 0
for tk, test in TESTS.items():
    for ok, orr in ORs.items():
        for ek, els in ELSES.items():
            new = (test + '      {\n        func_8002F6F4(D_80066C40, 0x135, &D_8004A258);\n'
                   + orr + '      }\n    }\n    else\n' + els)
            (OUT / f'{tk}_{ok}_{ek}.c').write_text(BASE.replace(OLD, new))
            n += 1
print(n)
