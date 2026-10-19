/* DRAFT. Remaining diff: Live call argument/stack handling and temporary registers differ. */
extern void func_801BED0C();
extern s32 D_80127CFC[];
extern u8 D_80127D30;
extern u8 D_80127D31;
extern s32 D_802D3800;
extern s32 D_802D3804;

extern s32 D_802D3808, D_802D380C;
void func_801CB998(u8 arg0, s32 arg1) {
    s32 sp1C;
    s32 temp_t6;
    s32 var_v0;

    temp_t6 = arg0;
    var_v0 = temp_t6;
    if (temp_t6 & 1) {
        sp1C = temp_t6;
        func_801BED0C(D_80127CFC[D_80127D30], arg1, D_802D3800, D_802D3804);
        var_v0 = sp1C;
    }
    if (var_v0 & 2) {
        func_801BED0C(D_80127CFC[D_80127D31], arg1, D_802D3808, D_802D380C);
    }
}
