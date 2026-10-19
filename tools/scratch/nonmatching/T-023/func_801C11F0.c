/* DRAFT. Remaining diff: Digit buffer/float-bit union stack layout and call scheduling differ. */
extern s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);
extern u8 D_8004A407;
extern s8 D_80292CC4;
extern f32 D_80292CF0;
extern s32 D_802956F4, D_802CA068, D_802D3818[];
void func_801C11F0(s32 list, s32 unused, s32 side, s32 player) {
    s8 digit[2];
    s32 phase, shade;
    union { f32 f; s32 i; } x;
    if (D_8004A407) player = 0;
    phase = D_802D3818[player];
    shade = (phase % 100) * 255 / 100;
    if (shade >= 65 && shade < 192) shade = 63;
    if (shade >= 193) shade = 255 - shade;
    shade *= 4;
    x.f = side * 218;
    digit[0] = phase / 100 + '0'; digit[1] = 0;
    D_802956F4 += func_801BE540(list, (D_802956F4 << 6) + D_802CA068, (s32)&D_80292CC4, x.i, 75.0f, -500.0f, 255, 255, 255, 255, 0.75f);
    shade &= 255;
    D_802956F4 += func_801BE540(list, (D_802956F4 << 6) + D_802CA068, (s32)digit, x.i, 0.0f, -500.0f, shade, shade, shade, 255, D_80292CF0);
}
