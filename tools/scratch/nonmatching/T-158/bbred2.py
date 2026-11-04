import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
GB = '''    if (i < 72) do
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
R = {
 'post_in_expr': '    for (; i < 40;) *palette++ = (((i++) - 8) << 11) | 1;\n',
 'post_in_expr_dw': '    if (i < 40) do { *palette++ = (((i++) - 8) << 11) | 1; } while (i < 40);\n',
 'pre_in_expr': '    if (i < 40) do { *palette++ = (((++i) - 9) << 11) | 1; } while (i < 40);\n',
 'two_stmt_comma': '    if (i < 40) do { *palette++ = ((i - 8) << 11) | 1, i++; } while (i < 40);\n',
 'ptr_first': '    if (i < 40) do { palette[0] = ((i - 8) << 11) | 1; i++; palette++; } while (i < 40);\n',
 'ptr_inc_first': '    if (i < 40) do { i++; *palette++ = ((i - 9) << 11) | 1; } while (i < 40);\n',
 'redvar': '    if (i < 40) do { red = i - 8; i++; *palette++ = (red << 11) | 1; } while (i < 40);\n',
}
names = list(R)
srcs = [bbl.HEAD + bbl.PRE + R[n] + GB + bbl.TAIL for n in names]
res = bbl.run(srcs)
for n, r in zip(names, res):
    print('==', n, r[0] if r else None)
    if r:
        ls = r[1]
        a = next(k for k, l in enumerate(ls) if l == 'slti at,v1,40')
        for l in ls[a:a+11]: print('@@', l)
