/* T-093 DRAFT: 151 -> 149 relocation-masked words; 764/772 bytes. See T-093/REPORT.md. */
extern f32 D_800488A0; extern f64 D_800488A8;
extern u8 D_8004A401;
extern void *D_8004A4C0[]; extern f32 D_8004A7B8;
extern f32 D_8004A740[]; extern f32 D_8004A980;
extern u8 D_8004A9D8;
extern f32 D_8004ACEC;
extern s32 D_8004ACF4;
extern f32 D_800695D0;
extern s32 D_800698C4;
extern u8 D_8019DDF0;
extern u8 D_801A24E0; extern u8 D_801A5290; extern u8 D_801A6200;
extern u8 D_801A63D0;
extern u8 D_801A6AD0; extern u8 D_801AAEB0;
extern s32 D_801C4220;
extern u8 D_801D7DF7;
extern void func_80015450(s32);
extern void func_8001AC80(void);
extern f32 D_8004A8C0[];
void func_80017A68(void) {
    if (D_800695D0 > 1000.0f) {
        ((T0331383CStagePart *)D_8004A4C0)[1].display = &D_801A24E0;
        ((T0331383CStagePart *)D_8004A4C0)[1].transform = 7;
        ((T0331383CStagePart *)D_8004A4C0)[0].display = &D_801A63D0;
        ((T0331383CStagePart *)D_8004A4C0)[0].transform = 0;
    }
    else {
        ((T0331383CStagePart *)D_8004A4C0)[1].display = &D_801A63D0;
        ((T0331383CStagePart *)D_8004A4C0)[1].transform = 0;
        ((T0331383CStagePart *)D_8004A4C0)[0].display = &D_801A24E0;
        ((T0331383CStagePart *)D_8004A4C0)[0].transform = 7; }
    if (D_8004AC8D == 1) {
        D_8004AC8D = 2;
    } if (D_801D7DF7 == 1) {
        if (D_8004AC8D == 0) { D_8004AC8D = 1;
        }
        ((T0331383CStagePart *)D_8004A4C0)[4].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[16].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[17].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[18].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[19].display = 0; ((T0331383CStagePart *)D_8004A4C0)[7].display = &D_801AAEB0;
        ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_8019DDF0; D_801C4220 = 0xFFFF31BC;
    }
    D_8004A8C0[0] += D_8004ACEC; if (D_800488A0 < D_8004A8C0[0]) {
        D_8004A8C0[0] -= 360.0f; }
    D_8004A980 += 10.0f;
    if (D_800488A0 < D_8004A980) {
        D_8004A980 -= 360.0f; } if (D_8004ACF4 == 1) {
        D_8004ACF4 = 0;
        D_8004ACEC = 2.0f;
    }
    if (D_8004ACEC > 0.0f) { D_8004ACEC = (f32) ((f64) D_8004ACEC - D_800488A8);
    }
    else {
        D_8004ACEC = 0.0f;
    }
    func_8001AC80();
    if ((D_8004A7B8 + 600.0f) < D_800695D0) {
        ((s8 *)D_8004A5E0)[35] = 0xF;
        ((s8 *)D_8004A5E0)[42] = 0x17;
    } else {
        ((s8 *)D_8004A5E0)[35] = 0x17;
        ((s8 *)D_8004A5E0)[42] = 0xF;
    }
    if ((D_8004A401 == 1) && (D_800698C4 == 0)) {
        ((T0331383CStagePart *)D_8004A4C0)[10].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[11].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[12].display = 0; ((T0331383CStagePart *)D_8004A4C0)[13].display = 0; ((T0331383CStagePart *)D_8004A4C0)[3].display = &D_801A6200; ((T0331383CStagePart *)D_8004A4C0)[2].display = &D_801A5290; ((T0331383CStagePart *)D_8004A4C0)[20].display = &D_801A5290;
        ((T0331383CStagePart *)D_8004A4C0)[21].display = &D_801A5290;
        ((T0331383CStagePart *)D_8004A4C0)[22].display = &D_801A5290; }
    else {
        ((T0331383CStagePart *)D_8004A4C0)[10].display = &D_801A6AD0;
        ((T0331383CStagePart *)D_8004A4C0)[11].display = &D_801A6AD0; ((T0331383CStagePart *)D_8004A4C0)[12].display = &D_801A6AD0; ((T0331383CStagePart *)D_8004A4C0)[13].display = &D_801A6AD0;
    }
    func_80015450(0x1800);
    if (D_8004AA29 == 1) {
        ((T0331383CStageRotation *)&D_8004A9D8)[0].pitch = 90.0f;
        ((T0331383CStageRotation *)&D_8004A9D8)[1].pitch = 90.0f;
        ((T0331383CStageRotation *)&D_8004A9D8)[2].pitch = 90.0f;
    }
}
