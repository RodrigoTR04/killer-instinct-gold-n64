/* T-160: 7 differing instructions (full-TU comparison), exact 544 B in the full TU. */
#include "frontend.h"

extern void func_801B695C(FrontendSprite *, s32);
extern s32 func_801B6A68(FrontendGfxWords **, FrontendSprite *, s32);
extern void func_801BCB70(FrontendGfxWords **, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, void *);
extern FrontendSprite D_801F2EA8[];
extern FrontendSpriteLayout D_802854D0[];
extern u8 D_802D38C8;

void func_801C2F5C(FrontendGfxWords **arg0, s32 arg1, s32 arg2)
{
    u8 selector;
    s32 sp58;
    s32 temp_a2;
    s32 var_s2;
    s32 var_v0;
    u8 temp_t1;
    FrontendSprite *temp_s0;
    FrontendSpriteLayout *temp_t0;
    FrontendSpriteLayout *temp_t0_2;
    FrontendGfxWords *temp_v0_2;
    temp_s0 = &D_801F2EA8[D_802D38C8];
    if (temp_s0->texture != 0)
    {
        sp58 = temp_s0->scale;
        temp_s0->scale = (D_802854D0[D_802D38C8].scale * temp_s0->scale) >> 8;
        var_s2 = arg1;
        var_s2 += D_802854D0[D_802D38C8].x;
        func_801B695C(temp_s0, 0);
        temp_a2 = func_801B6A68(arg0, temp_s0, 0);
        temp_t0 = &D_802854D0[D_802D38C8];
        if (temp_t0->flip != 0)
        {
            var_v0 = -0x10;
        }
        else
        {
            var_v0 = 0x10;
        }
        func_801BCB70(arg0, temp_s0->texture, temp_a2, 0xC0, 0x110, var_v0, 0x10, 0, 0, 0xBF, 0x10F, (f32) var_s2, (f32) (temp_t0->y + temp_s0->y), (s32) temp_s0->scale, 0xFF, temp_s0->clip);
        if (temp_s0->draw != 0)
        {
            temp_v0_2 = *arg0;
            *arg0 = temp_v0_2 + 1;
            temp_v0_2->w1 = 0;
            temp_v0_2->w0 = 0xE7000000;
            temp_v0_2 = *arg0;
            *arg0 = temp_v0_2 + 1;
            temp_v0_2->w0 = 0xB9000002; temp_v0_2->w1 = 1;
            temp_v0_2 = *arg0;
            *arg0 = temp_v0_2 + 1;
            temp_v0_2->w0 = 0xBA001701; temp_v0_2->w1 = 0x800000;
            temp_t1 = D_802854D0[D_802D38C8].flip;
            if (temp_t1 != 0)
            {
                var_s2 = 0x26C - var_s2;
            }
            temp_s0->draw(arg0, var_s2, D_802854D0[D_802D38C8].y, arg2, temp_s0, (s32) temp_t1);
        }
        temp_s0->scale = (u16) sp58;
    }
}
