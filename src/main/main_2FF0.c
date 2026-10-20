#include "common.h"

extern void boot_inflate(void *, void *, void *);

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80012950.s")

typedef struct {
    u8 *start;
    u8 *end;
} T020RomRange;
extern T020RomRange D_80007260[];
extern void *D_80044DF4[];
extern void boot_dma(void *, void *, s32);
extern void osInvalICache(void *, s32);
extern void osInvalDCache(void *, s32);

void func_80012A8C(u8 arg0) {
    T020RomRange *range;
    osInvalICache((void *)0x802D4000, 0x927C0);
    osInvalDCache((void *)0x802D4000, 0x927C0);
    range = &D_80007260[arg0];
    boot_dma(range->start, (void *)0x80313090, range->end - range->start);
    boot_inflate((void *)0x80313090, D_80044DF4[arg0], (void *)0x80311090);
}

extern u8 D_8004AC40[];
extern void guPerspective(void *, u16 *, f32, f32, f32, f32, f32);

void func_80012B24(u16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    guPerspective(D_8004AC40, arg0, arg1, arg2, arg3, arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80012B7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800131A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001346C.s")

typedef struct {
    u8 pad[0x28];
    s16 x, y, z;
} T020Position;

void func_8001372C(T020Position *arg0) {
    arg0->x = 0;
    arg0->y = 0;
    arg0->z = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001373C.s")

typedef struct { void *display; s16 flags, pad; s32 transform; } T0331383CStagePart;
typedef struct { f32 pitch, yaw, roll, speed, scale; } T0331383CStageRotation;
extern u8 D_80045220;
extern u8 D_80045260;
extern u8 D_80045280;
extern u8 D_800452C0;
extern u8 D_800452E0;
extern u8 D_80045320;
extern u8 D_80045360;
extern u8 D_80045364;
extern u8 D_80045370;
extern f32 D_800487FC;
extern f32 D_80048800;
extern f32 D_80048804;
extern void *D_8004A4C0[];
extern u8 D_8004A998;
extern u8 D_8004A9D8;
extern u8 D_8004AA28, D_8004AC88;
extern void (*D_8004AA30)(void);
extern void (*D_8004AA34)(T020Position *);
extern void (*D_8004AA38)();
extern u8 *D_8004AA3C;
extern f32 D_8004AC80;
extern f32 D_8004AC84;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern s8 D_8004AC8C;
extern u8 D_8004ACC5, D_8004ACC6, D_8004ACC7, D_8004ACC8, D_8004ACC9, D_8004ACCA;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern f32 D_800614D8[];
extern s8 D_80061520;
extern u8 D_80061CB8[];
extern u8 D_801A2770;
extern u8 D_801A4D00;
extern u8 D_801A5410;
extern u8 D_801A5C50;
extern u8 D_801A6870;
extern u8 D_801A6C10;
extern u8 D_801A7690;
extern u8 D_801A8110;
extern u8 D_801A82B0;
extern u8 D_801A87C0;
extern u8 D_801A9DE0;
extern u8 D_801A9F30;
extern u8 D_801AA080;
extern u8 D_801AA1D0;
extern u8 D_801AA610;
extern u8 D_802F02A0;
extern u8 D_802F0378;
extern u8 D_802F0450;
extern void func_8001372C(T020Position *);
extern s32 func_80013BA4(s32, s32, s32, s32);
extern void func_80013BE0();
extern void func_80013C84();
extern void func_80015594();
extern void func_80016078();
extern void func_8001C0E4(s32 *, s16 *, s32 *, s16 *, s32, s32 *, s32 *, s32);
extern void func_8001C43C(s32, void *, void *, void *, void *);
extern s32 func_80028600(s32, f32, f32, s32);
extern s32 func_80030020(u8 *, u8 *, u8 *, s32);

void func_8001383C(void) {
    ((T0331383CStagePart *)D_8004A4C0)[0].display = &D_801A5410;
    ((T0331383CStagePart *)D_8004A4C0)[1].display = &D_801A6C10;
    ((T0331383CStagePart *)D_8004A4C0)[2].display = &D_801A7690;
    ((T0331383CStagePart *)D_8004A4C0)[3].display = &D_801A82B0;
    ((T0331383CStagePart *)D_8004A4C0)[4].display = &D_801A5C50;
    ((T0331383CStagePart *)D_8004A4C0)[0].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[1].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[2].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[3].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[4].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_801A87C0;
    ((T0331383CStagePart *)D_8004A4C0)[5].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[6].display = &D_801A4D00;
    ((T0331383CStagePart *)D_8004A4C0)[6].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[7].display = &D_801A8110;
    ((T0331383CStagePart *)D_8004A4C0)[7].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[8].display = &D_801A6870;
    ((T0331383CStagePart *)D_8004A4C0)[8].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[9].flags = 6;
    ((T0331383CStagePart *)D_8004A4C0)[9].transform = 0;
    func_8001C43C(1, &D_80045360, &D_80045364, &D_80045370, 0);
    D_8004AEAC = &func_80013BA4;
    D_8004AA34 = &func_8001372C;
    D_8004AA38 = &func_80013BE0;
    D_8004AA3C = &D_801A2770;
    D_8004AA30 = &func_80015594;
    D_8004AC80 = D_800487FC;
    D_8004AC84 = 45.0f;
    D_8004AC89 = 2;
    D_8004AC8A = 1;
    D_8004AC8C = 6;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    D_800614D8[0] = -1960.0f;
    D_800614D8[1] = (f32) D_80048800;
    D_800614D8[2] = (f32) D_80048804;
    D_80061CB8[0] = 0xD0;
    D_80061CB8[1] = 0xD0;
    D_80061CB8[2] = 0xD0;
    D_80061CB8[3] = 0x80;
    D_80061CB8[4] = 0x80;
    D_80061CB8[5] = 0x80;
    D_80061CB8[6] = 0x30;
    D_80061CB8[7] = 0x30;
    D_80061CB8[8] = 0x30;
    D_80061520 = 0x14;
    ((void **)&D_8004A998)[0] = &D_801A9DE0;
    ((void **)&D_8004A998)[1] = &D_801A9F30;
    ((void **)&D_8004A998)[2] = &D_801AA080;
    ((void **)&D_8004A998)[6] = &D_801AA1D0;
    ((void **)&D_8004A998)[3] = 0;
    ((void **)&D_8004A998)[4] = 0;
    ((void **)&D_8004A998)[5] = 0;
    ((void **)&D_8004A998)[7] = 0;
    ((void **)&D_8004A998)[8] = 0;
    ((void **)&D_8004A998)[9] = 0;
    ((void **)&D_8004A998)[10] = &D_801AA610;
    ((void **)&D_8004A998)[11] = 0;
    ((T0331383CStageRotation *)&D_8004A9D8)[0].pitch = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[0].yaw = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[0].roll = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[0].speed = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[1].pitch = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[1].yaw = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[1].roll = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[1].speed = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[2].pitch = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[2].yaw = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[2].roll = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[2].speed = 0.0f;
    ((T0331383CStageRotation *)&D_8004A9D8)[1].scale = 1.0f;
    func_8001C0E4(&D_80045220, &D_80045260, &D_80045280, &D_800452C0, &D_802F02A0, &D_800452E0, &D_80045320, 0x10);
    func_80030020(&D_802F0378, &D_802F02A0, &D_802F0450, 0x36);
    if (D_8004AA28 == 0) {
        func_80013C84();
        return;
    }
    D_8004ACC5 = D_8004ACC6 = D_8004ACC7 = 0;
    D_8004AA30 = &func_80016078;
}


extern u8 D_8004A5EE;

s32 func_80013BA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 - arg2 + 0x1613 > 0) {
        D_8004A5EE = 2;
    } else {
        D_8004A5EE = 1;
    }
    return 0;
}

/* DRAFT T-020: Two instruction words differ: IDO folds division by 2.0f to multiplication by 0.5f. */
extern f32 D_8004A9FC, D_8004AC84;
extern s32 D_8004ACF0;
extern f32 D_80061CC8[];
extern s16 D_8004A530;
extern s32 func_80028600(s32, f32, f32, s32);

void func_80013BE0(void) {
    f32 half;
    if (D_8004A9FC == 0.0f && D_8004ACF0 == 0) {
        half = D_8004AC84 / 2;
        func_80028600(1, half, half, 240);
        D_80061CC8[0] = 3.0f;
        D_80061CC8[2] = 3.0f;
        D_80061CC8[1] = 0.0f;
        D_8004A530 = 3;
        D_8004ACF0 = 1;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80013C84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80013CD8.s")

extern u8 D_8004A401;
extern void *D_8004A4C0[];
extern s8 D_8004A736;
extern u8 D_8019C890[], D_8019F450[];

s32 func_8001414C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 >= 356) D_8004A4C0[18] = 0;
    else D_8004A4C0[18] = D_8019F450;
    if (arg2 < -700) D_8004A4C0[9] = 0;
    else D_8004A4C0[9] = D_8019C890;
    if (arg2 < -518 && arg0 >= -697 && arg0 < 170) {
        if (D_8004A401 == 1) {
            D_8004A736 = 9;
        } else {
            D_8004A736 = 12;
        }
        return 6;
    }
    if (arg0 < -698) {
        if (arg2 >= 391) return 4;
        return 3;
    }
    if (arg2 >= 391) {
        if (arg0 < 170) return 2;
        return 5;
    }
    if (arg0 < 170) return 0;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80014250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800142E0.s")

typedef struct {
    u8 pad[0x28];
    s16 vx, vy, vz;
} T033ForceTarget;
extern s32 D_8004ACF0;
extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);

void func_80014C40(T033ForceTarget *arg0) {
    arg0->vx = -50;
    arg0->vy = -50;
    arg0->vz = -50;
    if (D_8004ACF0 == 0) {
        func_8001373C(arg0, -268.0f, 210.0f, -652.0f, 96, 0, 0);
    } else {
        func_8001373C(arg0, -268.0f, 210.0f, -652.0f, 0, 96, 0);
    }
    func_8001373C(arg0, 29.0f, 230.0f, -216.0f, 96, 96, 96);
    func_8001373C(arg0, -690.0f, 230.0f, -645.0f, 96, 96, 96);
    func_8001373C(arg0, -570.0f, 230.0f, 292.0f, 96, 96, 96);
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80014D5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80015450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80015594.s")

extern void *D_8004A4C0[];
extern s8 D_8004A738;
extern s32 D_800698C4;
extern u8 D_8018E6D0[], D_8018EA70[], D_80193F40[], D_80195310[];
extern u8 D_80196730[], D_80197B10[], D_80198470[], D_80198F00[];

s32 func_80015B64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 x;
    if (D_800698C4 != 0) D_8004A738 = 2;
    else D_8004A738 = 0;
    if (arg2 >= 191) {
        D_8004A4C0[12] = D_8018E6D0;
        D_8004A4C0[15] = D_8018EA70;
    } else {
        D_8004A4C0[12] = D_8018EA70;
        D_8004A4C0[15] = D_8018E6D0;
    }
    if (arg1 >= 435) {
        D_8004A4C0[3] = D_80193F40;
        D_8004A4C0[18] = D_80197B10;
        D_8004A4C0[6] = D_80195310;
        D_8004A4C0[21] = D_80198470;
        D_8004A4C0[9] = D_80196730;
        D_8004A4C0[24] = D_80198F00;
    } else {
        D_8004A4C0[3] = D_80197B10;
        D_8004A4C0[18] = D_80193F40;
        D_8004A4C0[6] = D_80198470;
        D_8004A4C0[21] = D_80195310;
        D_8004A4C0[9] = D_80198F00;
        D_8004A4C0[24] = D_80196730;
    }
    if (arg2 >= 851) return 0;
    x = arg0 * 10;
    if (arg2 * 4 + x + 2000 < 0) return 1;
    if (arg2 * 15 - x + 18110 < 0) return 2;
    return 3;
}


typedef struct { void *display; s16 flags, pad; s32 transform; } T033StagePart;
typedef struct { f32 pitch, yaw, roll, speed, scale; } T033StageRotation;
extern u8 D_80044E4C;
extern u8 D_800454E8;
extern u8 D_80045520;
extern u8 D_8004553C;
extern u8 D_80045574;
extern u8 D_80045590;
extern u8 D_800455C8;
extern u8 D_80045600;
extern u8 D_80045604;
extern u8 D_80045628;
extern u8 D_8004562C;
extern void *D_8004A4C0[];
extern u8 D_8004A998;
extern u8 D_8004A9D8;
extern void (*D_8004AA30)(void);
extern void (*D_8004AA34)(T020Position *);
extern void (*D_8004AA38)();
extern u8 *D_8004AA3C;
extern f32 D_8004AC80;
extern f32 D_8004AC84;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern s8 D_8004AC8C;
extern u8 *D_8004ACD8;
extern s32 D_8004ACF8;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern u8 D_801776D0;
extern u8 D_8018E6D0[], D_8018EA70[], D_80193F40[], D_80195310[];
extern u8 D_8018EE10;
extern u8 D_80192520;
extern u8 D_80196730[], D_80197B10[], D_80198470[], D_80198F00[];
extern u8 D_80199940;
extern u8 D_80199B60;
extern u8 D_80199DA0;
extern u8 D_802E7E74;
extern u8 D_802E7EEC;
extern u8 D_802E7F64;
extern void func_8001372C(T020Position *);
extern s32 func_80015B64(s32, s32, s32, s32);
extern void func_80015F6C();
extern void func_80019880();
extern void func_8001C05C(u8 *);
extern void func_8001C0E4(s32 *, s16 *, s32 *, s16 *, s32, s32 *, s32 *, s32);
extern void func_8001C43C(s32, void *, void *, void *, void *);
extern s32 func_80028600(s32, f32, f32, s32);
extern s32 func_80030020(u8 *, u8 *, u8 *, s32);
extern u32 func_800326F0();

void func_80015CD0(void) {
    func_8001C05C(&D_80044E4C);
    ((T033StagePart *)D_8004A4C0)[0].display = &D_80192520;
    ((T033StagePart *)D_8004A4C0)[0].flags = 0;
    ((T033StagePart *)D_8004A4C0)[1].display = &D_80193F40;
    ((T033StagePart *)D_8004A4C0)[1].flags = 0;
    ((T033StagePart *)D_8004A4C0)[2].display = &D_80195310;
    ((T033StagePart *)D_8004A4C0)[2].flags = 0;
    ((T033StagePart *)D_8004A4C0)[3].display = &D_80196730;
    ((T033StagePart *)D_8004A4C0)[3].flags = 0;
    ((T033StagePart *)D_8004A4C0)[4].display = &D_8018E6D0;
    ((T033StagePart *)D_8004A4C0)[4].flags = 0;
    ((T033StagePart *)D_8004A4C0)[5].display = &D_8018EA70;
    ((T033StagePart *)D_8004A4C0)[5].flags = 0;
    ((T033StagePart *)D_8004A4C0)[6].display = &D_80197B10;
    ((T033StagePart *)D_8004A4C0)[6].flags = 0;
    ((T033StagePart *)D_8004A4C0)[7].display = &D_80198470;
    ((T033StagePart *)D_8004A4C0)[7].flags = 0;
    ((T033StagePart *)D_8004A4C0)[8].display = &D_80198F00;
    ((T033StagePart *)D_8004A4C0)[8].flags = 0;
    ((T033StagePart *)D_8004A4C0)[9].display = &D_8018EE10;
    ((T033StagePart *)D_8004A4C0)[9].flags = 0;
    func_8001C43C(4, &D_80045600, &D_80045604, &D_80045628, &D_8004562C);
    ((void **)&D_8004A998)[0] = &D_80199940;
    ((void **)&D_8004A998)[1] = &D_80199B60;
    ((void **)&D_8004A998)[2] = &D_80199DA0;
    ((void **)&D_8004A998)[3] = 0;
    ((void **)&D_8004A998)[4] = &D_80199940;
    ((void **)&D_8004A998)[5] = &D_80199B60;
    ((void **)&D_8004A998)[6] = &D_80199DA0;
    ((void **)&D_8004A998)[7] = 0;
    ((T033StageRotation *)&D_8004A9D8)[0].pitch = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[0].yaw = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[0].roll = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[0].speed = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[1].pitch = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[1].yaw = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[1].roll = 0.0f;
    ((T033StageRotation *)&D_8004A9D8)[1].speed = 0.0f;
    D_8004AEAC = &func_80015B64;
    D_8004AA34 = &func_8001372C;
    D_8004AA38 = &func_80015F6C;
    D_8004AA3C = &D_8018E6D0;
    D_8004AA30 = &func_80019880;
    D_8004ACD8 = &D_801776D0;
    D_8004AC80 = 0.0f;
    D_8004AC84 = 140.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 0;
    D_8004ACF8 = func_800326F0(&D_80199940, &D_80199B60, &D_80199DA0) & 0x23B;
    D_8004AC8C = 8;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    func_8001C0E4(&D_800454E8, &D_80045520, &D_8004553C, &D_80045574, &D_802E7E74, &D_80045590, &D_800455C8, 0xF);
    func_80030020(&D_802E7EEC, &D_802E7E74, &D_802E7F64, 0x1E);
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80015F6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80016078.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80016258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80016760.s")

extern u8 D_8004514C[], D_80045154[], D_800451DC[], D_800451E4[];
extern u8 D_8004A401;
extern void func_8001C43C(s32, void *, void *, void *, void *);

s32 func_80016824(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    if (D_8004A401 != 1 && arg1 < 300) {
        func_8001C43C(7, D_8004514C, D_80045154, D_800451DC, D_800451E4);
    }
    if (arg0 < -150) {
        if (arg2 >= -121) {
            if (arg2 >= 684) return 4;
            return 6;
        }
        return 5;
    }
    if (arg2 >= -121) {
        if (arg0 < 620) return 0;
        return 2;
    }
    if (arg0 < 580) return 1;
    return 3;
}

void func_80016908(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80016910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80016BE0.s")

extern s32 D_800698C4;

s32 func_80017064(s32 arg0, int arg1, s32 arg2, int arg3) {
    if (D_800698C4 > 0) {
        return 1;
    }
    if (arg2 >= 0xDAD) {
        return 1;
    }
    if (arg0 >= 0x329) {
        return 0;
    }
    if (arg0 >= -0x252) {
        return 1;
    }
    return 2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800170C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80017378.s")

s32 func_80017A50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80017A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80017D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001808C.s")

s32 func_800183B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

typedef struct { u8 pad[0x28]; s16 x, y, z; } T022Position;
extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);
void func_800183CC(T022Position *arg0) {
    arg0->z = 0; arg0->y = 0; arg0->x = 0;
    func_8001373C(arg0, -3417.0f, 45.0f, 3200.0f, 0x30, 0x10, 0);
}

extern s32 func_8001864C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void (*D_8004AA38)();
extern void (*D_8004AA30)(void);
extern f32 D_8004AC84;
extern void func_80019880(void);
extern void func_8001BB10(void);
extern void func_8001C05C(u8 *);
extern s32 func_80028600(s32, f32, f32, s32);
extern s32 func_80030020(u8 *, u8 *, u8 *, s32);
extern s8 D_8004A5E0;
extern s8 D_8004A730;
extern s8 D_8004A738;
extern void (*D_8004AA34)(T020Position *);
extern u8 *D_8004AA3C;
extern f32 D_8004AC80;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern s8 D_8004AC8C;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern f32 D_8004A740[];
extern f32 D_8004A800[];
extern f32 D_8004A860[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
extern void func_8001C0E4(s32 *arg0, s16 *arg1, s32 *arg2, s16 *arg3, s32 arg4, s32 *arg5, s32 *arg6, s32 arg7);
extern u8 D_8004AA28;
void func_80018664();                               /* extern */
s32 func_800281C4(s32);                     /* extern */
extern u8 D_80044E40;
extern s32 D_80045A70;
extern s16 D_80045A80;
extern s32 D_80045A88;
extern s16 D_80045A98;
extern s32 D_80045AA0;
extern s32 D_80045AB0;
extern f32 D_800488CC;
extern f32 D_8004A7A0;
extern u8 D_8004A998;
extern u8 D_8004A9D8;
extern s8 D_8004AA2C;
extern u8 D_80199ED0;
extern u8 D_801A3350;
extern u8 D_801A3660;
extern u8 D_802EE8E8;
extern u8 D_802EE98C;
extern u8 D_802EEA30;

void func_80018418(void) {
    (*(u8 **)((u8 *)(D_8004A4C0) + 0)) = &D_801A3660;
    (*(s16 *)((u8 *)(D_8004A4C0) + 4)) = 2;
    (*(s32 *)((u8 *)(D_8004A4C0) + 8)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0xC)) = &D_80199ED0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x10)) = 0;
    D_8004A730 = 1;
    D_8004A5E0 = 0;
    D_8004A738 = 0;
    (*(s32 *)((u8 *)(&D_8004A998) + 0)) = 0;
    (*(s32 *)((u8 *)(&D_8004A998) + 4)) = 0;
    (*(u8 **)((u8 *)(&D_8004A998) + 8)) = &D_801A3350;
    (*(s32 *)((u8 *)(&D_8004A998) + 0xC)) = 0;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0xC)) = 0.0f;
    *D_8004A740 = 370.0f;
    D_8004A7A0 = D_800488CC;
    *D_8004A800 = -380.0f;
    *D_8004A860 = 0.0f;
    *D_8004A8C0 = 0.0f;
    *D_8004A920 = 0.0f;
    D_8004AA2C = 0;
    D_8004AA3C = &D_80199ED0;
    D_8004AEAC = func_8001864C;
    D_8004AA30 = func_80019880;
    func_8001BB10();
    func_8001C05C(&D_80044E40);
    if (D_8004AA28 == 0) {
        func_800281C4(0);
    }
    D_8004AA38 = func_80018664;
    D_8004AA34 = func_8001372C;
    D_8004AC80 = 0.0f;
    D_8004AC84 = 50.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 1;
    D_8004AC8C = 0xE;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    func_8001C0E4(&D_80045A70, &D_80045A80, &D_80045A88, &D_80045A98, (s32) &D_802EE8E8, &D_80045AA0, &D_80045AB0, 4);
    func_80030020(&D_802EE98C, &D_802EE8E8, &D_802EEA30, 0x29);
}

