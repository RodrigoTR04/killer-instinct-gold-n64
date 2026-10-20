/* DRAFT (T-047). See T-047/REPORT.md for comparison counts and remaining differences. */
extern s32 guRandom(void);
extern u8 D_802C8C2A;
extern s32 D_802C8C18[];
extern s8 D_8004EA9C[];
extern s32 D_802C8C08[];
extern s8 D_802C8C28[];
extern void func_801B465C(u8, s32);
void func_801B5534(s32 arg0) {
    s32 index;
    s32 choice;
    choice = guRandom() % (s32)D_802C8C2A;
    index = arg0 * 4;
    *(s32 *)((u8 *)D_802C8C18 + index) = choice;
    D_8004EA9C[arg0] = choice;
    func_801B465C(arg0, 0);
    *(s32 *)((u8 *)D_802C8C08 + index) = 4;
    D_802C8C28[arg0] = 1;
}
