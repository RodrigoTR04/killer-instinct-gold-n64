/* DRAFT. Remaining diff: 3 words (T-040; was 6): 'sw zero' to D_800669A8 is scheduled before the li s0/s2 loop setup in the original; 116/116 bytes. */
extern s32 D_800669A8, D_800669AC, D_800669B0;
extern s32 func_8003278C(void);
void func_8002A1E0(void) {
    s32 i; D_800669A8 = 0; for (i = 1; i <= 16; i++) { D_800669A8 = (D_800669A8 << 1) + func_8003278C(); } D_800669AC = 0; D_800669B0 = 0xFFFF;
}
