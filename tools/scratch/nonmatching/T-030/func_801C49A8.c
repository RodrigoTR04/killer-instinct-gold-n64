/* DRAFT. Remaining diff: Frame (0x58 vs 0x48), mode/flag registers, argument spills and call scheduling differ. */
#include "common.h"

typedef struct { u32 w0, w1; } T030Cmd49A8;
typedef struct { u8 *vertices; u8 *matrices; u8 pad[0x14]; } T030Buffer49;
typedef struct { u8 pad[0x38]; T030Buffer49 buffers[2]; } T030State49;
extern void func_8001EC74(T030Cmd49A8 **, s32, s32, u32, u32, s32, s32, s32);
extern T030State49 D_8004CED0;
extern s16 D_8004D26E;
extern s32 D_8004EA78;
extern u8 D_8007D900[], D_800B0C60[], D_802918F0[];
extern u8 D_802D3970;

void func_801C49A8(T030Cmd49A8 **arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, u8 arg5, u8 arg6) {
    s32 sp28;
    u32 var_t4;
    u8 temp_v1;
    T030Buffer49 *buffer;
    T030Cmd49A8 *temp_v0_2;
    T030Cmd49A8 *temp_v0_3;
    T030Cmd49A8 *temp_v0_4;
    T030Cmd49A8 *temp_v0_5;
    T030Cmd49A8 *temp_v0_6;

    buffer = &D_8004CED0.buffers[arg1];
    buffer->vertices = D_8007D900 + arg1 * 0x11120;
    buffer->matrices = D_800B0C60 + arg1 * 0x8890;
    temp_v1 = D_802D3970;
    D_8004EA78 = arg1 + 2;
    var_t4 = arg4;
    D_8004D26E = 0x80;
    if (temp_v1 == 9) {
        var_t4 = arg4 * 6;
    }
    if ((temp_v1 == 9) || (arg5 & 4)) {
        temp_v0_2 = *arg0;
        *arg0 = temp_v0_2 + 1;
        temp_v0_2->w0 = 0x06000000;
        temp_v0_2->w1 = (u32)&D_802918F0;
        temp_v0_3 = *arg0;
        *arg0 = temp_v0_3 + 1;
        temp_v0_3->w1 = (u32)0xFF;
        temp_v0_3->w0 = 0xFA000100;
        temp_v0_4 = *arg0;
        *arg0 = temp_v0_4 + 1;
        temp_v0_4->w0 = 0xFB000000;
        temp_v0_4->w1 = (u32) ((arg6 << 0x18) | (arg6 << 0x10) | (arg6 << 8));
        sp28 = (s32) arg5;
        func_8001EC74(arg0, arg2, arg3, arg4, var_t4 >> 1, 1U, (arg5 & 1) != 0, (arg5 & 2) != 0);
    }
    if (temp_v1 != 9) {
        temp_v0_5 = *arg0;
        *arg0 = temp_v0_5 + 1;
        temp_v0_5->w1 = (u32)&D_802918F0;
        temp_v0_5->w0 = 0x06000000;
        func_8001EC74(arg0, arg2, (u32) arg3, arg4, arg4, 0, (arg5 & 1) != 0, (arg5 & 2) != 0);
    }
    temp_v0_6 = *arg0;
    *arg0 = temp_v0_6 + 1;
    temp_v0_6->w1 = (u32)0x80000;
    temp_v0_6->w0 = 0xBA001301;
}
