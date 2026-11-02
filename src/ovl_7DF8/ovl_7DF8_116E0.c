#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BD200.s")

typedef struct {
    u16 buttons;
    s8 x, y;
} PadState;

extern void func_8002B6EC(s32);
extern PadState **func_8002B710(void);
extern u8 D_80068520, D_802D3698, D_802D3699;
extern s32 D_80282A60;
extern PadState **D_802D3670;

/* Packs one player's stick position and button bits into the 64-bit input word. */
u64 func_801BD270(s32 player) {
    u16 buttons;
    s8 x;
    s16 y;
    u64 result;
    PadState *pad;

    if (player == 0 && D_802D3698) {
        D_802D3699 = 1;
        D_802D3670 = func_8002B710();
        if (D_80068520 & 15) {
            D_80282A60 = 2;
        } else {
            D_80282A60 = 0;
        }
        func_8002B6EC(player);
    }
    if (!D_802D3698 || !(D_80068520 & (1 << player))) {
        return 0;
    }
    pad = D_802D3670[player];
    x = pad->x;
    buttons = pad->buttons;
    y = pad->y;
    if (x >= 49) {
        buttons |= 0x100;
    } else if (x < -48) {
        buttons |= 0x200;
    }
    if (y >= 33) {
        buttons |= 0x800;
    } else if (y < -32) {
        buttons |= 0x400;
    }
    result = x & 0xFFFF;
    result = (result << 32) + ((y << 16) & 0xFFFF0000);
    result += buttons & 0xFFFF;
    return result;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BD3FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BD640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BDA6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BDF94.s")

typedef struct {
    s32 image;
    f32 width;
} GlyphRecord;

extern GlyphRecord D_80282A70[];
extern s32 func_801BDA6C(s32, void *, u8 *, f32, f32, f32, u8, u8, u8, u8, f32);

/* Measures a glyph string and draws it in front of `x`. */
s32 func_801BE540(s32 list, void *matrix, u8 *text, f32 x, f32 y, f32 z,
                  u8 r, u8 g, u8 b, u8 a, f32 scale) {
    f32 width = 0.0f;
    u8 *p;
    s8 index;
    GlyphRecord *glyph;

    if (*text != 0) {
        p = text;
        do {
            index = *p - ' ';
            glyph = &D_80282A70[index];
            if ((index < 59) && (index > 0) && glyph->image != 0) {
                width += 10.0f * glyph->width * scale;
            } else if (index <= 0) {
                width += 15.0 * scale;
            }
            p++;
        } while (*p != 0);
    }
    x -= width;
    return func_801BDA6C(list, matrix, text, x, y, z, r, g, b, a, scale);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BE660.s")