s32 func_8001864C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80018664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80018AE0.s")

s32 func_80018E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80018E88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80018F20.s")

s32 func_800191D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800191F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800193DC.s")

s32 func_80019704(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

extern s32 func_80019868(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void (*D_8004AA38)();
extern void func_8002FFDC(s32, s16, s32, s16, s32, s32, s32);
extern void (*D_8004AA30)(void);
extern f32 D_8004AC84;
extern void func_80019880(void);
extern void func_8001BB10(void);
extern void func_8001C05C(u8 *);
void D_8001AC78();                                  /* extern */
s32 func_80028600(s32, f32, f32, s32);  /* extern */
s32 func_80030020(u8 *, u8 *, u8 *, s32); /* extern */
extern u8 D_80044EAC;
extern s8 D_8004A5E0;
extern s8 D_8004A730;
extern s8 D_8004A738;
extern void (*D_8004AA34)(T020Position *);
extern u8 *D_8004AA3C;
extern f32 D_8004AC80;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern s8 D_8004AC8C;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern u8 D_801755F0;
extern u8 D_80175890;
extern u8 D_802D4000;
extern u8 D_802D4158;
extern u8 D_802D6098;
extern u8 D_802D60A4;
extern u8 D_802D60B0;

void func_8001971C(void) {
    D_8004A730 = 0;
    D_8004A5E0 = 0;
    D_8004A738 = 0;
    D_8004AA3C = &D_801755F0;
    D_8004AEAC = func_80019868;
    D_8004AA30 = &func_80019880;
    func_8001BB10();
    func_8001C05C(&D_80044EAC);
    D_8004AA38 = D_8001AC78;
    D_8004AA34 = func_8001372C;
    D_8004AC80 = 0.0f;
    D_8004AC84 = 250.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 0;
    D_8004AC8C = 9;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    func_8002FFDC(&D_802D4000, 0x54, &D_802D4158, 0x74, &D_802D6098, &D_80175890, &D_801755F0);
    func_80030020(&D_802D60A4, &D_802D6098, &D_802D60B0, 3);
}

s32 func_80019868(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80019880.s")

void func_8001AA20();                            /* extern */
void func_8001AA90(f32);                            /* extern */
extern void (*D_8004AA38)();

void func_8001A9E8(f32 arg0) {
    func_8001AA90(arg0);
    func_8001AA20();
    D_8004AA38();
}

extern u8 D_8004AC88, D_8004AD08;
extern s32 D_8004AD00;
void func_8001AA20(void) {
    if (D_8004AD00 < 256) {
        if (D_8004AD08 == 0) D_8004AD00++;
        if (D_8004AC88 == 4 || D_8004AC88 == 9) {
            D_8004AD08++;
            if (D_8004AD08 >= 5) D_8004AD08 = 0;
        }
    } else D_8004AD00 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001AA90.s")

void func_8001AD04();                            /* extern */
void func_8001B134();                            /* extern */
void func_8001B620();                            /* extern */
extern s32 D_8004ACF0;
extern s32 D_8004ACF8;

void func_8001AC80(void) {
    s32 temp_t7;

    if (D_8004ACF0 == 2) {
        D_8004ACF8++;
        if (D_8004ACF8 >= 0xC9) {
            func_8001B620();
        }
    } else {
        switch (D_8004ACF0) {                       /* irregular */
        case 0:
            func_8001AD04();
            return;
        default:
        case 1:
            func_8001B134();
            return;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001AD04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001B134.s")

extern f32 cosf(f32), sinf(f32);
extern f64 D_80048998, D_800489A0, D_800489A8, D_800489B0;
extern f32 D_8004A740[], D_8004A800[], D_8004A860[], D_8004A8C0[], D_8004A920[];
extern f32 D_8004ACE0, D_8004ACE4;
void func_8001B50C(s32 arg0) {
    D_8004A860[arg0] = D_8004ACE0 / 3.0f;
    D_8004A920[arg0] = -D_8004ACE4 * 50.0f;
    D_8004A800[arg0] += D_8004ACE0 * cosf((f32)(((f64)D_8004A8C0[arg0] * D_80048998) / D_800489A0));
    D_8004A740[arg0] += D_8004ACE0 * sinf((f32)(((f64)D_8004A8C0[arg0] * D_800489A8) / D_800489B0));
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001B620.s")

extern f64 D_800489D0;
extern f64 D_800489D8;
extern f32 D_8004ACE4;
extern f32 D_8004ACE8;

void func_8001BA18(f32 arg0) {
    if (((D_8004ACE8 * 4.0f) + D_8004ACE4) < arg0) {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 + D_800489D0);
    } else {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 - D_800489D8);
    }
    D_8004ACE4 += D_8004ACE8;
}

extern f64 D_800489E0;
extern f64 D_800489E8;
extern f32 D_8004ACE4;
extern f32 D_8004ACE8;

void func_8001BA94(f32 arg0) {
    if (((D_8004ACE8 * 4.0f) + D_8004ACE4) < arg0) {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 + D_800489E0);
    } else {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 - D_800489E8);
    }
    D_8004ACE4 += D_8004ACE8;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001BB10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001BB64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001BDE0.s")

extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80044A24;
extern f32 D_800489F8;
extern f32 D_800489FC;
extern u8 D_801D7E00;

void func_8001BF1C(u8 **arg0, s32 arg1, s32 arg2, f32 arg3) {
    u8 *temp_v0;
    f32 y;

    temp_v0 = (arg2 * 0x30) + &D_801D7E00;
    y = (*(f32 *)(temp_v0 + 0xF4)) * D_800489F8 - D_800489FC;
    y -= (*(f32 *)(temp_v0 + 0x114)) * 500.0f;
    guTranslate((void *)((((D_80044A24 * 0x28) + arg2) << 6) + 0x80190000), arg3, y, 767.0f);
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    (*(s32 *)((u8 *)(temp_v0) + 0)) = 0x01040040;
    (*(s32 *)((u8 *)(temp_v0) + 4)) = (s32) ((((D_80044A24 * 0x28) + arg2) << 6) + 0x80190000);
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    (*(s32 *)((u8 *)(temp_v0) + 0)) = 0x06000000;
    (*(s32 *)((u8 *)(temp_v0) + 4)) = (s32) *(void **)((u8 *)D_8004A4C0 + (arg1 * 0xC));
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 8;
    (*(s32 *)((u8 *)(temp_v0) + 4)) = 0;
    (*(s32 *)((u8 *)(temp_v0) + 0)) = 0xBD000000;
}


extern u8 D_8004ACC5, D_8004ACC6, D_8004ACC7, D_8004ACC8, D_8004ACC9, D_8004ACCA;
extern u8 D_8004ACCC[3], D_8004ACD0[3], D_8004ACD3;
void func_8001C05C(u8 *arg0) {
    s32 i;
    for (i = 0; i < 3; i++) {
        D_8004ACCC[i] = arg0[i];
        D_8004ACD0[i] = arg0[i+3];
    }
    D_8004ACC5 = arg0[6]; D_8004ACC6 = arg0[7]; D_8004ACC7 = arg0[8];
    D_8004ACC8 = arg0[9]; D_8004ACC9 = arg0[10]; D_8004ACCA = arg0[11];
}

void func_8002FFDC(s32, s16, s32, s16, s32, s32, s32); /* extern */

void func_8001C0E4(s32 *arg0, s16 *arg1, s32 *arg2, s16 *arg3, s32 arg4, s32 *arg5, s32 *arg6, s32 arg7) {
    s16 *var_s2;
    s16 *var_s4;
    s32 *var_s1;
    s32 *var_s3;
    s32 *var_s5;
    s32 *var_s6;
    s32 var_s0;

    var_s0 = 0;
    if (arg7 > 0) {
        var_s1 = arg0;
        var_s2 = arg1;
        var_s3 = arg2;
        var_s4 = arg3;
        var_s5 = arg5;
        var_s6 = arg6;
        do {
            func_8002FFDC(*var_s1, *var_s2, *var_s3, *var_s4, arg4, *var_s5, *var_s6);
            var_s0 += 1;
            var_s1++;
            var_s2++;
            var_s3++;
            var_s4++;
            var_s5++;
            var_s6++;
        } while (var_s0 != arg7);
    }
}


void func_8001C1B0(u8 **arg0, s32 arg1, u8 arg2, u8 arg3) {
    s32 i;
    for (i = 0; i < arg1; i++) {
        u8 value = (arg0[i] + arg2)[12];
        (arg0[i] + arg2)[12] = (arg0[i] + arg3)[12];
        (arg0[i] + arg3)[12] = value;
    }
}


void func_8001C2D4(u8 **arg0, int arg1, int arg2) {
    int i, j;
    for (i = 0; i < arg1; i++) {
        for (j = 0; j < 3; j++) {
            u8 *p = arg0[i] + j;
            p[12] += ((255 - p[12]) * arg2) / 255;
        }
    }
}

void func_8001C370(u8 **arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 i, j;
    s32 value;
    for (i = 0; i < arg1; i++) {
        for (j = 0; j < 3; j++) {
            value = arg3[i * 16 + j + 12] - (func_800326F0() & arg2);
            if (value < 0) arg0[i][j + 12] = 0;
            else arg0[i][j + 12] = value;
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001C43C.s")

extern u8 D_80044ECC[];
extern u8 D_8004AA28, D_8004AC88;
extern void (*D_8004AA30)(void);
extern f32 D_8004AC84;
extern u8 *D_8004ACD8;
extern void func_80019880(void);
extern void func_8001BB10(void), func_8001C05C(u8 *);
void func_8001C534(void) {
    D_8004AC84 = 75.0f;
    D_8004AA28 = 1;
    func_8001BB10();
    D_8004AA30 = func_80019880;
    D_8004AC88 = 0;
    D_8004ACD8 = (u8 *)0x801AAB20;
    func_8001C05C(D_80044ECC);
}

extern s32 D_8004AEB0;

void func_8001C5A0(void) {
    D_8004AEB0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001C5AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001CBCC.s")

extern void func_8001CBCC(f32 *, f32, f32, f32);
extern void guMtxF2L(void *, void *);
void func_8001CD0C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 matrix[4][4];
    func_8001CBCC(&matrix[0][0], arg1, arg2, arg3);
    guMtxF2L(matrix, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001CD50.s")

extern u8 D_8004EA9C[];
s32 osMapTLB(s32, s32, s32, s32, s32, s32);
s32 osUnmapTLB(s32);

void func_8001CF1C(void) {
    s32 i;

    for (i = 0; i < 31; i++) {
        osUnmapTLB(i);
    }
    osMapTLB(0, 0, 0, 0x3A4000, -1, -1);
    for (i = 0; i < 5; i++) {
        osMapTLB(i + 1, 0, (D_8004EA9C[0] << 16) + i * 0x2000 + 0x10000, 0x1DB000 + i * 0x2000, 0x1DC000 + i * 0x2000, -1);
    }
    if (D_8004EA9C[0] != D_8004EA9C[1]) {
        for (i = 0; i < 5; i++) {
            osMapTLB(i + 6, 0, (D_8004EA9C[1] << 16) + i * 0x2000 + 0x10000, 0x1E5000 + i * 0x2000, 0x1E6000 + i * 0x2000, -1);
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001D080.s")


typedef struct { u8 *start; u8 pad[28]; } T022DmaEntry;

extern T022DmaEntry D_80045E68[];
extern u8 D_8004EA9E[];
extern u8 D_8004CE90[][32], D_8004CEB0[], D_8004EA9F;
void func_8001D37C(u8 arg0, u8 arg1) {
    s32 index = arg0;
    boot_dma(((D_8004EA9E[0] == 9 ? 0 : D_8004EA9E[0]) << 5) + D_80045E68[index].start, D_8004CE90, 0x20);
    boot_dma(((D_8004EA9F == 9 ? 0 : D_8004EA9F) << 5) + D_80045E68[arg1].start, D_8004CEB0, 0x20);
}

extern T022DmaEntry D_80045E68[];
void func_8001D42C(u8 arg0, u8 arg1, void *arg2) {
    s32 index = (u8)arg0;
    boot_dma(D_80045E68[index].start + (arg1 << 5), arg2, 0x20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001D47C.s")

typedef struct {
    s32 unk0; void *data; s16 halfWidth, halfHeight, width, height, width2, height2;
    u8 pad[4]; s16 flags; u8 pad2[2];
} T022Sprite;
extern T022Sprite D_8004CED0[];
void func_8001D768(s32 arg0, s32 *arg1) {
    T022Sprite *p = &D_8004CED0[arg0];
    p->data = arg1 + 2;
    p->flags = 7;
    p->width = arg1[0]; p->height = arg1[1];
    p->halfWidth = p->width / 2; p->halfHeight = p->height / 2;
    p->width2 = arg1[0]; p->height2 = arg1[1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001D7E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001DE5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001E0B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001E33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001EC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80020E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800216D4.s")

#ifndef T032_ROM_ENTRY_DEFINED
#define T032_ROM_ENTRY_DEFINED
typedef struct {
    u8 *start, *end, *palette;
    u32 flags;
    u8 *spriteStart, *spriteEnd;
    u8 tail[8];
} T032RomEntry;
#endif
extern T032RomEntry D_80045E50[];
extern u8 D_8011E670[];
void func_80021ADC(u8 player, u8 entry) {
    T032RomEntry *p = &D_80045E50[entry];
    u8 *start = p->spriteStart;
    u32 size = p->spriteEnd - start;
    if (size < 0x321U) {
        boot_dma(start, (void *)0x802D4000, size);
        boot_inflate((void *)0x802D4000, D_8011E670 + player * 0x320, (void *)0x803A2000);
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80021B6C.s")

extern s32 D_8004EA78;
extern u16 D_8004EAC8[][256][2];
s32 func_8002365C(u16 count,u16 start) {
    s32 i; u16 result=320;
    for (i=0;i<count;i++) result=D_8004EAC8[D_8004EA78][start+i][0] >= result ? result : D_8004EAC8[D_8004EA78][start+i][0];
    return result;
}


extern s32 D_8004EA78;
extern u16 D_8004EAC8[][256][2];
s32 func_80023790(u16 count,u16 start) {
    s32 i; u16 result=0;
    for (i=0;i<count;i++) result=D_8004EAC8[D_8004EA78][start+i][1] < result ? result : D_8004EAC8[D_8004EA78][start+i][1];
    return result;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800238C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80023EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80024028.s")

extern void func_80020E98(u8,u8,void *);
extern s32 D_80045FE8;
extern u8 D_8004CE90[][32],D_8004F394;
void func_80024144(s32 player,s32 kind) {
    s32 offset;
    func_80020E98((u8)player,12,0);
    if (kind==0xBA) offset=32; else offset=0;
    boot_dma((void *)(D_80045FE8 + offset),D_8004CE90[player],32);
    D_8004F394=1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800241BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800244F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800245B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80024714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800249DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80024B0C.s")
