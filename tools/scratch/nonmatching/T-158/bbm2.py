import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbm import PK
HI = [40, 72, 128]
def mk(red, green, blue, decl='', form='for'):
    out = ''
    for p, hi in zip([red, green, blue], HI):
        out += f'    for (; i < {hi}; i++) {{ {p} }}\n' if form == 'for' else f'    if (i < {hi}) do {{ {p} i++; }} while (i < {hi});\n'
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i;\n' + decl)
    return bbl.HEAD + pre + out + bbl.TAIL
def st(r, g, b): return f'*palette++ = {PK(r, g, b)};'
variants = {}
# ramp expression styles
RE = {
 'shl': ('(i - 8) << 3', '(i - 40) << 3', '(i - 72) << 2'),
 'mul_var': ('k * 8', 'k * 8', 'k * 4'),
 'shl_var': ('k << 3', 'k << 3', 'k << 2'),
 'mul_paren': ('((i - 8) * 8)', '((i - 40) * 8)', '((i - 72) * 4)'),
}
for name, (r, g, b) in RE.items():
    if 'var' in name:
        variants[name] = mk(f'k = i - 8; ' + st(r, '0', '0'), f'k = i - 40; ' + st('248', g, '0'), f'k = i - 72; ' + st('248', '248', b), decl='    s32 k;\n')
    else:
        variants[name] = mk(st(r, '0', '0'), st('248', g, '0'), st('248', '248', b))
# macro variants
for mname, M in {'sdk': PK, 'nomask_a': lambda r, g, b: f'((({r}) << 8) & 0xF800) | ((({g}) << 3) & 0x7C0) | ((({b}) >> 2) & 0x3E) | 1', 'u8cast': lambda r, g, b: f'(((u8)({r}) << 8) & 0xF800) | (((u8)({g}) << 3) & 0x7C0) | (((u8)({b}) >> 2) & 0x3E) | 1', 'plus': lambda r, g, b: f'((({r}) << 8) & 0xF800) + ((({g}) << 3) & 0x7C0) + ((({b}) >> 2) & 0x3E) + 1'}.items():
    variants['m_' + mname] = mk(f'*palette++ = {M("(i - 8) << 3", "0", "0")};', f'*palette++ = {M("248", "(i - 40) << 3", "0")};', f'*palette++ = {M("248", "248", "(i - 72) << 2")};')
names = list(variants); res = bbl.run([variants[n] for n in names])
for n, r in zip(names, res): print(n, r[0] if r else None)
