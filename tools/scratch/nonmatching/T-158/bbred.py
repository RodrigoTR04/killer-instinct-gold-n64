import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
G_AND_B = '''    if (i < 72) do
    {
        green = i - 40;
        i++;
        *palette++ = ((green << 6) & 0x7C0) | 0xF801;
    }
    while (i < 72);
    if (i < 128) do
    {
        *palette++ = (i - 72) | 0xFFC1; i++;
    }
    while (i < 128);
'''
types = ['', 's32', 'u32', 's16', 'u16', 'u8', 's8']
casts = ['{}', '(u16)({})', '(s16)({})', '({}) & 0xFFFF']
exprs = ['(({r}) << 11) | 1', '(({r}) * 0x800) | 1', '(({r}) << 11) + 1', '(({r}) << 11) | (0 << 6) | (0 << 1) | 1']
forms = ['dw_inc_first', 'dw_inc_after', 'for', 'while', 'for_var']
def build(ty, cast, ex, form):
    decl = f'    {ty} red;\n' if ty else ''
    r = 'red' if ty else '(i - 8)'
    val = cast.format(ex.format(r=r))
    if form == 'dw_inc_first':
        if ty: body = f'    if (i < 40) do {{ red = i - 8; i++; *palette++ = {val}; }} while (i < 40);\n'
        else: return None
    elif form == 'dw_inc_after':
        body = (f'    if (i < 40) do {{ red = i - 8; *palette++ = {val}; i++; }} while (i < 40);\n' if ty else
                f'    if (i < 40) do {{ *palette++ = {val}; i++; }} while (i < 40);\n')
    elif form == 'for':
        body = (f'    for (; i < 40; i++) {{ red = i - 8; *palette++ = {val}; }}\n' if ty else
                f'    for (; i < 40; i++) *palette++ = {val};\n')
    elif form == 'while':
        body = (f'    while (i < 40) {{ red = i - 8; *palette++ = {val}; i++; }}\n' if ty else
                f'    while (i < 40) {{ *palette++ = {val}; i++; }}\n')
    else:
        if not ty: return None
        body = f'    for (red = i - 8; i < 40; i++, red++) *palette++ = {val};\n'
    return bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + decl if decl else '    s32 i, green;\n') + body + G_AND_B + bbl.TAIL
cands = {}
for t in itertools.product(types, casts, exprs, forms):
    s = build(*t)
    if s: cands[t] = s
names = list(cands)
res = bbl.run([cands[n] for n in names])
out = sorted([(r[0], n) for n, r in zip(names, res) if r])
for x in out[:25]: print(x)
print(len(out))
