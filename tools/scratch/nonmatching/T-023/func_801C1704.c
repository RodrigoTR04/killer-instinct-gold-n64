/* DRAFT. Remaining diff: Multiply versus shift/subtract address calculation; clear-loop unrolling and stores differ. */
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[], D_80128310[], D_80128328[];
void func_801C1704(u8 player) {
    s32 i, index;
    u8 *a, *b;
    index = player & 255;
    D_80128308[index] = 0;
    D_8012830A[index] = 0;
    a = D_80128310 + index * 11;
    b = D_80128328 + index * 11;
    for (i = 0; i < 11; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    D_80127C30[index] = 100;
}
