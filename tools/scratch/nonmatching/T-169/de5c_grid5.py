#!/usr/bin/env python3
"""T-169 DE5C: target uses frame 0x68 and NO callee-saved registers; v14 uses
s0. Grid the argument-decode spelling (plain assignment vs. initializers) and
the pointer-copy placement, which is what forces arg0/arg1 into s registers."""
import concurrent.futures as cf
import importlib.util
import itertools
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/de5cg4'
OUT.mkdir(exist_ok=True)

PRE = '''extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

'''

DECLS_INIT = '''void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 ax0 = (arg0[1] << 8) + arg0[0];
    s32 ay0 = (arg0[3] << 8) + arg0[2];
    s32 ax1 = (arg0[5] << 8) + arg0[4];
    s32 ay1 = (arg0[7] << 8) + arg0[6];
    s32 bx0;
    s32 by0;
    s32 bx1;
    s32 by1;
    s32 mx, my, maxX, maxY;
    T022Sprite *sprite;
'''

DECLS_PLAIN = '''void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 ax0, ay0, ax1, ay1;
    s32 bx0, by0, bx1, by1;
    s32 mx, my, maxX, maxY;
    T022Sprite *sprite;
'''

DECODE_INIT = ''
DECODE_PLAIN = '''    ax0 = (arg0[1] << 8) + arg0[0];
    ay0 = (arg0[3] << 8) + arg0[2];
    ax1 = (arg0[5] << 8) + arg0[4];
    ay1 = (arg0[7] << 8) + arg0[6];
'''

RECT = '''    if (arg1 != 0) {
        bx0 = (arg1[1] << 8) + arg1[0];
        by0 = (arg1[3] << 8) + arg1[2];
        bx1 = (arg1[5] << 8) + arg1[4];
        by1 = (arg1[7] << 8) + arg1[6];
    }
'''

CLAMP_WRAP = '''    if (ax0 >= 0x8000) {
        ax0 -= 0x10000;
    }
    if (bx0 >= 0x8000) {
        bx0 -= 0x10000;
    }
    bx0 -= 1;
    if (ay0 >= 0x8000) {
        do {
            ay0 -= 0x10000;
        } while (0);
    }
    if (by0 >= 0x8000) {
        by0 -= 0x10000;
    }
'''

CLAMP_PLAIN = CLAMP_WRAP.replace('''    if (ay0 >= 0x8000) {
        do {
            ay0 -= 0x10000;
        } while (0);
    }''', '''    if (ay0 >= 0x8000) {
        ay0 -= 0x10000;
    }''')

REST_SIMPLE = '''    mx = ax0;
    my = ay0;
    if (arg1 != 0) {
        if (bx0 >= ax0) {
            mx = bx0;
        }
        if (by0 >= ay0) {
            my = by0;
        }
    }
    maxX = ax1 + (mx - ax0);
    maxY = ay1 + (my - ay0);
    if (arg1 != 0) {
        bx1 += mx - bx0;
        by1 += my - by0;
        if (bx1 >= maxX) {
            maxX = bx1;
        }
        if (by1 >= maxY) {
            maxY = by1;
        }
    }
'''

# target-like: derived edges kept in named locals that spill to 0x20..0x54
REST_NAMED = '''    mx = ax0;
    my = ay0;
    if (arg1 != 0) {
        if (bx0 >= ax0) {
            mx = bx0;
        }
        if (by0 >= ay0) {
            my = by0;
        }
    }
    {
        s32 dx = mx - bx0;
        s32 dx0 = mx - ax0;
        s32 dy = my - ay0;
        s32 dyb = my - by0;
        maxX = ax1 + dx0;
        maxY = ay1 + dy;
        if (arg1 != 0) {
            bx1 += dx;
            by1 += dyb;
            if (bx1 >= maxX) {
                maxX = bx1;
            }
            if (by1 >= maxY) {
                maxY = by1;
            }
        }
    }
'''

TAIL = '''
    if ((s32)(((maxX + 9) & 0xFFF8) * ((maxY + 1) & 0xFFFE)) < 0x8891) {
        sprite = &D_8004CED0[D_8004EA78];
        sprite->halfWidth = mx;
        sprite->halfHeight = my;
        sprite->width = maxX;
        sprite->height = maxY;
        sprite->width2 = (maxX + 9) & 0xFFF8;
        ((s16 *)sprite)[10] = maxX;
        ((s16 *)sprite)[11] = maxY;
        ((s16 *)sprite)[13] = arg2;
        func_80031050(arg0, mx - ax0, ((maxY - maxY) << 16) | (my - ay0));
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, mx - bx0, ((maxY - maxY) << 16) | (my - by0));
        }
    }
}
'''

DECLS = {'init': (DECLS_INIT, DECODE_INIT), 'plain': (DECLS_PLAIN, DECODE_PLAIN)}
CLAMPS = {'wrap': CLAMP_WRAP, 'plain': CLAMP_PLAIN}
RESTS = {'simple': REST_SIMPLE, 'named': REST_NAMED}
PLACE = {'rect_first': 0, 'rect_last': 1}

tasks = []
for dk, ck, rk, pk in itertools.product(DECLS, CLAMPS, RESTS, PLACE):
    decl, dec = DECLS[dk]
    body = dec + (RECT + CLAMPS[ck] if pk == 'rect_first' else CLAMPS[ck] + RECT)
    src = PRE + decl + '\n' + body + RESTS[rk] + TAIL
    p = OUT / f'{dk}_{ck}_{rk}_{pk}.c'
    p.write_text(src)
    tasks.append(p)


def score(p):
    try:
        r = dict(screen.measure('func_8001DE5C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:50])


with cf.ThreadPoolExecutor(8) as pool:
    for row in sorted(pool.map(score, tasks))[:12]:
        print(row)
