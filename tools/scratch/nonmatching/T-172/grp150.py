"""Probe whether declaration grouping (shared vs separate statements) moves slots."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
NAMES = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']
OLD = '\n'.join(f'    double {n};' for n in NAMES) + '\n    s32 hi;\n    s32 exponent;\n'
assert OLD in BASE

tf, tc = target_sig('func_8002E150')
print('TARGET', fmt(tf, tc))


def sig(text, label):
    import detail
    w, s, f, _ = detail.detail('func_8002E150', text, label)
    if f is None:
        print(f'{label:24s} FAIL'); return
    # recompute counts from the dump
    from collections import Counter
    import re
    lines = slotdump.dump('func_8002E150', text, label)
    c = Counter()
    for ln in lines:
        for m in re.finditer(r'(\d+)\(sp\)', ln):
            c[int(m.group(1))] += 1
    match = (c == tc)
    print(f'{label:24s} w={w} frame={f:#x} {dict(sorted(c.items()))} {"MATCH" if match else ""}')


sig(BASE, 'base_sep93')
T = '    double ' + ', '.join(NAMES) + ';\n    s32 hi;\n    s32 exponent;\n'
sig(BASE.replace(OLD, T), 'combined')
for k in (1, 2, 3, 4):
    groups = []
    for i in range(0, len(NAMES), k):
        groups.append('    double ' + ', '.join(NAMES[i:i + k]) + ';')
    sig(BASE.replace(OLD, '\n'.join(groups) + '\n    s32 hi;\n    s32 exponent;\n'), f'group{k}')
