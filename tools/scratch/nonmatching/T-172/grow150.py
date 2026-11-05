"""Grow the pq-blocked frame from 0x50 to 0x60 without moving z (target relative offset).

With p/q block-scoped, z lands 0x30 below the argument home - exactly the target's
relative distance - but the frame is 0x50 instead of 0x60. So the original had one
more 0x10 of stack below z. Try to add that with an honest extra local that IDO
places there.
"""
import itertools
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

TOPDECL = '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z'])
TOPDECL = TOPDECL + '\n    s32 hi;\n    s32 exponent;\n'
BR1 = '''        if (exponent >= 0x3E3) {
            z = x * x;'''
BR2 = '''        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;'''

REST = ['w', 'u', 'r', 't', 'a', 'z']


def pq_blocked(tail_extra=''):
    t = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in REST)
                     + '\n    s32 hi;\n    s32 exponent;\n' + tail_extra)
    t = t.replace(BR1, BR1.replace('            z = x * x;', '            double p, q;\n\n            z = x * x;'))
    t = t.replace(BR2, BR2.replace('            t = 2.0', '            double p, q;\n\n            t = 2.0'))
    return t


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
print('pq_blocked:', sig(pq_blocked(), 'pq'), flush=True)

variants = {}
# grow the frame honestly: an extra double that the code really uses
for extra in (['s'], ['s', 'k']):
    names = extra
    decl = ''.join(f'    double {n};\n' for n in names)
    t = pq_blocked(decl)
    # make the extra locals genuinely used in the branch-1 polynomial chain
    if 's' in names:
        t = t.replace('''            return z * p * x / q + x;''',
                      '''            s = z * p * x / q + x;
            return s;''') if False else t
    variants['extra_' + ''.join(names)] = t

# reorder the remaining function-scope doubles (target z relative slot already right)
for order in itertools.permutations(REST):
    t = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in order)
                     + '\n    s32 hi;\n    s32 exponent;\n')
    t = t.replace(BR1, BR1.replace('            z = x * x;', '            double p, q;\n\n            z = x * x;'))
    t = t.replace(BR2, BR2.replace('            t = 2.0', '            double p, q;\n\n            t = 2.0'))
    variants['ord_' + ''.join(order)] = t

print(len(variants), 'variants', flush=True)
best = []
for name, text in variants.items():
    r = sig(text, name)
    if r:
        best.append((r[0], name, r[1], r[2], r[3] == TC, r[3]))
best.sort()
for w, name, s, f, match, c in best[:10]:
    print(f'{w}\t{name}\t{s}\t{f:#x}\tmatch={match}\t{dict(sorted(c.items()))}')
