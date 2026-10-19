/* DRAFT. Compiles; 788 vs 796 instructions, ~400 diff lines. Structure follows the asm (menu renderer: title, mode-5 save-info text, scrolling item list with D_802D39F8 scroll). Remaining: register/stack allocation, some branch layout in the item loop, and the m2c-ambiguous item-string access ((*items[i])->unk4/unk8) needs checking. Rodata floats/doubles referenced as externs. */
typedef struct {
    u32 w0;
    u32 w1;
} T034Gfx;

typedef struct {
    s32 unk0;
    u32 frame;
    u8 pad8[0xF0];
    u8 *unkF8;
} T034MenuCtx;

typedef struct {
    u8 *unk0;
    u8 *unk4;
    u8 *unk8;
} T034MenuItem;

extern s32 func_801BDA6C(T034Gfx **, u8 *, u8 *, f32, f32, f32, s32, s32, s32, s32, f32);
extern s32 func_801BE540(T034Gfx **, u8 *, u8 *, f32, f32, f32, s32, s32, s32, s32, f32);
extern s32 func_801BE660(T034Gfx **, u8 *, s32, s32, f32, f32, f32);
extern void func_801C0610(T034Gfx **);
extern void func_801C2D34(T034Gfx **, s32, s32, s32, u32);
extern void func_801C8004(void);
extern void func_801C80F0(T034Gfx **, T034MenuCtx *);
extern void func_801C90D4(T034Gfx **, T034MenuCtx *);
extern void func_801C9698(T034Gfx **, T034MenuCtx *);
extern void func_801CD100(u8 *, s32);
extern s32 func_801CD3BC(T034Gfx **, u8 *, s32, f32);
extern f32 sinf(f32);
extern u8 D_8007D900[];
extern u8 D_802923A0;
extern s8 D_802923A4;
extern s8 D_802923A8;
extern u8 D_802923C0[];
extern u8 D_802923F0[];
extern u8 D_802923F5;
extern T034MenuItem *D_802923FC;
extern T034MenuItem *D_80292404;
extern T034MenuItem ***D_80292698[];
extern f32 D_802926B0[];
extern f32 D_802926C8[];
extern s32 D_802926E0[];
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
extern u8 D_8029538C[];
extern u8 D_802953A0[0x24];
extern u8 D_802953C4[];
extern u8 D_802953E4[];
extern u8 D_802953F8[];
extern u8 D_80295418[];
extern f32 D_802954E8;
extern f64 D_802954F0;
extern f32 D_802954F8;
extern f32 D_802954FC;
extern f32 D_80295500;
extern f32 D_80295504;
extern f32 D_80295508;
extern f32 D_8029550C;
extern f32 D_80295510;
extern f32 D_80295514;
extern f64 D_80295518;
extern f32 D_80295520;
extern f32 D_80295524;
extern s32 D_802956F4;
extern f32 D_802D39F8;
extern u8 D_802D39FC;
extern u8 D_802D3A00;
extern u8 D_802D3A07;
extern u8 D_802D3E0E;
extern s32 D_802D3E10;
extern u8 D_802D3E14;

typedef struct {
    u8 b[0x24];
} T034Text24;

