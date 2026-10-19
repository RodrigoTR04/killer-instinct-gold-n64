/* DRAFT. Remaining diff: Compile blocked by unresolved types/prototypes: ? sp36; */
extern s32 func_8002F6F4();
s32 func_80035F10(void *, s32, u8 *, s32);           /* extern */
extern s32 func_800361C0();
extern u8 D_8004A25C;
extern s32 D_80066C40;
extern u8 D_802D3D30;

void func_801CD078(s32 arg0, s32 arg1) {
    ? sp36;
    ? sp32;
    ? sp28;
    void *sp20;
    void *temp_a0;

    temp_a0 = (arg1 * 0x68) + &D_802D3D30;
    sp20 = temp_a0;
    if (func_80035F10(temp_a0, arg0, &sp28, arg1) == 0) {
        func_800361C0(sp20, sp30, sp2C, &sp36, &sp32);
        func_8002F6F4(D_80066C40, 0x10A, &D_8004A25C);
    }
}
