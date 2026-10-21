/* T-106 draft: 106 differing words; 568/568 bytes.
 * Keep both draw coordinates in indexed pairs before mirroring.
 * T-111: explicit counter pointers recover symbolic accesses.
 * Still nonmatching: coordinate storage, allocation and scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BADEC;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3AA0;
extern s32 D_801F3AA4;
extern u8 D_801F3AA8[];

void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BADEC *arg4, s32 arg5) {
    s32 x[2], y[2];
    s32 *counter0;
    s32 *counter1;
    s32 temp_t5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u16 temp_t0;

    temp_t0 = arg4->scale;
    counter0 = &D_801F3AA0;
    counter1 = &D_801F3AA4;
    temp_v0 = arg2 * 4;
    temp_t5 = arg4->yOffset * 4;
    x[0] = (arg1 * 4) + ((s32) ((0x1CD - (arg5 * 4)) * temp_t0) >> 0xA);
    y[1] = temp_v0 + ((s32) (temp_t0 * 0x1E3) >> 0xA) + temp_t5;
    y[0] = temp_v0 + ((s32) (temp_t0 * 0x198) >> 0xA) + temp_t5;
    if (arg5 != 0) {
        x[0] = 0x9B0 - x[0];
    }
    temp_v0_2 = *counter0 + 1;
    *counter0 = temp_v0_2;
    if (temp_v0_2 >= 0x15) {
        if (temp_v0_2 >= 0x27) {
            *counter0 = 0;
        } else {
            *counter0 = temp_v0_2;


            func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_2 - 0x15) >> 1) * 4)), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x[0], (f32) y[0], (s32) temp_t0, arg5);
        }
    }
    temp_v0_3 = *counter1 + 1;
    *counter1 = temp_v0_3;
    if (temp_v0_3 >= 0x1C) {
        if (temp_v0_3 >= 0x2E) {
            *counter1 = 0;
            return;
        }
        *counter1 = temp_v0_3;
        func_801BC1B0(arg0, *(s32 *)(D_801F3AA8 + (((s32) (temp_v0_3 - 0x1C) >> 1) * 4)) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x[0], (f32) y[1], (s32) arg4->scale, arg5);
    }
}
