BASE = 'tools/scratch/nonmatching/T-158/w/bb60_base.c'
T = open(BASE).read()
a = T.index('    s16 *palette = D_802C9D20;')
b = T.index('    D_802C9F64 = 0;')
HEAD = T[:a]; TAIL = T[b:]
def body(decl, init, w):
    return HEAD + decl + '    s32 i, red, green;\n' + T[T.index('    D_802C9F68 = 0;'):T.index('    i = 0;\n    do')] + init + w + TAIL
IDX = '''    j = 0;
    i = 0;
    do { D_802C9D20[j++] = i++; } while (i < 128);
    i = 0;
    for (; i != 8; i++) { D_802C9D20[j++] = 0; }
    if (i < 40) do { red = i - 8; i++; D_802C9D20[j++] = (red << 11) | 1; } while (i < 40);
    if (i < 72) do { green = i - 40; i++; D_802C9D20[j++] = ((green << 6) & 0x7C0) | 0xF801; } while (i < 72);
    if (i < 128) do { D_802C9D20[j++] = (i - 72) | 0xFFC1; i++; } while (i < 128);
'''
V = [('base', [])]
import re
src_idx = HEAD + '    s32 i, j, red, green;\n' + T[T.index('    D_802C9F68 = 0;'):T.index('    i = 0;\n    do')] + IDX + TAIL
src_idx = src_idx.replace('    s16 *palette = D_802C9D20;\n','')
open('/tmp/bb_idx.c','w').write(src_idx)
BASE2 = '/tmp/bb_idx.c'
