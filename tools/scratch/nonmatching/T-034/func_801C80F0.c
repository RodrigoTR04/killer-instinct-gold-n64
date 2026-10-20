/* T-056: now compiles in ovl_7DF8_1BD90.c context (uses the real u8 D_80127D30[8]; func_801CA784 takes 1 arg). */
/* DRAFT. Same instruction count (308); ~200 diff lines from register allocation (s-regs and f20..f30 hoisted constants) and scheduling. Logic follows the asm: 7 rows, row 6 highlighted with a sin() pulse, per-player columns from D_80127C68 (T021Six) and D_802925CC strings. Needs T021Six + the D_80127D30 macro (see func_801CA7E4). */
typedef struct {
    u8 pad0[4];
    u32 frame;
    u8 pad8[0xF0];
    u8 *unkF8;
} T034TextCtx2;

extern s32 func_801BDA6C(s32, u8 *, u8 *, f32, f32, f32, s32, s32, s32, s32, f32);
extern f32 sinf(f32);
extern u8 *D_80127D00[];
extern u8 *D_802925CC[];
extern u8 ***D_80292698[];
extern f32 D_802926B0[];
extern u8 D_8029530C[];
extern u8 D_80295310[];
extern f64 D_802954B8;
extern f32 D_802954C0;
extern f32 D_802954C4;
extern s32 D_802956F4;
extern u8 D_802D39FE[2];
extern u8 D_802D3A00;
extern u8 D_802D3A06;

void func_801C80F0(s32 arg0, T034TextCtx2 *arg1) {
    u8 p1;
    u8 p2;
    u8 ***names;
    u8 *name1;
    u8 *name2;
    f32 y;
    f32 x;
    f32 scale;
    s32 pulse;
    s32 i;
    s32 r;
    s32 gb;

    p2 = 0;
    p1 = 1;
    y = D_802926B0[D_802D3A00];
    x = -450.0f;
    names = D_80292698[D_802D3A00];
    pulse = sinf(arg1->frame * D_802954B8 * 5.0) * 63.0f + 192.0f;
    if (D_802D3A06) {
        p2 = D_80127D30[0] + 1;
        p1 = D_80127D30[1] + 1;
        name1 = D_80127D00[D_80127D30[0] - 1];
        name2 = D_80127D00[D_80127D30[1] - 1];
    } else {
        name1 = D_8029530C;
        name2 = D_80295310;
    }
    scale = D_802954C0;
    D_802956F4 += func_801BDA6C(arg0, arg1->unkF8 + (D_802956F4 << 6), name1, 75.0f, 230.0f, -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, scale);
    D_802956F4 += func_801BDA6C(arg0, arg1->unkF8 + (D_802956F4 << 6), name2, 315.0f, 230.0f, -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, scale);
    for (i = 0; i < 7; i++) {
        r = 0xFF;
        if (i == 6 - (D_802D3A00 == 0)) {
            y = -300.0f;
            if (D_802D3A06) {
                x = -320.0f;
            } else {
                x = -200.0f;
            }
        }
        if (i == 6) {
            r = pulse;
            if (i == D_802D39FE[0]) {
                gb = 0;
            } else if (i == D_802D39FE[1]) {
                gb = 0;
            } else {
                r = 100;
                gb = 100;
            }
        } else {
            gb = 0xFF;
        }
        if (i == 3) {
            y -= 50.0f;
        }
        D_802956F4 += func_801BDA6C(arg0, arg1->unkF8 + (D_802956F4 << 6), *names[i], x, y, -800.0f, r, (u8)gb, (u8)gb, 0xFF, D_802954C4);
        if (i != 6) {
            if (i == D_802D39FE[0]) {
                r = pulse;
                gb = 0;
            } else {
                r = 100;
                gb = 100;
            }
            D_802956F4 += func_801BDA6C(arg0, arg1->unkF8 + (D_802956F4 << 6), D_802925CC[D_80127C68[p2].b[i]], 40.0f, y, -800.0f, (u8)gb, r, (u8)gb, 0xFF, 0.5f);
            if (i == D_802D39FE[1]) {
                r = pulse ^ 0x3F;
                gb = 0;
            } else {
                r = 100;
                gb = 100;
            }
            D_802956F4 += func_801BDA6C(arg0, arg1->unkF8 + (D_802956F4 << 6), D_802925CC[D_80127C68[p1].b[i]], 260.0f, y, -800.0f, r, (u8)gb, (u8)gb, 0xFF, 0.5f);
        }
        y -= 50.0f;
    }
}
