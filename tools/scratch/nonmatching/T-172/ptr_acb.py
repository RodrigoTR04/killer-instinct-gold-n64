"""Test the permuter's D_801CD45C pointer-local idea honestly in the TU."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base': BASE}

# permuter output 961: a pointer local for D_801CD45C
v['ptr_local'] = BASE.replace('''    s32 sp48;
''', '''    s32 *cd45c;
    s32 sp48;
''').replace('''        if (D_8004A414 < 2 && D_801CD45C <= 0) {''',
    '''        cd45c = &D_801CD45C;
        if (D_8004A414 < 2 && *cd45c <= 0) {''')

# only inside the condition, no assignment hoist
v['ptr_local2'] = BASE.replace('''    s32 sp48;
''', '''    s32 *cd45c;
    s32 sp48;
''').replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
    '''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    cd45c = &D_801CD45C;''').replace('D_801CD45C <= 0', '*cd45c <= 0')

# same idea for D_8004A414 (target keeps it in v0 across the branch)
v['ptr_414'] = BASE.replace('''    s32 sp48;
''', '''    s32 *a414;
    s32 sp48;
''').replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
    '''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''').replace(
    'D_8004A414--;', '(*a414)--;').replace(
    'D_8004A414 < 2', '(*a414) < 2')

# both
v['ptr_both'] = v['ptr_local2'].replace('''    s32 sp48;
''', '''    s32 *a414;
    s32 sp48;
''').replace('''    cd45c = &D_801CD45C;''',
    '''    cd45c = &D_801CD45C;
    a414 = &D_8004A414;''').replace(
    'D_8004A414--;', '(*a414)--;').replace(
    'D_8004A414 < 2', '(*a414) < 2')

detail.run('func_801ACB1C', v, jobs=4)
