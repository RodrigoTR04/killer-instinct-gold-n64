typedef int s32; typedef short s16; typedef unsigned char u8; typedef float f32; typedef double f64;
extern f64 D_DBL_800489D0;
extern f64 D_DBL_800489D8;
extern f32 D_FLT_8004ACE4;
extern f32 D_FLT_8004ACE8;

void func_8001BA18(f32 arg0) {
    if (((D_FLT_8004ACE8 * 4.0f) + D_FLT_8004ACE4) < arg0) {
        D_FLT_8004ACE8 = (f32) ((f64) D_FLT_8004ACE8 + D_DBL_800489D0);
    } else {
        D_FLT_8004ACE8 = (f32) ((f64) D_FLT_8004ACE8 - D_DBL_800489D8);
    }
    D_FLT_8004ACE4 += D_FLT_8004ACE8;
}
