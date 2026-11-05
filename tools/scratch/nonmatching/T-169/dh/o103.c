/* T-162: little-endian rectangle bounds, explicit sign extension, typed sprite record. */
extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 x = (arg0[1] << 8) + arg0[0];
    s32 y = (arg0[3] << 8) + arg0[2];
    s32 x2 = (arg0[5] << 8) + arg0[4];
    s32 y2 = (arg0[7] << 8) + arg0[6];
    struct {
        s32 x;
        s32 y;
        s32 x2;
        s32 y2;
    } b;
    s32 dx0;
    u32 areaW;
    T022Sprite *sprite;
    s32 my;
    s32 dy;
    s32 ry;
    s32 rx;
    s32 spanX;
    u32 areaH;
    s32 dyb;
    s32 spanY;
    s32 mx;
    s32 dx;
    if (arg1 != 0) {
        b.x = (arg1[1] << 8) + arg1[0];
        b.y = (arg1[3] << 8) + arg1[2];
        b.x2 = (arg1[5] << 8) + arg1[4];
        b.y2 = (arg1[7] << 8) + arg1[6];
    }
    if (x >= 0x8000) {
        x -= 0x10000;
    }
    if (b.x >= 0x8000) {
        b.x -= 0x10000;
    }
    b.x -= 1;
    if (y >= 0x8000) {
        y -= 0x10000;
    }
    if (b.y >= 0x8000) {
        b.y -= 0x10000;
    }
    mx = x;
    my = y;
    if (arg1 != 0) {
        if (b.x >= x) {
            mx = b.x;
        }
        if (b.y >= y) {
            my = b.y;
        }
    }
    dx = mx - b.x;
    spanX = b.x2 + dx;
    dx0 = mx - x;
    dy = my - y;
    dyb = my - b.y;
    x2 += dx0;
    y2 += dy;
    spanY = b.y2 + dyb;
    rx = x2;
    ry = y2;
    if (arg1 != 0) {
        if (spanX >= x2) {
            rx = spanX;
        }
        if (spanY >= y2) {
            ry = spanY;
        }
    }
    areaW = (rx + 9) & 0xFFF8;
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
            func_80031DD0(arg1, dx, ((ry - spanY) << 16) | dyb);
        }
    }
}
