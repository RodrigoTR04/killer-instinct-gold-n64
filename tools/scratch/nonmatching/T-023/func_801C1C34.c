/* T-076: nonmatching, 242 differing words including size penalty; 1224 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
extern s32 func_801BDA6C(s32, void *, s8 *, f32, f32, f32, u8, u8, u8, u8, f32);
extern s32 func_801BE660(s32, void *, s8 *, f32, f32, f32, f32);
extern void func_801BF678(s8 *, s32);
extern u8 D_80128308[], D_8012830A[], D_80128310[][11], D_80128328[][11];
typedef struct { u8 pad[0xF8]; u8 *matrices; } T070Render1C34;
extern T070Render1C34 D_802C9F70;
extern s32 D_80127C30[], D_802956F4;
extern s8 *D_80282DF0;
extern s8 ***D_8028326C[];
extern f32 D_80292CF4;
extern u8 D_802D37FD;
void func_801C1C34(s32 list, s32 unused, u8 *characters, s32 side) {
    s8 buffer[7];
    f32 x, valueX;
    s32 player;
    s32 y, i;
    u8 maxA, maxB;
    u8 *a, *b;
    s8 **label;
    maxA = maxB = 0;
    player = (D_802D37FD - 1) & 255;
    x = side * 320;
    D_802956F4 += func_801BE660(list, (D_802956F4 << 6) + D_802C9F70.matrices, **D_8028326C[characters[player]], (f32)(side * 180), 220.0f, -400.0f, D_80292CF4);
    label = &D_80282DF0;
    y = 55;
    do {
        D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, *label, x - 300.0f, (f32)y, -1200.0f, 255, 255, 255, 255, 0.75f);
        y -= 50; label++;
    } while (y >= -194);
    buffer[6] = 0;
    valueX = x + 80.0f;
    func_801BF678(buffer, D_80128308[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, valueX, 55.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, D_80127C30[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, valueX, 5.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, D_8012830A[player]); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, valueX, -45.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    a = D_80128310[player]; b = D_80128328[player];
    for (i = 0; i != 11; i++) {
        if (maxA < *a) maxA = *a;
        a++;
        if (maxB < *b) maxB = *b;
        b++;
    }
    func_801BF678(buffer, (u8)maxA); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, valueX, -95.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
    func_801BF678(buffer, (u8)maxB); buffer[0] = 'j';
    D_802956F4 += func_801BDA6C(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, valueX, -145.0f, -1200.0f, 255, 255, 255, 255, 0.75f);
}
