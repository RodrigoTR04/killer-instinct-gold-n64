/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA470;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F38C4;
extern u8 D_801F38C8[];
extern u8 D_801F38CC[];

void func_801BA470(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA470 *arg4, s32 arg5) {
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
    var_t1 = temp_v0 + ((s32) (temp_v1 * 0x1A0) >> 0xA);
    temp_a3 = arg2 * 4;
    temp_t9 = arg4->yOffset * 4;
    var_t2 = temp_v0 + ((s32) (temp_v1 * 0x10A) >> 0xA);
    temp_t4 = temp_a3 + ((s32) (temp_v1 * 0xE5) >> 0xA) + temp_t9;
    if (arg5 != 0) {
        var_t1 = 0x9B0 - var_t1;
        var_t2 = 0x9B0 - var_t2;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F38C8 + (D_801F38C4 * 8)), 2, 0x2C, 0x2A, 0x2C, 0x2A, 0, 0, 0x2B, 0x29, (f32) var_t1, (f32) (temp_a3 + ((s32) (temp_v1 * 0xED) >> 0xA) + temp_t9), (s32) temp_v1, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F38CC + (D_801F38C4 * 8)), 2, 0x24, 0x33, 0x24, 0x33, 0, 0, 0x23, 0x32, (f32) var_t2, (f32) temp_t4, (s32) arg4->scale, arg5);
    temp_v0_2 = D_801F38C4 + 1;
    D_801F38C4 = temp_v0_2;
    if (temp_v0_2 >= 0x20) {
        D_801F38C4 = 0;
    }
}
