/* T-132 DRAFT: 394 differing words; see T-132/REPORT.md. */
typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite24C;
typedef struct { s16 halfW,halfH,w,h; } T032Size24C;
extern T032Sprite24C D_8004CED0[];
extern u8 *D_8004CED4;
extern u8 *D_800612D8[];
extern T032Size24C D_80061368[];
extern u8 D_80047BF0[],D_80047C38[],D_8F6AE0[],D_8F9FA0[];
extern u8 D_8004F3A0[],D_8004FE40[],D_800508E0[],D_80051D80[],D_80053220[],D_80053748[],D_80053C70[],D_80054198[],D_80054458[],D_80058478[],D_800587B8[],D_80058D58[],D_800590B8[],D_80059668[],D_80059CF8[],D_8005A388[],D_8005AEC8[],D_8005AFB8[],D_8005E3F8[];
extern s8 D_80061496;
extern s32 D_8004EA78;
extern void boot_dma(void *,void *,s32),func_800238C4(u8 *,void *),func_800268C0(u8 *,s32,void *,u8);
extern s32 boot_inflate(void *,void *,void *);
#define T032_LE24C(p) ((p)[0]+((p)[1]<<8)+((p)[2]<<16)+((p)[3]<<24))
#define T032_BE24C(p) ((p)[3]+((p)[0]<<24)+((p)[1]<<16)+((p)[2]<<8))
void func_80024CE0(void)
{
    s32 sp40;
    u8 *sp38;
    u8 *var_s1_2;
    T032Size24C *var_v0;
    u8 **var_v1;
    s32 temp_a2;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    u8 *var_s2_2;
    u8 temp_s1;
    T032Sprite24C *temp_s0;
    T032Sprite24C *temp_s0_2;
    T032Sprite24C *temp_s0_3;
    T032Sprite24C *temp_s0_4;
    T032Sprite24C *temp_s0_5;
    T032Sprite24C *temp_s0_6;
    T032Sprite24C *temp_s0_7;
    u8 *temp_s3;
    u8 *temp_s3_2;
    u8 *temp_s3_3;
    u8 *temp_s3_4;
    u8 *temp_s3_5;
    u8 *temp_s5;
    u8 *var_s0;
    u8 *var_s2;

    temp_a2 = D_8F9FA0 - D_8F6AE0;
    D_80061496 = 0;
    sp40 = temp_a2;
    boot_dma(D_8F6AE0, (void *)0x802D4000, temp_a2);
    var_s0 = (u8 *)0x802D4000;
    temp_s5 = (u8 *)(sp40 + 0x802D4000);
    var_s2 = temp_s5;
    sp38 = temp_s5;
    var_s1 = 0;
    do {
        var_s1 += 1;
        var_s2 += boot_inflate(var_s0 + 4, var_s2, (void *)0x803A2000);
        var_s0 += var_s0[0x3] + (var_s0[0x0] << 0x18) + (var_s0[0x1] << 0x10) + (var_s0[0x2] << 8);
    } while (var_s1 != 6);
    temp_s0 = &D_8004CED0[4];
    D_8004EA78 = 4;
    temp_s0->pixels = (u16 *)D_800508E0;
    temp_s0->alpha = D_8004F3A0;
    func_800238C4((u8 *)((sp38[0xB] << 0x18) + sp40 + sp38[0x8] + (sp38[0x9] << 8) + (sp38[0xA] << 0x10) + 0x802D4000), D_80047C38);
    temp_s0_2 = &D_8004CED0[5];
    D_8004EA78 = 5;
    temp_s0_2->pixels = (u16 *)D_80051D80;
    temp_s0_2->alpha = D_8004FE40;
    func_800238C4((temp_s5[0xF] << 0x18) + temp_s5 + temp_s5[0xC] + (temp_s5[0xD] << 8) + (temp_s5[0xE] << 0x10), D_80047C38);
    D_8004EA78 = 0xC;
    temp_s3 = (temp_s5[0x7] << 0x18) + temp_s5 + temp_s5[0x4] + (temp_s5[0x5] << 8) + (temp_s5[0x6] << 0x10);
    var_v1 = D_800612D8;
    var_v0 = D_80061368;
    D_8004CED0[12].alpha = sp38;
    do {
        var_v1++;
        var_v0++;
        var_v0[-1].halfW = 0;
        var_v0[-1].halfH = 0;
        var_v0[-1].w = 0x10;
        var_v0[-1].h = 1;
        var_v1[-1] = D_80054458;
    } while ((u32) var_v1 < (u32) D_80061368);
    var_s2_2 = D_80047BF0;
    var_s0_2 = 0;
    do {
        temp_s1 = *var_s2_2;
        if ((temp_s1 != 0) || (var_s0_2 == 0)) {
            func_800268C0(temp_s3, var_s0_2, D_80054458 + (temp_s1 * 0x360), temp_s1);
        }
        var_s0_2 += 1;
        var_s2_2 += 1;
    } while (var_s0_2 < 0x1A);
    temp_s3_2 = (temp_s3[0x7] << 0x18) + temp_s3 + temp_s3[0x4] + (temp_s3[0x5] << 8) + (temp_s3[0x6] << 0x10);
    var_s1_2 = D_8005A388;
    var_s0_3 = 0;
    do {
        func_800268C0(temp_s3_2, var_s0_3, var_s1_2, var_s0_3 + 0x13);
        var_s0_3 += 1;
        var_s1_2 += 0x120;
    } while (var_s0_3 != 0xA);
    func_800268C0(temp_s3_2, 0xA, D_80058478, 0x1DU);
    func_800268C0(temp_s3_2, 0xB, D_8005AEC8, 0x1EU);
    temp_s3_3 = (temp_s3_2[0x7] << 0x18) + temp_s3_2 + temp_s3_2[0x4] + (temp_s3_2[0x5] << 8) + (temp_s3_2[0x6] << 0x10);
    func_800268C0(temp_s3_3, 0, D_800587B8, 0x1FU);
    func_800268C0(temp_s3_3, 1, D_80058D58, 0x20U);
    func_800268C0(temp_s3_3, 2, D_800590B8, 0x21U);
    func_800268C0(temp_s3_3, 4, D_80059668, 0x22U);
    func_800268C0(temp_s3_3, 5, D_80059CF8, 0x23U);
    temp_s0_3 = &D_8004CED0[0xC];
    temp_s3_4 = (temp_s3_3[0x7] << 0x18) + temp_s3_3 + temp_s3_3[0x4] + (temp_s3_3[0x5] << 8) + (temp_s3_3[0x6] << 0x10);
    D_8004EA78 = 0xC;
    temp_s0_3->pixels = (u16 *)D_80053220;
    temp_s0_3->alpha = D_80054198;
    func_800238C4((temp_s3_4[0xB] << 0x18) + temp_s3_4 + temp_s3_4[0x8] + (temp_s3_4[0x9] << 8) + (temp_s3_4[0xA] << 0x10), D_80047C38);
    temp_s0_4 = &D_8004CED0[0xD];
    D_8004EA78 = 0xD;
    temp_s0_4->pixels = (u16 *)D_80053748;
    temp_s0_4->alpha = D_80054198;
    func_800238C4((temp_s3_4[0xF] << 0x18) + temp_s3_4 + temp_s3_4[0xC] + (temp_s3_4[0xD] << 8) + (temp_s3_4[0xE] << 0x10), D_80047C38);
    temp_s0_5 = &D_8004CED0[0xE];
    D_8004EA78 = 0xE;
    temp_s0_5->pixels = (u16 *)D_80053C70;
    temp_s0_5->alpha = D_80054198;
    func_800238C4((temp_s3_4[0x13] << 0x18) + temp_s3_4 + temp_s3_4[0x10] + (temp_s3_4[0x11] << 8) + (temp_s3_4[0x12] << 0x10), D_80047C38);
    temp_s0_6 = &D_8004CED0[0x1E];
    temp_s3_5 = (temp_s3_4[0x7] << 0x18) + temp_s3_4 + temp_s3_4[0x4] + (temp_s3_4[0x5] << 8) + (temp_s3_4[0x6] << 0x10);
    D_8004EA78 = 0x1E;
    temp_s0_6->pixels = (u16 *)D_8005E3F8;
    temp_s0_6->alpha = 0;
    func_800238C4((temp_s3_5[0x1F] << 0x18) + temp_s3_5 + temp_s3_5[0x1C] + (temp_s3_5[0x1D] << 8) + (temp_s3_5[0x1E] << 0x10), D_80047C38);
    temp_s0_7 = &D_8004CED0[0x1D];
    D_8004EA78 = 0x1D;
    temp_s0_7->pixels = (u16 *)D_8005AFB8;
    temp_s0_7->alpha = 0;
    func_800238C4((temp_s3_5[0xB] << 0x18) + temp_s3_5 + temp_s3_5[0x8] + (temp_s3_5[0x9] << 8) + (temp_s3_5[0xA] << 0x10), D_80047C38);
}
