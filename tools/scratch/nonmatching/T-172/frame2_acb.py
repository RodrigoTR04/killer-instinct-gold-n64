"""Shrink func_801ACB1C's frame to 0x60 using C89-legal block scopes."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base_136': BASE}

# h declared at the top of the D_80295722 block (C89: before statements)
v['h_in_block'] = BASE.replace('    u32 diff;\n    s32 h;\n    s32 i;\n',
                               '    u32 diff;\n    s32 i;\n').replace(
    '''            if (D_80295722) {
''', '''            if (D_80295722) {
                s32 h;

''')

# diff also at the top of that block
v['diff_h_in_block'] = BASE.replace('    u32 diff;\n    s32 h;\n    s32 i;\n',
                                    '    s32 i;\n').replace(
    '''            if (D_80295722) {
''', '''            if (D_80295722) {
                u32 diff;
                s32 h;

''')

# i wrapped in its own block for the second loop
v['i_wrapped'] = BASE.replace('    u32 diff;\n    s32 h;\n    s32 i;\n',
                              '    u32 diff;\n    s32 h;\n').replace(
    '''    for (i = 0; i < 256; i++) {
        entry = &T172_CACHE[i][player];''', '''    {
        s32 i;

        for (i = 0; i < 256; i++) {
        entry = &T172_CACHE[i][player];''')
detail.run('func_801ACB1C', v, jobs=4)
