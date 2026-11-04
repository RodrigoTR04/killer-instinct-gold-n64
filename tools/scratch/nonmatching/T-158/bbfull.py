import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
PK = '((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1'
A = {'red': ['r = (i - 8) << 3;', 'g = 0;', 'b = 0;'],
     'green': ['r = 248;', 'g = (i - 40) << 3;', 'b = 0;'],
     'blue': ['r = 248;', 'g = 248;', 'b = (i - 72) << 2;']}
HI = {'red': 40, 'green': 72, 'blue': 128}
def loop(name, form, incpos, colvar):
    hi = HI[name]; a = list(A[name])
    st = f'color = {PK}; *palette++ = color;' if colvar else f'*palette++ = {PK};'
    if form == 'for':
        body = ' '.join(a) + ' ' + st
        return f'    for (; i < {hi}; i++) {{ {body} }}\n'
    items = a + [st]
    if incpos == 'end': items.append('i++;')
    elif incpos == 'beforest': items.insert(len(a), 'i++;')
    elif incpos == 'first': items.insert(0, 'i++;')  # not valid semantics (changes i); skip
    elif incpos == 'afterfirst': items.insert(1, 'i++;')
    body = ' '.join(items)
    if form == 'dw': return f'    if (i < {hi}) do {{ {body} }} while (i < {hi});\n'
    return f'    while (i < {hi}) {{ {body} }}\n'
def build(forms, incs, colvar, ty, cty):
    decl = f'    {ty} r, g, b;\n' + (f'    {cty} color;\n' if colvar else '')
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n' + decl)
    return bbl.HEAD + pre + ''.join(loop(n, f, ip, colvar) for n, f, ip in zip(['red', 'green', 'blue'], forms, incs)) + bbl.TAIL
if __name__ == '__main__':
    names, srcs = [], []
    for form in ['dw', 'for', 'while']:
        for ip in ['end', 'beforest', 'afterfirst']:
            for colvar, cty in [(False, ''), (True, 's32'), (True, 'u16'), (True, 's16'), (True, 'u32')]:
                for ty in ['s32', 'u32']:
                    if form == 'for' and ip != 'end': continue
                    names.append((form, ip, cty, ty))
                    srcs.append(build([form] * 3, [ip] * 3, colvar, ty, cty))
    res = bbl.run(srcs)
    rows = sorted([(r[0], n) for n, r in zip(names, res) if r])
    for x in rows[:15]: print(x)
