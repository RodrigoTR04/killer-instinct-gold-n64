import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
from bbred5 import rdiff
PK = '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1'
def loop(cnt, lo, hi, rexpr, gexpr, bexpr, pre='', colvar=None):
    pk = PK
    body = f'r = {rexpr}; g = {gexpr}; b = {bexpr}; '
    if colvar: body += f'color = {pk}; *palette++ = color; '
    else: body += f'*palette++ = {pk}; '
    return f'    if (i < {hi}) do {{ {body}i++; }} while (i < {hi});\n'
names, srcs = [], []
for ty in ['s32', 'u32', 'u8', 'u16', 's16']:
    for cv in [None, 's32', 'u16', 's16', 'u32']:
        R = loop(0, 8, 40, '(i - 8) << 3', '0', '0', colvar=cv)
        G = loop(0, 40, 72, '248', '(i - 40) << 3', '0', colvar=cv)
        B = loop(0, 72, 128, '248', '248', '0', colvar=cv)  # placeholder blue
        decl = f'    {ty} r, g, b;\n' + (f'    {cv} color;\n' if cv else '')
        pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n' + decl)
        names.append((ty, cv)); srcs.append(bbl.HEAD + pre + R + G + '    if (i < 128) do { *palette++ = (i - 72) | 0xFFC1; i++; } while (i < 128);\n' + bbl.TAIL)
res = bbl.run(srcs)
for n, r in zip(names, res):
    if not r: print(n, None); continue
    ls = r[1]
    print(n, r[0], 'red', region(ls)[2:8], '\n      green', seg(ls, 'green')[2:9], '\n      blue', seg(ls, 'blue')[2:9])