void func_801C9B14(T034Gfx **gfxp, T034MenuCtx *arg1) {
    T034Text24 buf;
    f32 bottom;
    T034MenuItem ***items;
    u8 pulse;
    f32 selY;
    u8 dim;
    f32 y;
    f32 scale;
    f32 x;
    s32 i;
    s32 row;
    s32 last;
    s32 r;
    s32 g;
    s32 b;
    s32 visible;
    u8 count;
    u8 hi;
    u8 kind;
    u8 *str;
    T034Gfx *gfx;

    bottom = 0.0f;
    y = D_802926B0[D_802D3A00];
    scale = D_802954E8;
    row = -3;
    pulse = sinf(arg1->frame * D_802954F0 * 5.0) * 63.0f + 192.0f;
    D_802923A8 = D_802923A4 = 0;
    dim = 0;
    selY = 0.0f;
    items = D_80292698[D_802D3A00];
    if (D_802D3A00 == 5) {
        arg1->unkF8 = D_8007D900 + arg1->unk0 * 0x11120;
    }
    func_801C8004();
    if (D_802D3A00 == 1) {
        if (D_802D3E14) {
            *items = &D_80292404;
        } else {
            *items = &D_802923FC;
        }
        if (D_802D3A07) {
            pulse = 0x80;
        }
    } else if (D_802D3A00 == 5) {
        D_802923F5 = D_802D3E0E;
    }
    func_801C0610(gfxp);
    func_801C2D34(gfxp, 1000, -250, -600, arg1->frame);
    D_802956F4 += func_801BE660(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_802926E0[D_802D3A00], 0, 300.0f, D_802954F8, 1.0f);
    if (D_802D3A00 < 2) {
        D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_8029538C, 0.0f, D_802954FC, -800.0f, pulse, pulse, pulse, 0xFF, D_80295500);
        D_802956F4 += func_801CD3BC(gfxp, arg1->unkF8 + (D_802956F4 << 6), 0, -450.0f);
    } else if (D_802D3A00 == 5) {
        buf = *(T034Text24 *)D_802953A0;
        func_801CD100(buf.b, D_802D3E10);
        D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), buf.b, 0.0f, -213.0f, -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, D_80295504);
        D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_802953C4, 0.0f, D_80295508, -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, D_8029550C);
        D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_802953E4, 0.0f, D_80295510, -800.0f, pulse, pulse, pulse, 0xFF, D_80295514);
        D_802956F4 += func_801BDA6C(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_802953F8, -440.0f, 240.0f, -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    }
    if (D_802D3A00 == 3) {
        func_801C80F0(gfxp, arg1);
    } else if (D_802D3A00 == 4) {
        func_801C9698(gfxp, arg1);
    } else {
        gfx = (*gfxp)++;
        gfx->w0 = 0xED000154;
        gfx->w1 = 0x00A005C8;
        count = D_802923F0[D_802D3A00];
        for (i = 0; i < count; i++) {
            if (D_802923A0 < row) {
                dim = 1;
            }
            if (i == D_802D39FC) {
                r = 0xFF;
                b = 0;
                hi = pulse;
                g = 0xFF;
            } else {
                r = 0x5A >> dim;
                hi = r;
                g = r;
                b = 0x96 >> dim;
            }
            kind = D_802926F8[D_802D3A00][i];
            if (kind == 0) {
                g = hi;
                r++;
            }
            visible = 0;
            if (y - D_802D39F8 < 260.0f && y - D_802D39F8 > -250.0f) {
                visible = 1;
            }
            if ((kind == 0xFF || i >= count + (D_802D3A00 == 0) - 1 || D_802D3A00 == 1) && D_802D3A00 != 5) {
                x = 0.0f;
                if (i + 1 == count - (D_802D3A00 == 0) * 3) {
                    y -= 48.0f;
                    last = row - 1;
                    scale += D_80295518;
                } else {
                    scale = D_80295520;
                    if (kind != 0xFF) {
                        b = r;
                    } else {
                        y -= 48.0f;
                        if (row == D_802923A0 && visible) {
                            D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), D_80295418, 200.0f, y - D_802D39F8, -800.0f, g, r, b, 0xFF, D_80295524);
                            x = -200.0f;
                        }
                        row++;
                    }
                    last = row - 1;
                }
                if (visible) {
                    D_802956F4 += func_801BE540(gfxp, arg1->unkF8 + (D_802956F4 << 6), (*items[i])->unk0, x, y - D_802D39F8, -800.0f, g, r, b, 0xFF, scale);
                }
            } else {
                last = row - 1;
                if (D_802D3A00 == 5) {
                    scale = 0.5f;
                    x = -450.0f;
                    y += 25.0f;
                } else {
                    x = -440.0f;
                }
                if (visible) {
                    D_802956F4 += func_801BDA6C(gfxp, arg1->unkF8 + (D_802956F4 << 6), (*items[i])->unk0, x, y - D_802D39F8, -800.0f, g, (u8)r, (u8)r, 0xFF, scale);
                }
            }
            kind = D_802926F8[D_802D3A00][i];
            if (kind != 0 && kind != 0xFF) {
                if (kind > 0x20) {
                    if (D_80292710[D_802D3A00][i] == 0) {
                        str = D_802923C0;
                    } else {
                        (*items[i])->unk4 = (*items[i])->unk8;
                        str = (*items[i])->unk4;
                        str[0] = D_80292710[D_802D3A00][i] + '0';
                        if (D_80292710[D_802D3A00][i] >= 2) {
                            str[5] = 'S';
                        } else {
                            str[5] = 0;
                        }
                    }
                } else {
                    str = (&(*items[i])->unk4)[D_80292710[D_802D3A00][i]];
                }
                if (visible && !dim) {
                    D_802956F4 += func_801BDA6C(gfxp, arg1->unkF8 + (D_802956F4 << 6), str, D_802926C8[D_802D3A00], y - D_802D39F8, -800.0f, hi, (u8)(r + 1), (u8)(r + 1), 0xFF, scale);
                }
            }
            count = D_802923F0[D_802D3A00];
            if (i == D_802D39FC) {
                selY = y;
                D_802923A4 = row;
                D_802923A8 = (D_802926F8[D_802D3A00][i + 1] == 0xFF) + row;
            }
            if (D_802923A0 >= last) {
                bottom = y;
            }
            y -= 48.0f;
        }
    }
    if (D_802D3A00 == 0) {
        if (selY + 15.0f < D_802D39F8) {
            D_802D39F8 -= 16.0f;
        } else if (D_802D39F8 < selY - 15.0f) {
            D_802D39F8 += 16.0f;
        } else {
            D_802D39F8 = selY;
        }
        if (D_802D39F8 > 0.0f) {
            D_802D39F8 = 0.0f;
        }
        if (D_802D39F8 < bottom + 200.0f) {
            D_802D39F8 = bottom + 200.0f;
        }
    }
    if (D_802D3A07) {
        func_801C90D4(gfxp, arg1);
    }
}
