#!/usr/bin/env python3
"""Random structural-variant search for func_801BCB70 (flags -> C text -> fast score).
usage: gen_cb70.py [--n N] [--seed S] [-j J] [--out dir]"""
import argparse, concurrent.futures as cf, importlib.util, itertools, random, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

HEAD = '''typedef struct { u32 w0, w1; } T157Gfx;
#define CLAMP(v) ((v) > 0 ? (v) : 0)
#define MIN0(v) ((v) < 0 ? (v) : 0)
#define GCMD(pkt, a, b) { T157Gfx *_g = (T157Gfx *)(pkt); _g->w0 = (a); _g->w1 = (b); }
void func_801BCB70(T157Gfx **dl, u32 tex, s32 arg2, s32 texW, s32 arg4, s32 stepX, u32 cellW, u32 top, u32 left, u32 bottom, u32 right, f32 fx, f32 fy0, s32 scale, u8 alpha, u16 *mask) {
'''

OPTS = {
    'pos': ['var', 'inline'],
    'end': ['var', 'inline'],
    'lrtv': ['var', 'inline'],
    'dsdx': ['var', 'inline'],
    'spB': ['var', 'inline'],
    't6c': ['var', 'inline'],
    'hx': ['var', 'inline'],
    'x0f': ['var', 'inline'],
    'x1f': ['var', 'inline'],
    'y1f': ['var', 'inline'],
    'init': ['early', 'late'],       # lrs/lrt/uls init placement
    'ult': ['ifelse', 'tern'],
    'order': ['a', 'b', 'c'],
    'decl': ['a', 'b', 'c', 'd'],
}

def build(o):
    decls = ['T157Gfx *g;', 'f32 dx;', 'f32 absDx;', 'f32 cellH;', 'f32 accX;', 'f32 fy;', 's32 flag;', 's32 i;',
             'u32 rows;', 'u16 bit;', 'u32 x;', 'u32 col;', 'u16 run;', 'f32 x1c;', 'f32 y1c;', 's32 div;', 's32 sx4;',
             's32 uls;', 'u32 lrs;', 'u32 lrt;', 's32 ult;', 's32 ca;']
    if o['pos'] == 'var': decls.append('u32 pos;')
    if o['end'] == 'var': decls.append('u32 end;')
    if o['dsdx'] == 'var': decls.append('s32 dsdx;')
    if o['spB'] == 'var': decls.append('s32 spB;')
    if o['t6c'] == 'var': decls.append('s32 t6c;')
    if o['hx'] == 'var': decls.append('s32 hx;')
    if o['x0f'] == 'var': decls.append('f32 x0f;')
    if o['x1f'] == 'var': decls.append('f32 x1f;')
    if o['y1f'] == 'var': decls.append('f32 y1f;')
    if o['decl'] == 'b': decls = decls[::-1]
    elif o['decl'] == 'c': decls = sorted(decls, key=lambda d: (d.split()[0] != 'f32', d))
    elif o['decl'] == 'd': decls = sorted(decls, key=lambda d: (d.split()[0] == 'f32', d))
    s = HEAD + ''.join('    %s\n' % d for d in decls) + '\n'
    X0 = 'x0f' if o['x0f'] == 'var' else '(accX + fx)'
    X1 = 'x1f' if o['x1f'] == 'var' else '(%s + absDx)' % X0
    POS = 'pos' if o['pos'] == 'var' else '(i + top)'
    END = 'end' if o['end'] == 'var' else '(i + stepX + top)'
    RUN = 'lrtv'
    LRTV = '(x + cellW * run)'
    DSDX = 'dsdx' if o['dsdx'] == 'var' else '(div & 0xFFFF)'
    SPBE = '((%s << 16) | %s)' % (DSDX, DSDX)
    SPB = 'spB' if o['spB'] == 'var' else SPBE
    T6CE = '(((s32) ((f32) (((f64) (f32) i - 0.5) + (f64) top) * 32.0f) + flag) & 0xFFFF)'
    T6C = 't6c' if o['t6c'] == 'var' else T6CE
    HX = 'hx' if o['hx'] == 'var' else '((sx4 * div) >> 7)'
    SX4 = '(s32) (%s * 4.0f)' % X0
    Y1F = 'y1f' if o['y1f'] == 'var' else '((f32) run * cellH + fy)'
    s += '''    dx = ((f32) stepX * (f32) scale) / 1024;
    g = *dl;
    bit = 1;
    cellH = ((f32) cellW * (f32) scale) / 1024;
    GCMD(g++, 0xFA000000, (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF);
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
'''
    P = []
    if o['x0f'] == 'var': P.append('x0f = accX + fx;')
    P.append('div = 0x100000 / scale;')
    if o['x1f'] == 'var': P.append('x1f = %s + absDx;' % X0)
    if o['pos'] == 'var': P.append('pos = i + top;')
    if o['end'] == 'var': P.append('end = i + stepX + top;')
    P.append('x1c = %s;' % X1)
    if o['init'] == 'early':
        P += ['lrs = bottom - 1;', 'lrt = right - 1;', 'uls = 0;']
    if o['dsdx'] == 'var': P.append('dsdx = div & 0xFFFF;')
    P.append('sx4 = %s;' % SX4)
    if o['t6c'] == 'var': P.append('t6c = %s;' % T6CE)
    if o['spB'] == 'var': P.append('spB = %s;' % SPBE)
    if o['hx'] == 'var': P.append('hx = (sx4 * div) >> 7;')
    if o['order'] == 'b':
        # move sx4/hx before div-derived stuff
        pass
    s += ''.join('                        %s\n' % p for p in P)
    s += '''                        while ((mask[col + run] & bit) && run < 5) {
                            run++;
                        }
'''
    if o['init'] == 'late':
        s += '                        lrs = bottom - 1;\n                        lrt = right - 1;\n                        uls = 0;\n'
    s += '''                        if (%s != 0) {
                            uls = %s;
                        }
                        if (%s < bottom - 1) {
                            lrs = %s;
                        }
''' % (POS, POS, END, END)
    if o['ult'] == 'ifelse':
        s += '''                        ult = x - 1;
                        if (ult > 0) {
                            ca = ult;
                        } else {
                            ca = 0;
                        }
'''
    else:
        s += '''                        ult = x - 1;
                        ca = ult > 0 ? ult : 0;
'''
    s += '''                        if (%s < right - 1) {
                            lrt = %s;
                        }
                        if (!(%s < 640.0f)) {
                            x1c = 640.0f;
                        }
''' % (LRTV, LRTV, X1)
    if o['y1f'] == 'var':
        s += '                        y1f = (f32) run * cellH + fy;\n'
    s += '''                        y1c = %s;
                        if (!(%s < 480.0f)) {
                            y1c = 480.0f;
                        }
''' % (Y1F, Y1F)
    s += '''                        GCMD(g++, ((texW - 1) & 0xFFF) | 0xFD480000, tex);
                        GCMD(g++, (((((s32) (lrs - uls) + 8) >> 3) & 0x1FF) << 9) | 0xF5480000, 0x07080140);
                        GCMD(g++, 0xE6000000, 0);
                        GCMD(g++, ((uls * 4) & 0xFFF) << 12 | 0xF4000000 | ((ca * 4) & 0xFFF), ((lrs * 4) & 0xFFF) << 12 | 0x07000000 | ((lrt * 4) & 0xFFF));
                        GCMD(g++, 0xE7000000, 0);
                        GCMD(g++, (((((s32) (lrs - uls) + 8) >> 3) & 0x1FF) << 9) | 0xF5480000, 0x80140);
                        GCMD(g++, ((uls * 4) & 0xFFF) << 12 | 0xF2000000 | ((ca * 4) & 0xFFF), ((lrs * 4) & 0xFFF) << 12 | ((lrt * 4) & 0xFFF));
                        GCMD(g++, (CLAMP((s32) (y1c * 4.0f)) & 0xFFF) | 0xE4000000 | ((CLAMP((s32) (x1c * 4.0f)) & 0xFFF) << 12), (CLAMP((s32) (fy * 4.0f)) & 0xFFF) | ((CLAMP(sx4) & 0xFFF) << 12));
'''
    s += '''                        GCMD(g++, 0xB3000000, (((s32) ((f32) ((f64) (f32) x - 0.5) * 32.0f) - MIN0(((s32) (fy * 4.0f) * div) >> 7)) & 0xFFFF) | ((%s - MIN0(%s)) << 16));
                        GCMD(g++, 0xB2000000, %s);
''' % (T6C, HX, SPB)
    s += '''                    }
                    x += cellW * run;
                    col += run;
                    fy += cellH * (f32) run;
                } while (x < right);
            }
            bit <<= 1;
            i += stepX;
            accX += dx;
        } while ((u32) i < rows);
    }
    *dl = g;
}
'''
    return s

