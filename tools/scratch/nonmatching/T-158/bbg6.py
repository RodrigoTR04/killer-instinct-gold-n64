import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
from bbg5 import L, R, G, PK
names, srcs = [], []
for rv, gv, bv in itertools.product(['248', '255', '31 << 3'], ['248', '255', '31 << 3'], ['(i - 72) << 2', '(i - 72) * 4', '(i - 72) << 3', '(i - 72) << 1', 'i - 72', '(i - 72) * 8']):
    for ty in ['s32', 'u8', 'u32']:
        pre = bbl.PRE.replace('    s32 i, red, green;\n', f'    s32 i;\n    {ty} r, g, b;\n')
        names.append((rv, gv, bv, ty))
        srcs.append(bbl.HEAD + pre + R + G + L(128, f'r = {rv}; g = {gv}; b = {bv};', PK) + bbl.TAIL)
res = bbl.run(srcs)
rows = sorted([(sdiff(TB, seg(r[1], 'blue')), r[0], n, seg(r[1], 'blue')[2:9]) for n, r in zip(names, res) if r], key=lambda x: (x[0], x[1]))
for x in rows[:12]: print(x)
