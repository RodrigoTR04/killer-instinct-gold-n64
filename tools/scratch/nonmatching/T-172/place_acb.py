"""Enumerate honest declaration placement for func_801ACB1C at the 130-word base.

Each local may be (a) a statement at function scope in any order, or (b) moved to
the top of the branch it is used in. Filter on official words; keep the best.
"""
import itertools
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_801ACB1C.c').read()
DECL = '''    s32 *a414;
    s32 sp48;
    s32 sp44;
    DisplayCommand *gfxStart;
    DisplayCommand *gfx;
    u32 diff;
    s32 h;
    s32 i;
'''
assert DECL in BASE

T = {
    'a414': 's32 *', 'sp48': 's32', 'sp44': 's32',
    'gfxStart': 'DisplayCommand *', 'gfx': 'DisplayCommand *',
    'diff': 'u32', 'h': 's32', 'i': 's32',
}
NAMES = list(T)

BRANCH = '''        if (D_8004A414 < 2 && D_801CD45C <= 0) {
'''
BRANCH2 = '''        if ((*a414) < 2 && D_801CD45C <= 0) {
'''
# the draft now uses (*a414)
assert BRANCH2 in BASE
BRANCH = BRANCH2

# which locals are used only inside the main branch
INNER_OK = {'sp48', 'sp44', 'gfxStart', 'gfx', 'diff', 'h'}
# i is used in both trailing loops; a414 spans both arms

v = {}
base_best = 130


def make(inner_set, order):
    outer = [n for n in order if n not in inner_set]
    inner = [n for n in order if n in inner_set]
    text = BASE.replace(DECL, ''.join(f'    {T[n]} {n};\n' for n in outer))
    if inner:
        text = text.replace(BRANCH, BRANCH + ''.join(f'            {T[n]} {n};\n' for n in inner) + '\n')
    return text


cands = []
for r in range(0, len(INNER_OK) + 1):
    for inner in itertools.combinations(sorted(INNER_OK), r):
        cands.append(set(inner))
import random
random.seed(7)
jobs = []
for inner in cands:
    orders = list(itertools.permutations(NAMES))
    random.shuffle(orders)
    for order in orders[:12]:
        v[f'{len(inner)}|{"".join(sorted(inner))}|{"".join(order)}'] = make(inner, order)
print(len(v), 'variants', flush=True)
detail.run('func_801ACB1C', v, jobs=14)
