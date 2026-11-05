#!/usr/bin/env python3
"""T-169 DE5C climb v2: rich HONEST moves over the 134 draft.

Moves:
  * declaration order of the named scalars (the IDO frame-layout lever)
  * clamp spelling: -= 0x10000 / += 0xFFFF0000, signed vs unsigned compare
  * which intermediates are named vs inlined (dx, dx0, dy, dyb, spanX, spanY)
  * spanX/spanY as fresh locals vs mutating bx2/by2 in place
  * do-while(0) wrapping of one real statement at each block boundary
  * mx/my vs writing the max straight back into x/y
Every candidate is real C produced by textual rewriting of real code.
"""
import concurrent.futures as cf
import importlib.util
import itertools
import random
import re
import sys
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
TMP = Path(f'/tmp/de5c_v2_{sys.argv[1]}.c')

BASE = Path(sys.argv[2]).read_text()
ITERS = int(sys.argv[3]) if len(sys.argv) > 3 else 500
SEED = int(sys.argv[4]) if len(sys.argv) > 4 else 3
OUT = Path(sys.argv[5])

DECLS = [
    '  s32 mx;\n  s32 my;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 spanX;\n  s32 spanY;\n  s32 rx;\n  s32 ry;\n  u32 areaW;\n  u32 areaH;\n',
    '  u32 areaW;\n  u32 areaH;\n  s32 rx;\n  s32 ry;\n  s32 spanX;\n  s32 spanY;\n  s32 dyb;\n  s32 dy;\n  s32 dx0;\n  s32 dx;\n  s32 my;\n  s32 mx;\n',
    '  s32 rx;\n  s32 ry;\n  s32 mx;\n  s32 my;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 spanX;\n  s32 spanY;\n  u32 areaW;\n  u32 areaH;\n',
    '  s32 spanX;\n  s32 spanY;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 mx;\n  s32 my;\n  s32 rx;\n  s32 ry;\n  u32 areaW;\n  u32 areaH;\n',
]

DECLS_ACTIVE = [
    '  s32 mx;\n  s32 my;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 spanX;\n  s32 spanY;\n  s32 rx;\n  s32 ry;\n  u32 areaW;\n  u32 areaH;\n',
    '  u32 areaW;\n  u32 areaH;\n  s32 rx;\n  s32 ry;\n  s32 spanX;\n  s32 spanY;\n  s32 dyb;\n  s32 dy;\n  s32 dx0;\n  s32 dx;\n  s32 my;\n  s32 mx;\n',
    '  s32 rx;\n  s32 ry;\n  s32 mx;\n  s32 my;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 spanX;\n  s32 spanY;\n  u32 areaW;\n  u32 areaH;\n',
    '  s32 spanX;\n  s32 spanY;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 mx;\n  s32 my;\n  s32 rx;\n  s32 ry;\n  u32 areaW;\n  u32 areaH;\n',
    '  u32 areaW;\n  u32 areaH;\n  s32 mx;\n  s32 my;\n  s32 dx;\n  s32 dx0;\n  s32 dy;\n  s32 dyb;\n  s32 spanX;\n  s32 spanY;\n  s32 rx;\n  s32 ry;\n',
]

WRAPS = [
    ('  if (y >= 0x8000)\n  {\n    do\n    {\n      y -= 0x10000;\n    }\n    while (0);\n  }',
     '  if (y >= 0x8000)\n  {\n    y -= 0x10000;\n  }'),
    ('  do\n  {\n    rx = x2;\n  }\n  while (0);', '  rx = x2;'),
    ('    do\n    {\n      sprite->halfWidth = mx;\n    }\n    while (0);', '    sprite->halfWidth = mx;'),
    ('  do\n  {\n    spanX = bx2 + dx;\n  }\n  while (0);', '  spanX = bx2 + dx;'),
]

CLAMP = [('-= 0x10000', '+= 0xFFFF0000')]

