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
F = {
 'base': f'    for (; i < 40; i++) *palette++ = {RE};\n',
 'le39': f'    for (; i <= 39; i++) *palette++ = {RE};\n',
 'ne': f'    for (; i != 40; i++) *palette++ = {RE};\n',
 'gt': f'    for (; 40 > i; i++) *palette++ = {RE};\n',
 'inc_cond': f'    if (i < 40) do {{ *palette++ = {RE}; }} while (++i < 40);\n',
 'inc_cond_le': f'    if (i < 40) do {{ *palette++ = {RE}; }} while (++i <= 39);\n',
 'p1': f'    for (; i + 1 < 41; i++) *palette++ = {RE};\n',
 'p1b': f'    if (i + 1 < 41) do {{ *palette++ = {RE}; i++; }} while (i + 1 < 41);\n',
 'neg': f'    for (; !(i >= 40); i++) *palette++ = {RE};\n',
 'forever': f'    for (;;) {{ if (i >= 40) break; *palette++ = {RE}; i++; }}\n',
 'forever2': f'    for (;;) {{ *palette++ = {RE}; i++; if (i >= 40) break; }}\n',
 'sub': f'    for (; i - 40 < 0; i++) *palette++ = {RE};\n',
 'cnt': f'    for (n = 32; n > 0; n--, i++) *palette++ = {RE};\n',
 'cnt2': f'    for (n = 40 - i; n > 0; n--, i++) *palette++ = {RE};\n',
}
names = list(F)
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, n;\n') + F[n] + GREEN + BLUE + bbl.TAIL for n in names]
res = bbl.run(srcs)
for n, r in zip(names, res):
    if r: print(n, r[0], rdiff(region(r[1])), region(r[1])[:9])
