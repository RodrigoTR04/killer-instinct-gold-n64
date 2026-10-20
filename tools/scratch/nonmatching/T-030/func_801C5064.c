/* T-071 DRAFT: 4 differing words; layout-sensitive scheduling. */
typedef struct { u8 pad[0xF8]; u8 *matrices; } T030Render5064;
extern s32 func_801BE540(s32, void *, s32, f32, f32, f32, s32, s32, s32, u8, f32);
extern f32 D_8029488C, D_80294890;
extern s32 D_802956F4;
extern u8 D_802D399F;
extern s32 *D_802D39AC;

void func_801C5064(s32 arg0, T030Render5064 *arg1, u8 arg2, s32 arg3) {
    f32 scale;
    f32 origin;
    f32 depth;
    s32 count;
    s32 i, offset;
    s32 used;
    scale = D_8029488C;
    origin = -540.0f;
    if (arg3 != 0) {
        scale = 1.0f;
        origin = -D_802D399F * 20;
    }
    count = D_802D399F;
    i = 0;
    offset = 0;
    if (count > 0) {
        depth = D_80294890; do {
            used = func_801BE540(arg0, arg1->matrices + (D_802956F4 << 6), *(s32 *)((u8 *)D_802D39AC + offset), 0.0f, ((count-i)*67)*scale + origin, depth, 255,255,255,arg2,scale);
            i++;
            offset += 4;
            count = D_802D399F;
            D_802956F4 += used;
        }
        while (i < count);
    }
}
