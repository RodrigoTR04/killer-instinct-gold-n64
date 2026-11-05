"""Find the declaration order whose gfx/out slots match the target exactly (a414 kept)."""
import itertools
import re
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail, slotdump

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
    'A': '    s32 *a414;\n',
    'b': '    s32 sp48;\n', 'c': '    s32 sp44;\n',
    'd': '    DisplayCommand *gfxStart;\n', 'e': '    DisplayCommand *gfx;\n',
    'f': '    u32 diff;\n', 'g': '    s32 h;\n', 'h': '    s32 i;\n',
}
groups = [('A',), ('b', 'c'), ('d', 'e'), ('f',), ('g',), ('h',)]
TARGET = {0x44, 0x48, 0x58, 0x5C}

for perm in itertools.permutations(range(len(groups))):
    order = [k for i in perm for k in groups[i]]
    text = BASE.replace(DECL, ''.join(LINES[k] for k in order))
    try:
        lines = slotdump.dump('func_801ACB1C', text)
    except SystemExit:
        continue
    frame = None
    for l in lines:
        m = re.search(r'sp,sp,-(\d+)', l.replace(' ', ''))
        if m:
            frame = int(m.group(1))
            break
    stores = [int(m.group(1)) for l in lines if l.startswith('sw') and '(sp)' in l
              for m in [re.search(r'(\d+)\(sp\)', l)] if m]
    if frame == 0x60 and TARGET.issubset(set(stores)):
        print(''.join(order), hex(frame), [hex(s) for s in stores[:8]])
