"""Array view of D_8004A414 for func_801ACB1C, applied to the 165-word plain base."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

CUR = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()

# Rebuild the plain (no pointer local) base first.
PLAIN = CUR.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in PLAIN, [l for l in PLAIN.splitlines() if 'a414' in l]

v = {'plain165': PLAIN}

A1 = PLAIN.replace('extern s32 D_8004A414;', 'extern s32 D_8004A414[1];')
assert 'D_8004A414[1]' in A1
v['arr1'] = A1.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

A2 = PLAIN.replace('extern s32 D_8004A414;', 'extern s32 D_8004A414[2];')
v['arr2'] = A2.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

U1 = PLAIN.replace('extern s32 D_8004A414;', 'extern u32 D_8004A414[1];')
v['uarr1'] = U1.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')

# only the condition through the array view (decrement left plain)
v['arr1_cond'] = A1.replace('D_8004A414 < 2', 'D_8004A414[0] < 2')
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=5)
