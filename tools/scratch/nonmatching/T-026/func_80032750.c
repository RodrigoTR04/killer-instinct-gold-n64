/* DRAFT. Remaining diff: 15 positional words; 44/60 bytes. Original materializes each global address and uses hand-assigned temporary registers. */
extern u8 D_80066590;
extern s32 D_80066594, D_80066598;
extern u8 *D_8006659C;
void func_80032750(u8 *stream) {
    D_80066594 = 8;
    D_80066598 = 8;
    D_8006659C = stream;
    D_80066590 = *stream;
}
