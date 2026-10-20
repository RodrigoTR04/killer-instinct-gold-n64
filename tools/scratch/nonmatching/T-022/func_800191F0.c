/* T-052 DRAFT: 106 relocation-masked positional words differ; 476/492 bytes. */
extern u8 D_8004AA28; extern f32 D_8004A920[];
extern u8 D_801D3430;
extern u8 D_801D5C30;

void func_800191F0(void) {
    u8 *var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;

    var_v1 = &D_801D3430;
    if (D_8004AA28 == 0) {
        do {
            if ((*(u8 *)((u8 *)(var_v1) + 0)) == 0x3C) {
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(var_v1) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(var_v1) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(var_v1) + 0x54)) + ((*D_8004A920 * 256.0f) / 200.0f));
            }
            temp_v0 = var_v1 + 0x100;
            if ((*(u8 *)((u8 *)(var_v1) + 0x100)) == 0x3C) {
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(temp_v0) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(temp_v0) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0) + 0x54)) + ((*D_8004A920 * 256.0f) / 200.0f));
            }
            temp_v0_2 = var_v1 + 0x200;
            if ((*(u8 *)((u8 *)(var_v1) + 0x200)) == 0x3C) {
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(temp_v0_2) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(temp_v0_2) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0_2) + 0x54)) + ((*D_8004A920 * 256.0f) / 200.0f));
            }
            temp_v0_3 = var_v1 + 0x300;
            if ((*(u8 *)((u8 *)(var_v1) + 0x300)) == 0x3C) {
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(temp_v0_3) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(temp_v0_3) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0_3) + 0x54)) + ((*D_8004A920 * 256.0f) / 200.0f));
            }
            var_v1 += 0x400;
        } while (var_v1 != &D_801D5C30);
    }
}
