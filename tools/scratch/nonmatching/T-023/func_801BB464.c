/* T-100 improved draft; measurements and remaining causes in T-100/REPORT.md. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB464;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3C34;
extern u8 D_801F3C38[];

void func_801BB464(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB464 *arg4, s32 arg5) {
    s32 temp_v0;
    s32 var_v0; s32 y;
    u16 temp_v1;

    temp_v1 = arg4->scale;
y = (arg2 * 4) + ((s32) (temp_v1 * 0x226) >> 0xA) + (arg4->yOffset * 4);
    var_v0 = (arg1 * 4) + ((s32) (temp_v1 * 0x214) >> 0xA);
    if (arg5 != 0) {
        var_v0 = 0x9B0 - var_v0;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3C38 + (((s32) D_801F3C34 / 3) * 4)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) var_v0, (f32)y, (s32) temp_v1, arg5);
    temp_v0 = D_801F3C34 + 1;
    D_801F3C34 = temp_v0;
    if (temp_v0 >= 0x78) {
        D_801F3C34 = 0;
    }
}
