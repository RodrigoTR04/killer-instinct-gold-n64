import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
def PK(r, g, b, a='1'):
    return f'((({r}) << 8) & 0xF800) | ((({g}) << 3) & 0x7C0) | ((({b}) >> 2) & 0x3E) | ({a})'
def build(form, ip, rt='s32'):
    P = [PK('(i - 8) << 3', '0', '0'), PK('248', '(i - 40) << 3', '0'), PK('248', '248', '(i - 72) << 2')]
    HI = [40, 72, 128]
    out = ''
    for p, hi in zip(P, HI):
        if form == 'for': out += f'    for (; i < {hi}; i++) *palette++ = {p};\n'
        elif form == 'dw_end': out += f'    if (i < {hi}) do {{ *palette++ = {p}; i++; }} while (i < {hi});\n'
        elif form == 'while': out += f'    while (i < {hi}) {{ *palette++ = {p}; i++; }}\n'
        elif form == 'dw_postinc': out += f'    if (i < {hi}) do {{ *palette++ = {p}; }} while (++i < {hi});\n'
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n')
    return bbl.HEAD + pre + out + bbl.TAIL
names, srcs = [], []
for f in ['for', 'dw_end', 'while', 'dw_postinc']:
    names.append(f); srcs.append(build(f, ''))
res = bbl.run(srcs)
for n, r in zip(names, res): print(n, r[0] if r else None)
open('/tmp/bbm_for.c', 'w').write(srcs[0])
