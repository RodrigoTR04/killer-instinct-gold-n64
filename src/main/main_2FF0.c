#include "common.h"

u8 D_8004A730[8];
u8 D_8004A738[8];
extern s8 D_8004A5E0[][7];
extern s8 D_8004A688[][7];


extern void boot_inflate(void *, void *, void *);

extern void func_80012B24(u16 *, f32, f32, f32, f32, f32);
extern u8 D_8004AA28;
extern s8 D_8004A984, D_8004ACD4;
extern u8 D_8004AA29;
extern u8 D_8004AC8D;
extern u8 D_8004ACD3, D_8004AD08;
extern u8 D_8004AD09;
extern u8 D_8004AE88, D_8004AE89;
extern u8 D_8004AC8E[], D_8004AC92[];
extern u8 *D_8004ACD8;
extern s32 D_8004ACF0, D_8004AD00, D_8004AD04;
extern f32 D_8004AC80, D_8004ACE0, D_8004AD0C, D_8004AD10;
extern u16 D_8004ACFC;

void func_80012950(s32 arg0) {
    D_8004AA28 = arg0;
    D_8004ACD3 = 0xFF;
    D_8004ACD4 = 0;
    D_8004AE88 = 0;
    D_8004AE89 = 0;
    D_8004ACF0 = 0;
    D_8004ACE0 = 0.0f;
    func_80012B24(&D_8004ACFC, 33.0f, 1.3333333730697632f, 2.0f, 20000.0f, 1.0f);
    D_8004AD00 = 0;
    D_8004AD04 = 0;
    D_8004AD08 = D_8004AD09 = 0;
    D_8004AD0C = 0.0f;
    D_8004AD10 = 0.0f;
    D_8004AC80 = 0.0f;
    D_8004AC92[0] = D_8004AC92[1] = D_8004AC92[2] = 0;
    D_8004AC8E[0] = D_8004AC8E[1] = D_8004AC8E[2] = 0;
    if (D_8004AA28 == 0) D_8004ACD8 = (u8 *)0x803A4200;
    else D_8004ACD8 = (u8 *)0x801AAB20;
    D_8004A984 = 0;
    D_8004AA29 = 0;
    D_8004AC8D = 0;
}

typedef struct {
    u8 *start;
    u8 *end;
} T020RomRange;
extern T020RomRange D_80007260[];
extern void *D_80044DF4[];
extern void boot_dma(s32, s32, s32);
extern void osInvalICache(void *, s32);
extern void osInvalDCache(void *, s32);

void func_80012A8C(u8 arg0) {
    T020RomRange *range;
    osInvalICache((void *)0x802D4000, 0x927C0);
    osInvalDCache((void *)0x802D4000, 0x927C0);
    range = &D_80007260[arg0];
    boot_dma((s32)range->start, 0x80313090, (s32)range->end - (s32)range->start);
    boot_inflate((void *)0x80313090, D_80044DF4[arg0], (void *)0x80311090);
}

extern u8 D_8004AC40[];
extern void guPerspective(void *, u16 *, f32, f32, f32, f32, f32);

