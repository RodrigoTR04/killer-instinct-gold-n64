#!/usr/bin/env python3
"""T-169 DE5C: filter on LAYOUT, not score. Target = frame 0x68, local slots
{0x20,0x24,0x30} + {0x48,0x4c,0x50,0x54}. Sweep which named intermediates are
inlined away (each removal kills one stack slot) and report frame + slot set.
"""
import concurrent.futures as cf
import importlib.util
import itertools
import re
import sys
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
sys.path.insert(0, str(ROOT / 'tools/scratch/nonmatching/T-169'))
import slotsig  # noqa: E402

spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/de5cframe'
OUT.mkdir(exist_ok=True)

BASE = (ROOT / 'tools/scratch/nonmatching/T-169/func_8001DE5C.c').read_text()

# name -> (decl line, assignment line(s), replacement expression)
INL = {
    'dx':   ('  s32 dx;\n',   '  dx = mx - (u16) bx;\n',   '(mx - (u16) bx)'),
    'dx0':  ('  s32 dx0;\n',  '  dx0 = mx - x;\n',        '(mx - x)'),
    'dy':   ('  s32 dy;\n',   '  dy = my - y;\n',         '(my - y)'),
    'dyb':  ('  s32 dyb;\n',  '  dyb = my - by;\n',       '(my - by)'),
    'spanX': ('  s32 spanX;\n', '  spanX = bx2 + dx;\n',  '(bx2 + (mx - (u16) bx))'),
    'spanY': ('  s32 spanY;\n', '  spanY = by2 + dyb;\n', '(by2 + (my - by))'),
    'rx':   ('  s32 rx;\n',   None, '(x2)'),
    'ry':   ('  s32 ry;\n',   None, '(y2)'),
    'areaW': ('  u32 areaW;\n', '  areaW = (rx + 9) & 0xFFF8;\n',  '((rx + 9) & 0xFFF8)'),
    'areaH': ('  u32 areaH;\n', '  areaH = (ry + 1) & 0xFFFE;\n',  '((ry + 1) & 0xFFFE)'),
}


def apply(names):
    src = BASE
    for n in names:
        decl, assign, expr = INL[n]
        src = src.replace(decl, '')
        if assign:
            src = src.replace(assign, '')
        if n == 'rx':
            # rx keeps its conditional assignments; fold them into areaW/maxX
            src = src.replace('''  do
  {
    rx = x2;
  }
  while (0);
  ry = y2;''', '  ry = y2;')
            src = src.replace('''    if (spanX >= x2)
    {
      rx = spanX;
    }''', '')
            src = re.sub(r'\brx\b', '(x2)', src)
            continue
        if n == 'ry':
            src = src.replace('  ry = y2;\n', '')
            src = src.replace('''    if (spanY >= y2)
    {
      ry = spanY;
    }''', '')
            src = re.sub(r'\bry\b', 'y2', src)
            continue
        src = re.sub(r'\b' + n + r'\b', expr, src)
    return src


def probe(p):
    try:
        frame, c = slotsig.draft_sig('func_8001DE5C', p)
        words = dict(screen.measure('func_8001DE5C', p))['words']
        locs = {k: v for k, v in c.items() if k < 0x68}
        return (frame, tuple(sorted(locs)), words, p.name)
    except Exception as e:
        return (None, (), 10**6, p.name + ' ' + str(e)[:40])


tasks = []
for r in (1, 2, 3):
    for combo in itertools.combinations(INL, r):
        p = OUT / ('_'.join(combo) + '.c')
        p.write_text(apply(combo))
        tasks.append(p)

rows = []
with cf.ThreadPoolExecutor(8) as pool:
    rows = list(pool.map(probe, tasks))

TF = -0x68
TS = (0x20, 0x24, 0x30, 0x48, 0x4c, 0x50, 0x54)
rows.sort(key=lambda r: (abs((r[0] or 0) - TF), -len(set(TS) & set(r[1])), r[2]))
for frame, locs, words, name in rows[:18]:
    fh = f'0x{frame:02x}' if frame is not None else 'fail'
    share = len(set(TS) & set(locs))
    print(f'{fh:>5} slots={len(locs)} match={share}/7 words={words:4d} {name}')
