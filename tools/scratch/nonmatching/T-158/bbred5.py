import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import GB, region, TR
def rdiff(r):
    sm = difflib.SequenceMatcher(None, TR, r, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
def gen():
    out = {}
    val = {'a': '((i - 8) << 11) | 1', 'b': '(((i++) - 8) << 11) | 1', 'c': '(((i) - 8) << 11) | 1'}
    casts = ['{}', '(s16)({})', '(u16)({})']
    # forms: (name, template)
    for cname, c in zip('012', casts):
        for vk in 'abc':
            v = c.format(val[vk])
            vn = val[vk]
            V = v
            tmpl = {
              'dw_cond_pre':  f'    if (i < 40) do {{ *palette++ = {V}; }} while (++i < 40);\n',
              'dw_cond_post': f'    if (i < 40) do {{ *palette++ = {V}; }} while (i++ < 39);\n',
              'dw_inc_after': f'    if (i < 40) do {{ *palette++ = {V}; i++; }} while (i < 40);\n',
              'dw_plus1':     f'    if (i < 40) do {{ *palette++ = {V}; i = i + 1; }} while (i < 40);\n',
              'dw_pluseq':    f'    if (i < 40) do {{ *palette++ = {V}; i += 1; }} while (i < 40);\n',
              'for':          f'    for (; i < 40; i++) *palette++ = {V};\n',
              'for_pre':      f'    for (; i < 40; ++i) *palette++ = {V};\n',
              'for_plus1':    f'    for (; i < 40; i = i + 1) *palette++ = {V};\n',
              'while_cond':   f'    while (i < 40) {{ *palette++ = {V}; i++; }}\n',
              'two_i':        f'    if (i < 40) do {{ j = i + 1; *palette++ = {V}; i = j; }} while (i < 40);\n',
              'two_i2':       f'    if (i < 40) do {{ j = i; i++; *palette++ = {V.replace("i - 8","j - 8")}; }} while (i < 40);\n',
              'two_i3':       f'    if (i < 40) do {{ j = i - 8; i++; *palette++ = {c.format("(j << 11) | 1")}; }} while (i < 40);\n',
            }
            for k, t in tmpl.items():
                out[(cname, vk, k)] = t
    return out
