/* T-022 DRAFT: 65 instruction words differ; compiled 272 bytes, original 248 bytes */


extern u8 D_8004A688;

void func_8001C43C(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    s8 *var_a1;
    s8 *var_t1;
    s8 *var_t3;
    u8 *var_t2;
    u8 *var_t2_2;
    u8 *var_a2;
    u8 *var_t1_2;
    u8 *var_t4;

    var_v0 = 0;
    var_v1 = 0;
    var_t0 = 0;
    if (arg0 > 0) {
        var_t3 = &D_8004A738;
        var_a1 = &D_8004A730;
        var_a2 = arg1;
        var_t4 = arg3;
        do {
            *var_a1 = (s8) *var_a2;
            var_a1 += 1;
            var_t1 = &(&D_8004A5E0)[var_t0];
            var_a3 = 0;
            if ((s32) *var_a2 > 0) {
                var_t2 = var_v1 + (u8 *)arg2;
                do {
                    var_a3 += 1;
                    var_t1 += 7;
                    (*(u8 *)((u8 *)(var_t1) + -7)) = (u8) *var_t2;
                    var_v1 += 1;
                    var_t2 += 1;
                } while (var_a3 < (s32) *var_a2);
                var_a3 = 0;
            }
            *var_t3 = (s8) *var_t4;
            var_a2 += 1;
            var_t3 += 1;
            var_t1_2 = var_t0 + &D_8004A688;
            if ((s32) *var_t4 > 0) {
                var_t2_2 = var_v0 + (u8 *)arg4;
                do {
                    var_a3 += 1;
                    var_t1_2 += 7;
                    (*(u8 *)((u8 *)(var_t1_2) + -7)) = (u8) *var_t2_2;
                    var_v0 += 1;
                    var_t2_2 += 1;
                } while (var_a3 < (s32) *var_t4);
            }
            var_t0 += 1;
            var_t4 += 1;
        } while (var_t0 != arg0);
    }
}
