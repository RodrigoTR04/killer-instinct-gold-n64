"""Apply the nested-callback-outs block on top of the 136-word (a414) base."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
assert 'a414' in BASE

ARG0 = '''            if (arg0 != 0) {
                arg0(&sp48, &sp44, &D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
'''
assert ARG0 in BASE

D7 = '''            func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
'''
assert D7 in BASE

v = {'base136': BASE}

# nested block around arg0 + the 801AD7D8 call
NEST = BASE.replace(ARG0, '''            {
                s32 sp48;
                s32 sp44;

                if (arg0 != 0) {
                    arg0(&sp48, &sp44, &D_802C9F70);
                }
                func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
''').replace(D7, '')
# remove the now-shadowed top-level outs
NEST = NEST.replace('    s32 sp48;\n    s32 sp44;\n', '')
v['nest_outs'] = NEST

# same but keeping the top-level declarations (shadowing them inside the block)
v['nest_shadow'] = BASE.replace(ARG0, '''            {
                s32 sp48;
                s32 sp44;

                if (arg0 != 0) {
                    arg0(&sp48, &sp44, &D_802C9F70);
                }
                func_801AD7D8(gfxStart, &gfx, sp48, sp44, (s32 *)&D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
''').replace(D7, '')
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=2)
