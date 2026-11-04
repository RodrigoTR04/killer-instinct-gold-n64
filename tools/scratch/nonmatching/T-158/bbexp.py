import sys, itertools, random
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region, TR
from bbred5 import rdiff
seed = int(sys.argv[1]); N = int(sys.argv[2])
rnd = random.Random(seed)
GREEN = '    for (; i < 72; i++) *palette++ = ((((248) << 8) & 0xF800) | ((((i - 40) << 3) << 3) & 0x7C0) | (((0) >> 2) & 0x3E) | 1);\n'
BLUE = '    for (; i < 128; i++) *palette++ = ((((248) << 8) & 0xF800) | (((248) << 3) & 0x7C0) | ((((i - 72) << 2) >> 2) & 0x3E) | 1);\n'
CT = ['(u8)', '(s8)', '(u16)', '(s16)', '(s32)', '(u32)']
def rexpr():
    e = '(i - 8)'
    for _ in range(rnd.randint(1, 4)):
        k = rnd.random()
        if k < 0.45: e = f'({e} << 3)'
        elif k < 0.55: e = f'({e} * 8)'
        elif k < 0.7: e = f'({e} & {rnd.choice(["0xFF", "0xF8", "0xFFFF", "0xFFF8"])})'
        elif k < 0.8: e = f'({e} | 0)'
        elif k < 0.95: e = f'{rnd.choice(CT)}{e}'
        else: e = f'({e} + 0)'
    if '<< 3' not in e and '* 8' not in e: e = f'({e} << 3)'
    return e
def pack(r, style):
    if style == 0: return f'((({r}) << 8) & 0xF800) | (((0) << 3) & 0x7C0) | (((0) >> 2) & 0x3E) | 1'
    if style == 1: return f'((({r}) << 8) & 0xF800) | 1'
    if style == 2: return f'(((({r}) << 8) & 0xF800) | 1)'
    return f'((({r}) << 8) & 0xF800) | (((g) << 3) & 0x7C0) | (((b) >> 2) & 0x3E) | 1'
cands = []
for _ in range(N):
    r = rexpr(); st = rnd.choice([0, 1, 2, 3])
    form = rnd.choice(['for', 'dw'])
    body = f'*palette++ = {pack(r, st)};'
    if form == 'for': loop = f'    for (; i < 40; i++) {{ {body} }}\n'
    else: loop = f'    if (i < 40) do {{ {body} i++; }} while (i < 40);\n'
    cands.append((r, st, form, loop))
srcs = [bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, g = 0, b = 0;\n') + c[3] + GREEN + BLUE + bbl.TAIL for c in cands]
res = bbl.run(srcs)
rows = sorted([(rdiff(region(r[1])), r[0], i) for i, r in enumerate(res) if r])
from collections import Counter
print(Counter(x[0] for x in rows).most_common(6))
for sc, tot, i in rows[:5]: print(sc, tot, cands[i][:3], region(res[i][1])[2:8])
