extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 mx, my, rx, ry, spanX, spanY;
    s32 areaW, areaH;
    T022Sprite *sprite;
    if (arg1 != 0) {
        if (((arg1[1] << 8) + arg1[2]) < 0x8000) {
            if (((arg0[1] << 8) + arg0[2]) < ((arg1[1] << 8) + arg1[2])) {
                mx = ((arg1[1] << 8) + arg1[2]);
            } else {
                mx = ((arg0[1] << 8) + arg0[2]);
            }
        } else if (((arg0[1] << 8) + arg0[2]) < ((arg1[1] << 8) + arg1[2]) - 0x10000) {
            mx = ((arg1[1] << 8) + arg1[2]) - 0x10000;
        } else {
            mx = ((arg0[1] << 8) + arg0[2]);
        }
        if (((arg1[3] << 8) + arg1[4]) < 0x8000) {
            if (((arg0[3] << 8) + arg0[4]) < ((arg1[3] << 8) + arg1[4])) {
                my = ((arg1[3] << 8) + arg1[4]);
            } else {
                my = ((arg0[3] << 8) + arg0[4]);
            }
        } else if (((arg0[3] << 8) + arg0[4]) < ((arg1[3] << 8) + arg1[4]) - 0x10000) {
            my = ((arg1[3] << 8) + arg1[4]) - 0x10000;
        } else {
            my = ((arg0[3] << 8) + arg0[4]);
        }
    } else {
        mx = ((arg0[1] << 8) + arg0[2]);
        my = ((arg0[3] << 8) + arg0[4]);
    }
    do {
        rx = ((arg0[5] << 8) + arg0[6]) + (mx - ((arg0[1] << 8) + arg0[2]));
    } while (0);
    ry = ((arg0[7] << 8) + arg0[8]) + (my - ((arg0[3] << 8) + arg0[4]));
    if (arg1 != 0) {
        spanX = ((arg1[5] << 8) + arg1[6]) + (mx - ((arg1[1] << 8) + arg1[2]));
        spanY = ((arg1[7] << 8) + arg1[8]) + (my - ((arg1[3] << 8) + arg1[4]));
        if (spanX >= rx) {
            rx = spanX;
        }
        if (spanY >= ry) {
            ry = spanY;
        }
    }
    areaW = (rx + 9) & 0xFFF8;
    areaH = (ry + 1) & 0xFFFE;
    if ((s32) (areaW * areaH) < 0x8891) {
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
        func_80031050(arg0, mx - ((arg0[1] << 8) + arg0[2]), ((ry - ((arg0[7] << 8) + arg0[8])) << 16) | (my - ((arg0[3] << 8) + arg0[4])));
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, mx - ((arg1[1] << 8) + arg1[2]), ((ry - ((arg1[7] << 8) + arg1[8])) << 16) | (my - ((arg1[3] << 8) + arg1[4])));
        }
    }
}
