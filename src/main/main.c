#include "common.h"

extern u8 D_8004A230[], D_80127C30[], D_80128350[], D_8006F1C0[];
extern void *D_8004A294;
extern u8 D_8004A298[], D_8004A2D0[], D_8004EA9C[], D_8004EA9E[];
extern s32 D_8004A414, D_80127D80;
extern void bzero(void *, s32);
extern void func_8000FA50(void), func_80001DF0(void), func_800006FC(void);
extern void func_8002A4F0(void), func_80027DA0(void), func_8002B500(void), func_8000FA80(void);
extern void osViBlack(s32);
extern void func_80001EF4(void *, void *);
extern void func_8002FAC0(s32, s32);
extern void func_8002A900(s32);

void func_8000F960(void) {
    bzero(D_8004A230, D_80127C30 - D_8004A230);
    bzero(D_80128350, 0x4A380);
    D_8004A294 = D_8006F1C0;
    func_8000FA50();
    func_80001DF0();
    osViBlack(1);
    func_80001EF4(D_8004A2D0, D_8004A298);
    func_800006FC();
    func_8002A4F0();
    func_8002FAC0(0, 0x4E20);
    func_80027DA0();
    D_8004EA9C[0] = 0;
    D_8004EA9C[1] = 0;
    D_8004A414 = 0;
    D_8004EA9E[0] = 0;
    D_8004EA9E[1] = 0;
    D_80127D80 = 0;
    func_8002B500();
    for (;;) {
        func_8000FA80();
        func_8002A900(0x11);
    }
}

extern u8 D_8004A298[], D_8004A2B0[];
extern void osCreateMesgQueue(void *, void *, s32);

