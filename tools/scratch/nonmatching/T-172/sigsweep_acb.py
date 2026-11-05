"""Sweep func_801ACB1C declaration orders, filtered on the exact target slot signature.

The plain (no pointer local) base already has the right frame (0x60) and the right
slot *counts*; only the assignment differs -- the target puts the two callback outs
at 0x44/0x48 (below) and the gfx pair at 0x58/0x5c (above), while the draft has
them the other way round.
"""
import itertools
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import slotdump
from slotsig import target_sig, fmt
import re
from collections import Counter

ROOT = '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743'
CUR = open(ROOT + '/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
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
LINES = {
    'b': '    s32 sp48;\n', 'c': '    s32 sp44;\n',
    'd': '    DisplayCommand *gfxStart;\n', 'e': '    DisplayCommand *gfx;\n',
    'f': '    u32 diff;\n', 'g': '    s32 h;\n', 'h': '    s32 i;\n',
}
groups = [('b', 'c'), ('d', 'e'), ('f',), ('g',), ('h',)]

TF, TC = target_sig('func_801ACB1C')
print('TARGET', fmt(TF, TC), flush=True)


def sig(text, label):
    try:
        lines = slotdump.dump('func_801ACB1C', text, label)
    except SystemExit:
        return None, None
    c = Counter()
    for ln in lines:
        m = re.search(r'sp,sp,-(\d+)', ln.replace(' ', ''))
        if m:
            frame = -int(m.group(1))
        for mm in re.finditer(r'(\d+)\(sp\)', ln):
            c[int(mm.group(1))] += 1
    return frame, c


base_frame, base_counts = sig(PLAIN, 'plain')
print('PLAIN ', fmt(base_frame, base_counts), flush=True)


def one(order):
    text = PLAIN.replace(DECL, ''.join(LINES[k] for k in order))
    return ''.join(order), text


hits = []
orders = []
for perm in itertools.permutations(groups):
    order = [k for g in perm for k in g]
    orders.append(order)
print(len(orders), 'orders', flush=True)

with ThreadPoolExecutor(max_workers=8) as pool:
    for label, text in pool.map(one, orders):
        f, c = sig(text, label)
        if f == TF and c == TC:
            hits.append((label, text))
            print('MATCH', label, flush=True)
print('hits', len(hits))
for label, text in hits[:5]:
    open(f'/tmp/acb_hit_{label}.c', 'w').write(text)
