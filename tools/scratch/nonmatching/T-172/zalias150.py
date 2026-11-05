"""Try z as a distinct narrower type / via a cast so IDO gives it a different slot."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, prof

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
OLD = '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']) + '\n    s32 hi;\n    s32 exponent;\n'
assert OLD in BASE

v = {'base93': BASE}

# z declared in its own inner scope? not legal (used across branches).
# Instead: declare an alias double for z used only in the sqrt branch.
v['z_alias'] = BASE.replace(
    OLD, '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z'])
    + '\n    double zs;\n    s32 hi;\n    s32 exponent;\n').replace(
    '''        z = (D_80048F78 - x) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;''',
    '''        zs = (D_80048F78 - x) * 0.5;
        t = sqrtf((float)zs);
        w = D_80048F58[0]+((zs+D_80048F58[2])*zs+D_80048F58[1])*zs;
        u = D_80048F38[1]+(D_80048F38[3]*zs+D_80048F38[2])*zs;
        r = zs*u*t/w+t;''')

# z last and exponent first
v['ex_first'] = BASE.replace(
    OLD, '    s32 exponent;\n' + '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z'])
    + '\n    s32 hi;\n')
print(len(v), 'variants', flush=True)
out = detail.run('func_8002E150', v, jobs=3)
for name, w, s, f, _ in out:
    if f is not None:
        print(name, w, s, hex(f), prof.profile('func_8002E150', v[name])[3] if w is not None else '')