void func_80012B24(u16 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    guPerspective(D_8004AC40, arg0, arg1, arg2, arg3, arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80012B7C.s")

typedef struct { u32 command, value; } T033RenderCommand;
extern u8 D_80044A24, D_8004ABC0;
extern u16 D_8004ACFC;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern void
func_8001346C(T033RenderCommand **, u8, f32);
extern void func_8001BB64(T033RenderCommand **);
/* Command scopes and paired stores preserve IDO allocation/scheduling. */
void func_800131A4(T033RenderCommand **arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5)
{
    extern u8 D_4AC40;
    T033RenderCommand *command;
    T033RenderCommand *g;
    s16 part;
    s32 i;
    f32 callbackX;
    g = (*arg0)++; g->command = 0x01020040;
    g->value = (((u32) (&D_8004ABC0)) + (D_80044A24 << 6)) + 0x80000000;
    g = (*arg0)++; g->command = 0x01030040; g->value = (u32)&D_4AC40;
    g = (*arg0)++; g->command = 0xE7000000; g->value = 0;
    func_8001BB64(arg0);
    g = (*arg0)++; g->command = 0xBA001701; g->value = 0;
    g = (*arg0)++;
    g->command = 0xBA001301; g->value = 0x80000;
    g = (*arg0)++; g->command = 0xB9000002; g->value = 0;
    g = (*arg0)++; g->command = 0xF9000000; g->value = 1; {
        T033RenderCommand *g;
        g = (*arg0)++;
        g->command = 0xB4000000;
        g->value = D_8004ACFC;
    }
    {
        T033RenderCommand *g;
        g = (*arg0)++; g->command = 0xBC000404; g->value = 3;
    }
    {
        T033RenderCommand *g;
        g = (*arg0)++; g->command = 0xBC000C04; g->value = 3;
    }
    g = (*arg0)++; g->command = 0xBC001404; g->value = 0xFFFD; command = (*arg0)++; callbackX = arg1; g = command; g->command = 0xBC001C04; g->value = 0xFFFD;
    part = ((s16 (*)(s32, s32, s32, s32, s32)) D_8004AEAC)((s32) callbackX, (s32) arg2, (s32) arg3, (s32) arg4, (s32) arg5);
    i = 0;
    if (D_8004A738[part] > 0) {
        do
        {
            func_8001346C(arg0, ((u8 (*)[7])D_8004A688)[i][part], arg1);
            g = (*arg0)++; g->command = 0xE7000000; g->value = 0;
            g = (*arg0)++; i = (s16)(i+1); g->command = 0xB9000002; g->value = 0;
        }
        while (i < D_8004A738[part]);
    }
}

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

typedef struct {
    u8 pad0[0xC];
    f32 x, y, z;
    u8 pad18[0x10];
    s16 vx, vy, vz;
} T020ForceTarget;
extern f32 D_800487F4, D_800487F8;
void func_8001373C(void *object, f32 x, f32 y, f32 z, u8 strengthX, u8 strengthY, u8 strengthZ)
{
    T020ForceTarget *target = object;
    f32 distance;
    s16 impulseX, impulseY, impulseZ;
    distance = (target->x - x) * (target->x - x)
             + (target->y - y) * (target->y - y)
             + (target->z - z) * (target->z - z);
    if (distance < D_800487F4) distance = D_800487F8;
    impulseX = (s32)((f32)(strengthX * 30000) / distance);
    impulseY = (s32)((f32)(strengthY * 30000) / distance);
    target->vx += impulseX;
    target->vy += impulseY;
    impulseZ = (s32)((f32)(strengthZ * 30000) / distance);
    target->vz += impulseZ;
}

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
extern u8 D_8004AC89;
extern u8 D_8004AC8A;
extern s8 D_8004AC8C;
extern u8 D_8004ACC5, D_8004ACC6, D_8004ACC7, D_8004ACC8, D_8004ACC9, D_8004ACCA;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern f32 D_800614D8[];
extern u8 D_80061520;
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
extern void func_8001C43C(s32, u8 *, u8 *, u8 *, u8 *);
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
extern f32 D_8004A9FC;
extern s32 D_8004ACF0;
extern f32 D_80061CC8[];
extern s16 D_8004A530;

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


extern u8 D_54E7D0[], D_551E60[];

void func_80013C84(void) {
    boot_dma((s32)D_54E7D0, (s32)0x802D4000, (s32)D_551E60 - (s32)D_54E7D0);
    boot_inflate((void *)0x802D4000, (void *)0x803A4200, (void *)0x803A2000);
}

typedef struct { void *display; s16 flags, pad; s32 transform; } T03313CD8StagePart;
typedef struct { f32 pitch, yaw, roll, speed, scale; } T03313CD8StageRotation;
extern u8 D_80044ED8;
extern u8 D_80045374;
extern u8 D_800453A8;
extern u8 D_800453C4;
extern u8 D_800453F8;
extern u8 D_80045414;
extern u8 D_80045448;
extern u8 D_8004547C;
extern u8 D_80045484;
extern u8 D_800454CC;
extern u8 D_800454D4;
extern f32 D_8004A740[];
extern f32 D_8004A7A0;
extern u8 D_8004ACCC[3], D_8004ACD0[3], D_8004ACD3;
extern s8 D_8004ACD4;
extern s32 D_8004ACF8;
extern u8 D_801990E0;
extern u8 D_8019AA30;
extern u8 D_8019AFB0;
extern u8 D_8019B8E0;
extern u8 D_8019BDE0;
extern u8 D_8019C890[], D_8019F450[];
extern u8 D_8019DD80;
extern u8 D_8019E340;
extern u8 D_801A0560;
extern u8 D_801A1330;
extern u8 D_801A1B40;
extern u8 D_802EABF8;
extern u8 D_802EAC94;
extern u8 D_802EAD30;
extern s32 func_8001414C(s32, s32, s32, s32);
extern void func_80014250();
extern void func_800142E0();
extern void func_80014C40();
extern void func_80014D5C();
extern void func_80019880();
extern void func_8001BB10();
extern void func_8001C1B0(u8 **, s32, u8, u8);
extern void func_8001C2D4(u8 **, int, int);
extern u32 func_800326F0();

extern f32 D_8004A800[];
extern f32 D_8004A860[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
void func_80013CD8(void) {
    ((T03313CD8StagePart *)D_8004A4C0)[0].display = &D_8019AFB0;
    ((T03313CD8StagePart *)D_8004A4C0)[1].display = &D_8019B8E0;
    ((T03313CD8StagePart *)D_8004A4C0)[2].display = &D_8019BDE0;
    ((T03313CD8StagePart *)D_8004A4C0)[3].display = &D_8019C890;
    ((T03313CD8StagePart *)D_8004A4C0)[4].display = &D_8019DD80;
    ((T03313CD8StagePart *)D_8004A4C0)[5].display = &D_8019E340;
    ((T03313CD8StagePart *)D_8004A4C0)[6].display = &D_8019F450;
    ((T03313CD8StagePart *)D_8004A4C0)[7].display = &D_801A0560;
    ((T03313CD8StagePart *)D_8004A4C0)[8].display = &D_801A1330;
    ((T03313CD8StagePart *)D_8004A4C0)[9].display = &D_8019AA30;
    ((T03313CD8StagePart *)D_8004A4C0)[10].flags = 0x11;
    ((T03313CD8StagePart *)D_8004A4C0)[11].flags = 0x21;
    ((T03313CD8StagePart *)D_8004A4C0)[0].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[1].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[2].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[3].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[4].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[5].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[6].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[7].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[8].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[9].flags = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[10].display = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[10].transform = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[11].display = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[11].transform = 1;
    ((T03313CD8StagePart *)D_8004A4C0)[12].display = 0;
    ((T03313CD8StagePart *)D_8004A4C0)[12].flags = 0x31;
    ((T03313CD8StagePart *)D_8004A4C0)[12].transform = 2;
    func_8001C43C(7, &D_8004547C, &D_80045484, &D_800454CC, &D_800454D4);
    D_8004A740[0] = -3000.0f;
    (&D_8004A7A0)[0] = 0.0f;
    D_8004A800[0] = 0.0f;
    D_8004A860[0] = 0.0f;
    D_8004A8C0[0] = 0.0f;
    D_8004A920[0] = 0.0f;
    D_8004A740[1] = -2300.0f;
    ((void **)&D_8004A998)[0] = &D_801A1B40;
    ((void **)&D_8004A998)[1] = 0;
    ((void **)&D_8004A998)[2] = 0;
    ((void **)&D_8004A998)[3] = 0;
    ((void **)&D_8004A998)[4] = &D_801A1B40;
    ((void **)&D_8004A998)[5] = 0;
    ((void **)&D_8004A998)[6] = 0;
    ((void **)&D_8004A998)[7] = 0;
    ((void **)&D_8004A998)[8] = &D_801A1B40;
    ((void **)&D_8004A998)[9] = 0;
    ((void **)&D_8004A998)[10] = 0;
    ((void **)&D_8004A998)[11] = 0;
    ((void **)&D_8004A998)[12] = &D_801A1B40;
    ((void **)&D_8004A998)[13] = 0;
    ((void **)&D_8004A998)[14] = 0;
    ((void **)&D_8004A998)[15] = 0;
    D_8004A740[2] = -1600.0f;
    (&D_8004A7A0)[1] = 0.0f;
    D_8004A800[1] = 0.0f;
    D_8004A860[1] = 0.0f;
    D_8004A8C0[1] = 0.0f;
    D_8004A920[1] = 0.0f;
    (&D_8004A7A0)[2] = 0.0f;
    D_8004A800[2] = 0.0f;
    D_8004A860[2] = 0.0f;
    D_8004A8C0[2] = 0.0f;
    D_8004A920[2] = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[0].pitch = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[0].yaw = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[0].roll = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[1].pitch = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[1].yaw = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[1].roll = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[2].pitch = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[2].yaw = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[2].roll = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[3].pitch = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[3].yaw = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[3].roll = 0.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[0].speed = 3.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[1].speed = 4.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[2].speed = 5.0f;
    ((T03313CD8StageRotation *)&D_8004A9D8)[3].speed = 6.0f;
    D_8004AEAC = &func_8001414C;
    D_8004AA34 = &func_80014C40;
    D_8004AA38 = &func_80014D5C;
    D_8004AA3C = &D_801990E0;
    D_8004AC80 = 0.0f;
    D_8004AC84 = 230.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 0;
    D_8004AC8C = 7;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    D_8004ACF0 = 1;
    D_8004ACF8 = (func_800326F0() & 0x3FF) + 0x12C;
    func_8001C0E4(&D_80045374, &D_800453A8, &D_800453C4, &D_800453F8, &D_802EABF8, &D_80045414, &D_80045448, 0xD);
    func_80030020(&D_802EAC94, &D_802EABF8, &D_802EAD30, 0x27);
    func_8001C2D4((u8 **)&D_80044ED8, 0x45, 0x80);
    D_8004AA30 = &func_800142E0;
    if (D_8004AA28 == 0) {
        func_80014250();
    } else {
        func_8001BB10();
        D_8004AA30 = &func_80019880;
        D_8004ACCC[0] = 0xFF;
        D_8004ACCC[1] = 0;
        D_8004ACCC[2] = 0;
        D_8004ACD0[0] = 0xFF;
        D_8004ACD0[1] = 0xC0;
        D_8004ACD0[2] = 4;
        D_8004ACC5 = 0;
        D_8004ACC6 = 0;
        D_8004ACC7 = 0;
        D_8004ACC8 = 0x30;
        D_8004ACC9 = 0;
        D_8004ACCA = 0;
        D_8004ACD3 = 0xFF;
        D_8004ACD4 = 0;
    }
    func_8001C1B0((u8 **)&D_80044ED8, 0x56, 0, 1);
}

extern u8 D_8004A401;

s32 func_8001414C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 >= 356) D_8004A4C0[18] = 0;
    else D_8004A4C0[18] = D_8019F450;
    if (arg2 < -700) D_8004A4C0[9] = 0;
    else D_8004A4C0[9] = D_8019C890;
    if (arg2 < -518 && arg0 >= -697 && arg0 < 170) {
        if (D_8004A401 == 1) {
            D_8004A730[6] = 9;
        } else {
            D_8004A730[6] = 12;
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

extern u8 D_1F4290, D_1F6700, D_1F7780;

void func_80014250(void) {
    boot_dma((s32)&D_1F4290, 0x802D4000, (u32)&D_1F6700 - (s32)&D_1F4290);
    boot_inflate((void *)0x802D4000, (void *)0x803A4200, (void *)0x803A2000);
    boot_dma((s32)&D_1F6700, 0x802D4000, (u32)&D_1F7780 - (s32)&D_1F6700);
    boot_inflate((void *)0x802D4000, (void *)0x803AC908, (void *)0x803A2000);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800142E0.s")

typedef struct {
    u8 pad[0x28];
    s16 vx, vy, vz;
} T033ForceTarget;
extern void func_8001373C(void *, f32, f32, f32, u8, u8, u8);

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

typedef struct T05518664Obj {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 pad1[0x53];
    /* 0x54 */ s16 vx;
    /* 0x56 */ s16 vy;
    /* 0x58 */ u8 pad58[0xA8];
} T05518664Obj;
extern T05518664Obj D_801D3430[40];

typedef struct {
    u8 kind;
    u8 pad1[11];
    s32 x;
    u8 pad10[0x44];
    u8 active, pad55, index;
    u8 pad57[0x2D];
    s16 speed;
    u8 pad86[0x7A];
} T033RotatingObject;
typedef struct { f32 pitch, yaw; u8 pad[12]; } T033Rotation;
extern u8 D_8004A9D8;

void func_80015450(s32 arg0)
{
  s32 i; T033RotatingObject *obj; s32 kind; for (i = 0; i < 40; i++)
  {
    obj = (T033RotatingObject *)&D_801D3430[i]; kind = obj->kind;
    if (kind == 0x3B)
    {
      ((T033Rotation *) (&D_8004A9D8))[obj->index].yaw = ((T033Rotation *) (&D_8004A9D8))[obj->index].yaw + (obj->speed / 50.0);
      while (((T033Rotation *) (&D_8004A9D8))[obj->index].yaw >= 360.0f)
      {
        ((T033Rotation *) (&D_8004A9D8))[obj->index].yaw -= 360.0f;
      }

      if ((obj->active != 0) && (((T033Rotation *) (&D_8004A9D8))[obj->index].pitch < 90.0f))
      {
        ((T033Rotation *) (&D_8004A9D8))[obj->index].pitch += 2.0f;
      }
      if (obj->active != 0)
      {
        if (arg0 < obj->x)
        {
          obj->x -= 128;
        }
        else
          if (obj->x < arg0)
        {
          obj->x = arg0;
        }
      }
    }
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_80015594.s")

extern s32 D_800698C4;
extern u8 D_8018E6D0[], D_8018EA70[], D_80193F40[], D_80195310[];
extern u8 D_80196730[], D_80197B10[], D_80198470[], D_80198F00[];

s32 func_80015B64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 x;
    if (D_800698C4 != 0) D_8004A738[0] = 2;
    else D_8004A738[0] = 0;
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
extern u8 *D_8004ACD8;
extern u8 D_801776D0;
extern u8 D_8018EE10;
extern u8 D_80192520;
extern u8 D_80199940;
extern u8 D_80199B60;
extern u8 D_80199DA0;
extern u8 D_802E7E74;
extern u8 D_802E7EEC;
extern u8 D_802E7F64;
extern s32 func_80015B64(s32, s32, s32, s32);
extern void func_80015F6C();
extern void func_8001C05C(u8 *);

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


extern s32 D_8004A264, D_8004ACF8, D_80066C40;
extern s16 D_8004A986;
extern void func_8002F8F8(void *);
extern void *func_8002F6F4(void *, s16, void **);


void func_80015F6C(void)
{
  s32 timer = D_8004ACF8;
  if ((timer < 20) && ((timer % 10) < 5))
  {
    D_8004ACD0[0] = D_8004ACD0[1] = 255;
    D_8004ACD0[2] = 255;
  }
  else
  {
    D_8004ACD0[0] = (&D_80044E4C)[3];
    D_8004ACD0[1] = (&D_80044E4C)[4];
    D_8004ACD0[2] = (&D_80044E4C)[5];
  }
  if (D_8004A986 > 0)
  {
    D_8004A986--;
    if (D_8004A986 == 1)
    {
      func_8002F8F8((void *)D_8004A264);
      func_8002F6F4((void *)D_80066C40, 0x1A2, (void **)&D_8004A264);
      timer = D_8004ACF8;
    }
  }
  if (timer > 0)
  {
    D_8004ACF8 = timer - 1;
    return;
  }
  D_8004ACF8 = (func_800326F0() & 0x1FF) + 220;
  D_8004A986 = 70;
}

extern u32 D_8004A428[];
extern T033RenderCommand D_80068930[][200];
/* Encode the two words of a fill rectangle, evaluating pkt once. */
#define FILL_RECTANGLE_COMMAND(pkt, x0, y0, x1, y1) { \
    T033RenderCommand *rect = (pkt); \
    rect->command = (((x1) & 0x3FF) << 14) | 0xF6000000 | (((y1) & 0x3FF) << 2); \
    rect->value = (((x0) & 0x3FF) << 14) | (((y0) & 0x3FF) << 2); \
}
void func_80016078(T033RenderCommand **arg0, s32 *arg1, s32 arg2, s32 arg3) {
    T033RenderCommand *g, *p0, *p1;
    s32 color;
    T033RenderCommand *p3, *p4, *p5, *p7, *p2;
    g = D_80068930[D_80044A24];
    *arg0 = g;
    p0 = g++; p0->command = 0xE7000000; p0->value = 0;
    p1 = g++;
    p1->command = 0xED000000;
    p1->value = (((s32)((f32)(320 << D_8004AA28) * 4.0f) & 0xFFF) << 12) |
    ((s32)((f32)(240 << D_8004AA28) * 4.0f) & 0xFFF);
    p2 = g++;
    p2->command = 0xFCFFFFFF; p2->value = 0xFFFE793C;
    p3 = g++;
    p3->command = (((320 << D_8004AA28) - 1) & 0xFFF) | 0xFF100000;
    p3->value = D_8004A428[D_80044A24];
    p4 = g++;
    p4->command = 0x2F300000;
    p4->value = 0;
    p5 = g++;
    p5->command = 0xF7000000;
    color = ((D_8004ACC5 << 8) & 0xF800) | ((D_8004ACC6 << 3) & 0x7C0) | ((D_8004ACC7 >> 2) & 0x3E) | 1;
    p5->value = (color << 16) | color;
    FILL_RECTANGLE_COMMAND(g++, 0, 0, (320 << D_8004AA28) - 1, (240 << D_8004AA28) - 1);
    p7 = g++;
    p7->command = 0xE9000000;
    p7->value = 0;
    *arg1 = (g - *arg0) * 8;
}

#undef FILL_RECTANGLE_COMMAND


extern u8 D_8004509C[], D_800450A4[], D_8004511C[], D_80045124[];
extern u8 D_80044E70, D_80044EB8;

extern u8 D_80045630, D_80045684, D_800456B0, D_80045704, D_80045730, D_80045784;
extern s16 D_8004A986;
extern f32 D_8004A988;
extern u8 D_801726D0, D_801946D0, D_80195590, D_80195C00, D_80195F10, D_80196B70, D_80196D90, D_80197580;
extern u8 D_8019A1C0, D_8019A4A0, D_8019ABA0, D_8019BB10, D_8019C340, D_8019CB70, D_8019D3A0, D_8019DBD0;
extern u8 D_8019DD20, D_8019E310, D_801A1580, D_801A1950, D_801A1C60;
extern u8 D_802E8EA0, D_802E8F28, D_802E8FB0;
extern s32 func_80016824(s32, s32, s32, s32);
extern void func_80016908();
extern void func_80016910();
extern s32 func_800281C4(s32);

void func_80016258(void) {
    s32 i;

    if (D_8004AC88 == 6) {
        func_8001C05C(&D_80044E70);
    } else {
        func_8001C05C(&D_80044EB8);
    }
    ((T0331383CStagePart *)D_8004A4C0)[0].display = &D_801946D0;
    ((T0331383CStagePart *)D_8004A4C0)[1].display = &D_80195F10;
    ((T0331383CStagePart *)D_8004A4C0)[2].display = &D_8019DBD0;
    ((T0331383CStagePart *)D_8004A4C0)[3].display = &D_8019ABA0;
    ((T0331383CStagePart *)D_8004A4C0)[4].display = &D_80196D90;
    ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_80197580;
    ((T0331383CStagePart *)D_8004A4C0)[6].display = &D_8019DD20;
    ((T0331383CStagePart *)D_8004A4C0)[7].display = &D_8019BB10;
    ((T0331383CStagePart *)D_8004A4C0)[8].display = &D_8019C340;
    ((T0331383CStagePart *)D_8004A4C0)[9].display = &D_8019CB70;
    ((T0331383CStagePart *)D_8004A4C0)[10].display = &D_8019D3A0;
    ((T0331383CStagePart *)D_8004A4C0)[11].display = &D_8019E310;
    ((T0331383CStagePart *)D_8004A4C0)[16].display = &D_8019A1C0;
    ((T0331383CStagePart *)D_8004A4C0)[0].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[1].flags = 4;
    ((T0331383CStagePart *)D_8004A4C0)[2].flags = 4;
    ((T0331383CStagePart *)D_8004A4C0)[3].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[4].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[5].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[6].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[7].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[8].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[9].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[10].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[11].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[12].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[12].flags = 3;
    ((T0331383CStagePart *)D_8004A4C0)[13].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[13].flags = 3;
    ((T0331383CStagePart *)D_8004A4C0)[14].transform = 2;
    ((T0331383CStagePart *)D_8004A4C0)[14].flags = 3;
    ((T0331383CStagePart *)D_8004A4C0)[15].transform = 3;
    ((T0331383CStagePart *)D_8004A4C0)[15].flags = 3;
    ((T0331383CStagePart *)D_8004A4C0)[16].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[17].display = &D_801A1580;
    ((T0331383CStagePart *)D_8004A4C0)[17].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[17].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[18].display = &D_80195590;
    ((T0331383CStagePart *)D_8004A4C0)[18].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[19].display = &D_80195C00;
    ((T0331383CStagePart *)D_8004A4C0)[19].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[20].display = &D_80196B70;
    ((T0331383CStagePart *)D_8004A4C0)[20].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[21].display = &D_801A1950;
    ((T0331383CStagePart *)D_8004A4C0)[21].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[21].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[22].display = &D_801A1C60;
    ((T0331383CStagePart *)D_8004A4C0)[22].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[22].transform = 2;
    func_8001C43C(7, D_8004509C, D_800450A4, D_8004511C, D_80045124);
    for (i = 0; i < 7; i++) {
        D_8004A730[i]--;
    }
    if (D_8004AC88 == 6) {
        for (i = 0; i < 7; i++) {
            D_8004A730[i] -= 2;
        }
    }
    D_8004A860[0] = 0.0f;
    D_8004A8C0[0] = 0.0f;
    D_8004A920[0] = 0.0f;
    D_8004A860[1] = 0.0f;
    D_8004A8C0[1] = 0.0f;
    D_8004A920[1] = 0.0f;
    D_8004A860[2] = 0.0f;
    D_8004A8C0[2] = 0.0f;
    D_8004A920[2] = 0.0f;
    D_8004AA3C = &D_8019A4A0;
    D_8004AEAC = &func_80016824;
    D_8004AA30 = &func_80019880;
    D_8004AA38 = &func_80016910;
    D_8004ACD8 = &D_801726D0;
    D_8004AA34 = &func_80016908;
    if (D_8004AA28 == 0) {
        func_800281C4(1);
    }
    D_8004AC80 = 0.0f;
    D_8004AC84 = 205.0f;
    D_8004AC89 = 2;
    D_8004AC8A = 1;
    if (D_8004AC88 == 6) {
        D_8004AC8C = 11;
    } else {
        D_8004AC8C = 18;
    }
    func_80028600(4, D_8004AC84, D_8004AC84, 0xFF);
    (&D_80061520)[0] = (&D_80061520)[1] = (&D_80061520)[2] = (&D_80061520)[3] = 20;
    D_8004A988 = 0.0f;
    D_8004A986 = 0;
    D_800614D8[0] = -162.0f;
    D_800614D8[1] = 136.0f;
    D_800614D8[2] = -153.0f;
    D_800614D8[3] = 607.0f;
    D_800614D8[4] = 136.0f;
    D_800614D8[5] = -144.0f;
    D_800614D8[6] = -162.0f;
    D_800614D8[7] = 136.0f;
    D_800614D8[8] = 626.0f;
    D_800614D8[9] = 620.0f;
    D_800614D8[10] = 136.0f;
    D_800614D8[11] = 626.0f;
    D_80061CB8[0] = 0xFF;
    D_80061CB8[1] = 0xFF;
    D_80061CB8[2] = 0xFF;
    D_80061CB8[3] = 0xFF;
    D_80061CB8[4] = 0xFF;
    D_80061CB8[5] = 0;
    D_80061CB8[6] = 0xFF;
    D_80061CB8[7] = 0;
    D_80061CB8[8] = 0;
    func_8001C0E4(&D_80045630, &D_80045684, &D_800456B0, &D_80045704, (s32)&D_802E8EA0, &D_80045730, &D_80045784, 0x15);
    func_80030020(&D_802E8F28, &D_802E8EA0, &D_802E8FB0, 0x22);
}


void func_80016760(s32 arg0) {
    s32 i;
    func_8001C43C(7, D_8004509C, D_800450A4, D_8004511C, D_80045124);
    for (i = 0; i < 7; i++) {
        D_8004A730[i] = D_8004A730[i] - arg0;
    }
}

extern u8 D_8004514C[], D_80045154[], D_800451DC[], D_800451E4[];

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

extern f32 sinf(f32), cosf(f32);
extern void func_8002DBDC(f32, f32 *), func_8002DC48(f32 *);
extern f32 D_8004ACE0;
extern f32 D_8004A98C, D_8004A990, D_8004A994;
extern f32 D_80061CD0;


void func_80016910(void) {
    if (D_8004A986 > 0) D_8004A986--;
    else {
        D_8004A986 = func_800326F0() & 255;
        D_8004A98C = (f32)(func_800326F0() & 255);
        D_8004A994 = (f32)(func_800326F0() % 360U);
    }
    D_8004A988 += (D_8004A98C - D_8004A988) / 5.0f;
    func_8002DBDC(D_8004A994, &D_8004A990);
    D_8004A990 += (D_8004A994 - D_8004A990) / 10.0f;
    func_8002DC48(&D_8004A990);
    D_80061CC8[0] = sinf((D_8004A990 * 3.14159) / 180.0) * D_8004A988 / (f32)256;
    D_80061CC8[1] = 0.0f;
    D_80061CD0 = cosf((D_8004A990 * 3.14159) / 180.0) * D_8004A988 / (f32)256;
    if (((u8 *)D_801D3430)[-0x7B] != 0) D_8004ACE0 = 4.0f;
    if (((u8 *)D_801D3430)[-0x7A] != 0) D_8004ACE0 = 0.0f;
    if (D_8004ACE0 > 4.0f) D_8004ACE0 = 4.0f;
    D_8004A8C0[1] += D_8004ACE0;
    D_8004A8C0[2] += D_8004ACE0;
    D_8004ACE0 -= D_8004ACE0 / 20.0f;
    while ((359.0f) < D_8004A8C0[0]) D_8004A8C0[0] -= 360.0f;
    while ((359.0f) < D_8004A8C0[1]) D_8004A8C0[1] -= 360.0f;
}



typedef struct T05516BE0Vtx_t {
    /* 0x00 */ s16 ob[3];
    /* 0x06 */ u16 flag;
    /* 0x08 */ s16 tc[2];
    /* 0x0C */ u8 cn[4];
} T05516BE0Vtx_t;

typedef union T05516BE0Vtx {
    T05516BE0Vtx_t v;
    s64 force_structure_alignment;
} T05516BE0Vtx;

extern u8 D_80044E7C;
extern T05516BE0Vtx *D_80045030[12];
extern T05516BE0Vtx *D_80045060[10];
extern u8 D_800457D8, D_800457FC, D_80045810, D_80045834, D_80045848, D_8004586C;
extern T05516BE0Vtx D_8004AD28[12];
extern T05516BE0Vtx D_8004ADE8[10];
extern u8 D_8018FED0[];
extern u8 D_8018AED0, D_8018FD90, D_801931C0, D_801943C0, D_801953B0, D_80195800;
extern u8 D_802E44E8, D_802E454C, D_802E45B0;
extern s32 func_80017064(s32, s32, s32, s32);
extern void func_800170C4();
extern void func_8001BB10(void);

void func_80016BE0(void) {
    s32 i;

    ((T0331383CStagePart *)D_8004A4C0)[1].display = D_8018FED0;
    ((T0331383CStagePart *)D_8004A4C0)[2].display = &D_801931C0;
    ((T0331383CStagePart *)D_8004A4C0)[3].display = &D_8018AED0;
    ((T0331383CStagePart *)D_8004A4C0)[4].display = &D_8018FD90;
    ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_801943C0;
    ((T0331383CStagePart *)D_8004A4C0)[0].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[0].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[1].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[2].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[3].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[4].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[5].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[6].display = &D_801953B0;
    ((T0331383CStagePart *)D_8004A4C0)[6].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[7].display = &D_80195800;
    ((T0331383CStagePart *)D_8004A4C0)[7].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[7].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[8].display = &D_80195800;
    ((T0331383CStagePart *)D_8004A4C0)[8].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[8].transform = 1;
    D_8004A730[0] = 8;
    ((u8 (*)[7])D_8004A5E0)[0][0] = 4;
    ((u8 (*)[7])D_8004A5E0)[1][0] = 3;
    ((u8 (*)[7])D_8004A5E0)[2][0] = 2;
    ((u8 (*)[7])D_8004A5E0)[3][0] = 0;
    ((u8 (*)[7])D_8004A5E0)[4][0] = 5;
    ((u8 (*)[7])D_8004A5E0)[5][0] = 6;
    ((u8 (*)[7])D_8004A5E0)[6][0] = 7;
    ((u8 (*)[7])D_8004A5E0)[7][0] = 8;
    D_8004A738[0] = 0;
    D_8004A730[1] = 9;
    ((u8 (*)[7])D_8004A5E0)[0][1] = 4;
    ((u8 (*)[7])D_8004A5E0)[1][1] = 3;
    ((u8 (*)[7])D_8004A5E0)[2][1] = 1;
    ((u8 (*)[7])D_8004A5E0)[3][1] = 2;
    ((u8 (*)[7])D_8004A5E0)[4][1] = 0;
    ((u8 (*)[7])D_8004A5E0)[5][1] = 5;
    ((u8 (*)[7])D_8004A5E0)[6][1] = 6;
    ((u8 (*)[7])D_8004A5E0)[7][1] = 7;
    ((u8 (*)[7])D_8004A5E0)[8][1] = 8;
    D_8004A738[1] = 0;
    D_8004A730[2] = 8;
    ((u8 (*)[7])D_8004A5E0)[0][2] = 4;
    ((u8 (*)[7])D_8004A5E0)[1][2] = 3;
    ((u8 (*)[7])D_8004A5E0)[2][2] = 1;
    ((u8 (*)[7])D_8004A5E0)[3][2] = 2;
    ((u8 (*)[7])D_8004A5E0)[4][2] = 5;
    ((u8 (*)[7])D_8004A5E0)[5][2] = 6;
    ((u8 (*)[7])D_8004A5E0)[6][2] = 7;
    ((u8 (*)[7])D_8004A5E0)[7][2] = 8;
    D_8004A738[2] = 0;
    D_8004A740[0] = 1000.0f;
    (&D_8004A7A0)[0] = 0.0f;
    D_8004A800[0] = -350.0f;
    D_8004A860[0] = 0.0f;
    D_8004A8C0[0] = 0.0f;
    D_8004A920[0] = 0.0f;
    D_8004A740[1] = -1400.0f;
    (&D_8004A7A0)[1] = 0.0f;
    D_8004A800[1] = -916.0f;
    D_8004A860[1] = 0.0f;
    D_8004A8C0[1] = 0.0f;
    D_8004A920[1] = 0.0f;
    D_8004AA3C = 0;
    D_8004AEAC = &func_80017064;
    D_8004AA38 = &func_800170C4;
    D_8004AA34 = &func_8001372C;
    func_8001BB10();
    D_8004AA30 = &func_80019880;
    func_8001C05C(&D_80044E7C);
    D_8004AC80 = 0.0f;
    D_8004AC84 = 60.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 1;
    D_8004AC8C = 12;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    func_8001C0E4(&D_800457D8, &D_800457FC, &D_80045810, &D_80045834, (s32)&D_802E44E8, &D_80045848, &D_8004586C, 9);
    func_80030020(&D_802E454C, &D_802E44E8, &D_802E45B0, 0x19);
    for (i = 0; i < 12; i++) {
        D_8004AD28[i] = *D_80045030[i];
    }
    for (i = 0; i < 10; i++) {
        D_8004ADE8[i] = *D_80045060[i];
    }
    for (i = 0; i < 10; i++) {
        D_80045060[i]->v.cn[2] = 0x80;
        D_80045060[i]->v.cn[0] = D_80045060[i]->v.cn[1] = D_80045060[i]->v.cn[2];
    }
}


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


typedef struct { u8 kind, pad1[0x53]; s16 speed; u8 pad56[0xAA]; } T033170C4Object;
typedef struct { void *display; s16 flags, pad; s32 transform; } T033170C4StagePart;
extern void *D_8004A4C0[];
extern u8 D_8004AC8D;
extern u8 D_801939F0;
extern s32 D_801C4234;
extern s32 D_801C4334;
extern u8 D_801D7DF7;
extern void func_8001C370(u8 **, s32, s32, u8 *);

extern f32 D_8004A920[];
void func_800170C4(void) {
    T033170C4Object *object;
    s32 i;
    s32 kind;

    if (D_801D7DF7 == 1) {
        D_8004AC8D = 1;
    }
    if (D_8004AC8D == 1) {
        D_8004AC8D = 2;
        ((T033170C4StagePart *)D_8004A4C0)[6].display = 0;
        ((T033170C4StagePart *)D_8004A4C0)[0].display = &D_801939F0;
        D_801C4234 = 0x1F0A5;
        D_801C4334 = 0x210D7;
        for (i = 0; i < 10; i++) {
            *D_80045060[i] = D_8004ADE8[i];
        }
    }
    for (i = 0; i < 40; i++) {
        object = (T033170C4Object *)&D_801D3430[i];
        kind = object->kind;
        if (kind == 0x3C) {
            D_8004A920[0] -= (f32) object->speed / 200.0f;
            if (D_8004A920[0] > 20.0f) {
                D_8004A920[0] = 20.0f;
            } else if (D_8004A920[0] < -20.0f) {
                D_8004A920[0] = -20.0f;
            }
            object->speed += (D_8004A920[0] * 256.0f) / 200.0f;
        }
    }
    func_8001C370((u8 **)D_80045030, 0xC, 0x3F, (u8 *)D_8004AD28);
}


extern u8 D_80045890, D_800458C0, D_800458D8, D_80045908, D_80045920, D_80045950;
extern f32 D_8004A980;
extern u8 D_8004ACC5, D_8004ACC6, D_8004ACC7;
extern u8 D_8019DDF0, D_801A2080, D_801A24E0, D_801A63D0, D_801A6950, D_801A6AD0, D_801A7840, D_801A7CA0, D_801AB7D0;
extern u8 D_802EBFAC, D_802EC078, D_802EC144;
extern void func_800142E0();
extern s32 func_80017A50(s32, s32, s32, s32);
extern void func_80017A68();
extern void func_80017D6C();
extern void func_8001B620();

void func_80017378(void) {
    s32 i;
    void **model;
    T0331383CStageRotation *rot;

    ((T0331383CStagePart *)D_8004A4C0)[0].display = &D_801A24E0;
    ((T0331383CStagePart *)D_8004A4C0)[0].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[0].transform = 7;
    ((T0331383CStagePart *)D_8004A4C0)[1].display = &D_801A63D0;
    ((T0331383CStagePart *)D_8004A4C0)[1].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[1].transform = 0;
    ((T0331383CStagePart *)D_8004A4C0)[2].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[2].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[3].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[3].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[4].display = &D_801A2080;
    ((T0331383CStagePart *)D_8004A4C0)[4].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[4].transform = 8;
    ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_801A7840;
    ((T0331383CStagePart *)D_8004A4C0)[5].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[6].display = &D_801A7CA0;
    ((T0331383CStagePart *)D_8004A4C0)[6].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[7].display = &D_8019DDF0;
    ((T0331383CStagePart *)D_8004A4C0)[7].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[8].display = &D_801AB7D0;
    ((T0331383CStagePart *)D_8004A4C0)[8].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[10].display = &D_801A6AD0;
    ((T0331383CStagePart *)D_8004A4C0)[10].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[10].transform = 1;
    ((T0331383CStagePart *)D_8004A4C0)[11].display = &D_801A6AD0;
    ((T0331383CStagePart *)D_8004A4C0)[11].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[11].transform = 2;
    ((T0331383CStagePart *)D_8004A4C0)[12].display = &D_801A6AD0;
    ((T0331383CStagePart *)D_8004A4C0)[12].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[12].transform = 3;
    ((T0331383CStagePart *)D_8004A4C0)[13].display = &D_801A6AD0;
    ((T0331383CStagePart *)D_8004A4C0)[13].flags = 0;
    ((T0331383CStagePart *)D_8004A4C0)[15].display = &D_801A24E0;
    ((T0331383CStagePart *)D_8004A4C0)[15].flags = 2;
    ((T0331383CStagePart *)D_8004A4C0)[15].transform = 6;
    ((T0331383CStagePart *)D_8004A4C0)[16].display = &D_801A2080;
    ((T0331383CStagePart *)D_8004A4C0)[16].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[16].transform = 9;
    ((T0331383CStagePart *)D_8004A4C0)[17].display = &D_801A2080;
    ((T0331383CStagePart *)D_8004A4C0)[17].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[17].transform = 10;
    ((T0331383CStagePart *)D_8004A4C0)[18].display = &D_801A2080;
    ((T0331383CStagePart *)D_8004A4C0)[18].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[18].transform = 11;
    ((T0331383CStagePart *)D_8004A4C0)[19].display = &D_801A2080;
    ((T0331383CStagePart *)D_8004A4C0)[19].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[19].transform = 12;
    ((T0331383CStagePart *)D_8004A4C0)[20].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[20].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[20].transform = 13;
    ((T0331383CStagePart *)D_8004A4C0)[21].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[21].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[21].transform = 14;
    ((T0331383CStagePart *)D_8004A4C0)[22].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[22].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[22].transform = 15;
    ((T0331383CStagePart *)D_8004A4C0)[23].display = &D_801A6950;
    ((T0331383CStagePart *)D_8004A4C0)[23].flags = 1;
    ((T0331383CStagePart *)D_8004A4C0)[23].transform = 16;
    D_8004A730[0] = 21;
    ((u8 (*)[7])&D_8004A5E0)[0][0] = 20;
    ((u8 (*)[7])&D_8004A5E0)[1][0] = 21;
    ((u8 (*)[7])&D_8004A5E0)[2][0] = 22;
    ((u8 (*)[7])&D_8004A5E0)[3][0] = 2;
    ((u8 (*)[7])&D_8004A5E0)[4][0] = 3;
    ((u8 (*)[7])&D_8004A5E0)[5][0] = 15;
    ((u8 (*)[7])&D_8004A5E0)[6][0] = 23;
    ((u8 (*)[7])&D_8004A5E0)[7][0] = 7;
    ((u8 (*)[7])&D_8004A5E0)[8][0] = 5;
    ((u8 (*)[7])&D_8004A5E0)[9][0] = 6;
    ((u8 (*)[7])&D_8004A5E0)[10][0] = 1;
    ((u8 (*)[7])&D_8004A5E0)[11][0] = 0;
    ((u8 (*)[7])&D_8004A5E0)[12][0] = 4;
    ((u8 (*)[7])&D_8004A5E0)[13][0] = 16;
    ((u8 (*)[7])&D_8004A5E0)[14][0] = 17;
    ((u8 (*)[7])&D_8004A5E0)[15][0] = 18;
    ((u8 (*)[7])&D_8004A5E0)[16][0] = 19;
    ((u8 (*)[7])&D_8004A5E0)[17][0] = 10;
    ((u8 (*)[7])&D_8004A5E0)[18][0] = 11;
    ((u8 (*)[7])&D_8004A5E0)[19][0] = 12;
    ((u8 (*)[7])&D_8004A5E0)[20][0] = 13;
    D_8004A738[0] = 1;
    ((u8 *)D_8004A688)[0] = 8;
    D_8004A740[0] = 2777.0f;
    (&D_8004A7A0)[0] = 1350.0f;
    D_8004A800[0] = -722.0f;
    D_8004A860[0] = 0.0f;
    D_8004A8C0[0] = 0.0f;
    D_8004A920[0] = 0.0f;
    D_8004A740[1] = 0.0f;
    (&D_8004A7A0)[1] = -3300.0f;
    D_8004A800[1] = 0.0f;
    D_8004A860[1] = 0.0f;
    D_8004A8C0[1] = 0.0f;
    D_8004A920[1] = 0.0f;
    D_8004A740[2] = 0.0f;
    (&D_8004A7A0)[2] = -2200.0f;
    D_8004A800[2] = 0.0f;
    D_8004A860[2] = 0.0f;
    D_8004A8C0[2] = 0.0f;
    D_8004A920[2] = 0.0f;
    D_8004A740[3] = 0.0f;
    (&D_8004A7A0)[3] = -1100.0f;
    D_8004A800[3] = 0.0f;
    D_8004A860[3] = 0.0f;
    D_8004A8C0[3] = 0.0f;
    D_8004A920[3] = 0.0f;
    func_8001B620(15, 23);
    D_8004A980 = 0.0f;
    D_8004A740[7] = 2761.0f;
    (&D_8004A7A0)[7] = 619.0f;
    D_8004A800[7] = -747.0f;
    D_8004A860[7] = 0.0f;
    D_8004A8C0[7] = 303.0f;
    D_8004A920[7] = 0.0f;
    D_8004A740[8] = -683.0f;
    (&D_8004A7A0)[8] = 140.0f;
    D_8004A800[8] = 500.0f;
    D_8004A860[8] = 0.0f;
    D_8004A8C0[8] = 0.0f;
    D_8004A920[8] = 0.0f;
    D_8004A740[9] = -650.0f;
    (&D_8004A7A0)[9] = 140.0f;
    D_8004A800[9] = 720.0f;
    D_8004A860[9] = 0.0f;
    D_8004A8C0[9] = 100.0f;
    D_8004A920[9] = 0.0f;
    D_8004A740[10] = -823.0f;
    (&D_8004A7A0)[10] = 140.0f;
    D_8004A800[10] = 920.0f;
    D_8004A860[10] = 0.0f;
    D_8004A8C0[10] = 30.0f;
    D_8004A920[10] = 0.0f;
    D_8004A740[11] = -620.0f;
    (&D_8004A7A0)[11] = 140.0f;
    D_8004A800[11] = 930.0f;
    D_8004A860[11] = 0.0f;
    D_8004A8C0[11] = 70.0f;
    D_8004A920[11] = 0.0f;
    D_8004A740[12] = -723.0f;
    (&D_8004A7A0)[12] = 140.0f;
    D_8004A800[12] = 1170.0f;
    D_8004A860[12] = 0.0f;
    D_8004A8C0[12] = 200.0f;
    D_8004A920[12] = 0.0f;
    D_8004A740[13] = 0.0f;
    (&D_8004A7A0)[13] = -5400.0f;
    D_8004A800[13] = 0.0f;
    D_8004A860[13] = 0.0f;
    D_8004A8C0[13] = 0.0f;
    D_8004A920[13] = 0.0f;
    D_8004A740[14] = 0.0f;
    (&D_8004A7A0)[14] = -3600.0f;
    D_8004A800[14] = 0.0f;
    D_8004A860[14] = 0.0f;
    D_8004A8C0[14] = 0.0f;
    D_8004A920[14] = 0.0f;
    D_8004A740[15] = 0.0f;
    (&D_8004A7A0)[15] = -1800.0f;
    D_8004A800[15] = 0.0f;
    D_8004A860[15] = 0.0f;
    D_8004A8C0[15] = 0.0f;
    D_8004A920[15] = 0.0f;
    D_8004AA3C = 0;
    D_8004AEAC = &func_80017A50;
    D_8004AA38 = &func_80017A68;
    D_8004AA34 = &func_8001372C;
    D_8004AC80 = 0.0f;
    D_8004AC84 = 60.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 1;
    D_8004AC8C = 10;
    func_80028600(0, D_8004AC84, D_8004AC84, 0);
    model = (void **)&D_8004A998;
    rot = (T0331383CStageRotation *)&D_8004A9D8;
    for (i = 0; i < 3; i++) {
        model[i * 4] = &D_801A2080;
        model[i * 4 + 1] = 0;
        model[i * 4 + 2] = 0;
        model[i * 4 + 3] = 0;
        rot[i].pitch = 0.0f;
        rot[i].yaw = 0.0f;
        rot[i].roll = 0.0f;
        rot[i].speed = 0.0f;
    }
    func_8001C0E4(&D_80045890, &D_800458C0, &D_800458D8, &D_80045908, (s32)&D_802EBFAC, &D_80045920, &D_80045950, 12);
    func_80030020(&D_802EC078, &D_802EBFAC, &D_802EC144, 0x33);
    D_8004AA30 = &func_800142E0;
    if (D_8004AA28 == 0) {
        func_80014250();
        return;
    }
    D_8004AA38 = &func_80017D6C;
    ((T0331383CStagePart *)D_8004A4C0)[15].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[1].display = 0;
    ((T0331383CStagePart *)D_8004A4C0)[6].display = 0;
    ((u8 (*)[7])&D_8004A5E0)[6][0] = 1;
    ((u8 (*)[7])&D_8004A5E0)[10][0] = 0;
    ((u8 (*)[7])&D_8004A5E0)[11][0] = 23;
    D_8004AA30 = &func_80016078;
    D_8004ACC5 = D_8004ACC6 = D_8004ACC7 = 0;
}

s32 func_80017A50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

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
extern void func_8001AC80();
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
        ((T0331383CStagePart *)D_8004A4C0)[5].display = &D_8019DDF0;
        D_801C4220 = 0xFFFF31BC;
    }
    D_8004A8C0[0] += D_8004ACEC; if (359.0f < D_8004A8C0[0]) {
        D_8004A8C0[0] -= 360.0f; }
    D_8004A980 += 10.0f;
    if (359.0f < D_8004A980) {
        D_8004A980 -= 360.0f; } if (D_8004ACF4 == 1) {
        D_8004ACF4 = 0;
        D_8004ACEC = 2.0f;
    }
    if (D_8004ACEC > 0.0f) { D_8004ACEC = (f32) ((f64) D_8004ACEC - 0.01);
    }
    else {
        D_8004ACEC = 0.0f;
    }
    func_8001AC80(15, 23);
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
        ((T0331383CStagePart *)D_8004A4C0)[12].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[13].display = 0;
        ((T0331383CStagePart *)D_8004A4C0)[3].display = &D_801A6200;
        ((T0331383CStagePart *)D_8004A4C0)[2].display = &D_801A5290;
        ((T0331383CStagePart *)D_8004A4C0)[20].display = &D_801A5290;
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


extern void *D_8004A4C0[];
extern f32 D_8004A740[], D_8004A800[], D_8004A860[], D_8004A8C0[], D_8004A920[], D_8004A7A0;
extern f32 D_8004A980, D_8004ACE0, D_8004ACE4;
extern s32 D_8004ACF8;
extern void func_8001B50C(s32);
extern void func_8001BA94(f32);

void func_80017D6C(void) {
    s32 index, other;

    index = ((T0331383CStagePart *)D_8004A4C0)[0].transform;
    other = ((T0331383CStagePart *)D_8004A4C0)[23].transform;
    D_8004ACF8++;
    if (D_8004A800[index] > 2000.0f || D_8004ACF8 < 2) {
        D_8004ACF8 = 1;
        (&D_8004A7A0)[index] = 0.0f;
        D_8004A740[index] = 4000.0f;
        D_8004A800[index] = (-15000.0f);
        D_8004A860[index] = 10.0f;
        D_8004A920[index] = -20.0f;
        D_8004A8C0[index] = -90.0f;
        D_8004ACE0 = 0.0f;
        func_8001BA94(0.0f);
    }
    D_8004A980 += 20.0f;
    if (359.0f < D_8004A980) D_8004A980 -= 360.0f;
    if ((&D_8004A7A0)[index] < 2000.0f) (&D_8004A7A0)[index] += 50.0f;
    else {
        if (D_8004A8C0[index] < 0.0f) func_8001BA94(0.8f);
        else func_8001BA94(0.0f);
        if (D_8004ACE0 < 110.0f) D_8004ACE0 += 1.0f;
        D_8004A8C0[index] += D_8004ACE4;
    }
    func_8001B50C(index);
    (&D_8004A7A0)[other] = (&D_8004A7A0)[index];
    D_8004A740[other] = D_8004A740[index];
    D_8004A800[other] = D_8004A800[index];
    if (D_8004A920[index] < -30.0f) D_8004A920[index] = -30.0f;
    D_8004A860[other] = D_8004A860[index];
    D_8004A920[other] = D_8004A920[index];
    D_8004A8C0[other] = D_8004A8C0[index];
}




extern s32 func_800183B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_800183CC();
extern void (*D_8004AA38)();
extern void (*D_8004AA30)(void);
extern f32 D_8004AC84;
extern void func_80019880(void);
extern void func_8001BB10(void);
extern void func_8001C05C(u8 *);
extern void D_8001AC78();
extern s32 func_80028600(s32, f32, f32, s32);
extern s32 func_80030020(u8 *, u8 *, u8 *, s32);



extern void (*D_8004AA34)(T020Position *);
extern u8 *D_8004AA3C;
extern f32 D_8004AC80;


extern s8 D_8004AC8C;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern void func_8001C0E4(s32 *arg0, s16 *arg1, s32 *arg2, s16 *arg3, s32 arg4, s32 *arg5, s32 *arg6, s32 arg7);
extern u8 D_8004AA28;
s32 func_800281C4(s32);                     /* extern */
extern u8 D_80044E94;
extern s32 D_80045980;
extern s16 D_800459B0;
extern s32 D_800459C8;
extern s16 D_800459F8;
extern s32 D_80045A10;
extern s32 D_80045A40;
extern f32 D_800488BC;
extern f32 D_800488C0;
extern f32 D_800488C4;
extern f32 D_800488C8;
extern u8 D_8004A998;
extern u8 D_8004A9D8;

extern u8 D_80061520;

extern u8 D_801924D0;
extern u8 D_801982C0;
extern u8 D_8019A760;
extern u8 D_8019AF20;
extern u8 D_8019C450;
extern u8 D_8019D150;
extern u8 D_8019D690;
extern u8 D_8019E060;
extern u8 D_8019EE70;
extern u8 D_8019F0A0;
extern u8 D_8019F250;
extern u8 D_802E917C;
extern u8 D_802E9208;
extern u8 D_802E9294;

void func_8001808C(void) {
    (*(u8 **)((u8 *)(D_8004A4C0) + 0)) = &D_801982C0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0xC)) = &D_8019A760;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x18)) = &D_8019AF20;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x24)) = &D_8019C450;
    (*(s16 *)((u8 *)(D_8004A4C0) + 4)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x10)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x1C)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x28)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x30)) = &D_8019D690;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x34)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x3C)) = &D_8019E060;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x40)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x48)) = &D_8019D150;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x4C)) = 4;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x80)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x7C)) = 3;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x8C)) = 1;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x88)) = 3;
    D_8004A730[0] = 9;
    ((u8 (*)[7])&D_8004A5E0)[0][0] = 5;
    ((u8 (*)[7])&D_8004A5E0)[1][0] = 4;
    ((u8 (*)[7])&D_8004A5E0)[3][0] = 3;
    ((u8 (*)[7])&D_8004A5E0)[2][0] = 0;
    ((u8 (*)[7])&D_8004A5E0)[4][0] = 1;
    ((u8 (*)[7])&D_8004A5E0)[5][0] = 2;
    ((u8 (*)[7])&D_8004A5E0)[6][0] = 6;
    ((u8 (*)[7])&D_8004A5E0)[7][0] = 0xA;
    ((u8 (*)[7])&D_8004A5E0)[8][0] = 0xB;
    D_8004A738[0] = 0;
    D_8004AA3C = &D_801924D0;
    D_8004AEAC = func_800183B4;
    D_8004AA30 = func_80019880;
    func_8001BB10();
    func_8001C05C(&D_80044E94);
    D_8004AA38 = D_8001AC78;
    D_8004AA34 = (void (*)(T020Position *)) func_800183CC;
    if (D_8004AA28 == 0) {
        func_800281C4(0);
    }
    D_8004AC80 = -70.0f;
    D_8004AC84 = 260.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 1;
    D_8004AC8C = 0xD;
    func_80028600(2, D_8004AC84, D_8004AC84, 0xC8);
    (*(u8 *)((u8 *)(&D_80061520) + 0)) = (*(u8 *)((u8 *)(&D_80061520) + 1)) = 0x14;
    (*(f32 *)((u8 *)(&D_800614D8) + 0)) = (-3380.0f);
    (*(f32 *)((u8 *)(&D_800614D8) + 4)) = 30.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 8)) = (3204.0f);
    (*(f32 *)((u8 *)(&D_800614D8) + 0xC)) = (-3460.0f);
    (*(f32 *)((u8 *)(&D_800614D8) + 0x10)) = 30.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 0x14)) = (3251.0f);
    (*(u8 **)((u8 *)(&D_8004A998) + 0)) = &D_8019EE70;
    (*(u8 *)((u8 *)(&D_80061CB8) + 0)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 1)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 2)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 3)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 4)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 5)) = 0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 6)) = 0xFF;
    (*(u8 *)((u8 *)(&D_80061CB8) + 7)) = 0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 8)) = 0;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0)) = 0.0f;
    (*(u8 **)((u8 *)(&D_8004A998) + 4)) = &D_8019F0A0;
    (*(u8 **)((u8 *)(&D_8004A998) + 8)) = &D_8019F250;
    (*(s32 *)((u8 *)(&D_8004A998) + 0xC)) = 0;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0xC)) = 0.0f;
    func_8001C0E4(&D_80045980, &D_800459B0, &D_800459C8, &D_800459F8, (s32) &D_802E917C, &D_80045A10, &D_80045A40, 0xC);
    func_80030020(&D_802E9208, &D_802E917C, &D_802E9294, 0x23);
}

