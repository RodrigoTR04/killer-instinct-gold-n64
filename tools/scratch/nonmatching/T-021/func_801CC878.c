/* DRAFT. Remaining diff: Compile blocked by unresolved types/prototypes: s32 func_801CC668(?); */
extern void func_801C7A98();
extern void func_801C8A38();
s32 func_801CC668(?);                               /* extern */
extern u8 D_80127D58;
extern u8 D_80295664;
extern u8 D_802D3A30;
extern u8 D_802D3A90;
extern u8 D_802D3AA0;
extern s32 D_802D3E04;

void func_801CC878(void) {
    u8 *var_v0;
    u8 *var_v1;
    s32 temp_t1;
    s32 temp_t5;

    if (func_801CC668(1) == 0) {
        D_802D3E04 = (s32)&D_80295664;
        var_v0 = &D_802D3A30;
        var_v1 = &D_80127D58;
        do {
            temp_t5 = *(s32 *)(var_v0+0x1C);
            temp_t1 = *(s32 *)(var_v0+0x14);
            var_v0 += 0x20;
            var_v1[17] = (s8) temp_t5;
            var_v1[16] = (s8) temp_t1;
            var_v1 += 4;
            var_v1[14] = (s8) *(s32 *)(var_v0+4);
            var_v1[15] = (s8) *(s32 *)(var_v0+12);
        } while (var_v0 != &D_802D3A90);
        func_801C8A38(&D_802D3AA0, 1);
        func_801C7A98();
    }
}
