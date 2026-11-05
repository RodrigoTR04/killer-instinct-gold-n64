"""Array-view variants of D_8004A414 for func_801ACB1C (no pointer local)."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
NOA = BASE.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

v = {}

# a) array-of-1, decrement written as an explicit read-modify-write
A1 = NOA.replace('extern s32 D_8004A414;', 'extern s32 D_8004A414[1];')
v['arr_rmw'] = A1.replace('D_8004A414--;', 'D_8004A414[0] = D_8004A414[0] - 1;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# b) array-of-1, compound decrement
v['arr_dec'] = A1.replace('D_8004A414--;', 'D_8004A414[0] -= 1;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# c) array-of-1, -- on the element
v['arr_minusminus'] = A1.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# d) two-element view indexed at 0 (same type, different declared size)
A2 = NOA.replace('extern s32 D_8004A414;', 'extern s32 D_8004A414[2];')
v['arr2'] = A2.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# e) struct view
S = NOA.replace('extern s32 D_8004A414;',
                'typedef struct { s32 count; } T172Counter;\nextern T172Counter D_8004A414;')
v['struct'] = S.replace('D_8004A414--;', 'D_8004A414.count--;').replace(
    'D_8004A414 < 2', 'D_8004A414.count < 2')

# f) u32 array
U = NOA.replace('extern s32 D_8004A414;', 'extern u32 D_8004A414[1];')
v['uarr'] = U.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=6)
