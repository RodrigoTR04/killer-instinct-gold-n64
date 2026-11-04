import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region, TR
from bbred5 import rdiff
from bbm import PK
GREEN = '    for (; i < 72; i++) *palette++ = ' + PK('248', '(i - 40) << 3', '0') + ';\n'
BLUE = '    for (; i < 128; i++) *palette++ = ' + PK('248', '248', '(i - 72) << 2') + ';\n'
E = lambda v: PK(f'({v} - 8) << 3', '0', '0')
forms = {
 'k_postinc': '    while (i < 40) { k = i++; *palette++ = %s; }\n' % E('k'),
 'k_then_inc': '    while (i < 40) { k = i; i++; *palette++ = %s; }\n' % E('k'),
 'k_then_inc_cast': '    while (i < 40) { k = i; i = k + 1; *palette++ = %s; }\n' % E('k'),
 'inline_postinc': '    while (i < 40) { *palette++ = %s; }\n' % E('(i++)'),
 'comma': '    while (i < 40) { *palette++ = (i++, %s); }\n' % E('(i - 1)'),
}
names = list(forms)
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, k;\n') + forms[n] + GREEN + BLUE + bbl.TAIL for n in names]
res = bbl.run(srcs)
for n, r in zip(names, res):
    if r: print(n, r[0], rdiff(region(r[1])), region(r[1])[2:9])
