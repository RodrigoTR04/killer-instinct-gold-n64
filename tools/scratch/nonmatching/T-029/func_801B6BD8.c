/* DRAFT. Remaining diff: Text helper float argument typing, saved count register, stack slots and scheduling differ. */
extern s32 func_801BE540(void *, void *, void *, s32, f32, f32, s32, s32, s32, s32, f32);
extern u8 D_802C8D0A[];
extern u8 D_802C8D0B;
extern s16 D_801F35AC;
extern u8 D_80292A44[], D_80292A4C[];
extern void *D_801F3570[], *D_801F3540[];
s32 func_801B6BD8(void *arg0, u8 *arg1) {
    s32 count;
    s32 offset;
    s32 first;
    s32 second;
    s32 shade;
    count = 0;
    offset = 0;
    if (D_802C8D0A[0] == 3 && D_802C8D0A[1] == 3) offset = 9;
    if (D_802C8D0A[0] != 0) {
        shade = (255 - D_801F35AC) & 255;
        first = func_801BE540(arg0, arg1, D_80292A44, 0, 170.0f, -1600.0f, 0, shade, shade, 255, 1.0f);
        shade = (255 - D_801F35AC) & 255;
        second = func_801BE540(arg0, arg1 + (first << 6), D_801F3570[D_802C8D0A[0] + offset], 0, 130.0f, -1600.0f, shade, shade, shade, 255, 1.0f);
        count = first + second;
    }
    if (D_802C8D0A[1] != 0) {
        shade = (255 - D_801F35AC) & 255;
        first = count + func_801BE540(arg0, arg1 + (count << 6), D_80292A4C, 0, 80.0f, -1600.0f, 0, shade, shade, 255, 1.0f);
        shade = (255 - D_801F35AC) & 255;
        count = first + func_801BE540(arg0, arg1 + (first << 6), D_801F3540[D_802C8D0B + offset], 0, 40.0f, -1600.0f, shade, shade, shade, 255, 1.0f);
    }
    return count;
}
