/* T-169: reconcile with the owning TU: D_80285574 is the TU's `s32` (a menu
   table base), D_802C9F70 is the FrontendRenderContext, and the text helpers are
   the frontend.h prototypes. */
extern s32 D_80285574;
extern s32 D_80285578;
extern FrontendRenderContext D_802C9F70;
extern s32 D_802956F4;
extern s32 D_802D3830;
extern s32 D_802D3834;
extern f32 D_802937B8;
extern f32 D_802937BC;

s32 func_801C317C(FrontendGfxWords **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    u8 **entries;
    u8 **slot;
    u8 *text;
    s32 index;
    s32 offset;
    s32 fade;
    s32 y;
    f32 z;

    result = 0;
    if (arg3 < 0) {
        D_80285578 = 0;
        D_802D3830 = 0x1F4;
        D_802D3834 = 0;
    }
    D_802956F4 += func_801BDF94(arg0, (u8 *)((D_802956F4 << 6) + (s32)D_802C9F70.matrices),
                                (u8 *)**(u8 ***)&D_80285574, (f32)(((arg1 * -2) / 3) - 0x5A), 200.0f,
                                (f32)(arg2 - 0x3E8), 1, 1.0f, ((f32)(arg3 + 0x1E) / 30.0f) * 360.0f);
    index = D_80285578;
    entries = (u8 **)*(u8 **)&D_80285574 + index;
    text = *entries;
    if ((text != 0) && (arg3 > 0)) {
        s32 first = index == 0;
        s32 column = first * 4;
        y = 0xB4;
        if (D_802D3830 < arg3) {
            D_802D3830 += 0x1F4;
            D_802D3834 = -1;
        }
        if ((D_802D3834 < 0x100) && (D_802D3834 >= 0)) {
            fade = D_802D3834 + 0x10;
            if (fade >= 0x100) {
                fade = 0xFF;
            }
        } else {
            fade = D_802D3834 - 0x10;
            if (fade < -0xFF) {
                D_80285578 = index + 1;
                index = index + 1;
                fade = 0;
                text = *((u8 **)*(u8 **)&D_80285574 + index);
            }
        }
        if ((text == 0) || ((fade < 0) && (((u8 **)*(u8 **)&D_80285574)[index + 1] == 0))) {
            if (text == 0) {
                D_80285578 = index - 1;
                text = ((u8 **)*(u8 **)&D_80285574)[index - 1];
            }
            if (fade == 0) {
                fade = -0xFF;
            }
            result = 1;
        }
        slot = (u8 **)((u8 *)text + column);
        z = (f32)(arg2 - 0x5DC);
        D_802D3834 = fade;
        if (*slot != 0) {
            do {
                s32 produced;
                produced = func_801BD640(arg0, (u8 *)((D_802956F4 << 6) + (s32)D_802C9F70.matrices),
                                         *slot, D_802937BC, (f32)(y - 5), z, 0, 0, 0,
                                         (s32)(D_802D3834 & 0xFF) >> 1);
                D_802956F4 = produced;
                D_802956F4 += func_801BD640(arg0, (u8 *)((produced << 6) + (s32)D_802C9F70.matrices),
                                            *((u8 **)((u8 *)((u8 **)*(u8 **)&D_80285574)[D_80285578] + column)),
                                            D_802937B8, (f32)y, z, 0xFF, 0xFF, 0xFF, D_802D3834);
                column += 4;
                y -= 0x37;
                slot = (u8 **)((u8 *)((u8 **)*(u8 **)&D_80285574)[D_80285578] + column);
            } while (*slot != 0);
        }
    }
    return result;
}
