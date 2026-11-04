import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region, TR
from bbred5 import rdiff
from bbm import PK
GREEN = '    for (; i < 72; i++) *palette++ = ' + PK('248', '(i - 40) << 3', '0') + ';\n'
BLUE = '    for (; i < 128; i++) *palette++ = ' + PK('248', '248', '(i - 72) << 2') + ';\n'
RE = PK('(i - 8) << 3', '0', '0')
RE2 = '(((((i - 8) << 3)) << 8) & 0xF800) |\n        (((0) << 3) & 0x7C0) |\n        (((0) >> 2) & 0x3E) |\n        1'
F = {
 'one': f'    for (; i < 40; i++) *palette++ = {RE};\n',
 'body_nl': f'    for (; i < 40; i++)\n        *palette++ = {RE};\n',
 'brace': f'    for (; i < 40; i++) {{\n        *palette++ = {RE};\n    }}\n',
 'brace2': f'    for (; i < 40; i++)\n    {{\n        *palette++ = {RE};\n    }}\n',
 'multiline_expr': f'    for (; i < 40; i++)\n        *palette++ = {RE2};\n',
 'for_split': f'    for (;\n         i < 40;\n         i++)\n        *palette++ = {RE};\n',
 'for_split2': f'    for (;\n         i < 40;\n         i++) {{\n        *palette++ = {RE};\n    }}\n',
 'dw': f'    if (i < 40) do {{\n        *palette++ = {RE};\n        i++;\n    }} while (i < 40);\n',
 'while': f'    while (i < 40) {{\n        *palette++ = {RE};\n        i++;\n    }}\n',
 'while2': f'    while (i < 40)\n    {{\n        *palette++ = {RE2};\n        i++;\n    }}\n',
}
names = list(F)
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n') + F[n] + GREEN + BLUE + bbl.TAIL for n in names]
res = bbl.run(srcs)
for n, r in zip(names, res):
    if r: print(n, r[0], rdiff(region(r[1])), region(r[1])[2:8])