s32 func_800183B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

typedef struct { u8 pad[0x28]; s16 x, y, z; } T022Position;
void func_800183CC(T022Position *arg0) {
    arg0->z = 0; arg0->y = 0; arg0->x = 0;
    func_8001373C(arg0, -3417.0f, 45.0f, 3200.0f, 0x30, 0x10, 0);
}

extern s32 func_8001864C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80019880(void);
extern void func_8001C0E4(s32 *arg0, s16 *arg1, s32 *arg2, s16 *arg3, s32 arg4, s32 *arg5, s32 *arg6, s32 arg7);
void func_80018664();                               /* extern */
s32 func_800281C4(s32);                     /* extern */
extern u8 D_80044E40;
extern s32 D_80045A70;
extern s16 D_80045A80;
extern s32 D_80045A88;
extern s16 D_80045A98;
extern s32 D_80045AA0;
extern s32 D_80045AB0;
extern u8 D_8004AA2C;
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
    D_8004A730[0] = 1;
    D_8004A5E0[0][0] = 0;
    D_8004A738[0] = 0;
    (*(s32 *)((u8 *)(&D_8004A998) + 0)) = 0;
    (*(s32 *)((u8 *)(&D_8004A998) + 4)) = 0;
    (*(u8 **)((u8 *)(&D_8004A998) + 8)) = &D_801A3350;
    (*(s32 *)((u8 *)(&D_8004A998) + 0xC)) = 0;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(&D_8004A9D8) + 0xC)) = 0.0f;
    *D_8004A740 = 370.0f;
    D_8004A7A0 = 650.0f;
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



