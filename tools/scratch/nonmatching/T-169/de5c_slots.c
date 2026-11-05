extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 x = (arg0[1] << 8) + arg0[0];
    s32 y = (arg0[3] << 8) + arg0[2];
    s32 bx;
    s32 by;
    s32 bx2;
    s32 by2;
    s32 dx;
    s32 dx0;
    s32 ry;
    T022Sprite *sprite;

    if (arg1 != 0) {
        bx = (arg1[1] << 8) + arg1[0];
        by = (arg1[3] << 8) + arg1[2];
        bx2 = (arg1[5] << 8) + arg1[4];
        by2 = (arg1[7] << 8) + arg1[6];
    }
    if (x >= 0x8000) {
        x -= 0x10000;
    }
    if (bx >= 0x8000) {
        bx -= 0x10000;
    }
    bx -= 1;
    if (y >= 0x8000) {
        do {
            y -= 0x10000;
        } while (0);
    }
    if (by >= 0x8000) {
        by -= 0x10000;
    }
    if (arg1 != 0) {
        if (bx >= x) {
            x = bx;
        }
        if (by >= y) {
            y = by;
        }
    }
    dx = x - bx;
    dx0 = x - ((arg0[1] << 8) + arg0[0]);
    ry = ((arg0[7] << 8) + arg0[6]) + (y - ((arg0[3] << 8) + arg0[2]));
    if (arg1 != 0) {
        bx2 += dx;
        by2 += y - by;
        if (bx2 >= ((arg0[5] << 8) + arg0[4]) + dx0) {
            }
        if (by2 >= ry) {
            ry = by2;
        }
    }
    if ((s32)((((bx2 >= ((arg0[5] << 8) + arg0[4]) + dx0) ? bx2 : ((arg0[5] << 8) + arg0[4]) + dx0) + 9) & 0xFFF8) *
        ((ry + 1) & 0xFFFE) < 0x8891) {
        sprite = &D_8004CED0[D_8004EA78];
        sprite->halfWidth = x;
        sprite->halfHeight = y;
        sprite->width = ((arg0[5] << 8) + arg0[4]) + dx0;
        sprite->height = ry;
        sprite->width2 = ((((bx2 >= ((arg0[5] << 8) + arg0[4]) + dx0) ? bx2 : ((arg0[5] << 8) + arg0[4]) + dx0) + 9) & 0xFFF8);
        ((s16 *)sprite)[10] = (bx2 >= ((arg0[5] << 8) + arg0[4]) + dx0) ? bx2 : ((arg0[5] << 8) + arg0[4]) + dx0;
        ((s16 *)sprite)[11] = ry;
        ((s16 *)sprite)[13] = arg2;
        func_80031050(arg0, dx0, ((ry - ((arg0[7] << 8) + arg0[6]) - (y - ((arg0[3] << 8) + arg0[2]))) << 16) | (y - ((arg0[3] << 8) + arg0[2])));
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, dx, ((ry - by2) << 16) | (y - by));
        }
    }
}
