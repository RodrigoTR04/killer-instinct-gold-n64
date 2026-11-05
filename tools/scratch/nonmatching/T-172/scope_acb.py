"""Block-scope the callback outs so IDO allocates them below the gfx pointers."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
DECL = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in BASE

v = {'base': BASE}

# gfxStart/gfx at function scope, the two outs declared inside the branch
v['outs_in_block'] = BASE.replace(DECL, '''    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
''').replace('''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
''', '''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
            s32 sp48;
            s32 sp44;

''')

# also scope diff/h inside the D_80295722 branch
v['outs_and_diff'] = v['outs_in_block'].replace('''            if (D_80295722) {
''', '''            if (D_80295722) {
                u32 diff;
                s32 h;

''').replace('''                diff = D_802C9F70.unk4 - D_802956F0;
''', '''                diff = D_802C9F70.unk4 - D_802956F0;
''')

# gfx pointers in an inner scope too
v['all_inner'] = BASE.replace(DECL, '''    u32 diff;
    s32 h;
    s32 i;
''').replace('''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
''', '''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
            s32 sp48;
            s32 sp44;
            DisplayCommand *gfxStart;
            DisplayCommand *gfx;

''')
detail.run('func_801ACB1C', v, jobs=4)
