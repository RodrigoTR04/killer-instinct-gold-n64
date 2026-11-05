extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 x, y, x2, y2, mx, my, rx, ry, areaW, areaH;
    T022Sprite *sprite;
    x = ((arg0[1] << 8) + arg0[2]); y = ((arg0[3] << 8) + arg0[4]);
    x2 = ((arg0[5] << 8) + arg0[6]); y2 = ((arg0[7] << 8) + arg0[8]);
    if (x >= 0x8000) x -= 0x10000;
    if (y >= 0x8000) y -= 0x10000;
    if (x2 >= 0x8000) x2 -= 0x10000;
    if (y2 >= 0x8000) y2 -= 0x10000;
    mx = x; my = y;
    if (arg1 != 0) {
        s32 bx, by, bx2, by2;
        bx = ((arg1[1] << 8) + arg1[2]); by = ((arg1[3] << 8) + arg1[4]);
        bx2 = ((arg1[5] << 8) + arg1[6]); by2 = ((arg1[7] << 8) + arg1[8]);
        if (bx >= 0x8000) bx -= 0x10000;
        if (by >= 0x8000) by -= 0x10000;
        if (bx2 >= 0x8000) bx2 -= 0x10000;
        if (by2 >= 0x8000) by2 -= 0x10000;
        if (bx >= x) mx = bx;
        if (by >= y) my = by;
        do { rx = x2 + (mx - x); } while (0);
        ry = y2 + (my - y);
        if (bx2 + (mx - bx) >= rx) rx = bx2 + (mx - bx);
        if (by2 + (my - by) >= ry) ry = by2 + (my - by);
    } else {
        rx = x2; ry = y2;
    }
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
    if (arg1 != 0) {
        func_80031DD0(arg1, mx - (((arg1[1] << 8) + arg1[2])), ((ry - (((arg1[7] << 8) + arg1[8]))) << 16) | (my - (((arg1[3] << 8) + arg1[4]))));
    }
}
