/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA088;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3678;
extern u8 D_801F367C[];
extern u8 D_801F3680[];

void func_801BA088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA088 *arg4, s32 arg5) {
    s32 temp_a3;
    s32 temp_t4;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t1;
    s32 var_t2;
    u16 temp_v1;

    temp_v1 = arg4->scale;
    temp_v0 = arg1 * 4;
    var_t1 = temp_v0 + ((s32) (temp_v1 * 0x13C) >> 0xA);
    temp_a3 = arg2 * 4;
    temp_t9 = arg4->yOffset * 4;
    var_t2 = temp_v0 + ((s32) (temp_v1 * 0xE0) >> 0xA);
    temp_t4 = temp_a3 + ((s32) (temp_v1 * 0x128) >> 0xA) + temp_t9;
    if (arg5 != 0) {
        var_t1 = 0x9B0 - var_t1;
        var_t2 = 0x9B0 - var_t2;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F367C + (D_801F3678 * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) var_t1, (f32) (temp_a3 + ((s32) (temp_v1 * 0x8A) >> 0xA) + temp_t9), (s32) temp_v1, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3680 + (D_801F3678 * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) var_t2, (f32) temp_t4, (s32) arg4->scale, arg5);
    temp_v0_2 = D_801F3678 + 1;
    D_801F3678 = temp_v0_2;
    if (temp_v0_2 >= 0x35) {
        D_801F3678 = 2;
    }
}
