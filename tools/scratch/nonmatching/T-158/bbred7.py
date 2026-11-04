import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region, TR
from bbred5 import rdiff
F = {
 'base': '    if (i < 40) do {{ *palette++ = (u16)((u16)({a}) << 11) | 1; i++; }} while (i < 40);\n',
 'inc_in_a': '    if (i < 40) do {{ *palette++ = (u16)((u16)(({i}++) - 8) << 11) | 1; }} while (i < 40);\n',
 'for': '    for (; i < 40; i++) *palette++ = (u16)((u16)(i - 8) << 11) | 1;\n',
 'whilepre': '    if (i < 40) do {{ *palette++ = (u16)((u16)(i - 8) << 11) | 1; }} while (++i < 40);\n',
 'wh': '    while (i < 40) {{ *palette++ = (u16)((u16)(i - 8) << 11) | 1; i++; }}\n',
 'var_u16': '    if (i < 40) do {{ r = i - 8; i++; *palette++ = (u16)(r << 11) | 1; }} while (i < 40);\n',
 'var_u16b': '    if (i < 40) do {{ r = i - 8; *palette++ = (u16)(r << 11) | 1; i++; }} while (i < 40);\n',
 'var_u16c': '    if (i < 40) do {{ r = i - 8; i++; c = (r << 11) | 1; *palette++ = c; }} while (i < 40);\n',
 'var_u16d': '    if (i < 40) do {{ r = i - 8; c = (r << 11) | 1; i++; *palette++ = c; }} while (i < 40);\n',
 'var_u16e': '    if (i < 40) do {{ r = i - 8; i++; c = r << 11; *palette++ = c | 1; }} while (i < 40);\n',
}
names = []; srcs = []
for k, t in F.items():
    for rt in ['u16', 's16']:
        for ct in ['u16', 's16', 's32']:
            body = t.format(a='i - 8', i='i')
            decl = f'    {rt} r;\n    {ct} c;\n'
            names.append((k, rt, ct))
            srcs.append(bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + decl) + body + GB + bbl.TAIL)
res = bbl.run(srcs)
rows = sorted([(rdiff(region(r[1])), r[0], n, region(r[1])[2:8]) for n, r in zip(names, res) if r], key=lambda x: x[:2])
for x in rows[:14]: print(x)
print('----')
for x in rows:
    if x[2][0].startswith('var') and x[2][1]=='u16' and x[2][2] in ('u16','s32'): print(x[0], x[2], x[3])
