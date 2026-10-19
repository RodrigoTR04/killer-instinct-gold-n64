/* DRAFT. Remaining diff: 26 positional words; 104/92 bytes. Original uses trapping addi plus private register choices. */
extern u8 D_80066590;
extern s32 D_80066594;
extern u8 *D_8006659C;
s32 func_8003278C(void) {
    s32 remaining = D_80066594 - 1;
    s32 bit = D_80066590 & 1;
    if (remaining != 0) {
        D_80066594 = remaining;
        D_80066590 >>= 1;
        return bit;
    }
    D_80066594 = 8;
    D_8006659C++;
    D_80066590 = D_8006659C[1];
    return bit;
}
