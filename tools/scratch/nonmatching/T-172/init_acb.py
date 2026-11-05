"""Pointer-local initializer forms for func_801ACB1C (target keeps &D_8004A414 in v0)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'current': BASE}

# strip the current a414 usage back to a plain pointer declared with an initializer
NOA = BASE.replace('''    s32 *a414;
''', '')
NOA = NOA.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    a414 = &D_8004A414;''', '''    osRecvMesg(D_8004A298, &D_801CD458, 1);''')

v['init_top'] = NOA.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
                            '''    s32 *a414 = &D_8004A414;
    osRecvMesg(D_8004A298, &D_801CD458, 1);''').replace(
    'D_8004A414--;', '(*a414)--;').replace('D_8004A414 < 2', '(*a414) < 2')

v['init_before_use'] = NOA.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
                                   '''    osRecvMesg(D_8004A298, &D_801CD458, 1);
    {
    s32 *a414 = &D_8004A414;''').replace(
    '''        func_801ADA04(&D_802C9F70);
    }
}''', '''        func_801ADA04(&D_802C9F70);
    }
    }
}''').replace('D_8004A414--;', '(*a414)--;').replace('D_8004A414 < 2', '(*a414) < 2')

# also a msg pointer for D_801CD458 like s0 in the target
v['msg_ptr'] = NOA.replace('''    osRecvMesg(D_8004A298, &D_801CD458, 1);''',
                           '''    s16 **msgp = &D_801CD458;

    osRecvMesg(D_8004A298, msgp, 1);''').replace(
    '*D_801CD458', '**msgp').replace('*D_801CD458', '**msgp')

detail.run('func_801ACB1C', v, jobs=3)
