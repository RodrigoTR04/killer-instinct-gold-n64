/* DRAFT. Remaining diff: Matrix-call float temporaries, display-list pointer registers and scheduling differ. */
#include "common.h"

typedef struct { u32 w0, w1; } T030Cmd2D34;
typedef struct { u8 pad[0xF8]; u8 *matrices; } T030Render2D34;
extern void guRotate(void *, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80285168[];
extern s32 D_802956F4;
extern T030Render2D34 D_802C9F70;

void func_801C2D34(T030Cmd2D34 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s2;
    T030Cmd2D34 *temp_v0;
    T030Cmd2D34 *temp_v0_2;
    T030Cmd2D34 *temp_v0_3;
    T030Cmd2D34 *temp_v0_4;
    T030Cmd2D34 *temp_v0_5;
    T030Cmd2D34 *temp_v0_6;
    T030Cmd2D34 *temp_v0_7;

    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    temp_v0->w1 = 0x80000;
    temp_v0->w0 = 0xBA001301;
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 1;
    temp_v0_2->w1 = 0;
    temp_v0_2->w0 = 0xBA000E02;
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 1;
    temp_v0_3->w0 = 0xB6000000;
    temp_v0_3->w1 = 0x60004;
    guRotate(((D_802956F4 + 2) << 6) + D_802C9F70.matrices, (f32) (arg4 * 2), 0.0f, 1.0f, 0.0f);
    guRotate(((D_802956F4 + 1) << 6) + D_802C9F70.matrices, -8.0f, 1.0f, 0.0f, 0.0f);
    if (arg1 >= 0x77) {
        var_s2 = -0x163;
    } else {
        var_s2 = (arg1 * 3) - 0x2C6;
    }
    guTranslate((D_802956F4 << 6) + D_802C9F70.matrices, (f32) var_s2, (f32) arg2, (f32) arg3);
    temp_v0_4 = *arg0;
    *arg0 = temp_v0_4 + 1;
    temp_v0_4->w0 = 0x01020040;
    temp_v0_4->w1 = (u32) ((D_802956F4 << 6) + D_802C9F70.matrices);
    temp_v0_5 = *arg0;
    *arg0 = temp_v0_5 + 1;
    temp_v0_5->w0 = 0x01000040;
    temp_v0_5->w1 = (u32) (((D_802956F4 + 1) << 6) + D_802C9F70.matrices);
    temp_v0_6 = *arg0;
    *arg0 = temp_v0_6 + 1;
    temp_v0_6->w0 = 0x01000040;
    temp_v0_6->w1 = (u32) (((D_802956F4 + 2) << 6) + D_802C9F70.matrices);
    D_802956F4 += 3;
    temp_v0_7 = *arg0;
    *arg0 = temp_v0_7 + 1;
    temp_v0_7->w1 = (u32)&D_80285168;
    temp_v0_7->w0 = 0x06000000;
}
