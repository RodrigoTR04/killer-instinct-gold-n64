/* DRAFT. Remaining diff: 1 instruction scheduled differently: in the second block target puts 'li t8,1' (changed = 1) after the two argument luis; here it lands in the bne delay slot region first. Everything else matches. */
extern void func_8002B57C(void);
extern s32 func_800344B0();
extern void func_801CBBE0();
extern s32 func_801CC3BC();
s32 osEepromProbe();
extern u8 D_800684E0;
extern u8 D_802D3D30;
extern u8 D_802D3D98;
extern u8 D_802D3E0D;
extern u8 D_802D3E16;

s32 func_801CBF8C(void) {
    s32 ret;
    u8 old;
    u8 changed;

    ret = 0;
    changed = 0;
    old = D_802D3E0D;
    func_801CBBE0(&D_800684E0, &D_802D3E0D);
    D_802D3E16 = osEepromProbe(&D_800684E0);
    if ((D_802D3E0D & 2) && ((old ^ D_802D3E0D) & 2) == 2) {
        ret = func_800344B0(&D_800684E0, &D_802D3D98, 1);
        if (ret != 0) {
            D_802D3E0D ^= 2;
            ret = func_801CC3BC(ret, 1);
        }
        changed = 1;
    }
    if ((D_802D3E0D & 1) && ((old ^ D_802D3E0D) & 1) == 1) {
        changed = 1;
        ret = func_800344B0(&D_800684E0, &D_802D3D30, 0);
        if (ret != 0) {
            D_802D3E0D ^= 1;
            ret = func_801CC3BC(ret, 0);
        }
    }
    if (changed) {
        func_8002B57C();
    }
    return ret;
}
