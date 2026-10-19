/* DRAFT. Remaining diff: Texture-swap condition/control flow, float temporaries and display-list/call scheduling differ. */
typedef struct { u32 w0, w1; } T025GfxFAA4;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern void *memcpy(void *, void *, u32);
extern void func_80030220(void *, void *, s32);
extern void func_8003037C(void *, void *, s32);
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_801D2E48[];
extern u8 D_801D2EA8;
extern f32 D_80292888;
extern f32 D_8029288C;
extern f32 D_80292890;
extern f32 D_80292894;
extern f32 D_80292898;
extern f32 D_8029289C;
extern f32 D_802928A0;
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern s32 D_8029571C;
extern u8 D_8029E800[];
extern u8 D_8029EB00[];
extern u8 D_8029EDD0[];
extern u8 D_8029EEC0[];
extern u8 D_8029EF80[];
extern u8 D_802C8340[];
extern f32 D_802C8728;
extern u8 D_802C872C[];

s32 func_801AFAA4(T025GfxFAA4 **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    s32 sp1EC;
    u8 sp128[0xC0];
    u8 sp38[0xF0];
    u32 sp24;
    f32 angle;
    T025GfxFAA4 *temp_v1;
    T025GfxFAA4 *temp_v1_2;
    T025GfxFAA4 *temp_v1_3;
    T025GfxFAA4 *var_v1;
    s32 temp_f8;
    s32 temp_t2;
    u32 temp_v0;

    sp1EC = 0xFF;
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0x06000000;
    temp_v1->w1 = (u32)&D_801D2E48;
    if (arg3 < 0x97U) {
        angle = (f32) ((f64) ((s32) ((s32) func_801AFA80(540.0f, D_80292888, arg3, (arg3 * 5) + 0x96) * 0x10) % 5760) * 0.0625);
        if (((D_802C872C[0] != 0) || !(angle > 120.0f) || (D_802C8728 = angle, !(angle < D_8029288C))) && ((D_802C872C[0] == 0) || (D_802C8728 = angle, !(angle < 120.0f)))) {
            if (D_80292890 < angle) {
                D_802C8728 = angle;
                goto block_8;
            }
        } else {
block_8:
            memcpy(&sp128, &D_8029EEC0, 0xC0);
            memcpy(&D_8029EEC0, &D_8029EF80, 0xC0);
            memcpy(&D_8029EF80, &sp128, 0xC0);
            D_802C872C[0] = (u8) (D_802C872C[0] ^ 1);
            angle = D_802C8728;
        }
        if (((D_802C872C[1] == 0) && (D_80292894 < angle) && (D_802C8728 = angle, (angle < D_80292898))) || ((D_802C872C[1] != 0) && (D_802C8728 = angle, (angle < D_8029289C))) || (D_802C8728 = angle, (D_802928A0 < angle))) {
            memcpy(&sp38, &D_8029EB00, 0xF0);
            memcpy(&D_8029EB00, &D_8029EDD0, 0xF0);
            memcpy(&D_8029EDD0, &sp38, 0xF0);
            D_802C872C[1] = (u8) (D_802C872C[1] ^ 1);
        }
        D_8029571C = 2;
        if (arg3 < 0x4BU) {
            sp1EC = (s32) func_801AFA80(50.0f, 255.0f, arg3, 0x4B);
        }
        D_801D2EA8 = 0;
        var_v1 = *arg0;
        *arg0 = var_v1 + 1;
        var_v1->w1 = 0x552048;
    } else {
        if (D_801D2EA8 == 0) {
            D_801D2EA8 = 1;
            func_80030220(&D_8029E800, &D_802C8340, 0xF9);
            D_802956F8 = 0x110;
            D_802956FC = 0x110;
            D_80295700 = 0x110;
            func_8002F6F4(D_80066C40, 8, &D_8004A258);
        }
        if (D_802956F8 >= 0x10) {
            D_80295700 -= 0x10;
            D_802956FC -= 0x10;
            D_802956F8 -= 0x10;
        } else {
            D_80295700 = 0;
            D_802956FC = 0;
            D_802956F8 = 0;
        }
        func_8003037C(&D_8029E800, &D_802C8340, 0xF9);
        temp_v0 = arg3 - 0x96;
        sp24 = temp_v0;
        temp_f8 = (s32) func_801AFA80(255.0f, 10.0f, temp_v0, 0x36);
        sp1EC = temp_f8;
        if (temp_f8 < 0x64) {
            func_801AF5D4(4);
        }
        if ((sp1EC < 0xA) && (sp24 >= 0x36U)) {
            func_801AF5EC(1);
            sp1EC = 0;
        }
        temp_v1_2 = *arg0;
        *arg0 = temp_v1_2 + 1;
        temp_v1_2->w1 = 0x2000;
        temp_v1_2->w0 = 0xB6000000;
        var_v1 = *arg0;
        *arg0 = var_v1 + 1;
        var_v1->w1 = 0x504240;
    }
    var_v1->w0 = 0xB900031D;
    guRotate(arg2, 30.0f, 1.0f, 0.0f, 0.0f);
    guRotate(arg2 + 0x40, D_802C8728, 0.0f, 1.0f, 0.0f);
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3->w0 = 0xFB000000;
    temp_t2 = (0xFF - sp1EC) & 0xFF;
    temp_v1_3->w1 = (s32) ((temp_t2 << 0x18) | (temp_t2 << 0x10) | (temp_t2 << 8) | (sp1EC & 0xFF));
    return 2;
}
