import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbm import PK
HI = [40, 72, 128]
def mk(parts, form):
    out = ''
    for p, hi in zip(parts, HI):
        if form == 'for': out += f'    for (; i < {hi};) *palette++ = {p};\n'
        elif form == 'dw': out += f'    if (i < {hi}) do {{ *palette++ = {p}; }} while (i < {hi});\n'
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n')
    return bbl.HEAD + pre + out + bbl.TAIL
names, srcs = [], []
for form in ['for', 'dw']:
    for rinc, ginc, binc in itertools.product(['i++ - 8', '(i++) - 8'], ['i++ - 40'], ['i++ - 72']):
        parts = [PK(f'({rinc}) << 3', '0', '0'), PK('248', f'({ginc}) << 3', '0'), PK('248', '248', f'({binc}) << 2')]
        names.append((form, rinc)); srcs.append(mk(parts, form))
res = bbl.run(srcs)
for n, r in zip(names, res): print(n, r[0] if r else None)