void func_8000FA50(void) {
    osCreateMesgQueue(D_8004A298, D_8004A2B0, 8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8000FA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001178C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80011FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800121C8.s")

void func_800122F8(s16 *arg0) {
    s32 i;
    for (i = 0; i < 0x12BFF; i++) {
        arg0[i] = 0;
    }
}

extern void boot_inflate(void *, void *, void *);

void func_80012338(void *arg0, void *arg1, s32 arg2) {
    boot_inflate(arg0, arg1, (void *)0x803A2000);
}

extern void func_80012390(void);
extern void func_80020E98(s32, s32, s32);

void func_80012360(void) {
    func_80012390();
    func_80020E98(1, 13, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001256C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800126D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001272C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012950.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012B7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800131A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001346C.s")

typedef struct {
    u8 pad[0x28];
    s16 x, y, z;
} T020Position;

void func_8001372C(T020Position *arg0) {
    arg0->x = 0;
    arg0->y = 0;
    arg0->z = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001373C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001383C.s")

extern u8 D_8004A5EE;

s32 func_80013BA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 - arg2 + 0x1613 > 0) {
        D_8004A5EE = 2;
    } else {
        D_8004A5EE = 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80013BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80013C84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80013CD8.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80014250.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800142E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80014C40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80014D5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80015450.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80015594.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80015B64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80015CD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80015F6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80016078.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80016258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80016760.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80016910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80016BE0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800170C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80017378.s")

s32 func_80017A50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80017A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80017D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001808C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80018664.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80018AE0.s")

s32 func_80018E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80018E88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80018F20.s")

s32 func_800191D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800191F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800193DC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80019880.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001AA90.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001AD04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001B134.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001B620.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001BB10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001BB64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001BDE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001BF1C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001C1B0.s")

void func_8001C2D4(u8 **arg0, int arg1, int arg2) {
    int i, j;
    for (i = 0; i < arg1; i++) {
        for (j = 0; j < 3; j++) {
            u8 *p = arg0[i] + j;
            p[12] += ((255 - p[12]) * arg2) / 255;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001C370.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001C43C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001C5AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001CBCC.s")

extern void func_8001CBCC(f32 *, f32, f32, f32);
extern void guMtxF2L(void *, void *);
void func_8001CD0C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 matrix[4][4];
    func_8001CBCC(&matrix[0][0], arg1, arg2, arg3);
    guMtxF2L(matrix, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001CD50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001CF1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001D080.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001D37C.s")

typedef struct { u8 *start; u8 pad[28]; } T022DmaEntry;
extern T022DmaEntry D_80045E68[];
void func_8001D42C(u8 arg0, u8 arg1, void *arg2) {
    s32 index = (u8)arg0;
    boot_dma(D_80045E68[index].start + (arg1 << 5), arg2, 0x20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001D47C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001D7E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001DE5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001E0B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001E33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001EC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80020E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800216D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80021ADC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80021B6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002365C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80023790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800238C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80023EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80024028.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80024144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800241BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800244F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800245B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80024714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800249DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80024B0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80024CE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80025354.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800253D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800257FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80025D58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80025FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80026738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800268C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800269AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80026AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80026B38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80027DA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80027E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800281C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80028230.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80028600.s")

extern u8 D_80061CD4,D_80061CD5;
extern s16 D_80061CD6;
extern u32 func_800326F0(void);
void func_80028708(void) {
    if (D_80061CD4!=255) {
        if (D_80061CD6>0) {
            D_80061CD6--;
            return;
        }
        D_80061CD5^=1;
        D_80061CD6=func_800326F0()&0x1FF;
        if (D_80061CD5==1) D_80061CD6=(D_80061CD6*255)/(256-D_80061CD4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800287D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80028A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002970C.s")

typedef struct { u8 pad[0x12C]; s16 timer; u8 tail[0x12]; } T024ResetEffect;
extern T024ResetEffect D_80061D60[];
void func_80029770(void) {
    s32 i;
    for (i=0;i<4;i++) D_80061D60[i].timer=-1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800297A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80029AB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80029BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A150.s")

extern s32 D_80065C7C;
void func_8002A194(s32 value) {
    D_80065C7C = value;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A1A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A1E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A254.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A40C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A4F0.s")

extern void *D_800669C0;
extern s32 alCSPGetState(void *);
extern void alCSPPlay(void *);
extern void func_8002AA98(s32);
void func_8002A888(void) {
    if (alCSPGetState(D_800669C0) == 0) {
        alCSPPlay(D_800669C0);
        func_8002AA98(0x7FFF);
    }
}

extern void *D_800669C4;
extern s32 alCSPGetState(void *);
extern void alCSPPlay(void *);
extern void func_8002AAEC(s32);
void func_8002A8C4(void) {
    if (alCSPGetState(D_800669C4) == 0) {
        alCSPPlay(D_800669C4);
        func_8002AAEC(0x7FFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002A9DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002AA98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002AAEC.s")

extern void *D_800669C0;
extern void alCSPStop(void *);
void func_8002AB40(void) {
    alCSPStop(D_800669C0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002AB64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002AB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002AEE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B034.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B1EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B22C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B3E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B500.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B57C.s")

extern u8 D_800684E0[];
extern s32 osContStartReadData(void *);
void func_8002B6EC(void) {
    osContStartReadData(D_800684E0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B710.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B7E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B8B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B91C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B95C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002B9B4.s")

typedef struct { s32 x,y,z; float worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T024WorldPoint;
extern float D_8004AC84,D_8004AC80;
void func_8002BAF0(T024WorldPoint *p) {
    p->worldX=(float)p->x/D_8004AC84;
    p->worldZ=(float)p->z/D_8004AC84+D_8004AC80;
    p->worldY=(float)p->y/D_8004AC84;
    p->height=(float)p->top/D_8004AC84+D_8004AC80;
}

extern float D_8004AC84, D_8004AC80;
void func_8002BB74(s32 x,s32 y,s32 z,float *outX,float *outZ,float *outY) {
    *outX=(float)x/D_8004AC84;
    *outZ=(float)z/D_8004AC84+D_8004AC80;
    *outY=(float)y/D_8004AC84;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002BBD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002D9C4.s")

void func_8002DBDC(float target,float *angle) {
    float current=*angle;
    float delta=target-current;
    if (delta > 180.0f) {
        *angle=current+360.0f;
        return;
    }
    if (delta < -180.0f) *angle=current-360.0f;
}

void func_8002DC48(float *angle) {
    while (*angle < 0.0f) *angle += 360.0f;
    while (*angle >= 360.0f) *angle -= 360.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002DCC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002DDD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002DF98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002E08C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002E150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002E4A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002E680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002E724.s")

typedef struct { u8 pad[0x14]; u8 queue[0x24]; void *synth; } T024VoicePlayer;
typedef struct { u8 pad[0xC]; u8 synthVoice[0x32]; u8 flags; } T024FreeVoice;
extern T024VoicePlayer *D_8004827C;
extern void alSynStopVoice(void *,void *),alSynFreeVoice(void *,void *);
extern void func_8002F5F0(T024FreeVoice *);
extern void func_8002F31C(void *,void *,u16);
void func_8002F234(T024FreeVoice *voice) {
    if (voice->flags & 4) {
        alSynStopVoice(D_8004827C->synth,voice->synthVoice);
        alSynFreeVoice(D_8004827C->synth,voice->synthVoice);
    }
    func_8002F5F0(voice);
    func_8002F31C(D_8004827C->queue,voice,0xFFFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F2B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F31C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F3DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F45C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F5F0.s")

typedef struct { u8 pad[0x36]; u8 value; } T024Value;
void func_8002F6C4(T024Value *p, u8 value) {
    if (p) p->value = value;
}

typedef struct { u8 pad[0x3F]; u8 value; } T024Result;
s32 func_8002F6DC(T024Result *p) {
    if (p) return p->value;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F6F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F8F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002F944.s")

extern void func_8002F944(s32);
void func_8002F9FC(void) {
    func_8002F944(1);
}

extern void func_8002F944(s32);
void func_8002FA1C(void) {
    func_8002F944(17);
}

extern void func_8002F944(s32);
void func_8002FA3C(void) {
    func_8002F944(3);
}

typedef struct { s16 type; s32 object; s32 value; s32 pad; } T024Event;
extern T024VoicePlayer *D_8004827C;
extern void alEvtqPostEvent(void *, void *, s32);
void func_8002FA5C(s32 object, s16 type, s32 value) {
    T024Event event;
    event.type=type;
    event.object=object;
    event.value=value;
    if (object) alEvtqPostEvent(D_8004827C->queue,&event,0);
}

extern u16 *D_80069928;
u16 func_8002FAA0(u8 index) {
    return D_80069928[index];
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002FAC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002FB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002FDA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8002FFDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80030020.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800300DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80030218.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80030220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003037C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80030440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800306B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80030EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80031050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800310C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80031A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80031DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032504.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032670.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800326F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80032750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003278C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800327E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osViSetSpecialFeatures.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guPerspectiveF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guPerspective.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guRandom.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800330B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guLookAtHilite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guTranslateF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guTranslate.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guRotateF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guRotate.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guLookAtReflectF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guLookAtReflect.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guScaleF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guScale.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/sqrtf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/main_memcpy.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/main_strlen.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/main_strchr.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80034180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003431C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800343F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800344B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80034554.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80034630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800347D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80034DBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800350A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035320.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035A84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035C84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osContStartQuery.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osContGetQuery.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035DE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80035F10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800361C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80036440.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80036644.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osEepromProbe.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osEepromLongWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osEepromLongRead.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osViBlack.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/sinf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/cosf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osWritebackDCacheAll.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guRotateRPYF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guRotateRPY.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxXFMF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxCatF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxF2L.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxIdentF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxIdent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guMtxL2F.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osUnmapTLB.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osMapTLB.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guOrthoF.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guOrtho.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alHeapInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alHeapDBAlloc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80037770.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80037780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alBnkfNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqFileNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__CSPPostNextSeqEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80037A30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80037A6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80037C3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003846C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPSetBank.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPGetState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPPlay.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPStop.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqGetLoc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqSetLoc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80038DE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80038EA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqNextEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqNewMarker.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqGetTicks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqSecToTicks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSeqTicksToSec.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__alCSeqNextDelta.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPSetSeq.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCSPSetVol.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osAiSetFrequency.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alUnlink.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alLink.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alClose.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osAiSetNextBuffer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osAiGetLength.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80039AC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_timeToSamples.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_freePVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_collectPVoices.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__freeParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__allocParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80039C00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80039C08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osContInit.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osContGetInitData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osPackRequestData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osContStartReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osContGetReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osPackReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEvtqFlushType.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEvtqFlush.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEvtqPostEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEvtqNextEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEvtqNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynAddPlayer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_allocatePVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynAllocVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynSetVol.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynStartVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynSetPan.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynSetPitch.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynSetFXMix.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynStopVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynFreeVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCents2Ratio.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/guNormalize.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osSiCreateAccessQueue.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osSiGetAccess.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osSiRelAccess.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osSiRawStartDma.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003B3E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003B45C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003B558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003B8A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003BA08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003BC0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003BD24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003BFC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003C030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003C25C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003C3C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003C5E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003C750.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osEepromWrite.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osPackEepWriteData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osEepStatus.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osSetTimer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osEepromRead.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osPackEepReadData.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__setInstChanState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__resetPerfChanState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__initFromBank.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003D348.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__vsDelta.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__vsVol.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__seqpReleaseVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__voiceNeedsNoteKill.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__unmapVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__postNextSeqEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003D71C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__vsPan.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__lookupVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__mapVoice.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__lookupSoundQuick.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003D9BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003E1DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__seqpStopOsc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__initChanState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqpNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynStartVoiceParams.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynDelete.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osAiDeviceBusy.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSaveNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alMainBusNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alAuxBusNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alResampleNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alLoadNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEnvmixerNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/init_lpfilter.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003EF90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynAllocFX.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alMainBusParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alMainBusPull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alLoadParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alRaw16Pull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8003FB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alAdpcmPull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alResampleParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alResamplePull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_ldexpf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_frexpf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEnvmixerParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800405E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800407B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80040A4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alEnvmixerPull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alAuxBusParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alAuxBusPull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSaveParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSavePull.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/osGetTime.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alCopy.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osContAddressCrc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__osContDataCrc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqGetLoc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqSetLoc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqGetTicks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800414F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800414F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqNextEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqNewMarker.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqSecToTicks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqTicksToSec.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/__alSeqNextDelta.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80041978.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800419C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSeqNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alSynSetPriority.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alFilterNew.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_doModFunc.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_filterBuffer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_saveBuffer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_loadBuffer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/_loadOutputBuffer.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80042198.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alFxParam.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/alFxPull.s")
