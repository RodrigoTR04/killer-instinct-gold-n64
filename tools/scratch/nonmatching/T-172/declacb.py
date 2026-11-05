"""Reorder func_801ACB1C declarations to move the callback outs / gfx pointers."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
OLD = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert OLD in BASE

LINES = {
    'a': '    s32 sp48;\n',
    'b': '    s32 sp44;\n',
    'c': '    DisplayCommand *gfxStart;\n',
    'd': '    DisplayCommand *gfx;\n',
    'e': '    u32 diff;\n',
    'f': '    s32 h;\n',
    'g': '    s32 i;\n',
}
# keep sp48 before sp44 and gfxStart before gfx; permute the four groups
groups = [('a', 'b'), ('c', 'd'), ('e',), ('f',), ('g',)]
v = {}
for perm in itertools.permutations(range(len(groups))):
    order = [k for i in perm for k in groups[i]]
    v[''.join(order)] = BASE.replace(OLD, ''.join(LINES[k] for k in order))
print(len(v), 'variants')
out = detail.run('func_801ACB1C', v, jobs=12)