extern u8 D_80045088[];
extern f32 D_800695E0;
extern u8 *D_8019B69C;

void func_80018664(void) {
    T05518664Obj *obj;
    s32 frame;
    s32 d;
    s32 ad;
    f32 step;
    s32 i;

    if (D_8004A401 == 3 && D_800698C4 == 20) {
        D_8004AA3C = 0;
        D_8004A730[0] = 0;
        D_8004A688[0][0] = 1;
        D_8004A688[1][0] = 0;
        D_8004A738[0] = 2;
    }
    D_8004AE89++;
    if (D_8004AE88 >= 10) {
        frame = 19 - D_8004AE88;
    } else {
        frame = D_8004AE88;
    }
    if (D_8004AE89 == D_80045088[D_8004AE88]) {
        D_8004AE89 = 0;
        D_8004AE88++;
        if (D_8004AE88 >= 20) {
            D_8004AE88 = 0;
        }
    }
    D_8019B69C = D_8018FED0 + (frame << 12);
    if (D_8004AA2C < 120) {
        d = 60 - D_8004AA2C;
        if (d >= 0) {
            ad = d;
        } else {
            ad = -d;
        }
        D_800695E0 = (f32)d / ((f32)ad * 0.25 + 20.0);
    } else {
        d = D_8004AA2C - 180;
        if (d >= 0) {
            ad = d;
        } else {
            ad = 180 - D_8004AA2C;
        }
        D_800695E0 = (f32)d / ((f32)ad * 0.25 + 20.0);
    }
    D_8004AA2C++;
    if (D_8004AA2C >= 240) {
        D_8004AA2C = 0;
    }
    if (D_8004AA28 == 0) {
        for (i = 0; i < 40; i++) {
            obj = &D_801D3430[i];
            d = obj->type;
            if (d == 60) {
                step = D_800695E0 * 6.0f;
                if (step > 0.0f) {
                    if (step > 5.0f) {
                        step = 5.0f;
                    }
                } else if (step < -5.0f) {
                    step = -5.0f;
                }
                obj->vy = obj->vy + step;
                D_8004A860[0] += (f32)obj->vx / 256;
                obj->vx = obj->vx - D_8004A860[0] * 256 / 100;
                D_8004A920[0] -= (f32)obj->vy / 256;
                obj->vy += D_8004A920[0] * 256 / 100;
            }
        }
    }
}



