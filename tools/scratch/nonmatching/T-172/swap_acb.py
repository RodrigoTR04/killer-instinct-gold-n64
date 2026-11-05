"""Honest parts of the permuter's 129-word acb1c hit: statement swaps near the top."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
OLD = '''            D_80044A24 = D_802C9F70.index;
            gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;
            gfxStart = gfx;
'''
assert OLD in BASE

v = {'base136': BASE}
v['gfx_first'] = BASE.replace(OLD, '''            gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;
            D_80044A24 = D_802C9F70.index;
            gfxStart = gfx;
''')
v['gfx_first_no_start'] = BASE.replace(OLD, '''            gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;
            D_80044A24 = D_802C9F70.index;
            gfxStart = D_802C9F70.index ? D_80076240 : D_8006F1C0;
''')
v['index_local'] = BASE.replace(OLD, '''            gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;
            D_80044A24 = D_802C9F70.index;
            gfxStart = gfx;
''').replace('    u32 diff;\n', '    u32 diff;\n    s32 index;\n').replace(
    '''            gfx = D_802C9F70.index ? D_80076240 : D_8006F1C0;
            D_80044A24 = D_802C9F70.index;''',
    '''            index = D_802C9F70.index;
            gfx = index ? D_80076240 : D_8006F1C0;
            D_80044A24 = index;''')
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=4)
