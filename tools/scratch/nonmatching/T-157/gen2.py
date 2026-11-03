#!/usr/bin/env python3
"""gen2.py : structural-variant search around w/h2.c for func_801BCB70.
Edits: statement order of the clamp block, inline/var for floats, placement of xl..yh,
x1c/y1c style.  usage: gen2.py [--n N] [--seed S] [-j J] [--out file]"""
import argparse, concurrent.futures as cf, importlib.util, itertools, random, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
BASE = (ROOT / 'tools/scratch/nonmatching/T-157/w/h2.c').read_text()

I = ' ' * 24
STM = {
    'uls': I + 'uls = MAX(i + top, 0);\n',
    'ult': I + 'ult = MAX(x - 1, 0);\n',
    'lrt': I + 'lrt = MIN(x + cellW * run, right - 1);\n',
    'y1f': I + 'y1f = (f32) run * cellH + fy;\n',
    'lrs': I + 'lrs = MIN(i + stepX + top, bottom - 1);\n',
}
CL = (I + 'x1c = x1f;\n' + I + 'if (!(x1f < 640.0f)) {\n' + I + '    x1c = 640.0f;\n' + I + '}\n'
      + I + 'y1c = y1f;\n' + I + 'if (!(y1f < 480.0f)) {\n' + I + '    y1c = 480.0f;\n' + I + '}\n')
XY = (I + 'xl = (s32) (x0f * 4.0f);\n' + I + 'yl = (s32) (fy * 4.0f);\n' + I + 'xh = (s32) (x1c * 4.0f);\n' + I + 'yh = (s32) (y1c * 4.0f);\n')

def build(o):
    s = BASE
    a = s.index(STM['uls'])
    b = s.index('                        GCMD(g++, _SHIFTL(0xFD')
    block = ''.join(STM[k] for k in o['order'])
    if o['cl'] == 'tern':
        cl = (I + 'x1c = MIN(x1f, 640.0f);\n' + I + 'y1c = MIN(y1f, 480.0f);\n')
    else:
        cl = CL
    xy = XY
    if o['xy'] == 'split':
        xy = (I + 'xl = (s32) (x0f * 4.0f);\n' + I + 'yl = (s32) (fy * 4.0f);\n')
        xy2 = (I + 'xh = (s32) (x1c * 4.0f);\n' + I + 'yh = (s32) (y1c * 4.0f);\n')
        mid = block + cl + xy + xy2
    elif o['xy'] == 'first':
        mid = XY.replace(I + 'xh = (s32) (x1c * 4.0f);\n', '').replace(I + 'yh = (s32) (y1c * 4.0f);\n', '')
        mid = mid + block + cl + I + 'xh = (s32) (x1c * 4.0f);\n' + I + 'yh = (s32) (y1c * 4.0f);\n'
    elif o['xy'] == 'clfirst':
        mid = cl + block + XY
    else:
        mid = block + cl + xy
    s = s[:a] + mid + s[b:]
    if o['y1f'] == 'inline':
        s = s.replace(I + 'y1f = (f32) run * cellH + fy;\n', '')
        s = s.replace('y1c = y1f;', 'y1c = (f32) run * cellH + fy;').replace('!(y1f < 480.0f)', '!((f32) run * cellH + fy < 480.0f)')
        s = s.replace('MIN(y1f, 480.0f)', 'MIN((f32) run * cellH + fy, 480.0f)')
        s = s.replace('    f32 y1f;\n', '')
    if o['x0f'] == 'inline':
        s = s.replace(I + 'x0f = accX + fx;\n', '')
        s = s.replace('x1f = x0f + absDx;', 'x1f = accX + fx + absDx;').replace('(x0f * 4.0f)', '((accX + fx) * 4.0f)')
        s = s.replace('    f32 x0f;\n', '')
    return s

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--n', type=int, default=64); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    a = ap.parse_args()
    rnd = random.Random(a.seed)
    keys = list(STM)
    base = {'order': ['uls', 'ult', 'lrt', 'y1f', 'lrs'], 'cl': 'if', 'xy': 'std', 'y1f': 'var', 'x0f': 'var'}
    combos = [base]
    seen = {repr(base)}
    while len(combos) < a.n:
        order = keys[:]; rnd.shuffle(order)
        o = {'order': order, 'cl': rnd.choice(['if', 'tern']), 'xy': rnd.choice(['std', 'split', 'first', 'clfirst']),
             'y1f': rnd.choice(['var', 'inline']), 'x0f': rnd.choice(['var', 'inline'])}
        # y1f inline requires y1f stmt removed from order
        if o['y1f'] == 'inline':
            pass
        if repr(o) in seen: continue
        seen.add(repr(o)); combos.append(o)
    def ev(o):
        try:
            return fast.score('func_801BCB70', build(o))
        except Exception as e:
            return None
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(zip(combos, ex.map(ev, combos)))
    res = [(s, o) for o, s in res if s]
    res.sort(key=lambda r: (r[0][1], r[0][0]))
    for s, o in res[:8]:
        print(s, o)
    if a.out and res:
        Path(a.out).write_text(build(res[0][1]))

if __name__ == '__main__':
    main()