extern s32 func_80018E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80018E88();                               /* extern */
extern u8 D_80044E28;
extern s32 D_80045AC0;
extern s16 D_80045AE4;
extern s32 D_80045AF8;
extern s16 D_80045B1C;
extern s32 D_80045B30;
extern s32 D_80045B54;

extern u8 D_801816D0;
extern u8 D_80186180;
extern u8 D_801861E0;
extern u8 D_80186330;
extern u8 D_80187D50;
extern u8 D_8018A650;
extern u8 D_8018A6B0;
extern u8 D_8018A710;
extern u8 D_8018A770;
extern u8 D_802DF420;
extern u8 D_802DF45C;
extern u8 D_802DF498;

void func_80018AE0(void) {
    if (D_8004AA28 == 0) {
        (*(u8 **)((u8 *)(D_8004A4C0) + 8)) = &D_80186180;
    } else {
        (*(u8 **)((u8 *)(D_8004A4C0) + 8)) = 0;
    }
    (*(u8 **)((u8 *)(D_8004A4C0) + 0)) = &D_801861E0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 4)) = 5;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0xC)) = &D_80186330;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x18)) = &D_80187D50;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x10)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x1C)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x24)) = &D_8018A650;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x28)) = 1;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x2C)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x30)) = &D_8018A6B0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x34)) = 1;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x38)) = 1;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x3C)) = &D_8018A710;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x40)) = 1;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x44)) = 2;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x4C)) = 3;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x50)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x54)) = &D_801816D0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x58)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x60)) = &D_8018A770;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x64)) = 0;
    (*(f32 *)((u8 *)(D_8004A740) + 0)) = 216.0f;
    (*(f32 *)((u8 *)(&D_8004A7A0) + 0)) = -621.0f;
    (*(f32 *)((u8 *)(D_8004A800) + 0)) = 256.0f;
    (*(f32 *)((u8 *)(D_8004A860) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A8C0) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A920) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A740) + 4)) = -1029.0f;
    (*(f32 *)((u8 *)(&D_8004A7A0) + 4)) = -1000.0f;
    (*(f32 *)((u8 *)(D_8004A800) + 4)) = 692.0f;
    (*(f32 *)((u8 *)(D_8004A860) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A8C0) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A920) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A740) + 8)) = 158.0f;
    (*(f32 *)((u8 *)(&D_8004A7A0) + 8)) = -1000.0f;
    (*(f32 *)((u8 *)(D_8004A800) + 8)) = -1237.0f;
    (*(f32 *)((u8 *)(D_8004A860) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A8C0) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(D_8004A920) + 8)) = 0.0f;
    D_8004A730[0] = 9;
    ((u8 (*)[7])&D_8004A5E0)[0][0] = 6;
    ((u8 (*)[7])&D_8004A5E0)[1][0] = 7;
    ((u8 (*)[7])&D_8004A5E0)[2][0] = 8;
    ((u8 (*)[7])&D_8004A5E0)[3][0] = 3;
    ((u8 (*)[7])&D_8004A5E0)[4][0] = 4;
    ((u8 (*)[7])&D_8004A5E0)[5][0] = 5;
    ((u8 (*)[7])&D_8004A5E0)[6][0] = 1;
    ((u8 (*)[7])&D_8004A5E0)[7][0] = 2;
    ((u8 (*)[7])&D_8004A5E0)[8][0] = 0;
    D_8004A738[0] = 0;
    D_8004AA3C = 0;
    D_8004AEAC = func_80018E70;
    D_8004AA30 = func_80019880;
    func_8001BB10();
    func_8001C05C(&D_80044E28);
    D_8004AA38 = func_80018E88;
    D_8004AA34 = func_8001372C;
    D_8004AC80 = -40.0f;
    D_8004AC84 = 110.0f;
    D_8004AC89 = 1;
    D_8004AC8A = 1;
    D_8004AC8C = 0xF;
    func_80028600(1, 10.0f, 100.0f, 0x1E);
    (&D_80061520)[0] = 0x14;
    (*(f32 *)((u8 *)(&D_800614D8) + 0)) = -2373.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 4)) = 1587.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 8)) = -16944.0f;
    (*(u8 *)((u8 *)(&D_80061CB8) + 0)) = 0xF0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 1)) = 0xF0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 2)) = 0xF0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 3)) = 0xE0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 4)) = 0xE0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 5)) = 0xE0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 6)) = 0xD0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 7)) = 0xD0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 8)) = 0xD0;
    func_8001C0E4(&D_80045AC0, &D_80045AE4, &D_80045AF8, &D_80045B1C, (s32) &D_802DF420, &D_80045B30, &D_80045B54, 9);
    func_80030020(&D_802DF45C, &D_802DF420, &D_802DF498, 0xF);
}

