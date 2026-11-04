import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
def seg(ls, which):
    try: return _seg(ls, which)
    except StopIteration: return []
def _seg(ls, which):
    i72 = next(k for k, l in enumerate(ls) if l == 'slti at,v1,72')
    i128 = next(k for k, l in enumerate(ls) if l == 'slti at,v1,128' and k > i72)
    iend = next((k for k, l in enumerate(ls) if l.startswith('lui at,%hi(0x802c9f64)')), len(ls))
    if which == 'green': return ls[i72:i128]
    return ls[i128:iend]
TG, TB = seg(bbl.TGT, 'green'), seg(bbl.TGT, 'blue')
def sdiff(a, b):
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
RED = '    if (i < 40) do { *palette++ = (u16)((u16)(i - 8) << 11) | 1; i++; } while (i < 40);\n'
def full(green, blue, decl=''):
    return bbl.HEAD + bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, green;\n' + decl) + RED + green + blue + bbl.TAIL
BLUE0 = '    if (i < 128) do { *palette++ = (i - 72) | 0xFFC1; i++; } while (i < 128);\n'
GREEN0 = '    if (i < 72) do { *palette++ = (((i - 40) << 6) & 0x7C0) | 0xF801; i++; } while (i < 72);\n'
if __name__ == '__main__':
    print('target green', TG); print('target blue', TB)
    C = ['', 's16', 'u16', 's8', 'u8']
    def cast(t, e): return f'({t})({e})' if t else e
    names, srcs = [], []
    for c in itertools.product(C, repeat=5):
        a = cast(c[0], 'i - 40'); b = cast(c[1], f'({a}) << 6'); m = cast(c[2], f'({b}) & 0x7C0'); o = cast(c[3], f'({m}) | 0xF801'); o = cast(c[4], o)
        g = f'    if (i < 72) do {{ *palette++ = {o}; i++; }} while (i < 72);\n'
        names.append(c); srcs.append(full(g, BLUE0))
    res = bbl.run(srcs)
    rows = sorted([(sdiff(TG, seg(r[1], 'green')), n, seg(r[1], 'green')) for n, r in zip(names, res) if r], key=lambda x: x[0])
    for x in rows[:10]: print(x[0], x[1], x[2][2:9])