FIXED = {}
def key(sc): return (abs(sc[3] - 312), sc[0], sc[1])
def cd(start, rounds=3, j=8):
    cur = dict(start)
    def ev(o): return fast.score('func_801BCB70', build(o))
    best = ev(cur)
    print('start', best, flush=True)
    for r in range(rounds):
        changed = False
        for k, vals in OPTS.items():
            if k in FIXED: continue
            cands = [dict(cur, **{k: v}) for v in vals if v != cur[k]]
            with cf.ThreadPoolExecutor(j) as ex:
                res = list(zip(cands, ex.map(ev, cands)))
            for o, sc in res:
                if sc and key(sc) < key(best):
                    best, cur, changed = sc, o, True
                    print('improved', k, o[k], best, flush=True)
        if not changed: break
    return cur, best

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--n', type=int, default=40); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    ap.add_argument('--cd', action='store_true')
    a = ap.parse_args()
    if a.cd:
        FIXED.update({'t6c': 'var', 'spB': 'var'})
        cur, best = cd({'pos':'var','end':'var','lrtv':'var','dsdx':'var','spB':'var','t6c':'var','hx':'var','x0f':'var','x1f':'var','y1f':'var','init':'early','ult':'ifelse','order':'a','decl':'a'})
        print(cur, best)
        if a.out: Path(a.out).write_text(build(cur))
        return
    rnd = random.Random(a.seed)
    base = {k: v[0] for k, v in OPTS.items()}
    combos = [dict(base)]
    for _ in range(a.n - 1):
        combos.append({k: rnd.choice(v) for k, v in OPTS.items()})
    def ev(o):
        return fast.score('func_801BCB70', build(o))
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
