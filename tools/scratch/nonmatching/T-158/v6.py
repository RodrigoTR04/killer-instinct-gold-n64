BASE = 'tools/scratch/nonmatching/T-158/w/bb60_base.c'
LOOPS = open(BASE).read()
a = LOOPS.index('    if (i < 40) do')
b = LOOPS.index('    D_802C9F64 = 0;')
OLD = LOOPS[a:b]
def rep(new): return [(OLD, new)]
V = [
 ('base', []),
 ('for3', rep('''    for (; i < 40; i++) *palette++ = ((i - 8) << 11) | 1;
    for (; i < 72; i++) *palette++ = (((i - 40) << 6) & 0x7C0) | 0xF801;
    for (; i < 128; i++) *palette++ = (i - 72) | 0xFFC1;
''')),
 ('for3_red', rep('''    for (; i < 40; i++) { red = i - 8; *palette++ = (red << 11) | 1; }
    for (; i < 72; i++) { green = i - 40; *palette++ = ((green << 6) & 0x7C0) | 0xF801; }
    for (; i < 128; i++) *palette++ = (i - 72) | 0xFFC1;
''')),
 ('for3_post', rep('''    for (; i < 40;) *palette++ = (((i++) - 8) << 11) | 1;
    for (; i < 72;) *palette++ = ((((i++) - 40) << 6) & 0x7C0) | 0xF801;
    for (; i < 128;) *palette++ = ((i++) - 72) | 0xFFC1;
''')),
 ('wh', rep('''    while (i < 40) { *palette++ = ((i - 8) << 11) | 1; i++; }
    while (i < 72) { *palette++ = (((i - 40) << 6) & 0x7C0) | 0xF801; i++; }
    while (i < 128) { *palette++ = (i - 72) | 0xFFC1; i++; }
''')),
]
