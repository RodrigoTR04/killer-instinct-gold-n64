/* T-061 DRAFT: 6 differing words, correct 552-byte body. Input coordinate reuse fixes saved registers; first/final command store scheduling remains. */
#include "common.h"

typedef union { struct { u32 w0, w1; } words; u64 full; } T030Cmd2D34;
typedef struct { u8 pad[0xF8]; u8 *matrices; } T030Render2D34;
extern void guRotate(void *, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80285168[];
extern s32 D_802956F4;
extern T030Render2D34 D_802C9F70;

void func_801C2D34(T030Cmd2D34 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    T030Cmd2D34 *temp_v0;
    T030Cmd2D34 *temp_v0_2;
    T030Cmd2D34 *temp_v0_3;
    T030Cmd2D34 *temp_v0_4;
    T030Cmd2D34 *temp_v0_5;
    T030Cmd2D34 *temp_v0_6;
    T030Cmd2D34 *temp_v0_7;

    temp_v0 = (*arg0)++;
    temp_v0->words.w0 = 0xBA001301;
    temp_v0->words.w1 = 0x80000;
    temp_v0_2 = (*arg0)++;
    temp_v0_2->words.w1 = 0;
    temp_v0_2->words.w0 = 0xBA000E02;
    temp_v0_3 = (*arg0)++;
    temp_v0_3->full = 0xB600000000060004ULL;
    guRotate(((D_802956F4 + 2) << 6) + D_802C9F70.matrices, (f32) (arg4 * 2), 0.0f, 1.0f, 0.0f);
    guRotate(((D_802956F4 + 1) << 6) + D_802C9F70.matrices, -8.0f, 1.0f, 0.0f, 0.0f);
    if (arg1 >= 0x77) {
        arg1 = -0x163;
    } else {
        arg1 = (arg1 * 3) - 0x2C6;
    }
    guTranslate((D_802956F4 << 6) + D_802C9F70.matrices, (f32) arg1, (f32) arg2, (f32) arg3);
    temp_v0_4 = (*arg0)++;
    temp_v0_4->words.w0 = 0x01020040;
    temp_v0_4->words.w1 = (u32) ((D_802956F4 << 6) + D_802C9F70.matrices);
    temp_v0_5 = (*arg0)++;
    temp_v0_5->words.w0 = 0x01000040;
    temp_v0_5->words.w1 = (u32) (((D_802956F4 + 1) << 6) + D_802C9F70.matrices);
    temp_v0_6 = (*arg0)++;
    temp_v0_6->words.w0 = 0x01000040;
    temp_v0_6->words.w1 = (u32) (((D_802956F4 + 2) << 6) + D_802C9F70.matrices);
    D_802956F4 += 3;
    temp_v0_7 = (*arg0)++;
    temp_v0_7->words.w0 = 0x06000000;
    temp_v0_7->words.w1 = (u32)&D_80285168;
}
