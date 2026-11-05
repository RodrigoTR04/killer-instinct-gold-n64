"""Try to recover the 0x60 frame in func_801ACB1C with a414 kept: drop temps."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base_136': BASE}

# no diff local: recompute from unk4 each time (target keeps diff in a3)
v['no_diff_local'] = BASE.replace('    u32 diff;\n', '').replace(
    'diff = D_802C9F70.unk4 - D_802956F0;', '').replace(
    'if (diff >= 16)', 'if (D_802C9F70.unk4 - D_802956F0 >= 16)').replace(
    'h = diff * 17;', 'h = (D_802C9F70.unk4 - D_802956F0) * 17;').replace(
    'func_8002AA98(0x8000 - diff * 2100, h);',
    'func_8002AA98(0x8000 - (D_802C9F70.unk4 - D_802956F0) * 2100, h);')

# no h local
v['no_h_local'] = BASE.replace('    s32 h;\n', '').replace(
    '                h = diff * 17;\n', '')
# replace h uses with an expression via a helper macro-like repetition
v['no_h_local'] = v['no_h_local'].replace(
    '(((h + 1) & 0x3FF) << 2)', '((((diff * 17) + 1) & 0x3FF) << 2)').replace(
    '((478 - h) & 0x3FF) << 2', '((478 - diff * 17) & 0x3FF) << 2').replace(
    'func_8002AA98(0x8000 - diff * 2100, h);',
    'func_8002AA98(0x8000 - diff * 2100, diff * 17);')

# no i local: reuse diff slot is not honest; instead scope i to each loop with a while
v['no_i_local'] = BASE.replace('    s32 i;\n', '').replace(
    '''    for (i = 0; i < D_80282A60; i++) {''', '''    for (i = 0; i < D_80282A60; i++) {''')

detail.run('func_801ACB1C', v, jobs=4)
