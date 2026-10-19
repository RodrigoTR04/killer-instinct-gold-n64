/* DRAFT. Remaining diff: Same instruction count; global-base/value registers and scheduling differ. */
extern void func_8002B6EC(void);
extern s32 D_800684A0;
extern s32 D_80282A60;
extern u8 D_802D3698, D_802D3699, D_802D369C[];
u8 func_801BD200(s32 arg0) {
    D_80282A60 = D_800684A0;
    D_802D369C[0] = 0;
    D_802D369C[1] = 1;
    if (arg0 < D_800684A0) D_80282A60 = arg0;
    func_8002B6EC();
    D_802D3699 = 1;
    D_802D3698 = 1;
    return ((u8 *)&D_80282A60)[3];
}
