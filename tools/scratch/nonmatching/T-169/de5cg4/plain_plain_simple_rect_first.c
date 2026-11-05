extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 ax0, ay0, ax1, ay1;
    s32 bx0, by0, bx1, by1;
    s32 mx, my, maxX, maxY;
    T022Sprite *sprite;

    ax0 = (arg0[1] << 8) + arg0[0];
    ay0 = (arg0[3] << 8) + arg0[2];
    ax1 = (arg0[5] << 8) + arg0[4];
    ay1 = (arg0[7] << 8) + arg0[6];
    if (arg1 != 0) {
        bx0 = (arg1[1] << 8) + arg1[0];
        by0 = (arg1[3] << 8) + arg1[2];
        bx1 = (arg1[5] << 8) + arg1[4];
        by1 = (arg1[7] << 8) + arg1[6];
    }
    if (ax0 >= 0x8000) {
        ax0 -= 0x10000;
    }
    if (bx0 >= 0x8000) {
        bx0 -= 0x10000;
    }
    bx0 -= 1;
    if (ay0 >= 0x8000) {
        ay0 -= 0x10000;
    }
    if (by0 >= 0x8000) {
        by0 -= 0x10000;
    }
    mx = ax0;
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
