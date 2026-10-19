/* DRAFT. Remaining diff: Four byte-store offsets/order differ; loop and registers match in closest draft. */
extern u8 D_80127D58[];
void func_801C8668(u8 arg0) {
    s32 i;
    for (i = 0; i < 16; i++) {
        D_80127D58[i + arg0 * 16] = 0;
    }
}
