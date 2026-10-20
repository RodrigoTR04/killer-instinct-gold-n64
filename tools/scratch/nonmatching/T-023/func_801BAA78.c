/* T-050: retained improvement; 222 differing words including size penalty, 912 compiled bytes. Full function remains nonmatching. */
/* DRAFT. Remaining diff: Rendering temporaries, stack spills and display-list command scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BAA78;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern u8 D_801F3A50[];
extern s32 D_801F3A58;
extern u8 D_801F3A5C[];

void func_801BAA78(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BAA78 *arg4, s32 arg5) {
    u8 *temp_v0_5;
    s32 temp_v1;
    s32 sp6C, sp68;
    u8 *temp_v0_3;
    s32 temp_a3;
    s32 var_v0;
    s32 *temp_t2;
    s32 *sp54;
    s32 var_t1;
    u8 *temp_v0_2;
    u16 temp_v0;
    s32 var_t4;
    u8 *temp_v0_4;
    s32 temp_t7;
    s32 temp_t3;

    temp_v0 = arg4->scale;
    temp_v1 = arg1 * 4;
    var_t1 = temp_v1 + ((s32) (((arg5 * 0x16) + 0x165) * temp_v0) >> 0xA);
    temp_a3 = arg2 * 4;
    temp_t7 = arg4->yOffset * 4;
    sp68 = temp_a3 + ((s32) (temp_v0 * 0xB4) >> 0xA) + temp_t7;
    temp_t3 = sp68;
    var_t4 = temp_v1 + ((s32) (((arg5 * 0x13) + 0x71) * temp_v0) >> 0xA);
    if (arg5 != 0) {
        var_t1 = 0x9B0 - var_t1;
        var_t4 = 0x9B0 - var_t4;
    }
    temp_t2 = (arg5 * 4) + &D_801F3A50;
    var_v0 = *temp_t2 + 1;
    *temp_t2 = var_v0;
    if (var_v0 >= 0x22) {
        *temp_t2 = 0;
        var_v0 = 0;
    }
    if (var_v0 >= 0x14) {
        sp6C = var_t4;
        sp54 = temp_t2;
        func_801BC1B0(arg0, *(s32 *)((u8 *)&D_801F3A58 + (((s32) (var_v0 - 0x14) >> 1) * 8)), 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32) var_t1, (f32) temp_t3, (s32) (arg4->scale * 4) / 3, arg5);
    } else {
        sp6C = var_t4;
        sp54 = temp_t2;
        func_801BC1B0(arg0, D_801F3A58, 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32) var_t1, (f32) temp_t3, (s32) (arg4->scale * 4) / 3, arg5);
    }
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    ((u32 *)temp_v0_2)[0] = 0xFCFFFFFF;
    ((u32 *)temp_v0_2)[1] = 0xFFFCF279;
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 8;
    ((u32 *)temp_v0_3)[1] = 0xFA;
    ((u32 *)temp_v0_3)[0] = 0xF9000000;
    temp_v0_4 = *arg0;
    *arg0 = temp_v0_4 + 8;
    ((u32 *)temp_v0_4)[0] = 0xB9000002;
    ((u32 *)temp_v0_4)[1] = 1;
    func_801BC1B0(arg0, *(s32 *)(D_801F3A5C + (((s32) *temp_t2 >> 2) * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) sp6C, (f32) sp68, (s32) (arg4->scale * 4) / 3, arg5);
    temp_v0_5 = *arg0;
    *arg0 = temp_v0_5 + 8;
    ((u32 *)temp_v0_5)[1] = 0;
    ((u32 *)temp_v0_5)[0] = 0xB9000002;
}
