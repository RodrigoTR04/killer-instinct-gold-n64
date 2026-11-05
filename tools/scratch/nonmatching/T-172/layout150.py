"""Source line-layout sweep for func_8002E150 (the brief lists this as a lever)."""
import itertools
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

# The three branch bodies are each a run of statements; join their lines in chunks.
REGIONS = {
    'br1': '''            z = x * x;
            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            return z * p * x / q + x;
''',
    'br2': '''            t = 2.0 * (x * x) - D_80048F78;
            do { z = t * t; } while (0);
            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
''',
    'br3': '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
''',
}
for k, v in REGIONS.items():
    assert v in BASE, k


def joined(text, one_line):
    lines = [l.strip() for l in one_line.strip().split('\n')]
    indent = one_line[:len(one_line) - len(one_line.lstrip())]
    return indent + ' '.join(lines) + '\n'


v = {'base93': BASE}
names = list(REGIONS)
for r in range(1, 4):
    for combo in itertools.combinations(names, r):
        t = BASE
        for k in combo:
            t = t.replace(REGIONS[k], joined(BASE, REGIONS[k]))
        v['+'.join(combo)] = t
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
rows = []
for name, text in v.items():
    r = sig(text, name)
    if r:
        rows.append((r[0], name, r[1], r[2], r[3] == TC))
rows.sort()
for w, name, s, f, match in rows:
    print(f'{w}\t{name}\t{s}\t{f:#x}\tmatch={match}')
