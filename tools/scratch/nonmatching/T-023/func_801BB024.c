/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB024;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3ACC;
extern u8 D_801F3AD0[];
extern u8 D_801F3AD4[];

void func_801BB024(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB024 *arg4, s32 arg5) {
    s32 temp_a3;
    s32 temp_t5;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_t2;
    s32 var_t3;
    u16 temp_t0;

    temp_t0 = arg4->scale;
    temp_v1 = arg5 * 0x16;
    temp_v0 = arg1 * 4;
    temp_a3 = arg2 * 4;
    var_t2 = temp_v0 + ((s32) ((temp_v1 + 0x124) * temp_t0) >> 0xA);
    temp_t9 = arg4->yOffset * 4;
    var_t3 = temp_v0 + ((s32) ((temp_v1 + 0x72) * temp_t0) >> 0xA);
    temp_t5 = temp_a3 + ((s32) (temp_t0 * 0xD6) >> 0xA) + temp_t9;
    if (arg5 != 0) {
        var_t2 = 0x9B0 - var_t2;
        var_t3 = 0x9B0 - var_t3;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3AD0 + (D_801F3ACC * 8)), 2, 0x34, 0x25, 0x34, 0x25, 0, 0, 0x33, 0x24, (f32) var_t2, (f32) (temp_a3 + ((s32) (temp_t0 * 0xCB) >> 0xA) + temp_t9), (s32) (temp_t0 * 4) / 3, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3AD4 + (D_801F3ACC * 8)), 2, 0x20, 0x40, 0x20, 0x40, 0, 0, 0x1F, 0x3F, (f32) var_t3, (f32) temp_t5, (s32) (arg4->scale * 4) / 3, arg5);
    temp_v0_2 = D_801F3ACC + 1;
    D_801F3ACC = temp_v0_2;
    if (temp_v0_2 >= 0x28) {
        D_801F3ACC = 0;
    }
}
