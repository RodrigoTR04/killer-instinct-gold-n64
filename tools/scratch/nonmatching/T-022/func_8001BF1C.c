/* T-022 DRAFT: 84 instruction words differ; compiled 336 bytes, original 320 bytes */

s32 guTranslate(s32, s32, s32, f32, s32); /* extern */
extern u8 D_80044A24;
extern f32 D_800489F8;
extern f32 D_800489FC;
extern u8 D_801D7E00;

void func_8001BF1C(u8 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    temp_v0 = (arg2 * 0x30) + &D_801D7E00;
    guTranslate(arg3, (((D_80044A24 * 0x28) + arg2) << 6) + 0x80190000, arg3, (((*(f32 *)((u8 *)(temp_v0) + 0xF4)) * D_800489F8) - D_800489FC) - ((*(f32 *)((u8 *)(temp_v0) + 0x114)) * 500.0f), 0x443FC000);
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    (*(s32 *)((u8 *)(temp_v0_2) + 0)) = 0x01040040;
    (*(s32 *)((u8 *)(temp_v0_2) + 4)) = (s32) ((((D_80044A24 * 0x28) + arg2) << 6) + 0x80190000);
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 8;
    (*(s32 *)((u8 *)(temp_v0_3) + 0)) = 0x06000000;
    (*(s32 *)((u8 *)(temp_v0_3) + 4)) = (s32) *(D_8004A4C0 + (arg1 * 0xC));
    temp_v0_4 = *arg0;
    *arg0 = temp_v0_4 + 8;
    (*(s32 *)((u8 *)(temp_v0_4) + 4)) = 0;
    (*(s32 *)((u8 *)(temp_v0_4) + 0)) = 0xBD000000;
}
