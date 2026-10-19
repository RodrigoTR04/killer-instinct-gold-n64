/* DRAFT. Remaining diff: Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB258;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3C10;
extern u8 D_801F3C14[];
extern u8 D_801F3C18[];

void func_801BB258(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB258 *arg4, s32 arg5) {
    s32 temp_t3;
    s32 temp_t5;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_t1;
    s32 var_t2;
    u16 temp_t0;

    temp_t0 = arg4->scale;
    var_t2 = (arg1 * 4) + ((s32) (temp_t0 * 0xC4) >> 0xA);
    temp_v1 = arg2 * 4;
    temp_t5 = arg4->yOffset * 4;
    temp_t3 = temp_v1 + ((s32) (temp_t0 * 0x153) >> 0xA) + temp_t5;
    var_t1 = var_t2;
    if (arg5 != 0) {
        var_t1 = 0x9B0 - var_t1;
        var_t2 = 0x9B0 - var_t2;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3C14 + (((s32) D_801F3C10 / 3) * 8)), 2, 0x2C, 0x20, 0x2C, 0x20, 0, 0, 0x2B, 0x1F, (f32) var_t2, (f32) (temp_v1 + ((s32) (temp_t0 * 0xD7) >> 0xA) + temp_t5), (s32) temp_t0, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3C18 + (((s32) D_801F3C10 / 3) * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) var_t1, (f32) temp_t3, (s32) arg4->scale, arg5);
    temp_v0 = D_801F3C10 + 1;
    D_801F3C10 = temp_v0;
    if (temp_v0 >= 0xC) {
        D_801F3C10 = 0;
    }
}