SPAN_STYLE = {
    'fresh': '''  dx = mx - (u16) bx;
  spanX = bx2 + dx;
  dx0 = mx - x;
  dy = my - y;
  dyb = my - by;
  x2 += dx0;
  y2 += dy;
  spanY = by2 + dyb;''',
    'inplace': '''  dx = mx - (u16) bx;
  dx0 = mx - x;
  dy = my - y;
  dyb = my - by;
  bx2 += dx;
  by2 += dyb;
  x2 += dx0;
  y2 += dy;''',
}

MXMY = {
    'locals': '''  mx = x;
  my = y;
  if (arg1 != 0)
  {
    if (bx >= x)
    {
      mx = bx;
    }
    if (by >= y)
    {
      my = by;
    }
  }''',
    'inplace': '''  if (arg1 != 0)
  {
    if (bx >= x)
    {
      x = bx;
    }
    if (by >= y)
    {
      y = by;
    }
  }''',
}


def score(text):
    TMP.write_text(text)
    try:
        return dict(screen.measure('func_8001DE5C', TMP))['words']
    except Exception:
        return 10 ** 6


def render(st):
    t = BASE
    # declaration order: only the trailing block starting at "  s32 mx;"
    mstart = t.index('  s32 mx;\n  s32 my;\n')
    mend = t.index('  T022Sprite *sprite;')
    t = t[:mstart] + DECLS_ACTIVE[st['decl']] + t[mend:]
    # span style
    src_style = SPAN_STYLE[st['span_from']]
    dst_style = SPAN_STYLE[st['span']]
    t = t.replace(src_style, dst_style)
    # mx/my
    src_m = MXMY[st['mxmy_from']]
    dst_m = MXMY[st['mxmy']]
    t = t.replace(src_m, dst_m)
    if st['mxmy'] == 'inplace':
        t = t.replace('mx', 'x').replace('my', 'y')
        t = re.sub(r'\bs32 x\b', 's32 x', t)
    # wraps
    for i, (wrap, plain) in enumerate(WRAPS):
        if st['wrap'][i]:
            t = t.replace(plain, wrap)
        else:
            t = t.replace(wrap, plain)
    return t


rng = random.Random(SEED)
start = {'decl': 0, 'clamp': 0, 'span': 'fresh', 'span_from': 'fresh',
         'mxmy': 'locals', 'mxmy_from': 'locals',
         'wrap': [False] * len(WRAPS)}
cur = start
best_text = render(cur)
best = score(best_text)
print(f'start {best}', flush=True)
OUT.write_text(best_text)

for it in range(ITERS):
    st = dict(cur)
    st['wrap'] = list(cur['wrap'])
    kind = rng.random()
    if kind < 0.3:
        st['decl'] = rng.randrange(len(DECLS_ACTIVE))
    elif kind < 0.75:
        i = rng.randrange(len(WRAPS))
        st['wrap'][i] = not st['wrap'][i]
    elif kind < 0.9:
        st['span_from'] = cur['span']
        st['span'] = 'inplace' if cur['span'] == 'fresh' else 'fresh'
    else:
        st['mxmy_from'] = cur['mxmy']
        st['mxmy'] = 'inplace' if cur['mxmy'] == 'locals' else 'locals'
    text = render(st)
    s = score(text)
    if s <= best:
        if s < best:
            best, best_text = s, text
            OUT.write_text(best_text)
            print(f'{best}  decl={st["decl"]} wraps={st["wrap"]} span={st["span"]} mxmy={st["mxmy"]}', flush=True)
        # accept equal to drift
        cur = dict(st)
        cur['span_from'] = st['span']
        cur['mxmy_from'] = st['mxmy']
        # renormalise the *_from keys to the current render
        cur['span_from'] = st['span']
        cur['mxmy_from'] = st['mxmy']
    else:
        pass

OUT.write_text(best_text)
print('final', best, flush=True)
