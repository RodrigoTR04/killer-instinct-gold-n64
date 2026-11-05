"""The target's sp44/sp48 are adjacent ascending -> try an array-of-2 for the outs."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
NOA = BASE.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

DECL2 = '''    s32 sp48;
    s32 sp44;
'''
assert DECL2 in NOA

v = {'base165': NOA}

# a) outs as one array of two, sp44 first (lower address)
v['outs_arr'] = NOA.replace(DECL2 + '    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n',
                            '    s32 outs[2];\n    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n').replace(
    '&sp48', '&outs[1]').replace('&sp44', '&outs[0]').replace(
    'sp48, sp44,', 'outs[1], outs[0],')

# b) outs array declared after the gfx pointers
v['outs_arr_after'] = NOA.replace(DECL2 + '    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n',
                                  '    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n    s32 outs[2];\n').replace(
    '&sp48', '&outs[1]').replace('&sp44', '&outs[0]').replace(
    'sp48, sp44,', 'outs[1], outs[0],')

# c) gfx pair as an array of two pointers, gfx = ptrs[1]
v['gfx_arr'] = NOA.replace('    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n',
                           '    DisplayCommand *ptrs[2];\n').replace(
    'gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;\n            gfxStart = gfx;',
    'ptrs[1] = D_802C9F70.index ? D_80076240 : D_8006F1C0;\n            ptrs[0] = ptrs[1];').replace(
    'gfxStart = gfx;', 'ptrs[0] = ptrs[1];')

# d) both as arrays
v['both_arr'] = v['outs_arr'].replace(
    '    DisplayCommand *gfxStart;\n    DisplayCommand *gfx;\n',
    '    DisplayCommand *ptrs[2];\n').replace(
    'gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;\n            gfxStart = gfx;',
    'ptrs[1] = D_802C9F70.index ? D_80076240 : D_8006F1C0;\n            ptrs[0] = ptrs[1];')

v = {k: t for k, t in v.items() if 'gfx' not in '' or True}
print('note: c/d need manual gfx renames, skipping')
detail.run('func_801ACB1C', {k: v[k] for k in ('base165', 'outs_arr', 'outs_arr_after')}, jobs=3)
