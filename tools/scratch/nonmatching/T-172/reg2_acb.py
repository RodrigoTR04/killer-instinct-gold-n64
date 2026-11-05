"""Keep the D_8004A414 pointer out of the frame in func_801ACB1C."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base_136': BASE}

# register storage class: cannot be spilled, so no stack slot
v['register'] = BASE.replace('    s32 *a414;', '    register s32 *a414;')

# pointer scoped inside each arm that uses it (disjoint live ranges)
v['arm_scoped'] = BASE.replace('''    s32 *a414;
''', '').replace('''    a414 = &D_8004A414;
''', '').replace(
    '''        if (*D_801CD458 == 2) {
            (*a414)--;''', '''        if (*D_801CD458 == 2) {
            s32 *a414 = &D_8004A414;

            (*a414)--;''').replace(
    '''        if ((*a414) < 2 && D_801CD45C <= 0) {''',
    '''        s32 *a414 = &D_8004A414;

        if ((*a414) < 2 && D_801CD45C <= 0) {''')

# both arms in one inner declaration but with the main branch's test hoisted after
v['two_ptrs'] = BASE.replace('''    s32 *a414;
''', '').replace('''    a414 = &D_8004A414;
''', '').replace(
    '''            (*a414)--;''', '''            (*a414)--;''').replace(
    '''    if (*D_801CD458 != 1) {''', '''    s32 *a414 = &D_8004A414;

    if (*D_801CD458 != 1) {''')
detail.run('func_801ACB1C', v, jobs=4)
