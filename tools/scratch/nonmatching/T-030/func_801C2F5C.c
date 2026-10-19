/* DRAFT. Remaining diff: Sprite/layout pointer lifetimes, callback arguments, frame (0x90 vs 0x60) and scheduling differ. */
#include "common.h"

typedef struct { u32 w0,w1; } T030Cmd2F5C;
typedef struct T030Sprite2F5C {
    u32 pad0; s32 texture; u8 pad8[0xA]; u8 clip[0x6C];
    u16 scale; s16 y; u8 pad82[6]; void (*draw)();
} T030Sprite2F5C;
typedef struct { s32 x,y; s32 scale; u8 flip; u8 padD[3]; } T030Layout2F5C;
extern void func_801B695C(T030Sprite2F5C *, s32);
extern s32 func_801B6A68(T030Cmd2F5C **, T030Sprite2F5C *, s32);
extern void func_801BCB70(T030Cmd2F5C **, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, void *);
extern T030Sprite2F5C D_801F2EA8[];
extern T030Layout2F5C D_802854D0[];
extern u8 D_802D38C8;

void func_801C2F5C(T030Cmd2F5C **arg0, s32 arg1, s32 arg2) {
    s32 sp58;
    s32 temp_a2;
    s32 var_s2;
    s32 var_v0;
    u16 temp_v0;
    u8 temp_t1;
    T030Sprite2F5C *temp_s0;
    T030Layout2F5C *temp_t0;
    T030Layout2F5C *temp_t0_2;
    T030Cmd2F5C *temp_v0_2;
    T030Cmd2F5C *temp_v0_3;
    T030Cmd2F5C *temp_v0_4;

    temp_s0 = &D_801F2EA8[D_802D38C8];
    if (temp_s0->texture != 0) {
        temp_v0 = temp_s0->scale;
        sp58 = (s32) temp_v0;
        temp_s0->scale = (u16) ((s32) (D_802854D0[D_802D38C8].scale * temp_v0) >> 8);
        var_s2 = arg1 + D_802854D0[D_802D38C8].x;
        func_801B695C(temp_s0, 0);
        temp_a2 = func_801B6A68(arg0, temp_s0, 0);
        temp_t0 = &D_802854D0[D_802D38C8];
        if (temp_t0->flip != 0) {
            var_v0 = -0x10;
        } else {
            var_v0 = 0x10;
        }
        func_801BCB70(arg0, temp_s0->texture, temp_a2, 0xC0, 0x110, var_v0, 0x10, 0, 0, 0xBF, 0x10F, (f32) var_s2, (f32) (temp_t0->y + temp_s0->y), (s32) temp_s0->scale, 0xFF, temp_s0->clip);
        if (temp_s0->draw != 0) {
            temp_v0_2 = *arg0;
            *arg0 = temp_v0_2 + 1;
            temp_v0_2->w1 = 0;
            temp_v0_2->w0 = 0xE7000000;
            temp_v0_3 = *arg0;
            *arg0 = temp_v0_3 + 1;
            temp_v0_3->w1 = 1;
            temp_v0_3->w0 = 0xB9000002;
            temp_v0_4 = *arg0;
            *arg0 = temp_v0_4 + 1;
            temp_v0_4->w1 = 0x800000;
            temp_v0_4->w0 = 0xBA001701;
            temp_t0_2 = &D_802854D0[D_802D38C8];
            temp_t1 = temp_t0_2->flip;
            if (temp_t1 != 0) {
                var_s2 = 0x26C - var_s2;
            }
            temp_s0->draw(arg0, var_s2, temp_t0_2->y, arg2, temp_s0, (s32) temp_t1);
        }
        temp_s0->scale = (u16) sp58;
    }
}
