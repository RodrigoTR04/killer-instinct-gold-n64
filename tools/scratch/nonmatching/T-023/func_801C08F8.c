/* DRAFT. Remaining diff: 64-bit score decoding, text buffers, float arguments and rendering sequencing differ. */
extern s32 func_801BD640(), func_801BDA6C(), func_801BDF94(), func_801BE660();
extern s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);
extern void func_801C0800();
extern f32 sinf(f32);
extern s8 *D_80282DD0[];
extern s8 ***D_8028326C[];
extern s8 D_80292CAC[], D_80292CBC[], D_80292CC0[];
extern f32 D_80292CD0;
extern f64 D_80292CD8, D_80292CE0, D_80292CE8;
extern s32 D_80282EF0, D_802956F4, D_802CA068, D_802D37D8[], D_802D37E0[], D_802D37F0[], D_802D3824;
void func_801C08F8(s32 list, s32 unused, u8 character, s32 side, u64 packed, s32 player) {
    s8 digit[2], name[5];
    s32 shade, y, i, radix, minimumA, minimumB, pair, quotient, remainder, phase, x;
    u64 work;
    union { f32 f; s32 i; } pos;
    minimumA = minimumB = 20; y = 262;
    D_802956F4 += func_801BE660(list, (D_802956F4 << 6) + D_802CA068, **D_8028326C[character], (f32)(side * 180), 220.0f, -400.0f, D_80292CD0);
    digit[0] = (D_802D3824 >> 8) + '0'; digit[1] = 0;
    if (D_802D3824 < 0) digit[0] = ' ';
    shade = D_802D3824 & 255;
    if (shade >= 128) shade = 255 - shade;
    shade = (shade * 2) & 255;
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802CA068, digit, (f32)(side * 300 - 30), -220.0f, -1000.0f, shade, shade, shade, 255, 1.0f);
    radix = 1;
    for (i = 0; i != 10; i++) {
        pair = (packed / (radix * 1331)) % 36;
        quotient = pair / 6; remainder = pair % 6; radix *= 36;
        if (quotient && quotient < minimumB) minimumB = quotient;
        if (remainder && remainder < minimumA) minimumA = remainder;
    }
    work = packed;
    for (i = 1; i != 6; i++) {
        if ((i < 4 && work % 11) || (i == 4 && minimumA < 20) || (i == 5 && minimumB < 20)) {
            shade = 255;
            if ((i == 4 && minimumA == 1) || (i == 5 && minimumB == 1) || (i < 4 && work % 11 == 1)) shade = sinf(((i * 72) + D_80282EF0) * D_80292CD8) * 127.0f + 128.0f;
            pos.f = side * 300;
            D_802956F4 += func_801BE540(list, (D_802956F4 << 6) + D_802CA068, (s32)D_80282DD0[i], pos.i, (f32)y, -1000.0f, 255, shade, 0, 255, 0.75f);
            y -= 37;
        }
        work /= 11;
    }
    phase = D_80282EF0 + 20; if (phase >= 361) phase -= 360; D_80282EF0 = phase;
    x = side * 350;
    func_801C0800(list, (f32)((D_802D37D8[player] * D_80292CE0 * 8.0 + x * 0.75) - 160.0), (f32)(37.5 - D_802D37E0[player] * D_80292CE8 * 8.0), -800.0f, 255, 0, 0, (u32)(sinf(phase * D_80292CD8 * 2.0) * 60.0f + 60.0f));
    y = 50;
    for (i = 0; i != 30; i += 6) {
        D_80292CAC[1] = i + 'A'; D_80292CAC[3] = i + 'B'; D_80292CAC[5] = i + 'C';
        D_80292CAC[7] = i + 'D'; D_80292CAC[9] = i + 'E'; D_80292CAC[11] = i + 'F';
        D_802956F4 += func_801BD640(list, (D_802956F4 << 6) + D_802CA068, D_80292CAC, (f32)(x - 227), (f32)y, -800.0f, 255, 255, 0, 255);
        y -= 50;
    }
    x = side * 650;
    D_802956F4 += func_801BD640(list, (D_802956F4 << 6) + D_802CA068, D_80292CBC, (f32)(x - 10), (f32)(y - 80), -2000.0f, 255, 255, 0, 255);
    D_802956F4 += func_801BD640(list, (D_802956F4 << 6) + D_802CA068, D_80292CC0, (f32)(x + 320), (f32)(y - 80), -2000.0f, 255, 255, 0, 255);
    name[0] = 'j'; *(u32 *)(name + 1) = D_802D37F0[player];
    D_802956F4 += func_801BDF94(list, (D_802956F4 << 6) + D_802CA068, name, (f32)(side * 180 - 106), -220.0f, -400.0f, 0, 1.0f, 0.0f);
}
