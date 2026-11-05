"""Drop the zero initialiser on `loaded` in func_800216D4 (target never stores it)."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_800216D4.c').read()
OLD = '    s32 offset, size, loaded = 0;\n'
assert OLD in BASE

v = {'base226': BASE}
v['no_loaded_init'] = BASE.replace(OLD, '    s32 offset, size, loaded;\n')
v['no_loaded_sep'] = BASE.replace(OLD, '    s32 offset;\n    s32 size;\n    s32 loaded;\n')
v['no_alt_init'] = BASE.replace(OLD, '    s32 offset, size, loaded;\n').replace(
    '    u16 id, i, alternate = 0;\n', '    u16 id, i, alternate;\n\n    alternate = 0;\n')
print(len(v), 'variants', flush=True)
detail.run('func_800216D4', v, jobs=3)
