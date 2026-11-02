#include "common.h"

extern void func_8002B6EC();
extern s32 D_800684A0;
extern s32 D_80282A60;
extern u8 D_802D3698, D_802D3699, D_802D369C[];

/* Resets the player-select cursor state, clamping the count to the available number. */
u8 func_801BD200(s32 arg0) {
    D_80282A60 = D_800684A0;
    D_802D369C[0] = 0;
    D_802D369C[1] = 1;
    if (arg0 < D_80282A60) {
        D_80282A60 = arg0;
    }
    func_8002B6EC();
    D_802D3699 = 1;
    D_802D3698 = 1;
    return D_80282A60;
}

typedef struct {
    u16 buttons;
    s8 x, y;
} PadState;

extern PadState **func_8002B710(void);
extern u8 D_80068520;
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

extern void func_801ADC64(s32);
extern void func_801ADCFC(s32);
extern void func_801AF5EC(s32);
extern u8 D_80127D50;
extern u8 D_8029571A;
extern u8 D_80295723;
extern u64 D_802D3678[];
extern s32 D_802D36A0;

/* Menu navigation for one player: `input` is the 64-bit pad word, D_802D3678 holds last frame's words. */
void func_801BD3FC(s32 player, u64 input, s32 *state) {
    /* The original computes these 64-bit shifts (a call to the shift helper each) and discards them. */
    input >> 32;
    input >> 16;
    if (input & 0xFFFF) {
        D_802D36A0 = state[1];
    }
    if ((D_8029571A == 1) || (D_8029571A == 5)) {
        D_80295723 = 0;
        if ((input & 0x2000) && !(D_802D3678[player] & 0x2000)) {
            func_801AF5EC(0xFFFF);
            func_801ADC64(3);
        }
        if ((input & 0x400) && !(D_802D3678[player] & 0x400)) {
            D_80127D50 += 1;
            if (D_80127D50 >= 8) {
                D_80127D50 = 7;
            }
        } else if ((input & 0x800) && !(D_802D3678[player] & 0x800)) {
            if (D_80127D50-- <= 0) {
                D_80127D50 = 0;
            }
        }
        if ((input & 0x1000) && !(D_802D3678[player] & 0x1000)) {
            if (D_80127D50 == 7) {
                func_801AF5EC(0xFFFF);
                func_801ADC64(2);
            } else {
                func_801AF5EC(0xFFFF);
                func_801ADCFC(player);
            }
        }
    } else if ((input & 0x1000) && !(D_802D3678[player] & 0x1000) && (D_80295723 == 0)) {
        func_801AF5EC(0xFFFF);
        D_8029571A = 1;
    }
    D_802D3678[player] = input;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BD640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_116E0/func_801BDA6C.s")

typedef struct {
    u32 w0, w1;
} TextGfx;

typedef union {
    u64 align;
    u8 bytes[64];
} TextMtx;

typedef struct {
    s32 image;
    f32 width;
} GlyphRecord;

extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
f32 sinf(f32);
f32 cosf(f32);
extern GlyphRecord D_80282C48[];
extern u8 D_80282D28[];
extern s32 D_80282DC0;
extern u8 D_802D36B0[];
extern u8 D_802D36C0[];

/* Draws `text` as one textured quad per letter with the reflection lookat set up first. */
s32 func_801BDF94(TextGfx **dl, TextMtx *matrices, u8 *text, f32 x, f32 y, f32 z, s32 mode, f32 scale, f32 angle)
{
    f64 width; /* one shared temp for all three width selections (match-only: sets frame and mul.d order) */
    s32 fixed = 0;
    GlyphRecord *glyph;
    s32 index;
    s32 count = 0;
    TextMtx reflection;
    s8 character;
    f32 sine;
    s32 *tick; /* match-only: reaching the counter through a pointer keeps IDO from sharing its address */
    s32 length;
    f32 rotation;

    if (scale != 1.0f && scale != -1.0f) {
        if (scale < 0.0f) {
            guScale(matrices, 1.0f, -scale, 1.0f);
            scale = 0.999f;
        } else {
            guScale(matrices, scale, scale, 1.0f);
        }
        count = 1;
    }
    if (mode == 2) {
        guRotate(&matrices[count], angle, 0.0f, 1.0f, 0.0f);
        {
            TextGfx *g = (*dl)++;
            g->w1 = (u32)&matrices[count++];
            g->w0 = 0x01020040;
        }
    }
    tick = &D_80282DC0;
    sine = sinf(*tick * 0.017453292519943295);
    guLookAtReflect(&reflection, D_802D36B0, sine * 60.0f, cosf(*tick * 0.017453292519943295) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    {
        TextGfx *g = (*dl)++;
        g->w1 = (u32)D_802D36B0;
        g->w0 = 0x03840010;
    }
    {
        TextGfx *g = (*dl)++;
        g->w0 = 0x03820010; g->w1 = (u32)D_802D36C0; /* both words on one line: match-only (scheduling) */
    }
    {
        TextGfx *g = (*dl)++;
        g->w0 = 0x06000000; g->w1 = (u32)D_80282D28;
    }
    (*tick)++;
    for (length = 0; text[length]; length++) {
    }
    angle -= length * 30;
    for (index = 0; text[index]; index++) {
        character = text[index] - 'A';
        if (character == -19) character = 26;
        glyph = &D_80282C48[character];
        if (character < 27 && character >= 0 && glyph->image) {
            rotation = 0.0f;
            if (fixed) width = 32.22;
            else width = glyph->width * 9.0f;
            x = x + scale * width;
            if (mode == 1) {
                rotation = index * 30 + angle;
                if (rotation < 360.0f) {
                    z -= (rotation - 360.0f) / 8;
                    y += (rotation - 360.0f) / 32;
                }
            }
            guTranslate(&matrices[count], x, y, z);
            if (mode == 2) {
                TextGfx *g = (*dl)++;
                g->w1 = (u32)&matrices[count++];
                g->w0 = 0x01040040;
            } else {
                TextGfx *g = (*dl)++;
                g->w1 = (u32)&matrices[count++];
                g->w0 = 0x01020040;
            }
            if (rotation < 360.0f && mode == 1) {
                guRotate(&matrices[count], rotation, 1.0f, 0.0f, 0.0f);
                {
                    TextGfx *g = (*dl)++;
                    g->w1 = (u32)&matrices[count++];
                    g->w0 = 0x01000040;
                }
            }
            if (scale != 1.0f) {
                TextGfx *g = (*dl)++;
                g->w1 = (u32)matrices;
                g->w0 = 0x01000040;
            }
            {
                TextGfx *g = (*dl)++;
                g->w0 = 0x06000000;
                g->w1 = glyph->image;
            }
            if (fixed) width = 35.8;
            else width = glyph->width * 10.0f;
            x = x + scale * width;
            if (mode == 2) {
                TextGfx *g = (*dl)++;
                g->w1 = 0;
                g->w0 = 0xBD000000;
            }
        } else if (character == 41) {
            fixed = 1;
        } else {
            if (fixed) width = 68.02;
            else width = 28.5;
            x += scale * width;
        }
    }
    return count;
}

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

/* Centres `text` around `x`: measures the string, then draws it half its width to the left. */
s32 func_801BE660(TextGfx **list, TextMtx *matrix, u8 *text, f32 x, f32 y, f32 z, f32 scale) {
    f32 width = 0.0f;
    u8 *p;
    s8 index;
    GlyphRecord *glyph;

    if (*text != 0) {
        p = text;
        do {
            index = *p - 'A';
            if (index == -19) {
                index = 26;
            }
            glyph = &D_80282C48[index];
            if ((index < 27) && (index >= 0) && glyph->image != 0) {
                width += 19.0f * glyph->width * scale;
            } else if (index < 0) {
                width += 28.5 * scale;
            }
            p++;
        } while (*p != 0);
    }
    x -= width / 2;
    return func_801BDF94(list, matrix, text, x, y, z, 0, scale, 0.0f);
}
