"""Combos of gfx placement x outs scope for func_801ACB1C slot layout."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

CUR = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
PLAIN = CUR.replace('    s32 *a414;\n', '').replace('    a414 = &D_8004A414;\n', '').replace(
    '(*a414)--;', 'D_8004A414--;').replace('(*a414) < 2', 'D_8004A414 < 2')
assert 'a414' not in PLAIN

DECL = '''    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in PLAIN

GF_FIRST = '''    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    s32 sp48;
    s32 sp44;
    u32 diff;
    s32 h;
    s32 i;
'''

ARG0 = '''            if (arg0 != 0) {
                arg0(&sp48, &sp44, &D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
'''
assert ARG0 in PLAIN

v = {}

# a) gfx first at top, outs nested around the arg0 call
a = PLAIN.replace(DECL, GF_FIRST).replace('    s32 sp48;\n    s32 sp44;\n', '')
a = a.replace(ARG0, '''            {
                s32 sp48;
                s32 sp44;

                if (arg0 != 0) {
                    arg0(&sp48, &sp44, &D_802C9F70);
                }
                func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
''')
# drop the later standalone func_801AD7D8 call
a = a.replace('''            func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
        }
        do { D_802C9F70.unk4++; } while (0);''', '''        }
        do { D_802C9F70.unk4++; } while (0);''')
v['gffirst_nest'] = a

# b) gfx first at top, outs declared inside the branch (not the deep block)
b = PLAIN.replace(DECL, GF_FIRST).replace('    s32 sp48;\n    s32 sp44;\n', '')
b = b.replace('''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
''', '''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
            s32 sp48;
            s32 sp44;

''')
v['gffirst_inner'] = b

# c) gfx first, outs at top (already known 165) as control
v['gffirst_top'] = PLAIN.replace(DECL, GF_FIRST)

print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=3)
