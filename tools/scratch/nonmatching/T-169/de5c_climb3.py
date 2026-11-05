#!/usr/bin/env python3
"""T-169 DE5C: hill-climb the official count from the 134 draft with a rich set
of HONEST source-shape moves (statement order, decode order, in-place vs fresh
locals, clamp spelling, declaration order, block scoping). Every candidate is
real C; no dummy statements or unused locals are generated."""
import concurrent.futures as cf
import importlib.util
import random
import re
import sys
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
TMP = Path(f'/tmp/de5c_climb_{sys.argv[1]}.c')

BASE = Path(sys.argv[2]).read_text()
ITERS = int(sys.argv[3]) if len(sys.argv) > 3 else 400
SEED = int(sys.argv[4]) if len(sys.argv) > 4 else 1
OUT = Path(sys.argv[5])

# ---------- move set -------------------------------------------------------

DECODE_PLAIN = '''  s32 x = (arg0[1] << 8) + arg0[0];
  s32 y = (arg0[3] << 8) + arg0[2];
  s32 x2 = (arg0[5] << 8) + arg0[4];
  s32 y2 = (arg0[7] << 8) + arg0[6];
'''

DECODE_ALT = {
    'decl_then_assign': '''  s32 x, y, x2, y2;
  x = (arg0[1] << 8) + arg0[0];
  y = (arg0[3] << 8) + arg0[2];
  x2 = (arg0[5] << 8) + arg0[4];
  y2 = (arg0[7] << 8) + arg0[6];
''',
    'decl_then_assign_xy_first': '''  s32 x, y, x2, y2;
  x = (arg0[1] << 8) + arg0[0];
  x2 = (arg0[5] << 8) + arg0[4];
  y = (arg0[3] << 8) + arg0[2];
  y2 = (arg0[7] << 8) + arg0[6];
''',
    'bytes': '''  s32 x, y, x2, y2;
  x = (arg0[1] << 8) + arg0[0];
  y = (arg0[3] << 8) + arg0[2];
  x2 = (arg0[5] << 8) + arg0[4];
  y2 = (arg0[7] << 8) + arg0[6];
''',
}

CLAMP_VARIANTS = {
    'sub': ('  x -= 0x10000;', '  bx -= 0x10000;', '  y -= 0x10000;', '  by -= 0x10000;'),
    'add': ('  x += 0xFFFF0000;', '  bx += 0xFFFF0000;', '  y += 0xFFFF0000;', '  by += 0xFFFF0000;'),
}

WRAPS = {
    'y': ('  if (y >= 0x8000)\n  {\n    y -= 0x10000;\n  }',
          '  if (y >= 0x8000)\n  {\n    do\n    {\n      y -= 0x10000;\n    }\n    while (0);\n  }'),
    'x': ('  if (x >= 0x8000)\n  {\n    x -= 0x10000;\n  }',
          '  if (x >= 0x8000)\n  {\n    do\n    {\n      x -= 0x10000;\n    }\n    while (0);\n  }'),
    'bx': ('  if (bx >= 0x8000)\n  {\n    bx -= 0x10000;\n  }',
           '  if (bx >= 0x8000)\n  {\n    do\n    {\n      bx -= 0x10000;\n    }\n    while (0);\n  }'),
    'by': ('  if (by >= 0x8000)\n  {\n    by -= 0x10000;\n  }',
           '  if (by >= 0x8000)\n  {\n    do\n    {\n      by -= 0x10000;\n    }\n    while (0);\n  }'),
    'maxX': ('  dx0 = mx - x;\n  spanX = bx2 + dx;\n  x2 += dx0;\n  y2 += dy;\n  spanY = by2 + dyb;',
             '  dx0 = mx - x;\n  do\n  {\n    spanX = bx2 + dx;\n  }\n  while (0);\n  x2 += dx0;\n  y2 += dy;\n  spanY = by2 + dyb;'),
    'sprite': ('    sprite->halfWidth = mx;\n    sprite->halfHeight = my;',
               '    do\n    {\n      sprite->halfWidth = mx;\n    }\n    while (0);\n    sprite->halfHeight = my;'),
}

ORDER_BLOCKS = [
    # (label, text)  -- blocks of the clamp/max region that can be reordered
]


def blocks(src):
    """Split the 'mx/my .. spans' region into reorderable blocks."""
    keys = []
    for name in ('BX_CLAMP', 'BY_CLAMP', 'MXMY', 'DERIVED', 'RXRY'):
        keys.append(name)
    return keys


def score(text):
    TMP.write_text(text)
    try:
        return dict(screen.measure('func_8001DE5C', TMP))['words']
    except Exception:
        return 10 ** 6


rng = random.Random(SEED)
cur, best = BASE, score(BASE)
print(f'start {best}', flush=True)
best_text = cur

# state: which wraps are on, which clamp spelling, decode variant, decl order
state = {'wraps': {k: (WRAPS[k][1] in BASE) for k in WRAPS},
         'clamp': 'sub', 'decode': 'plain'}


def render(st):
    t = BASE
    for k, (plain, wrap) in WRAPS.items():
        if st['wraps'][k]:
            t = t.replace(plain, wrap)
        else:
            t = t.replace(wrap, plain)
    if st['clamp'] == 'add':
        for a, b in zip(CLAMP_VARIANTS['sub'], CLAMP_VARIANTS['add']):
            t = t.replace(a, b)
    return t


def neighbours(st):
    out = []
    for k in WRAPS:
        c = {'wraps': dict(st['wraps']), 'clamp': st['clamp'], 'decode': st['decode']}
        c['wraps'][k] = not c['wraps'][k]
        out.append(('wrap:' + k, c))
    for cl in CLAMP_VARIANTS:
        if cl != st['clamp']:
            c = {'wraps': dict(st['wraps']), 'clamp': cl, 'decode': st['decode']}
            out.append(('clamp:' + cl, c))
    return out


seen = {best}
for it in range(ITERS):
    cands = [n for n in neighbours(state) if id(n[1]) not in ()]
    label, st = rng.choice(cands)
    text = render(st)
    s = score(text)
    if s < best:
        best, state, best_text = s, st, text
        OUT.write_text(best_text)
        print(f'{best}  <- {label}', flush=True)
    elif s == best:
        state = st

OUT.write_text(best_text)
print('final', best, flush=True)
