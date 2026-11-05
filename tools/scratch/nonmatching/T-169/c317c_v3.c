extern s32 D_80285574;
extern s32 D_80285578;
extern FrontendRenderContext D_802C9F70;
extern s32 D_802956F4;
extern s32 D_802D3830;
extern s32 D_802D3834;
extern f32 D_802937B8;
extern f32 D_802937BC;

s32 func_801C317C(FrontendGfxWords **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 **list;
    u8 **entry;
    u8 *text;
    s32 index;
    s32 column;
    s32 y;
    f32 z;
    s32 result;
    u8 *matrices;
    u8 *palette;

    result = 0;
    if (arg3 < 0) {
        D_80285578 = 0;
        D_802D3830 = 0x1F4;
        D_802D3834 = 0;
    }
    matrices = D_802C9F70.matrices;
    palette = *(u8 **)&D_80285574;
    D_802956F4 += func_801BDF94(arg0, (u8 *)((D_802956F4 << 6) + (s32)matrices),
                                (u8 *)((u8 **)palette)[0],
                                (f32)(((arg1 * -2) / 3) - 0x5A), 200.0f, (f32)(arg2 - 0x3E8), 1, 1.0f,
                                ((f32)(arg3 + 0x1E) / 30.0f) * 360.0f);
    index = D_80285578;
    list = (u8 **)*(u8 **)&D_80285574;
    entry = &list[index];
    text = *entry;
    if ((text != 0) && (arg3 > 0)) {
        column = (index == 0) * 4;
        y = 0xB4;
        if (D_802D3830 < arg3) {
            D_802D3830 += 0x1F4;
            D_802D3834 = -1;
        }
        if ((D_802D3834 < 0x100) && (D_802D3834 >= 0)) {
            D_802D3834 += 0x10;
            if (D_802D3834 >= 0x100) {
                D_802D3834 = 0xFF;
            }
        } else {
            D_802D3834 -= 0x10;
            if (D_802D3834 < -0xFF) {
                D_80285578 = index + 1;
                index = index + 1;
                entry = &list[index];
                text = *entry;
                D_802D3834 = 0;
            }
        }
        if ((text == 0) || ((D_802D3834 < 0) && (entry[1] == 0))) {
            if (text == 0) {
                D_80285578 = index - 1;
                text = list[index - 1];
            }
            if (D_802D3834 == 0) {
                D_802D3834 = -0xFF;
            }
            result = 1;
        }
        text += column;
        z = (f32)(arg2 - 0x5DC);
        if (*(u8 **)text != 0) {
            do {
                s32 produced;
                produced = func_801BD640(arg0, (u8 *)((D_802956F4 << 6) + (s32)matrices),
                                         *(u8 **)text, D_802937BC, (f32)(y - 5), z, 0, 0, 0,
                                         (s32)(D_802D3834 & 0xFF) >> 1);
                D_802956F4 = produced;
                D_802956F4 += func_801BD640(arg0, (u8 *)((produced << 6) + (s32)matrices),
                                            *((u8 **)((u8 *)list[D_80285578] + column)),
                                            D_802937B8, (f32)y, z, 0xFF, 0xFF, 0xFF, D_802D3834);
                column += 4;
                y -= 0x37;
                text = (u8 *)list[D_80285578] + column;
            } while (*(u8 **)text != 0);
        }
    }
    return result;
}
