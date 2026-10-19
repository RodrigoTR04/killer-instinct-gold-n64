/* DRAFT. Remaining diff: Compile blocked by unresolved types/prototypes: extern u8 D_80127C68; */
extern void func_801C7F90();
extern u8 D_80127C68;
extern u8 D_80127C74;
extern s32 D_802926F8;
extern u8 *D_80292710;

void func_801C8004(void) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_t1;
    s32 var_v1;
    u8 *var_a3;
    u8 *var_t2;
    u8 *var_v0;
    u8 temp_v0;
    u8 temp_v1;

    var_t1 = 0;
    var_v0 = D_80292710;
    var_a0 = 0;
    do {
        temp_v1 = *var_v0;
        if ((temp_v1 != 0) && ((s32) temp_v1 >= (s32) *(u8 *)(D_802926F8 + var_a0))) {
            var_t1 = 1;
        }
        var_a0 += 1;
        var_v0 += 1;
    } while (var_a0 < 0x22);
    var_t2 = &D_80127C68;
    do {
        var_a1 = 0;
        var_a2 = 0;
        var_a3 = var_t2;
loop_7:
        temp_v0 = *var_a3;
        var_a2 += 1;
        var_a3 += 1;
        if (((s32) temp_v0 >= 8) || (var_v1 = 1 << temp_v0, ((var_v1 & var_a1) != 0))) {
            var_v1 = 1 << temp_v0;
            var_t1 = 2;
        }
        var_a1 = (var_a1 | var_v1) & 0xFF;
        if (var_a2 != 6) {
            goto loop_7;
        }
        var_t2 += 6;
    } while (var_t2 != &D_80127C74);
    if (var_t1 != 0) {
        func_801C7F90(var_a1, var_a1, var_a2, var_a3);
    }
}
