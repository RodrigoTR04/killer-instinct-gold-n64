import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
from bbred3 import region
from bbgb import seg, TG, TB, sdiff
R = '    if (i < 40) do { r = (i - 8) << 3; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1; i++; } while (i < 40);\n'
G = '    if (i < 72) do { g = (i - 40) << 3; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1; i++; } while (i < 72);\n'
B_forms = {
 'plain': '    if (i < 128) do { *palette++ = (i - 72) | 0xFFC1; i++; } while (i < 128);\n',
 'rgv': '    if (i < 128) do { r = 248; g = 248; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | (i - 72) | 1; i++; } while (i < 128);\n',
 'rgbv': '    if (i < 128) do { r = 248; g = 248; b = i - 72; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | b | 1; i++; } while (i < 128);\n',
 'rgbv2': '    if (i < 128) do { r = 255; g = 255; b = i - 72; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1; i++; } while (i < 128);\n',
 'rgbv3': '    if (i < 128) do { b = (i - 72) << 2; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1; i++; } while (i < 128);\n',
 'rgbv4': '    if (i < 128) do { b = i - 72; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | b | 1; i++; } while (i < 128);\n',
 'rgbv5': '    if (i < 128) do { b = i - 72; *palette++ = 0xF800 | 0x7C0 | b | 1; i++; } while (i < 128);\n',
 'rgbv6': '    if (i < 128) do { r = 248; g = 248; b = i - 72; *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | (b & 0x3E) | 1; i++; } while (i < 128);\n',
}
names, srcs = [], []
for k, B in B_forms.items():
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, r = 248, g = 248, b = 0;\n')
    names.append(k); srcs.append(bbl.HEAD + pre + R + G + B + bbl.TAIL)
    pre = bbl.PRE.replace('    s32 i, red, green;\n', '    s32 i, r, g, b;\n')
    names.append(k+'/noinit'); srcs.append(bbl.HEAD + pre + R + G + B + bbl.TAIL)
res = bbl.run(srcs)
for n, r in zip(names, res):
    if r: print(n, r[0], 'blue', seg(r[1], 'blue')[:8])
    else: print(n, None)
