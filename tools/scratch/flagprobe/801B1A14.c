typedef int s32; typedef short s16; typedef unsigned char u8; typedef float f32; typedef double f64;
f32 func_800340D0(f32);                             /* extern */

f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_f0;

    temp_f0 = func_800340D0((arg1 * arg1) + (arg0 * arg0));
    arg1 = ((arg2 - temp_f0) * arg1) / temp_f0;
    if (arg1 < 0.0f) {
        return 0.0f;
    }
    return arg1;
}
