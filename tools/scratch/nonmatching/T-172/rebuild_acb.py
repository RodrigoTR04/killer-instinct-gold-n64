"""Rebuild func_801ACB1C with the declaration order that matches the target's gfx slots."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
NOA = BASE.replace('    s32 *a414;\n', '').replace(
    '''    a414 = &D_8004A414;\n''', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

DECL = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in NOA
NEW = '''    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    s32 sp48;
    s32 sp44;
    u32 diff;
    s32 h;
    s32 i;
'''
v = {'cdabefg': NOA.replace(DECL, NEW)}

# same order but with the a414 pointer appended last (keeps the 136 win?)
v['cdabefg_a414_last'] = NOA.replace(DECL, NEW.replace(
    '    s32 i;\n', '    s32 i;\n    s32 *a414;\n')).replace(
    '''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
    '''    s32 *a414p = &D_8004A414;

    osRecvMesg(D_8004A298, &D_801CD458, 1);''').replace(
    'D_8004A414--;', '(*a414p)--;').replace('D_8004A414 < 2', '(*a414p) < 2')
detail.run('func_801ACB1C', v, jobs=2)
