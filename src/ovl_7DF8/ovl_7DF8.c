#include "common.h"

typedef struct RenderState {
    s32 index, unk4;
    u8 pad8[0xCC];
    f32 unkD4, unkD8, unkDC, unkE0, unkE4;
    s32 width, height, mode, height2;
    void *unkF8;
} RenderState;

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ABB20.s")

extern s32 guRandom(void);
void func_801AC95C(u8 *arg0, s32 arg1) {
    s32 value = guRandom() % 10;
    s32 i;
    u8 *b, *a;
    s32 j;
    u8 u;
    for (i = 0; i < arg1; i++) {
        arg0[i] = value;
        value++;
        if (value >= 10) {
            value = 0;
        }
    }
    for (i = 0; i != 50; i++) {
        j = guRandom() % arg1;
        a = &arg0[j];
        b = i % arg1 + arg0;
        u = *a;
        *a = *b;
        *b = u;
    }
}

extern u64 osGetTime(void);
extern s32 guRandom(void);
void func_801ACAD8(void) {
    s32 n = osGetTime() & 0xFF;
    while (n > 0) {
        guRandom();
        n--;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACB1C.s")

extern s32 func_801AF67C(int);                               /* extern */
extern int func_801AF68C(s32, s32);                          /* extern */
extern int func_801BBC84(void);                                  /* extern */
extern int func_801C3E40(s32);                               /* extern */
extern u8 D_801CD454;

void func_801ACE04(s32 arg0, s32 arg1) {
    if (D_801CD454 != 0) {
        func_801BBC84();
    }
    func_801AF68C(arg0, arg1);
    if (func_801AF67C(4) != 0) {
        func_801C3E40(arg0);
    }
}

typedef void (*Callback)();
extern int func_801ACB1C(Callback, Callback, Callback);                     /* extern */
extern s32 func_801AF67C(int);                               /* extern */
extern void func_801ACE04();
extern void func_801AD568();
extern void func_801B47A4();
extern void func_801BD3FC();

void func_801ACE5C(void) {
    if (func_801AF67C(0x20) != 0) {
        func_801ACB1C(func_801AD568, func_801ACE04, func_801B47A4);
        return;
    }
    func_801ACB1C(func_801AD568, func_801ACE04, func_801BD3FC);
}

extern void (*D_8004AA30)(int, int, int, int, float, float, float);
extern int D_800695CC, D_800695D0;
extern float D_800695D4, D_800695D8, D_800695DC;
void func_801ACEC0(int a0, int a1, int a2) {
    D_8004AA30(a0, a1, D_800695CC, D_800695D0,
        D_800695D4, D_800695D8, D_800695DC);
}

extern s32 func_801C23C0(void);
extern void func_801ADC64(int);
void func_801ACF1C(void) {
    if (func_801C23C0() == 1) {
        func_801ADC64(0);
    }
}

extern void func_801ACEC0();
extern void func_801ACF1C();
extern void func_801C2ADC();
void func_801ACF50(void) {
    func_801ACB1C(func_801ACEC0, func_801ACF1C, func_801C2ADC);
}

extern s32 func_801C5298(void);
extern s32 D_8029570C;
extern void func_8002AB64(void), func_8002F9FC(void);
void func_801ACF84(void) {
    if (func_801C5298() == 1) {
        func_801ADC64(D_8029570C);
        func_8002AB64();
        func_8002F9FC();
    }
}

extern int func_801ACB1C(Callback, Callback, Callback);                     /* extern */
extern void func_801ACEC0();
extern void func_801ACF84();
extern void func_801AD568();
extern void func_801C71FC();
extern u8 D_802D39BA;

void func_801ACFC8(void) {
    if (D_802D39BA & 1) {
        func_801ACB1C(func_801ACEC0, func_801ACF84, func_801C71FC);
        return;
    }
    func_801ACB1C(func_801AD568, func_801ACF84, func_801C71FC);
}

extern void func_801AD568();
extern void func_801C7310();
extern void func_801C780C();
void func_801AD030(void) {
    func_801ACB1C(func_801AD568, func_801C7310, func_801C780C);
}

extern void func_801AD568();
extern void func_801C9B14();
extern void func_801CAA00();
void func_801AD064(void) {
    func_801ACB1C(func_801AD568, func_801C9B14, func_801CAA00);
}

extern void func_801ACEC0();
extern void func_801C4240();
extern void func_801C4780();
void func_801AD098(void) {
    func_801ACB1C(func_801ACEC0, func_801C4240, func_801C4780);
}

extern u8 D_80295719;
extern unsigned char D_8004EA9C[], D_8004EA9E[];
extern void func_801C0784(s32, s32), func_801C1434(s32, s32, void *);
void func_801AD0CC(s32 arg0, s32 *arg1) {
    if (D_80295719 == 0) {
        func_801C0784(arg0, arg1[1]);
    } else {
        func_801C1434(arg0, arg1[1], D_8004EA9C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD114.s")

extern void func_801AD568();
extern void func_801AD0CC();
extern void func_801AD114();
void func_801AD388(void) {
    func_801ACB1C(func_801AD568, func_801AD0CC, func_801AD114);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD3BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD568.s")

extern void func_8002B7E0(RenderState *);
void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->width = arg1;
    arg0->height = arg2;
    arg0->mode = arg3;
    arg0->height2 = arg2;
    arg0->unk4 = 0;
    arg0->unkD4 = 0.0f;
    arg0->unkD8 = 0.0f;
    arg0->unkE0 = 0.0f;
    arg0->unkE4 = 0.0f;
    func_8002B7E0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD7D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADA04.s")

extern u8 D_801CD450;
extern void func_8002A900(void), func_8002A888(void);
void func_801ADAD4(s32 arg0) {
    if (arg0 != D_801CD450) {
        func_8002A900();
        func_8002A888();
    }
    D_801CD450 = arg0;
}

extern u8 D_801CD450;
s32 func_801ADB14(void) {
    return D_801CD450;
}

extern u8 D_8004A298[];
extern s32 osRecvMesg(void *, void *, s32);
extern s32 D_8004A414;
extern s16 *D_801CD458;
void func_801ADB20(void) {
    while (D_8004A414 != 0) {
        osRecvMesg(&D_8004A298, &D_801CD458, 1);
        if (*D_801CD458 == 2) {
            D_8004A414--;
        }
    }
}

extern void osViBlack(s32);
extern u8 D_80295721;
void func_801ADBB0(void) {
    osViBlack(1);
    while (D_8004A414 != 0) {
        osViBlack(1);
        osRecvMesg(&D_8004A298, &D_801CD458, 1);
        if (*D_801CD458 == 2) {
            D_8004A414--;
        }
    }
    osViBlack(1);
    D_80295721 = 2;
}

extern s32 D_80295708;
extern u8 D_8004AA28;
extern RenderState D_802C9F70;
extern void func_801C4238(void);
void func_801ADC64(s32 arg0) {
    if (D_80295708 == 6) {
        func_801C4238();
    }
    if (arg0 == 5) {
        func_801ADAD4(13);
    }
    if (D_80295708 == 4) {
        D_8004AA28 = 1;
        func_801AD794(&D_802C9F70, 320 << D_8004AA28, 240 << D_8004AA28, 8);
    }
    D_80295708 = arg0;
}

extern void func_801ADC64(s32);
extern void func_801B3DB0(u8, s32);
extern void func_801C1704(s32);
extern u8 D_8004A403;
extern u8 D_80127D50;

void func_801ADCFC(s32 arg0) {
    D_8004A403 = 0;
    func_801C1704(0);
    func_801C1704(1);
    switch (D_80127D50) {
        case 0:
            func_801B3DB0(arg0, 0);
            break;
        case 1:
            func_801B3DB0(arg0, 8);
            break;
        case 2:
            func_801B3DB0(arg0, 0x40);
            break;
        case 3:
            func_801ADC64(9);
            break;
        case 4:
            D_8004A403 = 1;
            func_801B3DB0(arg0, 7);
            break;
        default:
            func_801B3DB0(arg0, 6);
            break;
    }
}

extern u8 D_80127C30[], D_80128350[], D_80127D40[];
extern void func_801BE790(void), func_801C7F90(void), func_801C85C0(void), func_801C8668(s32), func_801B4300();
extern void func_801AC95C(u8 *, s32);
void func_801ADDD8(void) {
    bzero(D_80127C30, D_80128350 - D_80127C30);
    func_801BE790();
    func_801C7F90();
    func_801C85C0();
    func_801C8668(0);
    func_801C8668(1);
    func_801B4300();
    func_801AC95C(D_80127D40, 10);
}

extern unsigned char D_8004EA9C[], D_8004EA9E[];
extern void func_801ADC64(int);
void func_801ADE48(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    D_8004EA9C[0] = a;
    D_8004EA9C[1] = b;
    D_8004EA9E[0] = c;
    D_8004EA9E[1] = d;
    func_801ADC64(10);
}

