/* T-133 fresh m2c draft: 497 differing words, 2076/2108 B in prefix context.
 * Full TU blocked by the later D_8004D278 view; see T-133/REPORT.md. */
#ifndef T032_ROM_ENTRY_DEFINED
#define T032_ROM_ENTRY_DEFINED
typedef struct
{
    u8 *start, *end, *palette;
    u8 *spriteStart, *spriteEnd;
    u8 tail[12];
}
T032RomEntry;
#endif
typedef struct
{
    u8 *first,*second;
}
T032Cache20E;
extern T032RomEntry D_80045E50[];
extern T032Cache20E D_8004D278[][3];
extern u8 D_A94460[],D_A94560[],D_A94D80[],D_119F0[],D_13200[];
extern u8 D_80045D8C[][14],D_80063C60[],D_80064C60[];
extern u16 D_800460D4[];
extern u16 *D_800460E0[],*D_800460E8[],*D_800460F0[],*D_800460F8[];
extern u8 **D_800460D8[];
extern s32 D_8004EA78;
extern void boot_dma_chunked(void *,void *,s32),func_800238C4(u8 *,void *);
void func_80020E98(u8 arg0, u8 arg1, u8 *arg2) {
    s32 temp_at;
    T032RomEntry *sp58;
    T022Sprite *temp_a0_2; u32 temp_a3_2;
    u8 *sp74, *var_a3_2;
    s32 decoded; T032Cache20E *temp_v1;
    s32 temp_t1_3, temp_t1_2;
    u16 **sp44;
    u8 *temp_a3;
    s32 var_s5, var_v1_2;
    T032Cache20E *var_s3_2;
    u16 sp7C;
    u8 *temp_v0_2, *sp70;
    T032Cache20E *temp_v0_3;
    s32 temp_at_3, var_v1, var_s5_3;
    u16 **temp_fp, var_a2;
    s32 var_a1, temp_at_2, temp_t5_2, var_s0;
    u8 *var_s3, *var_a3;
    s32 temp_t5, temp_t3_2, temp_t3; T022Sprite *temp_a0;
    s32 sp5C;
    u8 *var_s4_2;
    s32 var_s5_2;
    T022Sprite *temp_a0_3;
    s32 var_a0;
    u16 *temp_t1;
    u8 *temp_s3;
    s32 temp_a1;
    u8 *var_s4;
    T032Cache20E *temp_v0_4;
    u8 *sp6C;
    T032RomEntry *temp_v0;
    u8 *sp84;
    u16 **temp_s7;
    if (arg2 == 0) {
        sp5C = (s32) arg0;
        if (arg0 == 0) {
            sp6C = (u8 *)0x8020B480;
        } else if (sp5C == 1) {
            sp6C = (u8 *)0x802D7A40;
        } else { sp6C = (u8 *)0x801EE000;
        }
    } else {
        sp6C = arg2;
        sp5C = (s32) arg0;
    }
    temp_v0 = &D_80045E50[arg1];
    temp_a3 = temp_v0->start;
    sp70 = temp_v0->end;
    if (sp5C == 2) { sp58 = temp_v0;
        sp74 = temp_a3;
        boot_dma_chunked(D_A94460, (u8 *)0x802D4000, D_A94560 - D_A94460); boot_dma_chunked(D_A94560, (u8 *)0x802D4100, D_A94D80 - D_A94560); D_8004EA78 = 0xF;
        var_s4 = (u8 *)0x802D4100;
        var_a2 = 0;
        temp_a0 = &D_8004CED0[0xF];
        temp_a0->unk0 = 0x80206000;
        temp_a0->data = 0;
        var_s5 = 0;
        do
    {
            var_a3 = 0;
            var_a1 = (((u8 *)var_s4)[3] << 8) + ((u8 *)var_s4)[2];
            var_v1 = 0;
            if (var_a1 > 0) {
                do {
                    temp_v0_2 = (var_v1 * 4) + var_s4;
                    temp_s3 = (((u8 *)temp_v0_2)[11] << 0x18) + var_s4 + ((u8 *)temp_v0_2)[8] + (((u8 *)temp_v0_2)[9] << 8) + (((u8 *)temp_v0_2)[10] << 0x10);
                    if ((temp_s3 != var_a3) && ((u32) temp_s3 < (u32) ((((u8 *)var_s4)[7] << 0x18) + var_s4 + ((u8 *)var_s4)[4] + (((u8 *)var_s4)[5] << 8) + (((u8 *)var_s4)[6] << 0x10)))) {
                        D_800460D8[var_a2][var_s5] = (u8 *) D_8004CED0[D_8004EA78].unk0;
                        sp44 = &D_800460F8[var_a2];
                        sp84 = temp_s3;
                        sp7C = var_a2;
                        temp_fp = &D_800460F0[var_a2];
                        temp_s7 = &D_800460E8[var_a2];
                        func_800238C4(temp_s3, (u8 *)0x802D4000);
                        temp_t1 = D_800460E0[var_a2];
                        var_a3 = sp84;
                        temp_t1[var_s5] = (u16) D_8004CED0[D_8004EA78].width2;
                        (*temp_s7)[var_s5] = (u16) D_8004CED0[D_8004EA78].height;
                        (*temp_fp)[var_s5] = (u16) D_8004CED0[D_8004EA78].halfWidth;
                        (*sp44)[var_s5] = (u16) D_8004CED0[D_8004EA78].halfHeight;
                        temp_a0_2 = &D_8004CED0[D_8004EA78];
                        temp_a0_2->unk0 += temp_a0_2->width2 * temp_a0_2->height * 2;
                        var_a1 = (((u8 *)var_s4)[3] << 8) + ((u8 *)var_s4)[2];
                    } else if (var_v1 < (s32) D_800460D4[var_a2]) {
                        temp_a0_3 = &D_8004CED0[D_8004EA78]; D_800460D8[var_a2][var_s5] = (u8 *)temp_a0_3->unk0 - (temp_a0_3->height * temp_a0_3->width2 * 2); D_800460E0[var_a2][var_s5] = (u16) D_8004CED0[D_8004EA78].width2;
                        D_800460E8[var_a2][var_s5] = (u16) D_8004CED0[D_8004EA78].height;
                        D_800460F0[var_a2][var_s5] = (u16) D_8004CED0[D_8004EA78].halfWidth;
                        D_800460F8[var_a2][var_s5] = (u16) D_8004CED0[D_8004EA78].halfHeight;
                        var_a1 = (((u8 *)var_s4)[3] << 8) + ((u8 *)var_s4)[2];
                    }
                    var_v1 = (var_s5 + 1) & 0xFFFF;
                    var_s5 = var_v1; } while (var_v1 < var_a1);
                var_s5 = 0;
            }
            temp_t5 = (var_a2 + 1) & 0xFFFF;
            temp_at = temp_t5 < 2;
            var_a2 = (u16) temp_t5;
            var_s4 = (((u8 *)var_s4)[7] << 0x18) + var_s4 + ((u8 *)var_s4)[4] + (((u8 *)var_s4)[5] << 8) + (((u8 *)var_s4)[6] << 0x10);
        } while (temp_at != 0);
        boot_dma_chunked(sp74, (u8 *)0x802D4000, sp70 - sp74);
        var_a3_2 = (u8 *)0x802D4000;
        var_s3 = sp6C;
        sp70 = sp74;
        do {
            sp84 = var_a3_2;
            decoded = ((s32 (*)(u8 *, u8 *, u8 *))boot_inflate)(var_a3_2 + 4, var_s3, (u8 *)0x803A2000);
            sp70 = &sp70[decoded];
            temp_t1_2 = (var_s5 + 1) & 0xFFFF;
            temp_at_2 = temp_t1_2 < 0xB;
            var_s5 = temp_t1_2;
            var_s3 += decoded;
            var_a3_2 = &var_a3_2[((u8 *)var_a3_2)[3] + (((u8 *)var_a3_2)[0] << 0x18) + (((u8 *)var_a3_2)[1] << 0x10) + (((u8 *)var_a3_2)[2] << 8)];
        } while (temp_at_2 != 0);
    } else {
        sp58 = temp_v0;
        sp74 = temp_a3;
        boot_dma_chunked(temp_a3, sp6C, sp70 - temp_a3);
    }
    var_a0 = 0;
    var_s4_2 = sp6C;
    if (arg1 == 0xC) {
        var_s3_2 = &(*D_8004D278)[arg0];
        var_v1_2 = (s32) D_8004D278[199][arg0].second;
        var_s0 = arg0 * 8;
    } else {
        var_s0 = arg0 * 8;
        var_s3_2 = &(*D_8004D278)[arg0];
        var_v1_2 = 0;
    }
    var_s5_2 = 0;
    do {
        temp_t3 = (var_s5_2 + 1) & 0xFFFF;
        temp_at_3 = temp_t3 < 0x100;
        temp_v0_3 = &D_8004D278[var_s5_2][arg0];
        var_s5_2 = temp_t3; temp_v0_3->second = 0;
        temp_v0_3->first = 0;
    } while (temp_at_3 != 0);
    temp_a3_2 = (u32)(sp6C + (sp70 - sp74));
    D_8004D278[199][arg0].second = (u8 *)var_v1_2;
    if ((u32) (sp6C + 0xF) < temp_a3_2) {
        do {
            temp_t1_3 = ((((u8 *)var_s4_2)[1] << 8) + ((u8 *)var_s4_2)[0]) & 0xFFFF;
            if (temp_t1_3 == D_80045D8C[arg1][var_a0])
    {
                var_a0 = (var_a0 + 1) & 0xFFFF;
                D_8004D278[temp_t1_3][arg0].second = var_s4_2;
            } else {
                temp_v1 = &D_8004D278[temp_t1_3][arg0];
                if (temp_v1->first == 0) {
                    temp_v1->first = var_s4_2;
                } else {
                    temp_v1->second = var_s4_2;
                }
            }
            var_s4_2 = (((u8 *)var_s4_2)[7] << 0x18) + var_s4_2 + ((u8 *)var_s4_2)[4] + (((u8 *)var_s4_2)[5] << 8) + (((u8 *)var_s4_2)[6] << 0x10);
        } while ((u32) (var_s4_2 + 0xF) < temp_a3_2);
    }
    if (arg1 == 1) {
        temp_a1 = (temp_a3_2 + 0xF) & ~0xF;
        boot_dma((s32) D_119F0, temp_a1, D_13200 - D_119F0);
        D_8004D278[176][arg0].first = 0;
        D_8004D278[176][arg0].second = (u8 *)temp_a1;
        D_8004D278[175][arg0].first = 0;
        D_8004D278[175][arg0].second = (u8 *) ((((u8 *)temp_a1)[7] << 0x18) + temp_a1 + ((u8 *)temp_a1)[4] + (((u8 *)temp_a1)[5] << 8) + (((u8 *)temp_a1)[6] << 0x10));
    }
    var_s5_3 = 0;
    do {
        temp_v0_4 = &D_8004D278[var_s5_3][arg0];
        temp_t5_2 = (var_s5_3 + 1) & 0xFFFF;
        if ((temp_v0_4->first == 0) && (temp_v0_4->second == 0)) {
            if (*D_80045D8C[arg1] == 0) {
                temp_v0_4->second = sp6C;
            } else {
                temp_v0_4->first = sp6C;
            }
        }
        var_s5_3 = temp_t5_2;
    } while (temp_t5_2 < 0x100);
    if (sp5C != 2) {
        temp_t3_2 = arg0 << 0xB;
        boot_dma((s32) sp58->palette, (s32) (temp_t3_2 + D_80063C60), 0x800);
        boot_dma((s32) (sp58->palette + 0x800), (s32) (temp_t3_2 + D_80064C60), 0x800);
    }
}
