"""Remove one existing local to pay for the a414 pointer slot in func_801ACB1C."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'current': BASE}

# drop the "diff" local by using D_802C9F70.unk4 arithmetic inline
v['no_diff'] = BASE.replace('    u32 diff;\n', '    u32 diff;\n').replace(
    'diff = D_802C9F70.unk4 - D_802956F0;', 'diff = D_802C9F70.unk4 - D_802956F0;')

# h as a temporary expression
v['no_h'] = BASE.replace('    s32 h;\n', '').replace(
    '''                h = diff * 17;''', '''                h = diff * 17;''')

# i merged into the loop with a different name reused
v['merge_i'] = BASE.replace('    s32 h;\n    s32 i;\n', '    s32 h, i;\n')

# declare a414 as u32* and reuse diff slot by pointer arithmetic
v['a414_u32'] = BASE.replace('    s32 *a414;', '    u32 *a414;')

# drop i (single loop variable reused for both loops is already the case)
v['no_i_decl'] = BASE.replace('    s32 h;\n    s32 i;\n', '    s32 h;\n    s32 i = 0;\n')

# sp44 unused? check
print('sp44 uses:', BASE.count('sp44'))
detail.run('func_801ACB1C', v, jobs=6)
