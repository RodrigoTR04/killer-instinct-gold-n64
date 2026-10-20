/* DRAFT. Remaining diff: Only the first address addiu and command ori are exchanged (2 words); all registers and 160-byte size match. */
typedef struct { u32 w0, w1; } T021Gfx;
extern u8 D_4AC40;

void func_801C51F8(T021Gfx **arg0) {
    T021Gfx *p0, *p1, *p2, *p3, *p4;

    p0 = (*arg0)++;
    p0->w0 = 0x01030040;
    p0->w1 = (u32) &D_4AC40;
    p1 = (*arg0)++;
    p1->w0 = 0xBC000404;
    p1->w1 = (u32)1;
    p2 = (*arg0)++;
    p2->w1 = (u32)1;
    p2->w0 = 0xBC000C04;
    p3 = (*arg0)++;
    p3->w0 = 0xBC001404;
    p3->w1 = (u32)0xFFFF;
    p4 = (*arg0)++;
    p4->w1 = (u32)0xFFFF;
    p4->w0 = 0xBC001C04;
}
