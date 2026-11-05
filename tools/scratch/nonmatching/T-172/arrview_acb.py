"""Array/struct views of D_8004A414 so lui+addiu lands right without a pointer local."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
# current draft uses s32 *a414 local; strip it back to plain D_8004A414 first
NOA = BASE.replace('    s32 *a414;\n', '').replace(
    '    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

v = {}

# 1. array-of-1 view, indexed at use
ARR = NOA.replace('extern s32 D_8004A414;', 'extern s32 D_8004A414[1];')
v['arr1'] = ARR.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# 2. array of a struct with one member
STRUCT = NOA.replace('extern s32 D_8004A414;', 'typedef struct { s32 v; } T172Word;\nextern T172Word D_8004A414;')
v['struct1'] = STRUCT.replace('D_8004A414--;', 'D_8004A414.v--;').replace(
    'D_8004A414 < 2', 'D_8004A414.v < 2')

# 3. array view but only at the condition site (decrement stays plain)
v['arr1_cond'] = ARR.replace('D_8004A414 < 2', 'D_8004A414[0] < 2')

# 4. volatile pointer-free s32 array read at both sites, decrement via compound assign
v['arr1_m1'] = ARR.replace('D_8004A414--;', 'D_8004A414[0] = D_8004A414[0] - 1;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# 5. u32 array view
UARR = NOA.replace('extern s32 D_8004A414;', 'extern u32 D_8004A414[1];')
v['uarr1'] = UARR.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')
detail.run('func_801ACB1C', v, jobs=6)
