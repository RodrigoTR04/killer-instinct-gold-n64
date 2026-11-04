import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region, TR
from bbgb import seg, TG, TB, sdiff
from bbred5 import rdiff
PK = '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1'
def stm(kind):
    return {'r': None}
def loop(hi, assigns, order):
    items = {'a%d' % k: a for k, a in enumerate(assigns)}
    items['st'] = f'*palette++ = {PK};'
    items['inc'] = 'i++;'
    body = ' '.join(items[k] for k in order)
    return f'    if (i < {hi}) do {{ {body} }} while (i < {hi});\n'
RA = ['r = (i - 8) << 3;', 'g = 0;', 'b = 0;']
GA = ['r = 248;', 'g = (i - 40) << 3;', 'b = 0;']
BA = ['r = 248;', 'g = 248;', 'b = (i - 72) << 2;']
BL = loop(128, BA, ['a0', 'a1', 'a2', 'st', 'inc'])
RED0 = loop(40, RA, ['a0', 'a1', 'a2', 'inc', 'st'])
def keys(): return ['a0', 'a1', 'a2', 'st', 'inc']
def mk(red, green, blue):
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, r, g, b;\n')
    return bbl.HEAD + pre + red + green + blue + bbl.TAIL
GRN0 = loop(72, GA, ['a0', 'a1', 'a2', 'inc', 'st'])
perms = list(itertools.permutations(keys()))
# red search
srcs = [mk(loop(40, RA, p), GRN0, BL) for p in perms]
res = bbl.run(srcs)
import sys as _s
if len(_s.argv) > 1: pass
print('RED')
rows = sorted([(rdiff(region(r[1])), r[0], p) for p, r in zip(perms, res) if r])
for x in rows[:6]: print(x)
srcs = [mk(RED0, loop(72, GA, p), BL) for p in perms]
res = bbl.run(srcs)
print('GREEN')
rows = sorted([(sdiff(TG, seg(r[1], 'green')), r[0], p) for p, r in zip(perms, res) if r])
for x in rows[:6]: print(x)
print('DISTINCT RED')
srcs = [mk(loop(40, RA, p), GRN0, BL) for p in perms]
res = bbl.run(srcs)
seen = {}
for p, r in zip(perms, res):
    if r: seen.setdefault(tuple(region(r[1])[2:8]), []).append(p)
for k, v in seen.items(): print(len(v), v[0], k)
