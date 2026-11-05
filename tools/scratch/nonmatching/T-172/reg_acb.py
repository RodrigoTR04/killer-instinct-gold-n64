"""Keep the D_8004A414 pointer in a register (no frame growth) for func_801ACB1C."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'current': BASE}

# a) assign inside the ==2 arm only
v['inner_assign'] = BASE.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''', '''    osRecvMesg(D_8004A298, &D_801CD458, 1);''').replace(
    '''            (*a414)--;''', '''            a414 = &D_8004A414;
            (*a414)--;''')

# b) no local at all, but force address materialisation per use
v['inline_addr'] = BASE.replace('''    s32 *a414;
''', '').replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''', '''    osRecvMesg(D_8004A298, &D_801CD458, 1);''').replace(
    '(*a414)--;', '(*&D_8004A414)--;').replace(
    '(*a414) < 2', '(*&D_8004A414) < 2')

# c) pointer local declared last, so IDO may reuse the slot
v['decl_last'] = BASE.replace('''    s32 *a414;
    s32 sp48;''', '''    s32 sp48;''').replace('''    s32 i;
''', '''    s32 i;
    s32 *a414;
''')

# d) use a typed pointer to the whole word array
v['ptr_before_use'] = BASE.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''', '''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;
    if (*D_801CD458 != 1) {
        if (*D_801CD458 == 2) {
            (*a414)--;
        }
    } else {''').replace('''    if (*D_801CD458 != 1) {
        if (*D_801CD458 == 2) {
            (*a414)--;
        }
    } else {
    if (*D_801CD458 != 1) {''', '''    if (*D_801CD458 != 1) {''')
detail.run('func_801ACB1C', v, jobs=4)
