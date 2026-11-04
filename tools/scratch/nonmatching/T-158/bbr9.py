import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region, TR
from bbred5 import rdiff
from bbm import PK
GREEN = '    for (; i < 72; i++) *palette++ = ' + PK('248', '(i - 40) << 3', '0') + ';\n'
BLUE = '    for (; i < 128; i++) *palette++ = ' + PK('248', '248', '(i - 72) << 2') + ';\n'
forms = {}
exprs = {
 'nomask': '(((i - 8) << 3) << 8) | 1',
 'mask': '((((i - 8) << 3) << 8) & 0xF800) | 1',
 'sh11': '((i - 8) << 11) | 1',
}
for en, e in exprs.items():
    for fn_, tmpl in {
        'for': '    for (; i < 40; i++) *palette++ = %s;\n',
        'dw_end': '    if (i < 40) do { *palette++ = %s; i++; } while (i < 40);\n',
        'dw_pre': '    if (i < 40) do { i++; *palette++ = %s; } while (i < 40);\n',
    }.items():
        e2 = e if fn_ != 'dw_pre' else e.replace('i - 8', 'i - 9')
        forms[(en, fn_)] = tmpl % e2
names = list(forms)
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n') + forms[n] + GREEN + BLUE + bbl.TAIL for n in names]
res = bbl.run(srcs)
for n, r in zip(names, res):
    if r: print(n, r[0], rdiff(region(r[1])), region(r[1])[2:8])
