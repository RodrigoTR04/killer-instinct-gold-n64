/* DRAFT. Remaining diff: Same size; display-list pointer/temporary registers and two instruction schedules differ. */
typedef struct { u32 w0, w1; } T021Gfx;
extern u8 D_802855C8;

s32 func_801C3524(T021Gfx **arg0, s32 arg1) {

    T021Gfx *temp_a2;


    
    if (arg1 >= 0x11) {
        arg1 = 0x10;
    }
    temp_a2 = *arg0;
    *arg0 = temp_a2 + 1;
    temp_a2->w1 = (s32) ((arg1 * 0xF) & 0xFF);
    temp_a2->w0 = 0xFA000000;
    temp_a2 = *arg0;
    *arg0 = temp_a2 + 1;
    temp_a2->w0 = 0x06000000;
    temp_a2->w1 = (s32) &D_802855C8;
    return arg1 == 0x10;
}
