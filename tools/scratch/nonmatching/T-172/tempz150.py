"""Is the sp+0x30 slot a compiler temp rather than a declared local? (func_8002E150)

Target facts: frame 0x60, hi at 0x1C, the spilled double at 0x30, and 16 bytes
(0x20..0x2F) allocated but never used. If the spilled double were a *declared* local
the sweep would have placed it anywhere including 0x20 (where the draft puts it), so
the 0x10 gap hints that the value spilled is an IDO temporary, allocated at the top
of the temp area, and that the original therefore did not declare it as a local.
"""
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

DECL8 = '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']) + '\n    s32 hi;\n    s32 exponent;\n'
assert DECL8 in BASE

SQ = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
'''
assert SQ in BASE

v = {}
# no z declared: the sqrt branch keeps the half-difference in an expression temporary,
# re-deriving it from the already-named t (which holds sqrt of it).
D7 = '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p']) + '\n    s32 hi;\n    s32 exponent;\n'
v['no_z_local'] = BASE.replace(DECL8, D7).replace(SQ, '''        t = sqrtf((float)((D_80048F78 - a) * 0.5));
        z = t * t;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
''')

# same but with seven declared doubles and an eighth that is only a temp elsewhere
v['no_z_local_b'] = BASE.replace(DECL8, D7).replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        z = t * t;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
''')

# keep eight declarations but make z used only after the call (so it is not live there)
v['z_after'] = BASE.replace(SQ, '''        t = sqrtf((float)((D_80048F78 - a) * 0.5));
        z = (D_80048F78 - a) * 0.5;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
''')

print(len(v), 'variants', flush=True)


def sig(text, label):
    w, s, f, _ = detail.detail('func_8002E150', text, label)
    if f is None:
        return None
    lines = slotdump.dump('func_8002E150', text, label)
    c = Counter()
    for ln in lines:
        for m in re.finditer(r'(\d+)\(sp\)', ln):
            c[int(m.group(1))] += 1
    return w, s, f, c


print('TARGET', fmt(TF, TC), flush=True)
for name, text in v.items():
    r = sig(text, name)
    if r is None:
        print(f'{name:16s} FAIL'); continue
    w, s, f, c = r
    print(f'{name:16s} w={w} size={s} frame={f:#x} match={c == TC} {dict(sorted(c.items()))}')
