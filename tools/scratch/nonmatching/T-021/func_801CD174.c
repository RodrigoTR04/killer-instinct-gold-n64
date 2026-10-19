/* DRAFT. Remaining diff: Stack slots differ: pointer at sp+0x18 instead of 0x1C; output at sp+0x1C instead of 0x20. */
s32 func_8003C750(void *, s32 *);                   /* extern */
extern void func_801CC3BC();
extern u8 D_802D3D30;
extern s32 D_802D3E10;

void func_801CD174(s32 arg0) {

    s32 var_v0;
    void *temp_a0;
    s32 sp20;

    temp_a0 = (arg0 * 0x68) + &D_802D3D30;

    var_v0 = func_8003C750(temp_a0, &sp20);
    if (var_v0 != 0) {
        func_801CC3BC(var_v0, arg0);
        var_v0 = func_8003C750(temp_a0, &sp20);
    }
    if (var_v0 == 0) {
        D_802D3E10 = (s32) (sp20 + 0xFF) >> 8;
    }
}
