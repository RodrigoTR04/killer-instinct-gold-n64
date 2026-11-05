extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

typedef struct {
    s32 by;
    s32 by2;
    s32 bx2;
    s32 bx;
} T169Rect;

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 x = (arg0[1] << 8) + arg0[0];
    s32 y = (arg0[3] << 8) + arg0[2];
    s32 x2 = (arg0[5] << 8) + arg0[4];
    s32 y2 = (arg0[7] << 8) + arg0[6];
    T169Rect r;
    s32 mx;
    s32 my;
    s32 rx;
    s32 ry;
    T022Sprite *sprite;

    if (arg1 != 0) {
        r.bx = (arg1[1] << 8) + arg1[0];
        r.by = (arg1[3] << 8) + arg1[2];
        r.bx2 = (arg1[5] << 8) + arg1[4];
        r.by2 = (arg1[7] << 8) + arg1[6];
    }
    if (x >= 0x8000) {
        x -= 0x10000;
    }
    if (r.bx >= 0x8000) {
        r.bx -= 0x10000;
    }
    r.bx -= 1;
    if (y >= 0x8000) {
        y -= 0x10000;
    }
    if (r.by >= 0x8000) {
        r.by -= 0x10000;
    }
    mx = x;
    my = y;
    if (arg1 != 0) {
        if (r.bx >= x) {
            mx = r.bx;
        }
        if (r.by >= y) {
            my = r.by;
        }
    }
    x2 += mx - x;
    y2 += my - y;
    if (arg1 != 0) {
        r.bx2 += mx - r.bx;
        r.by2 += my - r.by;
    }
    rx = x2;
    ry = y2;
    if (arg1 != 0) {
        if (r.bx2 >= x2) {
            rx = r.bx2;
        }
        if (r.by2 >= y2) {
            ry = r.by2;
        }
    }
    if ((s32)(((rx + 9) & 0xFFF8) * ((ry + 1) & 0xFFFE)) < 0x8891) {
        sprite = &D_8004CED0[D_8004EA78];
        sprite->halfWidth = mx;
        sprite->halfHeight = my;
        sprite->width = x2;
        sprite->height = ry;
        sprite->width2 = (rx + 9) & 0xFFF8;
        ((s16 *)sprite)[10] = rx;
        ((s16 *)sprite)[11] = ry;
        ((s16 *)sprite)[13] = arg2;
        func_80031050(arg0, mx - x, ((ry - y2) << 16) | (my - y));
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, mx - r.bx, ((ry - r.by2) << 16) | (my - r.by));
        }
    }
}
