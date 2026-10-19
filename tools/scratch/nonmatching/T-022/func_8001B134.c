/* DRAFT. Remaining diff: 228 linked instruction words; compiled 984 bytes, original 984 bytes. */

extern f32 D_8004A800[];
extern f32 D_8004A8C0[];
extern f32 D_8004ACE0;
extern f32 D_8004ACE4;
extern void func_8001B50C(s32 arg0);
extern void func_8001BA18(f32 arg0);
s32 func_8002FA5C(s32, s32, s32, f32 *);    /* extern */
extern f32 D_8004896C;
extern f32 D_80048970;
extern f32 D_80048974;
extern f32 D_80048978;
extern f32 D_8004897C;
extern f32 D_80048980;
extern f32 D_80048984;
extern f32 D_80048988;
extern f32 D_8004898C;
extern f32 D_80048990;
extern s32 D_8004A264;

extern s16 D_8004AA2A;

void func_8001B134(s32 arg0, s32 arg1) {
    s32 sp2C;
    s32 sp28;
    f32 *sp20;
    f32 *sp1C;
    f32 *sp18;
    f32 *temp_a2;
    f32 *temp_a3;
    f32 *temp_v0_2;
    f32 *temp_v0_3;
    f32 *temp_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 temp_t8;
    s32 temp_v0;

    temp_t8 = (*(s32 *)((u8 *)((D_8004A4C0 + (arg0 * 0xC))) + 8));
    temp_v0 = temp_t8 * 4;
    temp_a2 = temp_v0 + ((u8 *)D_8004A800);
    sp2C = temp_t8;
    temp_v1 = temp_v0 + (u8 *)&D_8004A7A0;
    sp28 = (*(s32 *)((u8 *)((D_8004A4C0 + (arg1 * 0xC))) + 8));
    if (D_8004896C < *temp_a2) {
        func_8001B620(temp_a2, 0xC);
        return;
    }
    temp_f0 = *temp_v1;
    if (temp_f0 < 1000.0f) {
        sp1C = temp_v1;
        func_8002FA5C(D_8004A264, 8, (s32) (((temp_f0 + 2000.0f) * D_80048970) / D_80048974), (f32 *)0xC);
        temp_f0_2 = *temp_v1;
        D_8004AA2A = (s16) (u32) (((temp_f0_2 + 2000.0f) * D_80048978) / D_8004897C);
        temp_v0_2 = (sp28 * 4) + (u8 *)&D_8004A7A0;
        *temp_v1 = temp_f0_2 + 30.0f;
        *temp_v0_2 += 30.0f;
        return;
    }
    temp_a3 = temp_v0 + ((u8 *)D_8004A8C0);
    if (*temp_a3 < 90.0f) {
        sp1C = temp_v1;
        sp20 = temp_a2;
        sp18 = temp_a3;
        func_8001BA18(D_80048980);
    } else {
        sp1C = temp_v1;
        sp20 = temp_a2;
        sp18 = temp_a3;
        func_8001BA18(0.0f);
    }
    if (*temp_a2 > 2000.0f) {
        sp1C = temp_v1;
        func_8002FA5C(D_8004A264, 8, (s32) (((D_80048984 - *temp_v1) * D_80048988) / 4000.0f), sp18);
        D_8004AA2A = (s16) (u32) (((D_8004898C - *temp_v1) * D_80048990) / 4000.0f);
    }
    *sp18 += D_8004ACE4;
    temp_v0_3 = (sp28 * 4) + ((u8 *)D_8004A8C0);
    *temp_v0_3 += D_8004ACE4;
    if (D_8004ACE0 < 50.0f) {
        D_8004ACE0 += 1.0f;
    }
    func_8001B50C(sp2C);
    func_8001B50C(sp28);
}
