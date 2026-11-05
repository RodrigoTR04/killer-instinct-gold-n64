"""Slot-order sweep for func_801ACB1C at the 136-word base (target: 0x44/0x48 outs, 0x58/0x5C gfx)."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
DECL = '''    s32 *a414;
    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in BASE

LINES = {
    'a': '    s32 *a414;\n',
    'b': '    s32 sp48;\n',
    'c': '    s32 sp44;\n',
    'd': '    DisplayCommand *gfxStart;\n',
    'e': '    DisplayCommand *gfx;\n',
    'f': '    u32 diff;\n',
    'g': '    s32 h;\n',
    'h': '    s32 i;\n',
}
groups = [('a',), ('b', 'c'), ('d', 'e'), ('f',), ('g',), ('h',)]
v = {}
for perm in itertools.permutations(range(len(groups))):
    order = [k for i in perm for k in groups[i]]
    v[''.join(order)] = BASE.replace(DECL, ''.join(LINES[k] for k in order))
print(len(v), 'variants')
out = detail.run('func_801ACB1C', v, jobs=12)
