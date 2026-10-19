/* DRAFT. Remaining diff: Text/digit buffers, pointer traversal and rendering-call register allocation differ. */
extern s32 func_801BDA6C();
extern s32 func_801BE660();
extern void func_801BF678();
extern u8 D_80128308[], D_8012830A[], D_80128310[], D_80128328[], D_802C9F70[];
extern s32 D_80127C30[], D_802956F4;
extern s8 *D_80282DF0;
extern s8 ***D_8028326C[];
extern f32 D_80292CF4;
extern u8 D_802D37FD;
void func_801C1C34(s32 list, s32 unused, u8 *characters, s32 side) {
    s8 buffer[7];
    f32 x, valueX;
    s32 player, y, i, maxA, maxB;
    u8 *a, *b;
    s8 **label;
    player = (D_802D37FD - 1) & 255;
    x = side * 320;
    D_802956F4 += func_801BE660(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), **D_8028326C[characters[player]], (f32)(side * 180), 220.0f, -400.0f, D_80292CF4);
    label = &D_80282DF0;
    y = 55;
    do {
        D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), *label, x - 300.0f, (f32)y, -1200.0f, 255, 255, 255, 255, 0.75f);
        y -= 50; label++;
    } while (y >= -194);
    buffer[6] = 0;
    valueX = x + 80.0f;
    func_801BF678(buffer, D_80128308[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), buffer, valueX, 55.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, (u8)D_80127C30[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), buffer, valueX, 5.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, D_8012830A[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), buffer, valueX, -45.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    a = D_80128310 + player * 11; b = D_80128328 + player * 11;
    maxA = maxB = 0;
    for (i = 0; i != 11; i++) {
        if (maxA < a[i]) maxA = a[i];
        if (maxB < b[i]) maxB = b[i];
    }
    func_801BF678(buffer, (u8)maxA); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), buffer, valueX, -95.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, (u8)maxB); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8), buffer, valueX, -145.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
}
