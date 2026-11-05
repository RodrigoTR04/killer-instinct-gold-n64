/* Matched. Official screen.measure 88 (declarations) -> 0 (full TU, 504 B). */
extern u8 D_80291808[];
typedef struct { u32 w0, w1; } Cmd;

void func_801C3E40(Cmd **arg0) {
    s32 count, index;
    s8 dx, dy;
    D_802D38F4 = D_802D38F0;
    D_802D38F0 = 0.1f;
    if (D_802D38F8 != 0) {
        { Cmd *dl = (*arg0)++; dl->w0 = 0x01060040; dl->w1 = (u32)D_802D3900; }
        { Cmd *dl = (*arg0)++; dl->w0 = 0x06000000; dl->w1 = (u32)D_80291808; }
        count = D_802D38F8;
        index = D_802D38FC;
        if (count > 0) {
            do {
                index &= 255;
                { Cmd *dl = (*arg0)++; count--; dl->w0 = 0x04200030; dl->w1 = (u32)&D_802D3940[index * 3]; }
                { Cmd *dl = (*arg0)++; dl->w0 = 0xBF000000; dl->w1 = 0xA14; }
                D_802D3940[index * 3].a -= 32;
                if (D_802D3940[index * 3].a < 32) {
                    D_802D3940[index * 3].a = 32;
                    D_802D38F8--;
                    D_802D38FC = (D_802D38FC + 1) & 255;
                } else {
                    dx = (s8)D_802D3940[index * 3 + 1].r;
                    D_802D3940[index * 3].x += dx;
                    D_802D3940[index * 3 + 1].x += dx;
                    D_802D3940[index * 3 + 2].x += dx;
                    dy = (s8)D_802D3940[index * 3 + 1].g;
                    D_802D3940[index * 3].y += dy;
                    D_802D3940[index * 3 + 1].y += dy;
                    D_802D3940[index * 3 + 2].y += dy;
                }
                index++;
            } while (count > 0);
        }
    }
}
