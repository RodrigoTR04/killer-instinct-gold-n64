import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
PK = '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1'
def L(hi, body, pk):
    return f'    if (i < {hi}) do {{ {body} *palette++ = {pk}; i++; }} while (i < {hi});\n'
R = L(40, 'r = (i - 8) << 3; g = 0; b = 0;', PK)
G = L(72, 'r = 248; g = (i - 40) << 3; b = 0;', PK)
if __name__ == '__main__':
    Rp = ['((r << 8) & 0xF800)', '(r << 8)', '0xF800', '(248 << 8)', '((248 << 8) & 0xF800)']
    Gp = ['((g << 3) & 0x7C0)', '(g << 3)', '0x7C0', '((248 << 3) & 0x7C0)']
    Bp = ['b', '(b & 0x3E)', '((b >> 2) & 0x3E)', '(b | 0)', '(b & 0xFF)', '(b << 0)']
    Ap = ['1', 'a', '(a & 1)']
    sets = ['r = 248; g = 248; b = i - 72; a = 1;', 'r = 255; g = 255; b = i - 72; a = 1;', 'b = i - 72; a = 1;', 'a = 1; b = i - 72; r = 248; g = 248;', 'r = 248; g = 248; a = 1; b = i - 72;', 'r = 248; g = 248; b = i - 72;']
    names, srcs = [], []
    for st in sets:
        for rp, gp, bp, ap in itertools.product(Rp, Gp, Bp, Ap):
            if 'a' in ap and 'a = 1' not in st: continue
            pk = f'{rp} | {gp} | {bp} | {ap}'
            pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, r = 248, g = 248, b, a;\n')
            names.append((st, pk))
            srcs.append(bbl.HEAD + pre + R + G + L(128, st, pk) + bbl.TAIL)
    print(len(srcs), flush=True)
    res = bbl.run(srcs)
    rows = sorted([(sdiff(TB, seg(r[1], 'blue')), r[0], n, seg(r[1], 'blue')[2:9]) for n, r in zip(names, res) if r], key=lambda x: (x[0], x[1]))
    for x in rows[:12]: print(x)
