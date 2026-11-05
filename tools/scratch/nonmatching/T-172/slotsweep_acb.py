"""Report the gfx/out slot pair for each declaration order of func_801ACB1C."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail, slotdump

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
# back out the a414 pointer: rebuild from the 165-word shape
NOA = BASE.replace('    s32 *a414;\n', '').replace(
    '''    a414 = &D_8004A414;\n''', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in NOA

DECL = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in NOA
LINES = {
    'a': '    s32 sp48;\n', 'b': '    s32 sp44;\n',
    'c': '    DisplayCommand *gfxStart;\n', 'd': '    DisplayCommand *gfx;\n',
    'e': '    u32 diff;\n', 'f': '    s32 h;\n', 'g': '    s32 i;\n',
}
groups = [('a', 'b'), ('c', 'd'), ('e',), ('f',), ('g',)]
for perm in itertools.permutations(range(len(groups))):
    order = [k for i in perm for k in groups[i]]
    text = NOA.replace(DECL, ''.join(LINES[k] for k in order))
    lines = slotdump.dump('func_801ACB1C', text)
    frame = next((int(l.split()[-1].split(',')[-1]) for l in lines
                  if 'sp,sp,-' in l.replace(' ', '')), None)
    sw = [l.replace(' ', '') for l in lines if l.startswith('sw') and '(sp)' in l]
    # first two gfx stores and the out stores
    print(''.join(order), frame, sw[:4], sw[4:8])
