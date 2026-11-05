import importlib.util, itertools, concurrent.futures, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
specc = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(specc); specc.loader.exec_module(screen)

HDR = '''extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

'''
READFAR = '''    if (arg1 != 0) {
        bx = (arg1[1] << 8) + arg1[0];
        by = (arg1[3] << 8) + arg1[2];
        bx2 = (arg1[5] << 8) + arg1[4];
        by2 = (arg1[7] << 8) + arg1[6];
    }
'''
# which far values are kept as separate locals vs recomputed at use
DECL = '''    s32 x = (arg0[1] << 8) + arg0[0];
    s32 y = (arg0[3] << 8) + arg0[2];
    s32 x2 = (arg0[5] << 8) + arg0[4];
    s32 y2 = (arg0[7] << 8) + arg0[6];
'''
SPANMODE = {
 # keep spanX and spanY as named locals (4 extra live across the writer calls)
 'spans': '''    s32 spanX;
    s32 spanY;
''',
 'nospans': '',
}
CMP = {
 'spans': '''    if (arg1 != 0) {
        if (spanX >= x2) {
            rx = spanX;
        }
        if (spanY >= y2) {
            ry = spanY;
        }
    }
''',
 'nospans': '''    if (arg1 != 0) {
        if (bx2 + dx >= x2) {
            rx = bx2 + dx;
        }
        if (by2 + dyb >= y2) {
            ry = by2 + dyb;
        }
    }
''',
}
LAST = {'spans': '((ry - spanY) << 16) | dyb', 'nospans': '((ry - y2) << 16) | dyb'}

BODY = '''    s32 mx;
    s32 my;
    s32 dx;
    s32 dx0;
    s32 dy;
    s32 dyb;
    s32 rx;
    s32 ry;
    u32 areaW;
    u32 areaH;
    T022Sprite *sprite;

''' + READFAR + '''    if (x >= 0x8000) {
        x -= 0x10000;
    }
    if (bx >= 0x8000) {
        bx -= 0x10000;
    }
    bx -= 1;
    if (y >= 0x8000) {
        y -= 0x10000;
    }
    if (by >= 0x8000) {
        by -= 0x10000;
    }
    mx = x;
    my = y;
    if (arg1 != 0) {
        if (bx >= x) {
            mx = bx;
        }
        if (by >= y) {
            my = by;
        }
    }
    dx = mx - bx;
    dx0 = mx - x;
    dy = my - y;
    dyb = my - by;
    x2 += dx0;
    y2 += dy;
    rx = x2;
    ry = y2;
%CMP%    areaW = (rx + 9) & 0xFFF8;
    areaH = (ry + 1) & 0xFFFE;
    if ((s32)(areaW * areaH) < 0x8891) {
        sprite = &D_8004CED0[D_8004EA78];
        sprite->halfWidth = mx;
        sprite->halfHeight = my;
        sprite->width = x2;
        sprite->height = ry;
        sprite->width2 = areaW;
        ((s16 *)sprite)[10] = rx;
        ((s16 *)sprite)[11] = ry;
        ((s16 *)sprite)[13] = arg2;
        func_80031050(arg0, dx0, ((ry - y2) << 16) | dy);
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, dx, %LAST%);
        }
    }
}
'''
out = Path('tools/scratch/nonmatching/T-169/srch'); out.mkdir(exist_ok=True)

def build(mode):
    head = HDR + 'void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {\n' + DECL
    if mode == 'spans':
        head += '    s32 bx;\n    s32 by;\n    s32 bx2;\n    s32 by2;\n'
    else:
        head += '    s32 bx;\n    s32 by;\n    s32 bx2;\n    s32 by2;\n'
    head += SPANMODE[mode]
    b = BODY.replace('%CMP%', CMP[mode]).replace('%LAST%', LAST[mode])
    if mode == 'spans':
        b = b.replace('    ry = y2;\n', '    spanX = bx2 + dx;\n    spanY = by2 + dyb;\n    ry = y2;\n')
    return head + b

def info(path):
    r = dict(screen.measure('func_8001DE5C', path))
    source, tu = cm.build_source('func_8001DE5C', path, False)
    with tempfile.TemporaryDirectory() as td:
        o = cm.compile_source(source, Path(td)/'c.c')
        pairs = cm.draft_raw(o, 'func_8001DE5C')
    mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    fr = next((-int(m.split(',')[-1]) for m in mine if m.startswith('addiu sp,sp,-')), 0)
    return r['words'], r['compiled'], fr, len(mine)

for mode in SPANMODE:
    p = out/f'{mode}.c'
    p.write_text(build(mode))
    print(mode, info(p))
