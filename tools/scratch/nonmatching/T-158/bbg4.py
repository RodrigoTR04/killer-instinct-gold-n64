import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
PK = '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1'
def L(hi, ra, ga, ba, pk=PK):
    return f'    if (i < {hi}) do {{ r = {ra}; g = {ga}; b = {ba}; *palette++ = {pk}; i++; }} while (i < {hi});\n'
R = L(40, '(i - 8) << 3', '0', '0')
G = L(72, '248', '(i - 40) << 3', '0')
forms = {}
for rv in ['248', '255', '0xF8']:
    for gv in ['248', '255']:
        for pk in [PK, '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | b | 1', '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | b', '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | b | 1', 'r << 8 | g << 3 | b | 1']:
            forms[(rv, gv, pk[-18:])] = L(128, rv, gv, 'i - 72', pk)
names = list(forms)
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, r, g, b;\n') + R + G + forms[n] + bbl.TAIL for n in names]
res = bbl.run(srcs)
rows = sorted([(sdiff(TB, seg(r[1], 'blue')), r[0], n, seg(r[1], 'blue')[2:9]) for n, r in zip(names, res) if r])
for x in rows[:10]: print(x)
print(TB[2:9])
