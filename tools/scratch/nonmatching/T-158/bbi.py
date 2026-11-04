import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region
from bbred5 import rdiff
names, srcs = [], []
E = {'cast2': '(u16)((u16)(i - 8) << 11) | 1', 'plain': '((i - 8) << 11) | 1'}
for it in ['s32', 's16', 'u16', 'u8', 's8', 'u32']:
    for ek, e in E.items():
        for form in ['dw', 'for']:
            pre = bbl.PRE.replace('    s32 i, red, green;\n', f'    {it} i;\n    s32 green;\n')
            body = (f'    if (i < 40) do {{ *palette++ = {e}; i++; }} while (i < 40);\n' if form == 'dw' else f'    for (; i < 40; i++) *palette++ = {e};\n')
            gb = GB.replace('green = i - 40;', 'green = i - 40;')
            names.append((it, ek, form)); srcs.append(bbl.HEAD + pre + body + gb + bbl.TAIL)
res = bbl.run(srcs)
for n, r in zip(names, res):
    print(n, r[0] if r else None, region(r[1])[2:9] if r else '')
