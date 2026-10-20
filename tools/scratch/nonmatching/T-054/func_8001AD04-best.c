typedef struct { void *display; s16 flags,pad; s32 transform; } T054Part;
extern void *D_8004A4C0[];
extern f32 D_8004A800[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
extern f32 D_8004A7A0;
/* T-022 DRAFT: 251 instruction words differ; compiled 1100 bytes, original 1072 bytes */

extern f32 D_8004ACE0;
extern f32 D_8004ACE4;
extern void func_8001B50C(s32 arg0);
extern void func_8001BA18(f32 arg0);

extern f32 D_8004ACE0, D_8004ACE4;
s32 func_8002FA5C();    /* extern */
extern f32 D_80048940;
extern f32 D_80048944;
extern f32 D_80048948;
extern f32 D_8004894C;
extern f32 D_80048950;
extern f32 D_80048954;
extern f32 D_80048958;
extern f32 D_8004895C;
extern f32 D_80048960;
extern f32 D_80048964;
extern f32 D_80048968;
extern s32 D_8004A264;
extern s16 D_8004AA2A;

void func_8001AD04(s32 arg0, s32 arg1) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    f32 *sp20;                                      /* compiler-managed */
    f32 *sp1C;
    f32 *sp18;
    f32 *temp_a3;
    f32 *temp_v0;
    f32 *temp_v0_2;
    f32 *temp_v0_3;
    f32 *temp_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 temp_t0;
    s32 temp_t8;

    temp_t8 = ((T054Part *)D_8004A4C0)[arg0].transform;
    temp_t0 = temp_t8 * 4;
    temp_v0 = &D_8004A800[temp_t8];
    sp2C = temp_t8;
    temp_v1 = &(&D_8004A7A0)[temp_t8];
    sp28 = ((T054Part *)D_8004A4C0)[arg1].transform;
    if (D_80048940 < *temp_v0) {
        func_8001B620(0xC);
        return;
    }
    temp_f0 = *temp_v1;
    if (temp_f0 < D_80048944) {
        sp1C = temp_v1;
        func_8002FA5C(D_8004A264, 8, (s32) (((temp_f0 + 2000.0f) * D_80048948) / D_8004894C));
        temp_f0_2 = *temp_v1;
        D_8004AA2A = (s16) (u32) (((temp_f0_2 + 2000.0f) * D_80048950) / D_80048954);
        temp_v0_2 = &(&D_8004A7A0)[sp28];
        *temp_v1 = temp_f0_2 + 30.0f;
        *temp_v0_2 += 30.0f;
        return;
    }
    temp_a3 = &D_8004A8C0[temp_t8];
    if ((*temp_a3 < 360.0f) && (D_8004ACE0 >= 50.0f)) {
        sp20 = temp_v0;
        sp1C = temp_v1;
        sp18 = temp_a3;
        sp24 = temp_t0;
        func_8001BA18(D_80048958);
    } else {
        sp20 = temp_v0;
        sp1C = temp_v1;
        sp18 = temp_a3;
        sp24 = temp_t0;
        func_8001BA18(0.0f);
    }
    if (*temp_v0 > 2000.0f) {
        sp1C = temp_v1;
        func_8002FA5C(D_8004A264, 8, (s32) (((D_8004895C - *temp_v1) * D_80048960) / 4000.0f), sp18);
        D_8004AA2A = (s16) (u32) (((D_80048964 - *temp_v1) * D_80048968) / 4000.0f);
    }
    temp_v0_3 = &D_8004A8C0[sp28];
    *sp18 += D_8004ACE4;
    *temp_v0_3 += D_8004ACE4;
    if (D_8004ACE0 < 50.0f) {
        D_8004ACE0 += 1.0f;
    }
    sp20 = sp28 * 4;
    func_8001B50C(sp2C);
    func_8001B50C(sp28);
    D_8004A920[sp2C] = 0.0f;
    D_8004A920[sp28] = 0.0f;
}
