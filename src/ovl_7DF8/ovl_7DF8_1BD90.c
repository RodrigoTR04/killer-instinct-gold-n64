#include "common.h"

typedef struct {
    u8 b[6];
} T021Six;

extern T021Six D_80127C68[];

extern u16 D_80127CA8[][6];
extern u16 D_802923AC[];

void func_801C78B0(arg0, arg1)
u8 arg0;
u8 arg1;
{
    s32 i;

    if ((arg0 < 2) && (arg1 < 10)) {
        for (i = 0; i < 6; i++) {
            D_80127CA8[arg0][i] = D_802923AC[D_80127C68[arg1].b[i]];
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C7998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C7A98.s")

extern void func_801ADAD4(s32);
extern void func_801C7A98(void);
extern u8 func_801CD038(s32, s32);
extern u8 D_800F4070[];
extern s8 D_801CD454, D_802923F5;
extern void *D_802925AC, *D_802926AC;
extern u8 D_802952E0[], D_802952FC[];
extern s32 D_802956F8, D_802956FC, D_80295700, D_802CA064;
extern u64 D_802D3678[2];
extern f32 D_802D39F8;
extern s8 D_802D39FC, D_802D3A01, D_802D3A02, D_802D3A07;
extern u8 D_802D3A00, D_802D3A06, D_802D3E15;

void func_801C7CD0(u8 arg0)
{
    if (D_802D3E15)
    {
        arg0 = 5;
    }
    func_801C7A98();
    D_802D39F8 = 0.0f;
    if (D_802D3A06)
    {
        arg0 = 3;
        D_802925AC = D_802952E0;
    }
    else
    {
        D_802925AC = D_802952FC;
    }
    D_802D39FC = 0;
    D_802956F8 = D_802956FC = D_80295700 = 0;
    D_802CA064 = 480;
    D_801CD454 = 0;
    D_802D3A00 = arg0;
    if (D_802D3A00 == 5)
    {
        if (D_802D3E15 == 0)
        {
            D_802D3E15 = 1;
        }
        D_802D3678[0] = 0x1000;
        D_802D3678[1] = 0x1000;
        D_802923F5 = 0;
        func_801CD038((s32) D_800F4070, D_802D3E15 - 1);
        D_802926AC = D_800F4070;
    }
    else if (D_802D3A00 != 4 && D_802D3A06 == 0)
    {
        func_801ADAD4(40);
    }
    D_802D3A01 = 0;
    D_802D3A02 = 65;
    D_802D3A07 = 0;
}

void func_801C7E4C(u8 arg0) {
    T021Six *p;

    p = &D_80127C68[arg0];
    p->b[0] = 6;
    p->b[1] = 1;
    p->b[2] = 3;
    p->b[3] = 7;
    p->b[4] = 2;
    p->b[5] = 0;
}

void func_801C7E98(u8 arg0, u8 arg1) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_80127C68[arg1].b[i] = D_80127C68[arg0].b[i];
    }
}

extern void func_801C78B0();

void func_801C7F10(void) {
    func_801C78B0(0, 0);
    func_801C78B0(1, 1);
}

extern void func_801C78B0();
extern u8 D_80127D30[8];
extern u8 D_80127D31;

void func_801C7F40(void) {
    func_801C78B0(0, (D_80127D30[0] + 1) & 0xFF);
    func_801C78B0(1, (D_80127D31 + 1) & 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C7F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C8004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C80F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C85C0.s")

extern u8 D_80127D58[];
void func_801C8668(u8 arg0) {
    s32 i;
    for (i = 0; i < 16; i++) {
        D_80127D58[i + arg0 * 16] = 0;
    }
}

extern u8 D_80127CC0[];

s32 func_801C86A8(u8 *arg0) {
    s32 i;
    s32 j;
    u32 v;
    u8 b;
    u8 *start = arg0;

    for (i = 0; i < 10; i++) {
        v = 0;
        for (j = 0; j < 6; j++) {
            v |= D_80127C68[i].b[j] << (j * 3);
        }
        *arg0++ = v & 0xFF;
        v >>= 8;
        *arg0++ = v & 0xFF;
        v >>= 8;
        *arg0++ = v & 0xFF;
    }
    for (i = 0; i < 34; i++) {
        if (i & 1) {
            b |= D_80127CC0[i] << 4;
            *arg0++ = b;
        } else {
            b = D_80127CC0[i];
        }
    }
    if (i & 1) {
        *arg0++ = b;
    }
    return arg0 - start;
}


extern u8 D_80127CC0[];

s32 func_801C8868(u8 *arg0) {
    s32 i;
    s32 j;
    u32 v;
    u8 *start = arg0;

    for (i = 0; i < 10; i++) {
        v = arg0[0] + (arg0[1] << 8) + (arg0[2] << 16);
        arg0 += 3;
        for (j = 0; j < 6; j++) {
            D_80127C68[i].b[j] = (v >> (j * 3)) & 7;
        }
    }
    for (i = 0; i < 34; i++) {
        if (i & 1) {
            D_80127CC0[i] = (*arg0++ >> 4) & 0xF;
        } else {
            D_80127CC0[i] = *arg0 & 0xF;
        }
    }
    if (i & 1) {
        arg0++;
    }
    return arg0 - start;
}


void func_801C8A38(u8 *arg0, s32 arg1) {
    s32 j;
    u32 v;

    arg0 += arg1 * 3;
    v = arg0[0] + (arg0[1] << 8) + (arg0[2] << 16);
    for (j = 0; j < 6; j++) {
        D_80127C68[arg1].b[j] = (v >> (j * 3)) & 7;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C8AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C8C24.s")

extern u8 D_80127D58[];

void func_801C8DBC(u8 *arg0) {
    u64 bits;
    u8 i;
    u8 level;

    bits = 0;
    for (i = 0; i < 10; i++) {
        if (D_80127D58[i] > D_80127D58[i + 16]) {
            level = D_80127D58[i];
        } else {
            level = D_80127D58[i + 16];
        }
        if (level >= 120) {
            level = 3;
        } else if (level >= 55) {
            level = 2;
        } else if (level >= 5) {
            level = 1;
        } else {
            level = 0;
        }
        bits |= level << (i * 2);
    }
    bits |= bits << 20;
    arg0[0] = bits;
    arg0[1] = bits >> 8;
    arg0[2] = bits >> 16;
    arg0[3] = bits >> 24;
    arg0[4] = bits >> 32;
}


void func_801C8F28(u8 *arg0)
{
    u8 i;
    u8 v;
    /* Keep the first row value in a signed halfword for IDO register allocation. */
    s16 intensity;
    u64 bits;
    bits = (u64)arg0[0] + ((u64)arg0[1] << 8) + ((u64)arg0[2] << 16) + ((u64)arg0[3] << 24) + ((u64)arg0[4] << 32);
    for (i = 0; i < 20; i++)
    {
        switch ((s32)(bits >> (i * 2)) & 3)
        {
            default:
                v = 0;
                break;

            case 3:
                v = 120;
                break;

            case 2:
                v = 55;
                break;

            case 1:
                v = 5;
                break;

        }

        if (i < 10)
        {
            intensity = v;
            D_80127D58[i] = intensity;
        }
        else
        {
            D_80127D58[i + 6] = v;
        }
    }

}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C90D4.s")

extern void *memcpy(void *, const void *, u32);
extern u8 D_80127D20[];
extern u8 D_80127D28[];
extern char D_8029531C[];
typedef struct {
    char line1[8];
    char line2[8];
} T034Text;
extern T034Text D_802D3A20;

char *func_801C9584(u8 arg0, u8 arg1) {
    char *ret = D_802D3A20.line1;

    memcpy(&D_802D3A20, D_8029531C, sizeof(T034Text));
    D_802D3A20.line1[4] = D_80127D20[arg0] / 10 + '0';
    D_802D3A20.line1[5] = D_80127D20[arg0] % 10 + '0';
    D_802D3A20.line2[5] = D_80127D28[arg0] / 10 + '0';
    D_802D3A20.line2[6] = D_80127D28[arg0] % 10 + '0';
    switch (arg1) {
    case 2:
        D_802D3A20.line1[6] = ',';
        return D_802D3A20.line1;
    }
    D_802D3A20.line1[6] = 0;
    if (arg1 == 0) {
        return D_802D3A20.line2;
    }
    return D_802D3A20.line1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C9698.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C9B14.s")

void func_801CA784(s32 arg0) {
    s32 i;

    for (i = 0; i < 7 && D_80127D30[i]; i++) {
        if (arg0 == D_80127D30[i]) {
            return;
        }
    }
    if (i < 8) {
        D_80127D30[i] = arg0;
    }
}

/* Queue alias retained for the following functions. */
typedef u8 T034Queue8[8];
#define T034_D_80127D30 (*(T034Queue8 *)&D_80127D30)

void func_801CA7E4(s32 arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < 8 && arg0 != T034_D_80127D30[i]; i++) {
    }
    if (arg0 == T034_D_80127D30[i]) {
        for (j = i + 1; j < 8; j++) {
            T034_D_80127D30[j - 1] = T034_D_80127D30[j];
        }
        T034_D_80127D30[j - 1] = 0;
        for (i = 0; i < 8; i++) {
            if (arg0 < T034_D_80127D30[i]) {
                T034_D_80127D30[i]--;
            }
        }
    }
}


extern u8 D_80127D20[];
extern u8 D_80127D28[];

void func_801CA91C(s32 arg0) {
    s32 i;
    u8 v;

    if (arg0 == 1) {
        v = T034_D_80127D30[0];
        T034_D_80127D30[0] = T034_D_80127D30[1];
    } else {
        v = T034_D_80127D30[1];
    }
    for (i = 1; i < 8 && T034_D_80127D30[i] != 0; i++) {
        T034_D_80127D30[i] = T034_D_80127D30[i + 1];
    }
    T034_D_80127D30[i - 1] = v;
    if (++D_80127D20[T034_D_80127D30[0] - 1] >= 100) {
        D_80127D20[T034_D_80127D30[0] - 1] = 99;
    }
    if (++D_80127D28[v - 1] >= 100) {
        D_80127D28[v - 1] = 99;
    }
    if (arg0 == 1) {
        u8 t = T034_D_80127D30[0];

        T034_D_80127D30[0] = T034_D_80127D30[1];
        T034_D_80127D30[1] = t;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801CAA00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801CB998.s")

extern void func_801C7A98(void);
extern u8 D_80127C40[];
extern u8 D_80127C48[];
extern u8 D_80127C58[];
extern u8 D_80127CC0[];
extern u8 D_80292674;
extern u8 D_80292728[];
extern u8 D_80292730[];
extern u8 D_8029273C[];

void func_801CBA2C(void) {
    s32 i;

    func_801C7A98();
    for (i = 0; i < 5; i++) {
        if (D_80292728[i] != 0) {
            D_80127C40[i] = D_80127CC0[D_80292728[i] - 1];
        }
    }
    if (D_80292674 == 4) {
        D_80127C40[2] = D_80127CC0[0];
    } else if (D_80127CC0[0] >= 3) {
        D_80127C40[2] = 7 - D_80127CC0[0];
    }
    for (i = 0; i < 10; i++) {
        if (D_80292730[i] != 0) {
            D_80127C48[i] = D_80127CC0[D_80292730[i] - 1];
        }
    }
    for (i = 0; i < 11; i++) {
        if (D_8029273C[i]) {
            D_80127C58[i] = D_80127CC0[D_8029273C[i] - 1];
        }
    }
}

