/* T-022 DRAFT: 177 instruction words differ; compiled 756 bytes, original 764 bytes */
typedef struct {
    s32 unk0; void *data; s16 halfWidth, halfHeight, width, height, width2, height2;
    u8 pad[4]; s16 flags; u8 pad2[2];
} T022Sprite;

extern T022Sprite D_8004CED0[];
extern u8 D_80044A24;
extern u8 D_8004EAA4;
extern s32 D_8004EAA8;
extern u8 *D_8004EAAC;
extern s32 D_8004EAB0;
extern u8 *D_8004EAB4;
extern u8 D_8004EABC;
extern u8 D_8004EAC0;
extern u8 D_800CA610;
extern u8 D_800E4650;
extern u8 D_800F1670;
extern u8 D_800F1A70;
extern u8 D_800F1C70;
extern u8 D_800F4070;
extern u8 D_8010C670;
extern u8 D_8011ECB0;
extern u8 D_80126D30;
extern u8 D_80350000;
extern u8 D_8035E100;

void func_8001D080(void) {
    T022Sprite *temp_a1;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v1_2;
    u8 temp_t9;
    u8 temp_t9_2;
    u8 *temp_a3;
    u8 *temp_t0;
    u8 *temp_t1;
    u8 *temp_v1;

    temp_a1 = &D_8004CED0[D_8004EAA4];
    temp_t8 = temp_a1->unk0;
    D_8004EAB0 = temp_t8;
    D_8004EAB4 = temp_a1->data;
    temp_a1->unk0 = D_8004EAA8;
    temp_a1->data = D_8004EAAC;
    D_8004EAA8 = temp_t8;
    D_8004EAAC = D_8004EAB4;
    temp_a3 = (D_80044A24 * 0xC300) + &D_800F4070;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x58)) = (u8 *) (temp_a3 + 0x6180);
    temp_v1 = (D_80044A24 * 0x9000) + &D_8010C670;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x234)) = (u8 *) (temp_v1 + 0x3000);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x218)) = (u8 *) (temp_v1 + 0x1800);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x250)) = (u8 *) (temp_v1 + 0x4800);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x288)) = (u8 *) (temp_v1 + 0x7800);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x26C)) = (u8 *) (temp_v1 + 0x6000);
    temp_t0 = (D_80044A24 * 0xD020) + &D_800CA610;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x2BC)) = (u8 *) (temp_t0 + 0x6810);
    temp_t1 = (D_80044A24 * 0x6810) + &D_800E4650;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x2C0)) = (u8 *) (temp_t1 + 0x3408);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x138)) = (u8 *) ((D_80044A24 * 0x3C80) + &D_8011ECB0);
    temp_t9 = D_8004EAC0 ^ 1;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x1C4)) = (u8 *) ((D_80044A24 * 0x780) + &D_80126D30);
    temp_t6 = (temp_t9 & 0xFF) * 0x17BB0;
    D_8004EAC0 = temp_t9;
    (*(s32 *)((u8 *)(D_8004CED0) + 0x2D8)) = (s32) (temp_t6 + 0x80254860);
    (*(s32 *)((u8 *)(D_8004CED0) + 0x2DC)) = (s32) (temp_t6 + 0x80264580);
    (*(s32 *)((u8 *)(D_8004CED0) + 0x2F4)) = (s32) (temp_t6 + 0x80320E20);
    (*(s32 *)((u8 *)(D_8004CED0) + 0x2F8)) = (s32) (temp_t6 + 0x80330B40);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x368)) = (u8 *) ((D_80044A24 * 0x1200) + &D_800F1C70);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x3C)) = temp_a3;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x1FC)) = temp_v1;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x2A0)) = temp_t0;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x2A4)) = temp_t1;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x310)) = (u8 *) ((D_80044A24 << 9) + &D_800F1670);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x314)) = (u8 *) ((D_80044A24 << 8) + &D_800F1A70);
    if (D_8004AC88 == 0xC) {
        temp_t9_2 = D_8004EABC ^ 1;
        temp_v1_2 = temp_t9_2 & 0xFF;
        D_8004EABC = temp_t9_2;
        (*(u8 **)((u8 *)(D_8004CED0) + 0x380)) = (u8 *) ((temp_v1_2 * 0x7080) + &D_80350000);
        (*(u8 **)((u8 *)(D_8004CED0) + 0x384)) = (u8 *) ((temp_v1_2 * 0x3840) + &D_8035E100);
        return;
    }
    if (D_8004AC88 == 7) {
        (*(u8 **)((u8 *)(D_8004CED0) + 0x380)) = 0;
        (*(u8 **)((u8 *)(D_8004CED0) + 0x384)) = (u8 *) ((D_80044A24 * 0x4800) + 0x801A3000);
    }
}