s32 func_80018E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

void func_80018E88(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_8004A8C0[i] = (f64)D_8004A8C0[i] + 0.2;
        if (359.0f < D_8004A8C0[i]) D_8004A8C0[i] = 0.0f;
    }
    D_8004A8C0[2] = (f64)D_8004A8C0[2] - 0.2;
    if (D_8004A8C0[2] < 0.0f) D_8004A8C0[2] = 359.0f;
}

extern void *D_8004A4C0[];
extern u8 D_8004AA28;
extern u8 D_8004A730[8];
extern s8 D_8004AC8C;
extern f32 D_8004A740[];
extern f32 D_8004A800[]; extern f32 D_8004A860[]; extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
extern f32 D_8004A7A0;
extern f32 D_8004AC80; extern f32 D_8004AC84;
extern u8 *D_8004AA3C; extern s32 (*D_8004AEAC)(s32,s32,s32,s32); extern void (*D_8004AA30)();
extern void (*D_8004AA34)(T020Position *);
extern void (*D_8004AA38)();
extern void func_80019880(void);
extern void func_8001372C(T020Position *); extern s32 func_800191D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800191F0(); extern u8 D_80044E58;
extern s32 D_80045B78;
extern s16 D_80045B84;
extern s32 D_80045B8C;
extern s16 D_80045B98; extern s32 D_80045BA0;
extern s32 D_80045BAC;
extern f32 D_800488F8;
extern f32 D_800488FC;
extern f32 D_80048900; extern u8 D_80061520;
extern u8 D_80183ED0; extern u8 D_80186990;
extern u8 D_8018AA00; extern u8 D_802DEEB0;
extern u8 D_802DEEF8;
extern u8 D_802DEF40;
void func_80018F20(void)
{ f32 temp_f0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 4)) = 3; (*(s32 *)((u8 *)(D_8004A4C0) + 8)) = 0;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x10)) = 3;
    (*(s32 *)((u8 *)(D_8004A4C0) + 0x14)) = 1;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x18)) = &D_80186990; (*(s16 *)((u8 *)(D_8004A4C0) + 0x1C)) = 0;
    (*(u8 **)((u8 *)(D_8004A4C0) + 0x24)) = &D_8018AA00;
    (*(s16 *)((u8 *)(D_8004A4C0) + 0x28)) = 1; (*(s32 *)((u8 *)(D_8004A4C0) + 0x2C)) = 0;
    D_8004A730[0] = 4; ((u8 (*)[7])&D_8004A5E0)[0][0] = 0;
    ((u8 (*)[7])&D_8004A5E0)[1][0] = 1;
    ((u8 (*)[7])&D_8004A5E0)[2][0] = 2;
    ((u8 (*)[7])&D_8004A5E0)[3][0] = 3;
    D_8004A738[0] = 0;
    *D_8004A740 = 42.0f; D_8004A7A0 = 65.0f;
    *D_8004A800 = (1289.0f);
    *D_8004A860 = 0.0f;
    *D_8004A8C0 = 0.0f; *D_8004A920 = 0.0f;
    D_8004AA3C = &D_80183ED0; D_8004AEAC = func_800191D8; D_8004AA30 = func_80019880;
    func_8001BB10();
    func_8001C05C(&D_80044E58);
    D_8004AA38 = func_800191F0; D_8004AA34 = func_8001372C;
    if (D_8004AA28 == 0)
    {
        func_800281C4(1);
    }
    D_8004AC80 = 0.0f;
    D_8004AC84 = (1100.0f); D_8004AC89 = 1; D_8004AC8A = 0; D_8004AC8C = 0x10;
    temp_f0 = D_8004AC84 / 2;
    func_80028600(2, temp_f0, temp_f0, 0xC8);
    (*(s8 *)((u8 *)(&D_80061520) + 0)) = 0x14;
    (*(s8 *)((u8 *)(&D_80061520) + 1)) = 0x1E;
    (*(u8 *)((u8 *)(&D_80061CB8) + 0)) = 0x80;
    (*(u8 *)((u8 *)(&D_80061CB8) + 1)) = 0x80;
    (*(u8 *)((u8 *)(&D_80061CB8) + 2)) = 0x80;
    (*(u8 *)((u8 *)(&D_80061CB8) + 3)) = 0x40;
    (*(u8 *)((u8 *)(&D_80061CB8) + 4)) = 0x40;
    (*(u8 *)((u8 *)(&D_80061CB8) + 5)) = 0x40;
    (*(u8 *)((u8 *)(&D_80061CB8) + 6)) = 0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 7)) = 0;
    (*(u8 *)((u8 *)(&D_80061CB8) + 8)) = 0;
    (*(f32 *)((u8 *)(&D_800614D8) + 4)) = 47.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 0x10)) = 47.0f; (*(f32 *)((u8 *)(&D_800614D8) + 8)) = (f32) (1198.0f);
    (*(f32 *)((u8 *)(&D_800614D8) + 0x14)) = (f32) (1198.0f); (*(f32 *)((u8 *)(&D_800614D8) + 0)) = -64.0f;
    (*(f32 *)((u8 *)(&D_800614D8) + 0xC)) = 1.0f;
    func_8001C0E4(&D_80045B78, &D_80045B84, &D_80045B8C, &D_80045B98, (s32) &D_802DEEB0, &D_80045BA0, &D_80045BAC, 3); func_80030020(&D_802DEEF8, &D_802DEEB0, &D_802DEF40, 0x12); }

