typedef int s32; typedef short s16; typedef unsigned char u8; typedef float f32; typedef double f64;
s32 func_801B55DC(u8 arg0) {
    s32 temp_t6;

    temp_t6 = arg0;
    if (temp_t6 < 0xA) {
        return (temp_t6 + 0x30) << 0x18;
    }
    return (((temp_t6 / 10) + 0x30) << 0x18) + (((temp_t6 % 10) + 0x30) << 0x10);
}
