#!/usr/bin/env python3
"""gen3.py : explicit enumeration of variable-set / hoisting structure for func_801BCB70.
Options: pos/end/limS/limT as variables assigned before the run loop, end shared with ult,
xl/yl/xh/yh as vars or inline, uls/lrs/lrt as presets-before-loop vs ternary-after-loop.
usage: gen3.py [-j J] [--out file]"""
import argparse, concurrent.futures as cf, importlib.util, itertools, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

HEAD = '''typedef struct { u32 w0, w1; } T157Gfx;
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define GCMD(pkt, a, b) { T157Gfx *_g = (T157Gfx *)(pkt); _g->w0 = (a); _g->w1 = (b); }
void func_801BCB70(T157Gfx **dl, u32 tex, s32 arg2, s32 texW, s32 arg4, s32 stepX, u32 cellW, u32 top, u32 left, u32 bottom, u32 right, f32 fx, f32 fy0, s32 scale, u8 alpha, u16 *mask) {
'''

def build(o):
    d = ['s32 i;', 'T157Gfx *g;', 'f32 dx;', 'f32 absDx;', 'f32 cellH;', 'f32 accX;', 'f32 fy;', 's32 flag;', 's32 rows;',
         'u16 bit;', 's32 x;', 's32 col;', 'u16 run;', 's32 div;', 's32 uls;', 's32 ult;', 's32 lrs;', 's32 lrt;',
         'f32 x0f;', 'f32 x1f;', 'f32 y1f;', 'f32 x1c;', 'f32 y1c;']
    if o['pos']: d.append('u32 pos;')
    if not o['share'] and o['end']: d.append('u32 end;')
    if o['limS']: d.append('u32 limS;')
    if o['limT']: d.append('u32 limT;')
    for k in ('xl', 'yl', 'xh', 'yh'):
        if o[k]: d.append('s32 %s;' % k)
    s = HEAD + ''.join('    %s\n' % x for x in d) + '\n'
    END = 'ult' if o['share'] else 'end'
    POS = 'pos' if o['pos'] else '(i + top)'
    ENDX = END if o['end'] else '(i + stepX + top)'
    LS = 'limS' if o['limS'] else '(bottom - 1)'
    LT = 'limT' if o['limT'] else '(right - 1)'
    XL = 'xl' if o['xl'] else '(s32) (x0f * 4.0f)'
    YL = 'yl' if o['yl'] else '(s32) (fy * 4.0f)'
    XH = 'xh' if o['xh'] else '(s32) (x1c * 4.0f)'
    YH = 'yh' if o['yh'] else '(s32) (y1c * 4.0f)'
    s += '''    dx = ((f32) stepX * (f32) scale) / 1024;
    g = *dl;
    bit = 1;
    cellH = ((f32) cellW * (f32) scale) / 1024;
    GCMD(g++, 0xFA000000, _SHIFTL(alpha, 24, 8) | _SHIFTL(alpha, 16, 8) | _SHIFTL(alpha, 8, 8) | _SHIFTL(255, 0, 8));
    if (dx < 0.0f) {
        absDx = -dx;
        flag = 0x200;
        stepX = -stepX;
    } else {
        absDx = dx;
        flag = 0;
    }
    i = 0;
    accX = 0.0f;
    rows = bottom - top;
    if (rows != 0) {
        do {
            x = left;
            fy = fy0;
            col = 0;
            if (x < right) {
                do {
                    run = 1;
                    if (mask[col] & bit) {
                        div = 0x100000 / scale;
                        x0f = accX + fx;
                        x1f = x0f + absDx;
'''
    pre = []
    if o['pos']: pre.append('pos = i + top;')
    if o['end']: pre.append('%s = i + stepX + top;' % END)
    if o['limS']: pre.append('limS = bottom - 1;')
    if o['limT']: pre.append('limT = right - 1;')
    if o['preset']:
        pre += ['uls = 0;', 'lrs = %s;' % LS, 'lrt = %s;' % LT]
    s += ''.join('                        %s\n' % p for p in pre)
    s += '''                        while ((mask[col + run] & bit) && run < 5) {
                            run++;
                        }
'''
    if o['preset']:
        s += '''                        if (%s > 0) { uls = %s; }
                        if (%s < %s) { lrs = %s; }
''' % (POS, POS, ENDX, LS, ENDX)
        ult = '                        ult = MAX(x - 1, 0);\n'
        s += ult
        s += '                        if (x + cellW * run < %s) { lrt = x + cellW * run; }\n' % LT
    else:
        s += '                        uls = MAX(%s, 0);\n' % POS
        s += '                        lrs = MIN(%s, %s);\n' % (ENDX, LS)
        s += '                        ult = MAX(x - 1, 0);\n'
        s += '                        lrt = MIN(x + cellW * run, %s);\n' % LT
    s += '''                        y1f = (f32) run * cellH + fy;
                        x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
'''
    for k, e in (('xl', '(s32) (x0f * 4.0f)'), ('yl', '(s32) (fy * 4.0f)'), ('xh', '(s32) (x1c * 4.0f)'), ('yh', '(s32) (y1c * 4.0f)')):
        if o[k]: s += '                        %s = %s;\n' % (k, e)
    s += '''                        GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);
                        GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), 0x07080140);
                        GCMD(g++, 0xE6000000, 0);
                        GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12));
                        GCMD(g++, 0xE7000000, 0);
                        GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), 0x00080140);
                        GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(0, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12));
'''
    s += '''                        GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX(%s, 0), 12, 12) | _SHIFTL(MAX(%s, 0), 0, 12),
                                  _SHIFTL(0, 24, 3) | _SHIFTL(MAX(%s, 0), 12, 12) | _SHIFTL(MAX(%s, 0), 0, 12));
''' % (XH, YH, XL, YL)
    s += '''                        GCMD(g++, 0xB3000000, _SHIFTL((((s32) ((f32) (((f64) (f32) i - 0.5) + (f64) top) * 32.0f) + flag) & 0xFFFF) - MIN((%s * div) >> 7, 0), 16, 16) | _SHIFTL((s32) ((f32) ((f64) (f32) x - 0.5) * 32.0f) - MIN((%s * div) >> 7, 0), 0, 16));
                        GCMD(g++, 0xB2000000, _SHIFTL(div, 16, 16) | _SHIFTL(div, 0, 16));
                    }
                    x += cellW * run;
                    col += run;
                    fy += cellH * (f32) run;
                } while (x < right);
            }
            bit <<= 1;
            i += stepX;
            accX += dx;
        } while ((u32) i < bottom - top);
    }
    *dl = g;
}
''' % (XL, YL)
    return s

KEYS = ['pos', 'end', 'share', 'limS', 'limT', 'xl', 'yl', 'xh', 'yh', 'preset']

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    a = ap.parse_args()
    combos = []
    for vals in itertools.product([0, 1], repeat=len(KEYS)):
        o = dict(zip(KEYS, vals))
        if o['share'] and not o['end']: continue
        combos.append(o)
    def ev(o):
        try: return fast.score('func_801BCB70', build(o))
        except Exception: return None
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(zip(combos, ex.map(ev, combos)))
    res = [(s, o) for o, s in res if s and s[2] >= 400 and s[3] == 312]
    res.sort(key=lambda r: (r[0][1], r[0][0]))
    for s, o in res[:12]:
        print(s, ''.join(str(o[k]) for k in KEYS), o)
    if a.out and res:
        Path(a.out).write_text(build(res[0][1]))

if __name__ == '__main__':
    main()
