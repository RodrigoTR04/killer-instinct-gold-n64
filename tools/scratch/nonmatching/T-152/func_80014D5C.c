/* T-148 draft: 14 differing words, 1780/1780 bytes in the full TU. */
extern u8 D_80044ED8;






extern s32 D_8004A264;
extern u8 D_8004A401;
extern void *D_8004A4C0[];
extern f32 D_8004A740[];
extern s16 D_8004AA2A;
extern u8 D_8004AC98[];
extern u8 D_8004ACB0[];
extern u8 D_8004ACB9;
extern s32 D_8004ACF0;
extern s32 D_8004ACF8;
extern s32 D_80066C40;
extern f32 D_800695CC;
extern s32 D_800698C4;
extern u8 D_801A22E0;
extern u8 D_801D7DF7;
extern void func_80015450();

extern void *func_8002F6F4(void *, s16, void **);
extern void func_8002F8F8(void *);
extern s32 func_8002FA5C();
extern u32 func_800326F0();

void func_80014D5C(void)
    {
    s32 var_a2, i;
    f32 var_f2_2, temp_f0;
    s32 var_v0;
    f32 var_f2_6, var_f2;
    f32 var_f2_5, var_f2_3, *var_a1;
    u8 *var_a0;
    f32 var_f2_4;
    u8 *var_v1_2;
    D_801D7DF7 = 1;
    if ((D_8004ACF8 == 0x3C) || (D_8004ACF8 == 0x1E))
    {
    func_8001C1B0((u8 **)&D_80044ED8, 0x56, 0, 1);
    D_8004ACF0 = 0;
    func_8002F8F8((void *)D_8004A264);
    func_8002F6F4((void *)D_80066C40, 0x1A0, (void **)&D_8004A264);
    func_8002FA5C((void *)D_8004A264, 8, 0x7FFF);
    D_8004AA2A = 0x7FFF;
    }
    else if (D_8004ACF8 == 0x32)
    {
    func_8001C1B0((u8 **)&D_80044ED8, 0x56, 0, 1);
    D_8004ACF0 = 1;
    }
    if ((D_800698C4 == 0x26) && (D_8004A401 == 3))
    {
    D_8004ACF8 = 1;
    }
    if (D_8004ACF8 == 1)
    {
    ((T0331383CStagePart *)D_8004A4C0)[10].display = &D_801A22E0;
    ((T0331383CStagePart *)D_8004A4C0)[11].display = &D_801A22E0;
    ((T0331383CStagePart *)D_8004A4C0)[12].display = &D_801A22E0;
    D_8004A740[0] = (-6000.0f);
    D_8004A740[1] = (f32) (-5300.0f);
    D_8004A740[2] = (f32) (-4600.0f);
    D_8004ACF8 = D_8004ACF8 - 1;
    func_8002F8F8((void *)D_8004A264);
    func_8002F6F4((void *)D_80066C40, 0x19C, (void **)&D_8004A264);
    }
    if (D_8004ACF8 == 0)
    {
    if (D_8004A740[2] < D_800695CC)
    {
    ((T0331383CStagePart *)D_8004A4C0)[10].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[11].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[12].transform = 2;
    ((T0331383CStagePart *)D_8004A4C0)[10].flags = 0x11;
    ((T0331383CStagePart *)D_8004A4C0)[11].flags = 0x21;
    ((T0331383CStagePart *)D_8004A4C0)[12].flags = 0x31;
    }
    else if (D_800695CC < D_8004A740[0])
    {
    ((T0331383CStagePart *)D_8004A4C0)[10].transform = 2;
    ((T0331383CStagePart *)D_8004A4C0)[11].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[12].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[10].flags = 0x31;
    ((T0331383CStagePart *)D_8004A4C0)[11].flags = 0x21;
    ((T0331383CStagePart *)D_8004A4C0)[12].flags = 0x11;
    }
    else
    {
    ((T0331383CStagePart *)D_8004A4C0)[10].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[11].transform = 2;
    ((T0331383CStagePart *)D_8004A4C0)[12].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[10].flags = 0x11;
    ((T0331383CStagePart *)D_8004A4C0)[11].flags = 0x31;
    ((T0331383CStagePart *)D_8004A4C0)[12].flags = 0x21;
    }
    i = 0;
    var_v1_2 = D_8004ACB0;
    var_a0 = D_8004AC98;
    do
    {
    var_a1 = &D_8004A740[i];
    *var_a1 += 25.0f;
    temp_f0 = D_8004A740[i];
    if (temp_f0 >= -260.0f)
    {
    var_v0 = (s32) (temp_f0 - -260.0f);
    }
    else
    {
    var_v0 = (s32) -(temp_f0 - -260.0f);
    }
    if (var_v0 < 0x190)
    {
    var_v0 = 0x190;
    }
    if ((temp_f0 < (-3000.0f)) || ((3000.0f) < temp_f0))
    {
    var_a0[0] = 0;
    var_a0[1] = 0;
    var_a0[2] = 0;
    if (temp_f0 >= 0.0f)
    {
    var_f2 = temp_f0;
    }
    else
    {
    var_f2 = -temp_f0;
    }
    var_v1_2[0] = (s8) (u32) ((var_f2 - (3000.0f)) / 24.0f);
    if (temp_f0 >= 0.0f) var_f2_2 = temp_f0;
    else var_f2_2 = -temp_f0;
    var_v1_2[1] = (s8)(u32)((var_f2_2 - 3000.0f) / 24.0f);
    if (temp_f0 >= 0.0f) var_f2_3 = temp_f0;
    else var_f2_3 = -temp_f0;
    var_v1_2[2] = (s8)(u32)((var_f2_3 - 3000.0f) / 24.0f);
    }
    else
    {
    var_a0[0] = (s8) (0x2710 / var_v0);
    var_a0[1] = 0;
    var_a0[2] = 0;
    var_v1_2[0] = 0;
    var_v1_2[1] = 0;
    var_v1_2[2] = 0;
    }
    i++;
    var_a0 += 3;
    var_v1_2 += 3;
    }
    while (var_v1_2 != &D_8004ACB9);
    if ((6000.0f) < D_8004A740[0])
    {
    D_8004ACF8 = (func_800326F0() & 0x3FF) + 0x12C;
    ((T0331383CStagePart *)D_8004A4C0)[10].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[11].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[12].display = 0;
    func_8001C1B0((u8 **)&D_80044ED8, 0x56, 0, 1);
    D_8004ACF0 = 1;
    if ((void *)D_8004A264 != 0)
    {
    func_8002F8F8((void *)D_8004A264);
    }
    }
    else
    {
    if (D_8004A740[0] >= 0.0f)
    {
    var_f2_4 = D_8004A740[0];
    }
    else
    {
    var_f2_4 = -D_8004A740[0];
    }
    if ((((6000.0f) - var_f2_4) * 8.0f) >= 0.0f)
    {
    if (D_8004A740[0] >= 0.0f)
    {
    var_f2_5 = D_8004A740[0];
    }
    else
    {
    var_f2_5 = -D_8004A740[0];
    }
    var_a2 = (s32) (((6000.0f) - var_f2_5) * 8.0f);
    }
    else
    {
    if (D_8004A740[0] >= 0.0f)
    {
    var_f2_6 = D_8004A740[0];
    }
    else
    {
    var_f2_6 = -D_8004A740[0];
    }
    var_a2 = (s32) -(((6000.0f) - var_f2_6) * 8.0f);
    }
    if (var_a2 >= 0x8000)
    {
    var_a2 = 0x7FFF;
    }
    func_8002FA5C((void *)D_8004A264, 8, var_a2);
    D_8004AA2A = (s16) var_a2;
    }
    }
    else
    {
    D_8004ACF8 = D_8004ACF8 - 1;
    }
    func_80015450(0xE00);
    }
