/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA884;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F39EC;
extern u8 D_801F39F0[];
extern u8 D_801F39F4[];

void func_801BA884(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA884 *arg4, s32 arg5) {
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t1;
    s32 var_t2;
    u16 temp_t0;

    temp_t0 = arg4->scale;
    temp_v0 = arg1 * 4;
    var_t1 = temp_v0 + ((s32) (((arg5 * 0x15) + 0x1CC) * temp_t0) >> 0xA);
    temp_t4 = (arg2 * 4) + ((s32) (temp_t0 * 0x70) >> 0xA) + (arg4->yOffset * 4);
    var_t2 = temp_v0 + ((s32) (temp_t0 * 0x12C) >> 0xA);
    if (arg5 != 0) {
        var_t1 = 0x9B0 - var_t1;
        var_t2 = 0x9B0 - var_t2;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F39F0 + (D_801F39EC * 8)), 2, 0x20, 0x40, 0x20, 0x40, 0, 0, 0x1F, 0x3F, (f32) var_t1, (f32) temp_t4, (s32) (temp_t0 * 4) / 3, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F39F4 + (D_801F39EC * 8)), 2, 0x34, 0x1C, 0x34, 0x1C, 0, 0, 0x33, 0x1B, (f32) var_t2, (f32) temp_t4, (s32) arg4->scale, arg5);
    temp_v0_2 = D_801F39EC + 1;
    D_801F39EC = temp_v0_2;
    if (temp_v0_2 >= 0xC) {
        D_801F39EC = 0;
    }
}
