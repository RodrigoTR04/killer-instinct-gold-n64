/* DRAFT. Remaining diff: 4 register-numbering differences only (store address temps t0/t1 here vs t2/t3 in target, in the i<10 / else stores). Instruction sequence identical. */
extern u8 D_80127D58[2][16];

void func_801C8F28(u8 *arg0) {
    u8 i;
    u8 v;
    u64 bits;

    bits = (u64)arg0[0] + ((u64)arg0[1] << 8) + ((u64)arg0[2] << 16) + ((u64)arg0[3] << 24) + ((u64)arg0[4] << 32);
    for (i = 0; i < 20; i++) {
        switch ((s32)(bits >> (i * 2)) & 3) {
            default:
                v = 0;
                break;
            case 3:
                v = 120;
                break;
            case 2:
                v = 55;
                break;
            case 1:
                v = 5;
                break;
        }
        if (i < 10) {
            D_80127D58[0][i] = v;
        } else {
            D_80127D58[1][i - 10] = v;
        }
    }
}
