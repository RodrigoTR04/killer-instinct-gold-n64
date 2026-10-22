/* T-133 DRAFT: 24 differing words, 232/236 B in full TU.
 * Declaration order and line joins affect IDO allocation; see T-133/REPORT.md. */
#include "frontend.h"
extern void func_801C7F90();

extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];

void func_801C8004(void)
    {
    int step;
    u8 var_a1;
    s32 var_a0;
    s32 var_a2;
    s32 var_t1; u8 *var_a3; u8 *var_t2;
    u8 *var_v0;
    s32 temp_v0;
    u8 temp_v1;
 var_t1 = 0;
    var_v0 = D_80292710[0];
    step = 1; var_a0 = 0; for (;;) {
    temp_v1 = *var_v0; if ((temp_v1 != 0) && (((s32) temp_v1) >= ((s32) D_802926F8[0][var_a0]))) { var_t1 = step; } var_a0 += step; var_v0 += step; if (var_a0 >= 34) { break;
    } } var_t2 = (u8 *) D_80127C68; do { var_a1 = 0; var_a2 = 0; var_a3 = var_t2;
    nextButton:
    temp_v0 = *var_a3; var_a2 += step; var_a3 += step; if ((((s32) temp_v0) >= 8) || ((1 << temp_v0) & var_a1)) { var_t1 = 2;
    } var_a1 = (var_a1 | (1 << temp_v0)) & 0xFF; if (var_a2 != 6) {
    goto nextButton; }
    var_t2 += 6; } while (var_t2 != (&D_80127C74)); if (var_t1 != 0) { func_801C7F90(); } }
