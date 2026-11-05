#!/usr/bin/env python3
"""T-169 DE5C: the frame is 0x78 vs the target's 0x68 and 11 user spills vs 7.
Inline each named intermediate (one at a time, then pairs) so IDO allocates
fewer stack slots."""
import concurrent.futures as cf
import importlib.util
import itertools
import re
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/de5cg'
OUT.mkdir(exist_ok=True)

BASE = (ROOT / 'tools/scratch/nonmatching/T-169/func_8001DE5C.c').read_text()

# simple textual substitutions: (decl line, assignment line, uses -> expr)
INLINES = {
    'dx0': ['    s32 dx0;\n', '    dx0 = mx - x;\n', 'dx0', '(mx - x)'],
    'dx': ['    s32 dx;\n', '    dx = mx - bx;\n', 'dx', '(mx - bx)'],
    'dy': ['    s32 dy;\n', '    dy = my - y;\n', 'dy', '(my - y)'],
    'dyb': ['    s32 dyb;\n', '    dyb = my - by;\n', 'dyb', '(my - by)'],
    'areaW': ['    u32 areaW;\n', '    areaW = (rx + 9) & 0xFFF8;\n', 'areaW', '((rx + 9) & 0xFFF8)'],
    'areaH': ['    u32 areaH;\n', '    areaH = (ry + 1) & 0xFFFE;\n', 'areaH', '((ry + 1) & 0xFFFE)'],
    'spanX': ['    s32 spanX;\n', '    spanX = bx2 + dx;\n', 'spanX', '(bx2 + (mx - bx))'],
    'spanY': ['    s32 spanY;\n', '    spanY = by2 + dyb;\n', 'spanY', '(by2 + (my - by))'],
}


def apply(names):
    src = BASE
    for n in names:
        decl, assign, old, new = (INLINES[n] + [''])[:4]
        src = src.replace(decl, '')
        src = src.replace(assign, '')
        src = re.sub(r'\b' + re.escape(old) + r'\b', new, src)
    return src


tasks = []
for r in (1, 2):
    for combo in itertools.combinations(INLINES, r):
        p = OUT / ('_'.join(combo) + '.c')
        p.write_text(apply(combo))
        tasks.append(p)
# also all single declarations removed but assignments kept where possible is
# invalid; skip.


def score(p):
    try:
        res = dict(screen.measure('func_8001DE5C', p))
        return (res['words'], res['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:50])


with cf.ThreadPoolExecutor(8) as pool:
    for row in sorted(pool.map(score, tasks))[:20]:
        print(row)
