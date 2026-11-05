"""Separate declaration statements for func_801ACB1C (slot order lever)."""
import itertools
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
DECL = '''    s32 *a414;
    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in BASE
NAMES = ['a414', 'sp48', 'sp44', 'gfxStart', 'gfx', 'diff', 'h', 'i']
TYPE = {'a414': 's32 *', 'sp48': 's32', 'sp44': 's32',
        'gfxStart': 'DisplayCommand *', 'gfx': 'DisplayCommand *',
        'diff': 'u32', 'h': 's32', 'i': 's32'}

v = {}
sep = '\n'.join(f'    {TYPE[n]} {n};' for n in NAMES) + '\n'
v['sep_decl'] = BASE.replace(DECL, sep)

# separate statements with a414 last
order = [n for n in NAMES if n != 'a414'] + ['a414']
v['sep_a414_last'] = BASE.replace(DECL, '\n'.join(f'    {TYPE[n]} {n};' for n in order) + '\n')

# a414 first (current order) but separate
v['sep_a414_first'] = BASE.replace(DECL, sep)

# no a414, separate decls -> establishes the slot baseline
noa = BASE.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
v['sep_noa'] = noa.replace(DECL, '\n'.join(
    f'    {TYPE[n]} {n};' for n in NAMES if n != 'a414') + '\n')
detail.run('func_801ACB1C', v, jobs=4)
