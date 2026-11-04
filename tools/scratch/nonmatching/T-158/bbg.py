import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
from bbred5 import rdiff
def mkfn(decl, red, green, blue):
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n' + decl)
    return bbl.HEAD + pre + red + green + blue + bbl.TAIL
names, srcs = [], []
for tr in ['u8', 's32', 'u16', 's16', 'u32']:
    for mul in ['* 8', '<< 3']:
        for pk in ['full', 'mask']:
            if pk == 'full':
                R = f'    if (i < 40) do {{ red = (i - 8) {mul}; *palette++ = ((red << 8) & 0xF800) | ((0 << 3) & 0x7C0) | ((0 >> 2) & 0x3E) | 1; i++; }} while (i < 40);\n'
                G = f'    if (i < 72) do {{ green = (i - 40) {mul}; *palette++ = ((248 << 8) & 0xF800) | ((green << 3) & 0x7C0) | ((0 >> 2) & 0x3E) | 1; i++; }} while (i < 72);\n'
            else:
                R = f'    if (i < 40) do {{ red = (i - 8) {mul}; *palette++ = ((red << 8) & 0xF800) | 1; i++; }} while (i < 40);\n'
                G = f'    if (i < 72) do {{ green = (i - 40) {mul}; *palette++ = 0xF800 | ((green << 3) & 0x7C0) | 1; i++; }} while (i < 72);\n'
            B = '    if (i < 128) do { *palette++ = (i - 72) | 0xFFC1; i++; } while (i < 128);\n'
            names.append((tr, mul, pk)); srcs.append(mkfn(f'    {tr} red, green;\n', R, G, B))
res = bbl.run(srcs)
for n, r in zip(names, res):
    if not r: print(n, None); continue
    ls = r[1]
    print(n, r[0], 'red', region(ls)[2:8], '\n      green', seg(ls, 'green')[2:9])
print('TARGET red', region(bbl.TGT)[2:8]); print('TARGET green', TG[2:9])
