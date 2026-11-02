/* T-149 DRAFT: 390 differing words, 1648/1652 bytes in the full TU. */
typedef struct { s16 halfW,halfH,w,h; } T032Size24C;
extern T032Sprite25D D_8004CED0[];
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
    u32 blockLength;
    s32 sp40;
    u8 *archive;
    u8 *var_s1_2;
    T032Size24C *var_v0;
    u8 **var_v1;
    s32 glyphIndex;
    s32 frameIndex;
    s32 var_s1;
    u8 temp_s1;
    T032Sprite25D *temp_s0;
    u8 *section;
    u8 *source;
    u8 *var_s2;

    sp40 = D_8F9FA0 - D_8F6AE0;
    D_80061496 = 0;
    boot_dma(D_8F6AE0, (void *)0x802D4000, sp40);
    source = (u8 *)0x802D4000;
    archive = (u8 *)(sp40 + 0x802D4000);
    var_s2 = archive;
    var_s1 = 0;
    do {
        var_s1 += 1;
        var_s2 += boot_inflate(source + 4, var_s2, (void *)0x803A2000);
        blockLength = source[3] + ((u32)source[0] << 24) + (source[1] << 16) + (source[2] << 8);
        source += blockLength;
    } while (var_s1 != 6);
    D_8004EA78 = 4;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_800508E0;
    temp_s0->alpha = D_8004F3A0;
    func_800238C4((u8 *)((archive[0xB] << 0x18) + sp40 + archive[0x8] + (archive[0x9] << 8) + (archive[0xA] << 0x10) + 0x802D4000), D_80047C38);
    D_8004EA78 = 5;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_80051D80;
    temp_s0->alpha = D_8004FE40;
    func_800238C4((archive[0xF] << 0x18) + archive + archive[0xC] + (archive[0xD] << 8) + (archive[0xE] << 0x10), D_80047C38);
    D_8004EA78 = 0xC;
    section = (archive[0x7] << 0x18) + archive + archive[0x4] + (archive[0x5] << 8) + (archive[0x6] << 0x10);
    var_v1 = D_800612D8;
    var_v0 = D_80061368;
    D_8004CED0[D_8004EA78].alpha = archive;
    do {
        var_v1++;
        var_v0++;
        var_v0[-1].halfW = 0;
        var_v0[-1].halfH = 0;
        var_v0[-1].w = 0x10;
        var_v0[-1].h = 1;
        var_v1[-1] = D_80054458;
    } while ((u32) var_v1 < (u32) D_80061368);
    source = D_80047BF0;
    glyphIndex = 0;
    do {
        temp_s1 = *source;
        if ((temp_s1 != 0) || (glyphIndex == 0)) {
            func_800268C0(section, glyphIndex, D_80054458 + (temp_s1 * 0x360), temp_s1);
        }
        glyphIndex += 1;
        source += 1;
    } while (glyphIndex < 0x1A);
    section = (section[0x7] << 0x18) + section + section[0x4] + (section[0x5] << 8) + (section[0x6] << 0x10);
    var_s1_2 = D_8005A388;
    frameIndex = 0;
    do {
        func_800268C0(section, frameIndex, var_s1_2, frameIndex + 0x13);
        frameIndex += 1;
        var_s1_2 += 0x120;
    } while (frameIndex != 0xA);
    func_800268C0(section, 0xA, D_80058478, 0x1DU);
    func_800268C0(section, 0xB, D_8005AEC8, 0x1EU);
    section = (section[0x7] << 0x18) + section + section[0x4] + (section[0x5] << 8) + (section[0x6] << 0x10);
    func_800268C0(section, 0, D_800587B8, 0x1FU);
    func_800268C0(section, 1, D_80058D58, 0x20U);
    func_800268C0(section, 2, D_800590B8, 0x21U);
    func_800268C0(section, 4, D_80059668, 0x22U);
    func_800268C0(section, 5, D_80059CF8, 0x23U);
    section = (section[0x7] << 0x18) + section + section[0x4] + (section[0x5] << 8) + (section[0x6] << 0x10);
    D_8004EA78 = 0xC;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_80053220;
    temp_s0->alpha = D_80054198;
    func_800238C4((section[0xB] << 0x18) + section + section[0x8] + (section[0x9] << 8) + (section[0xA] << 0x10), D_80047C38);
    D_8004EA78 = 0xD;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_80053748;
    temp_s0->alpha = D_80054198;
    func_800238C4((section[0xF] << 0x18) + section + section[0xC] + (section[0xD] << 8) + (section[0xE] << 0x10), D_80047C38);
    D_8004EA78 = 0xE;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_80053C70;
    temp_s0->alpha = D_80054198;
    func_800238C4((section[0x13] << 0x18) + section + section[0x10] + (section[0x11] << 8) + (section[0x12] << 0x10), D_80047C38);
    section = (section[0x7] << 0x18) + section + section[0x4] + (section[0x5] << 8) + (section[0x6] << 0x10);
    D_8004EA78 = 0x1E;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_8005E3F8;
    temp_s0->alpha = 0;
    func_800238C4((section[0x1F] << 0x18) + section + section[0x1C] + (section[0x1D] << 8) + (section[0x1E] << 0x10), D_80047C38);
    D_8004EA78 = 0x1D;
    temp_s0 = &D_8004CED0[D_8004EA78];
    temp_s0->pixels = (u16 *)D_8005AFB8;
    temp_s0->alpha = 0;
    func_800238C4((section[0xB] << 0x18) + section + section[0x8] + (section[0x9] << 8) + (section[0xA] << 0x10), D_80047C38);
}
