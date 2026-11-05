"""Slot-layout sweep for func_801ACB1C: which declarations fix sp+0x58/0x5C/0x48/0x44."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
v = {'base': BASE}

DECL = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in BASE

# target has sp+0x58 gfxStart, sp+0x5C gfx, sp+0x48 sp48, sp+0x44 sp44.
# IDO allocates in declaration order for address-taken locals, descending.
v['ints_first'] = BASE.replace(DECL, '''    s32 sp48;
    s32 sp44;
    u32 diff;
    s32 h;
    s32 i;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
''')
v['gfx_first'] = BASE.replace(DECL, '''    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    s32 sp48;
    s32 sp44;
    u32 diff;
    s32 h;
    s32 i;
''')
# declare sp44 before sp48 (target sp48 is at the higher offset)
v['sp44_first'] = BASE.replace(DECL, '''    s32 sp44;
    s32 sp48;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
''')
# put diff/h/i before the pointers
v['scalars_mid'] = BASE.replace(DECL, '''    s32 sp48;
    s32 sp44;
    u32 diff;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    s32 h;
    s32 i;
''')
# move i to the top
v['i_first'] = BASE.replace(DECL, '''    s32 i;
    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
''')
detail.run('func_801ACB1C', v, jobs=6)
