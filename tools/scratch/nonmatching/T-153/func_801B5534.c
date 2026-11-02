extern s32 guRandom(void);
extern u8 D_802C8C2A;
extern s32 D_802C8C18[];
extern s8 D_8004EA9C[];
extern s32 D_802C8C08[];
extern s8 D_802C8C28[];
extern void func_801B465C(s32, s32);
void func_801B5534(u8 arg0) {
    s32 sample;
    sample = guRandom();
    D_802C8C18[arg0] = sample % (s32)D_802C8C2A;
    D_8004EA9C[arg0] = sample % (s32)D_802C8C2A;
    func_801B465C(arg0, 0);
    D_802C8C08[arg0] = 4;
    D_802C8C28[arg0] = 1;
}
