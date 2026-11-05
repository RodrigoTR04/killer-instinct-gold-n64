"""Write D_8004A414's decrement as an explicit read-modify-write (func_801ACB1C).

The target materialises the address of D_8004A414 into a register in each arm and
does `lw; addiu -1; sw 0(reg)`, i.e. the address is live across the load/store
pair. `--` on a plain global lets IDO fuse the load into %lo(reg).
"""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
NOA = BASE.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

v = {'base165': NOA}
v['rmw'] = NOA.replace('D_8004A414--;', 'D_8004A414 = D_8004A414 - 1;')
v['rmw_compound'] = NOA.replace('D_8004A414--;', 'D_8004A414 -= 1;')
v['rmw_plus'] = NOA.replace('D_8004A414--;', 'D_8004A414 = D_8004A414 + -1;')

# condition also written through the same read
v['rmw_cond'] = NOA.replace('D_8004A414--;', 'D_8004A414 = D_8004A414 - 1;').replace(
    'D_8004A414 < 2', 'D_8004A414 - 0 < 2')

# the two counter statements nearby wrapped (block boundary lever), with rmw
v['rmw_wrap'] = NOA.replace('D_8004A414--;', 'D_8004A414 = D_8004A414 - 1;').replace(
    '        do { D_802C9F70.unk4++; } while (0);',
    '        do { D_802C9F70.unk4++; } while (0);')
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=6)