s32 func_800191D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800191F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_800193DC.s")

s32 func_80019704(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

extern s32 func_80019868(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8002FFDC(s32, s16, s32, s16, s32, s32, s32);
void D_8001AC78();                                  /* extern */
s32 func_80028600(s32, f32, f32, s32);  /* extern */
s32 func_80030020(u8 *, u8 *, u8 *, s32); /* extern */
extern u8 D_80044EAC;
extern u8 D_801755F0;
extern u8 D_80175890;
extern u8 D_802D4000;
extern u8 D_802D4158;
extern u8 D_802D6098;
extern u8 D_802D60A4;
extern u8 D_802D60B0;

void func_8001971C(void) {
    D_8004A730[0] = 0;
    D_8004A5E0[0][0] = 0;
    D_8004A738[0] = 0;
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

void func_8001A9E8(f32 arg0) {
    func_8001AA90(arg0);
    func_8001AA20();
    D_8004AA38();
}

extern u8 D_8004AD08;
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

extern u8 D_8004AC88;
extern f32 cosf(f32);
extern f32 sinf(f32);

extern f64 D_80048930;
extern f64 D_80048938;
extern u8 D_8004AD09;
extern f32 D_8004AD0C;
extern f32 D_8004AD10;

void func_8001AA90(f32 arg0) {
    f32 sine;
    f32 cosine;
    s32 period;
    f32 angle;

    if (D_8004AC88 == 0) {
        arg0 -= 90.0f;
    }
    angle = (f32)(((f64)arg0 * D_80048930) / D_80048938);
    sine = sinf(angle);
    cosine = cosf(angle);
    if (D_8004AC88 == 0xB) {
        sine *= 4.0f;
        cosine = cosine * 4.0f;
    }
    if ((D_8004AC88 == 0) || (D_8004AC88 == 4)) {
        period = 4;
    } else {
        period = 1;
    }
    D_8004AD09++;
    if (period < D_8004AD09) {
        D_8004AD09 = 0;
        D_8004AD0C += sine;
        D_8004AD10 -= cosine;
    }
    while (D_8004AD0C > 255.0f) {
        D_8004AD0C -= 256.0f;
    }
    while (D_8004AD0C < 0.0f) {
        D_8004AD0C += 256.0f;
    }
    while (D_8004AD10 > 255.0f) {
        D_8004AD10 -= 256.0f;
    }
    while (D_8004AD10 < 0.0f) {
        D_8004AD10 += 256.0f;
    }
}

void D_8001AC78(void) {}


void func_8001AD04();                            /* extern */
void func_8001B134();                            /* extern */
void func_8001B620();                            /* extern */

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

typedef struct { void *display; s16 flags,pad; s32 transform; } T117Part;
extern void *D_8004A4C0[];
extern f32 D_8004A800[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
extern f32 D_8004A7A0;
extern f32 D_8004ACE0;
extern f32 D_8004ACE4;
extern void func_8001B50C(s32 arg0);
extern void func_8001BA18(f32 arg0);

extern s32 func_8002FA5C();

extern s32 D_8004A264;
extern s16 D_8004AA2A;

void func_8001AD04(s32 arg0, s32 arg1) {
    s32 first;
    s32 second;
    first = ((T117Part *)D_8004A4C0)[arg0].transform;
    second = ((T117Part *)D_8004A4C0)[arg1].transform;
    if (D_8004A800[first] > 6000.0f) {
        func_8001B620(arg0, arg1);
        return;
    }
    if ((&D_8004A7A0)[first] < 1500.0f) {
        func_8002FA5C(D_8004A264, 8, (s32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3500.0f));
        D_8004AA2A = (u32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3500.0f);
        (&D_8004A7A0)[first] += 30.0f;
        (&D_8004A7A0)[second] += 30.0f;
        return;
    }
    if (D_8004A8C0[first] < 360.0f && D_8004ACE0 >= 50.0f) {
        func_8001BA18(0.3f);
    } else {
        func_8001BA18(0.0f);
    }
    if (D_8004A800[first] > 2000.0f) {
        func_8002FA5C(D_8004A264, 8, (s32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f));
        D_8004AA2A = (u32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f);
    }
    D_8004A8C0[first] += D_8004ACE4;
    D_8004A8C0[second] += D_8004ACE4;
    if (D_8004ACE0 < 50.0f) {
        D_8004ACE0 += 1.0f;
    }
    func_8001B50C(first);
    func_8001B50C(second);
    D_8004A920[first] = 0.0f;
    D_8004A920[second] = 0.0f;
}

void func_8001B134(s32 arg0, s32 arg1) {
    s32 first;
    s32 second;
    first = ((T117Part *)D_8004A4C0)[arg0].transform;
    second = ((T117Part *)D_8004A4C0)[arg1].transform;
    if (D_8004A800[first] > 6000.0f) {
        func_8001B620(arg0, arg1);
        return;
    }
    if ((&D_8004A7A0)[first] < 1000.0f) {
        func_8002FA5C(D_8004A264, 8, (s32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3000.0f));
        D_8004AA2A = (u32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3000.0f);
        (&D_8004A7A0)[first] += 30.0f;
        (&D_8004A7A0)[second] += 30.0f;
    } else {
        if (D_8004A8C0[first] < 90.0f) {
            func_8001BA18(0.3f);
        } else {
            func_8001BA18(0.0f);
        }
        if (D_8004A800[first] > 2000.0f) {
            func_8002FA5C(D_8004A264, 8, (s32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f));
            D_8004AA2A = (u32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f);
        }
        D_8004A8C0[first] += D_8004ACE4;
        D_8004A8C0[second] += D_8004ACE4;
        if (D_8004ACE0 < 50.0f) {
            D_8004ACE0 += 1.0f;
        }
        func_8001B50C(first);
        func_8001B50C(second);
    }
}

extern f32 cosf(f32), sinf(f32);
extern f32 D_8004ACE4;
void func_8001B50C(s32 arg0) {
    D_8004A860[arg0] = D_8004ACE0 / 3.0f;
    D_8004A920[arg0] = -D_8004ACE4 * 50.0f;
    D_8004A800[arg0] += D_8004ACE0 * cosf((f32)(((f64)D_8004A8C0[arg0] * 3.14159) / 180.0));
    D_8004A740[arg0] += D_8004ACE0 * sinf((f32)(((f64)D_8004A8C0[arg0] * 3.14159) / 180.0));
}

extern f32 D_800695CC, D_8004ACE8;
extern s32 D_8004A264, D_80066C40;


void func_8001B620(s32 arg0, s32 arg1) {
    s32 first;
    s32 second;

    first = ((T0331383CStagePart *)D_8004A4C0)[arg0].transform;
    second = ((T0331383CStagePart *)D_8004A4C0)[arg1].transform;
    if (D_8004ACF0 == 2) {
        D_8004ACF0 = func_800326F0() & 3;
    } else {
        D_8004ACF0 = 2;
    }
    if ((1650.0f < D_800695CC) && (D_8004ACF0 == 0)) {
        D_8004ACF0 = 2;
    }

    if ((D_800695CC < 4750.0f) && (D_8004ACF0 == 1)) {
        D_8004ACF0 = 2;

    }
    D_8004ACF8 = 0;
    switch (D_8004ACF0) {                               /* irregular */
    case 0:
        func_8002F8F8(D_8004A264);
        func_8002F6F4(D_80066C40, 0x1B3, &D_8004A264);
        D_8004A740[second] = -200.0f;
        D_8004A740[first] = -200.0f;
        (&D_8004A7A0)[second] = -2000.0f;
        (&D_8004A7A0)[first] = -2000.0f;
        D_8004A800[second] = -8821.0f;
        D_8004A800[first] = -8821.0f;
        D_8004A860[second] = 0.0f;
        D_8004A860[first] = 0.0f;
        D_8004A8C0[second] = 270.0f;
        D_8004A8C0[first] = 270.0f;
        D_8004A920[second] = 0.0f;
        D_8004A920[first] = 0.0f;
        ((T0331383CStagePart *)D_8004A4C0)[arg0].flags = 1;
        break;
    case 1:
        func_8002F8F8(D_8004A264);
        func_8002F6F4(D_80066C40, 0x1B3, &D_8004A264);
        D_8004A740[second] = 7000.0f;
        D_8004A740[first] = 7000.0f;
        (&D_8004A7A0)[second] = -2000.0f;
        (&D_8004A7A0)[first] = -2000.0f;
        D_8004A800[second] = -1000.0f;
        D_8004A800[first] = -1000.0f;
        D_8004A860[second] = 0.0f;
        D_8004A860[first] = 0.0f;
        D_8004A8C0[second] = 0.0f;
        D_8004A8C0[first] = 0.0f;
        D_8004A920[second] = 0.0f;
        D_8004A920[first] = 0.0f;
        ((T0331383CStagePart *)D_8004A4C0)[arg0].flags = 2;
        break;
    default:
    case 2:
        func_8002F8F8(D_8004A264);
        D_8004A740[second] = 7000.0f;
        D_8004A740[first] = 7000.0f;
        (&D_8004A7A0)[second] = -2000.0f;
        (&D_8004A7A0)[first] = -2000.0f;
        D_8004A800[second] = (10000.0f);
        D_8004A800[first] = (10000.0f);
        D_8004A860[second] = 0.0f;
        D_8004A860[first] = 0.0f;
        D_8004A8C0[second] = 0.0f;
        D_8004A8C0[first] = 0.0f;
        D_8004A920[second] = 0.0f;
        D_8004A920[first] = 0.0f;
        ((T0331383CStagePart *)D_8004A4C0)[arg0].flags = 2;
        break;
    }
    D_8004ACE0 = 0.0f;
    D_8004ACE4 = 0.0f;
    D_8004ACE8 = 0.0f;
}



void func_8001BA18(f32 arg0) {
    if (((D_8004ACE8 * 4.0f) + D_8004ACE4) < arg0) {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 + 0.001);
    } else {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 - 0.001);
    }
    D_8004ACE4 += D_8004ACE8;
}


void func_8001BA94(f32 arg0) {
    if (((D_8004ACE8 * 4.0f) + D_8004ACE4) < arg0) {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 + 0.007);
    } else {
        D_8004ACE8 = (f32) ((f64) D_8004ACE8 - 0.007);
    }
    D_8004ACE4 += D_8004ACE8;
}

extern u8 D_803A4200[], D_A68A20, D_A69A20;
void func_8001BB10(void) {
    s32 size = (s32)&D_A69A20 - (s32)&D_A68A20;
    boot_dma((s32)&D_A68A20, (s32)D_8004ACD8, size);
    if (D_8004AA28 == 0) D_8004ACD8 = D_803A4200;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001BB64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_2FF0/func_8001BDE0.s")

extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80044A24;
extern u8 D_801D7E00;

void func_8001BF1C(u8 **arg0, s32 arg1, s32 arg2, f32 arg3) {
    u8 *temp_v0;
    f32 y;

    temp_v0 = (arg2 * 0x30) + &D_801D7E00;
    y = (*(f32 *)(temp_v0 + 0xF4)) * 1500.0f - 4525.0f;
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
