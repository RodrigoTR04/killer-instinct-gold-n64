"""Get the callback outs to 0x44/0x48 for func_801ACB1C.

gfxStart/gfx are now at 0x58/0x5c (matching). The outs sit at 0x50/0x54, i.e. the
slot immediately below gfx; the target has them at 0x44/0x48, 8 bytes further down,
with 0x4c..0x58 free in between. So the target's outs are not the next allocation
after the pointers - something in between is allocated and unused, or the outs are
declared inside a deeper block that is allocated first.
"""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/tmp/acb_gf_first.c').read()
v = {'gf_first': BASE}

# outs declared inside the branch body (block-scoped) instead of at function top
OUTS_TOP = '''    s32 sp48;
    s32 sp44;
'''
assert OUTS_TOP in BASE
INNER = BASE.replace(OUTS_TOP, '')
INNER = INNER.replace('''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
''', '''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
            s32 sp48;
            s32 sp44;

''')
v['outs_inner'] = INNER

# outs declared inside their own nested block around the arg0 call only
NEST = INNER.replace('''            if (arg0 != 0) {
                arg0(&sp48, &sp44, &D_802C9F70);
            }''', '''            {
                s32 sp48;
                s32 sp44;

                if (arg0 != 0) {
                    arg0(&sp48, &sp44, &D_802C9F70);
                }
                func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
            }''').replace(
    '''            func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
        }''', '''        }''')
v['outs_nest'] = NEST
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=3)
