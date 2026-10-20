/* DRAFT. Remaining diff: Display-list pointer and constant registers plus scheduling differ. */
typedef struct { u32 w0, w1; } T021Gfx;
extern u8 D_4AC40;

void func_801C51F8(T021Gfx **arg0) {
    T021Gfx *temp_v1;

    temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x01030040;
    temp_v1->w1 = (u32) &D_4AC40;
    temp_v1 = (*arg0)++;
    temp_v1->w0 = 0xBC000404;
    temp_v1->w1 = (u32)1;
    temp_v1 = (*arg0)++;
    temp_v1->w1 = (u32)1;
    temp_v1->w0 = 0xBC000C04;
    temp_v1 = (*arg0)++;
    temp_v1->w0 = 0xBC001404;
    temp_v1->w1 = (u32)0xFFFF;
    temp_v1 = (*arg0)++;
    temp_v1->w1 = (u32)0xFFFF;
    temp_v1->w0 = 0xBC001C04;
}
