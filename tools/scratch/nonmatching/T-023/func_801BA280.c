/* T-050: retained improvement; 129 differing words including size penalty, 532 compiled bytes. Full function remains nonmatching. */
/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA280;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern u8 D_801F3824[];
extern u8 D_801F388C[];

void func_801BA280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA280 *arg4, s32 arg5) {
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_t2;
    s32 var_t3;
    u16 temp_v1;

    temp_t9 = arg4->yOffset * 4;
    temp_v1 = arg4->scale;
    temp_v0 = arg1 * 4;
    var_t2 = temp_v0 + ((s32) (temp_v1 * 0x120) >> 0xA);
    temp_t0 = arg2 * 4;
    var_t3 = temp_v0 + ((s32) (temp_v1 * 0xB5) >> 0xA);
    temp_t5 = temp_t0 + ((s32) (temp_v1 * 0x11C) >> 0xA) + temp_t9;
    if (arg5 != 0) {
        var_t2 = 0x9B0 - var_t2;
        var_t3 = 0x9B0 - var_t3;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3824 + (((s32) (arg3 >> 3) % 25) * 4)), 2, 0x28, 0x1E, 0x28, 0x1E, 0, 0, 0x27, 0x1D, (f32) var_t2, (f32) (temp_t0 + ((s32) (temp_v1 * 0xF9) >> 0xA) + temp_t9), (s32) temp_v1, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F388C + (((s32) (arg3 >> 2) % 13) * 4)), 2, 0x1C, 0x26, 0x1C, 0x26, 0, 0, 0x1B, 0x25, (f32) var_t3, (f32) temp_t5, (s32) arg4->scale, arg5);
}
