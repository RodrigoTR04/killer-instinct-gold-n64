#!/usr/bin/env python3
"""T-169 DE5C: D47C's winning lever -- drop the cached intermediates and read
the byte-pair fields inline, so IDO needs fewer stack slots (target frame 0x68,
7 user spills; draft 0x78, 11 spills)."""
import concurrent.futures as cf
import importlib.util
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/de5cg2'
OUT.mkdir(exist_ok=True)

PRE = '''extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

'''

# helper macros as source text (honest: they expand to real expressions)
def P(b, i):
    return f'(({b}[{i}] << 8) + {b}[{i + 1}])'


V = {}

# A: no locals at all except what the sprite store needs; recompute freely
V['a_inline_all'] = f'''void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {{
    s32 mx, my, rx, ry, spanX, spanY;
    s32 areaW, areaH;
    T022Sprite *sprite;
    if (arg1 != 0) {{
        if ({P('arg1', 1)} < 0x8000) {{
            if ({P('arg0', 1)} < {P('arg1', 1)}) {{
                mx = {P('arg1', 1)};
            }} else {{
                mx = {P('arg0', 1)};
            }}
        }} else if ({P('arg0', 1)} < {P('arg1', 1)} - 0x10000) {{
            mx = {P('arg1', 1)} - 0x10000;
        }} else {{
            mx = {P('arg0', 1)};
        }}
        if ({P('arg1', 3)} < 0x8000) {{
            if ({P('arg0', 3)} < {P('arg1', 3)}) {{
                my = {P('arg1', 3)};
            }} else {{
                my = {P('arg0', 3)};
            }}
        }} else if ({P('arg0', 3)} < {P('arg1', 3)} - 0x10000) {{
            my = {P('arg1', 3)} - 0x10000;
        }} else {{
            my = {P('arg0', 3)};
        }}
    }} else {{
        mx = {P('arg0', 1)};
        my = {P('arg0', 3)};
    }}
    do {{
        rx = {P('arg0', 5)} + (mx - {P('arg0', 1)});
    }} while (0);
    ry = {P('arg0', 7)} + (my - {P('arg0', 3)});
    if (arg1 != 0) {{
        spanX = {P('arg1', 5)} + (mx - {P('arg1', 1)});
        spanY = {P('arg1', 7)} + (my - {P('arg1', 3)});
        if (spanX >= rx) {{
            rx = spanX;
        }}
        if (spanY >= ry) {{
            ry = spanY;
        }}
    }}
    areaW = (rx + 9) & 0xFFF8;
    areaH = (ry + 1) & 0xFFFE;
    if ((s32) (areaW * areaH) < 0x8891) {{
        sprite = &D_8004CED0[D_8004EA78];
        sprite->halfWidth = mx;
        sprite->halfHeight = my;
        sprite->width = rx;
        sprite->height = ry;
        sprite->width2 = areaW;
        sprite->height2 = areaH;
        ((s16 *) sprite)[10] = rx;
        ((s16 *) sprite)[11] = ry;
        ((s16 *) sprite)[12] = areaH;
        ((s16 *) sprite)[13] = arg2;
        func_80031050(arg0, mx - {P('arg0', 1)}, ((ry - {P('arg0', 7)}) << 16) | (my - {P('arg0', 3)}));
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {{
            func_80031DD0(arg1, mx - {P('arg1', 1)}, ((ry - {P('arg1', 7)}) << 16) | (my - {P('arg1', 3)}));
        }}
    }}
}}
'''

# B: same but signed-pair extraction helper spelled through a local per axis
V['b_mx_my_only'] = f'''void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {{
    s32 x, y, x2, y2, mx, my, rx, ry, areaW, areaH;
    T022Sprite *sprite;
    x = {P('arg0', 1)}; y = {P('arg0', 3)};
    x2 = {P('arg0', 5)}; y2 = {P('arg0', 7)};
    if (x >= 0x8000) x -= 0x10000;
    if (y >= 0x8000) y -= 0x10000;
    if (x2 >= 0x8000) x2 -= 0x10000;
    if (y2 >= 0x8000) y2 -= 0x10000;
    mx = x; my = y;
    if (arg1 != 0) {{
        s32 bx, by, bx2, by2;
        bx = {P('arg1', 1)}; by = {P('arg1', 3)};
        bx2 = {P('arg1', 5)}; by2 = {P('arg1', 7)};
        if (bx >= 0x8000) bx -= 0x10000;
        if (by >= 0x8000) by -= 0x10000;
        if (bx2 >= 0x8000) bx2 -= 0x10000;
        if (by2 >= 0x8000) by2 -= 0x10000;
        if (bx >= x) mx = bx;
        if (by >= y) my = by;
        do {{ rx = x2 + (mx - x); }} while (0);
        ry = y2 + (my - y);
        if (bx2 + (mx - bx) >= rx) rx = bx2 + (mx - bx);
        if (by2 + (my - by) >= ry) ry = by2 + (my - by);
    }} else {{
        rx = x2; ry = y2;
    }}
    areaW = (rx + 9) & 0xFFF8;
    areaH = (ry + 1) & 0xFFFE;
    if ((s32) (areaW * areaH) >= 0x8891) return;
    sprite = &D_8004CED0[D_8004EA78];
    sprite->halfWidth = mx;
    sprite->halfHeight = my;
    sprite->width = rx;
    sprite->height = ry;
    sprite->width2 = areaW;
    sprite->height2 = areaH;
    ((s16 *) sprite)[10] = rx;
    ((s16 *) sprite)[11] = ry;
    ((s16 *) sprite)[12] = areaH;
    ((s16 *) sprite)[13] = arg2;
    func_80031050(arg0, mx - x, ((ry - y2) << 16) | (my - y));
    D_8004F2C8 = D_8004F2CC;
    if (arg1 != 0) {{
        func_80031DD0(arg1, mx - ({P('arg1', 1)}), ((ry - ({P('arg1', 7)})) << 16) | (my - ({P('arg1', 3)})));
    }}
}}
'''


def score(p):
    try:
        res = dict(screen.measure('func_8001DE5C', p))
        return (res['words'], res['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:70])


paths = []
for n, body in V.items():
    p = OUT / f'{n}.c'
    p.write_text(PRE + body)
    paths.append(p)
with cf.ThreadPoolExecutor(4) as pool:
    for row in sorted(pool.map(score, paths)):
        print(row)
