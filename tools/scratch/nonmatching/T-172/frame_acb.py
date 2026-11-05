"""Shrink func_801ACB1C's frame from 0x68 to 0x60 while keeping the a414 win."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base_136': BASE}

# declare the loop counters inside the for statements
v['loop_scoped'] = BASE.replace('    s32 h;\n    s32 i;\n', '    s32 h;\n').replace(
    'for (i = 0; i < D_80282A60; i++)', 'for (s32 i = 0; i < D_80282A60; i++)').replace(
    'for (i = 0; i < 256; i++)', 'for (s32 i = 0; i < 256; i++)')

# h inside the block that uses it
v['h_scoped'] = BASE.replace('    u32 diff;\n    s32 h;\n    s32 i;\n', '    u32 diff;\n    s32 i;\n').replace(
    '''                h = diff * 17;''', '''                s32 h = diff * 17;''')

# both
v['both_scoped'] = v['loop_scoped'].replace('    s32 h;\n', '').replace(
    '''                h = diff * 17;''', '''                s32 h = diff * 17;''')

# diff scoped too
v['all_scoped'] = v['both_scoped'].replace('    u32 diff;\n', '').replace(
    '''                diff = D_802C9F70.unk4 - D_802956F0;''',
    '''                u32 diff = D_802C9F70.unk4 - D_802956F0;''')
detail.run('func_801ACB1C', v, jobs=6)
