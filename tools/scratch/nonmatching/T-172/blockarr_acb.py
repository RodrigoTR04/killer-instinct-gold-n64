"""Block-scope extern array view of D_8004A414 for func_801ACB1C."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

CUR = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
PLAIN = CUR.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in PLAIN

V = PLAIN.replace('D_8004A414--;', 'D_8004A414[0]--;').replace(
    'D_8004A414 < 2', 'D_8004A414[0] < 2')
# put the local array spelling of the extern at the top of the function body
V = V.replace('int func_801ACB1C(void (*arg0)(), void (*arg1)(), void (*arg2)()) {\n',
              'int func_801ACB1C(void (*arg0)(), void (*arg1)(), void (*arg2)()) {\n'
              '    extern s32 D_8004A414[1];\n')
assert 'extern s32 D_8004A414[1];' in V

v = {'plain165': PLAIN, 'blockarray': V}
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=2)
