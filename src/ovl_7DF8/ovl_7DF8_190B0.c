#include "common.h"

extern void func_801C47E0(u32, u32, void *, u32);
extern u8 D_800F4070;
extern u8 D_802D3985;
extern u8 D_802D3986;
extern u8 D_802D399C;
extern u8 D_802D399D;
extern u8 D_802D399E;

void func_801C4BD0(arg0)
u8 arg0;
{
    if (arg0 == 0xC8) {
        func_801C47E0((D_802D3985 + 0x80) & 0xFF, D_802D3986, &D_800F4070, D_802D3985);
    } else {
        func_801C47E0(D_802D3985, D_802D3986, &D_800F4070, arg0);
    }
    D_802D399E = arg0;
    D_802D399C = 0;
    D_802D399D = 1;
}

extern f32 D_802D3880;
extern f32 D_802D3884;
extern f32 D_802D3888;
extern f32 D_802D388C;
extern f32 D_802D3898;
extern f32 D_802D389C;
extern f32 D_802D38A0;
extern f32 D_802D38A4;
extern f32 D_802D38A8;
extern f32 D_802D38AC;
extern f32 D_802D38B0;
extern f32 D_802D38B4;
extern f32 D_802D38B8;
extern f32 D_802D38BC;
extern f32 D_802D38C0;
extern f32 D_802D38C4;

void func_801C4C64(f32 *arg0, f32 *arg1) {
    D_802D3898 = arg0[0];
    D_802D38A8 = arg0[4];
    D_802D38B8 = arg0[8];
    D_802D3880 = arg1[0];
    D_802D389C = arg0[1];
    D_802D38AC = arg0[5];
    D_802D38BC = arg0[9];
    D_802D3884 = arg1[1];
    D_802D38A0 = arg0[2];
    D_802D38B0 = arg0[6];
    D_802D38C0 = arg0[10];
    D_802D3888 = arg1[2];
    D_802D38A4 = arg0[3];
    D_802D38B4 = arg0[7];
    D_802D38C4 = arg0[11];
    D_802D388C = arg1[3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C4D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C4D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C4E38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C5064.s")

typedef struct { u32 w0, w1; } T021Gfx;
extern u8 D_4AC40;

void func_801C51F8(T021Gfx **arg0)
{
    T021Gfx *p0, *p1, *p2, *p3, *p4;
    p0 = (*arg0)++;
    p0->w0 = 0x01030040; p0->w1 = (u32) &D_4AC40;
    p1 = (*arg0)++;
    p1->w0 = 0xBC000404;
    p1->w1 = (u32)1;
    p2 = (*arg0)++;
    p2->w1 = (u32)1;
    p2->w0 = 0xBC000C04;
    p3 = (*arg0)++;
    p3->w0 = 0xBC001404;
    p3->w1 = (u32)0xFFFF;
    p4 = (*arg0)++;
    p4->w1 = (u32)0xFFFF;
    p4->w0 = 0xBC001C04;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C5298.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C5E74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C67CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C6A80.s")

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C6BA4(s32 arg0, u32 arg1) {
    u8 temp_t2;

    if (arg1 >= 0xCEU) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x75);
            D_802D399C = 0x29;
            func_8002F6F4(D_80066C40, 0xE0, &D_8004A258, &D_802D399C);
        }
        if (D_802D399C-- < 0x1B) {
            D_802D399C = 0x1B;
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
            func_8002F6F4(D_80066C40, 0xDC, &D_8004A258, &D_802D399C);
        }
    }
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;
extern s8 D_802D39B5;

u32 func_801C6C78(s32 arg0, u32 arg1) {
    s32 var_v1;
    u8 temp_t2;
    u8 temp_t9;

    if (arg1 >= 0xD3U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x83);
        }
        var_v1 = (D_802D399C += 2);
        if (var_v1 >= 0x2A) {
            var_v1 = (D_802D399C = 0x29);
        }
        if (var_v1 == 0x18) {
            func_8002F6F4(D_80066C40, 0xC2, &D_8004A258);
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
        }
    }
    D_802D39B5 = 0x40;
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_190B0/func_801C6D40.s")

extern u8 D_802D399C;

s32 func_801C6E6C(s32 arg0, s32 arg1) {
    D_802D399C = 1;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern s32 D_800698C4;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C6E84(s32 arg0, u32 arg1) {
    u8 temp_t9;

    if (arg1 >= 0xF1U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x82);
            func_8002F6F4(D_80066C40, 0xED, &D_8004A258);
        }
        D_802D399C += 2;
        if (D_802D399C >= 0x2C) {
            D_802D399C = 0x2B;
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
        }
    }
    D_800698C4 = 1;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;
extern u8 D_802D39B4;

u32 func_801C6F3C(s32 arg0, u32 arg1) {
    s32 temp_v1;
    u8 temp_t2;
    u8 temp_t9;

    if (arg1 >= 0xD3U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x84);
        }
        temp_v1 = (D_802D399C += 2);
        if (temp_v1 >= 0x28) {
            D_802D399C = 0x27;
        } else if (temp_v1 == 0x10) {
            func_8002F6F4(D_80066C40, 0xF8, &D_8004A258);
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
            func_8002F6F4(D_80066C40, 0xF0, &D_8004A258);
        }
    }
    D_802D39B4 = 1;
    return arg1;
}

extern u8 D_802D39B4;

s32 func_801C701C(s32 arg0, s32 arg1) {
    D_802D39B4 = 0xFF;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern f32 D_8004AC84;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C7034(s32 arg0, u32 arg1) {
    s32 var_v1;

    u8 temp_t2;

    if (arg1 < 0xF0U) {
        D_8004AC84 = 390.0f;
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
        }
    } else {
        if (D_802D399E == 0) {
            func_801C4BD0(0xAB);
        }
        var_v1 = (D_802D399C += 2);
        if (var_v1 >= 0x47) {
            var_v1 = (D_802D399C = 0x47);
        }
        if (var_v1 == 0x1C) {
            func_8002F6F4(D_80066C40, 0x103, &D_8004A258);
        }
        arg1 = 0xF0;
    }
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399D;
extern u8 D_802D399E;

u32 func_801C7100(s32 arg0, u32 arg1) {
    s32 temp_v1;
    u8 temp_t2;

    if (arg1 < 0x78U) {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
        }
    } else {
        if (D_802D399E == 0) {
            func_801C4BD0(0xA0);
            D_802D399D = 0;
            func_8002F6F4(D_80066C40, 0x8B, &D_8004A258);
        }
        if (D_802D399E == 0xA0) {
            temp_v1 = (D_802D399C += 2);
            if (temp_v1 >= 0xC) {
                D_802D399D += 1;
                if (D_802D399D < 0xA) {
                    D_802D399C = 0xC;
                } else if (temp_v1 >= 0x1D) {
                    D_802D399C = 0x1D;
                }
            }
        }
    }
    return arg1;
}

extern u8 D_80295720;
extern u8 D_802D39BA;
extern void func_801C4D6C(void);
extern u64 D_802D3678[];
extern s8 D_802D39B6;

void func_801C71FC(s32 arg0, u64 arg1) {
    if (arg0 + 1 == D_80295720 && (arg1 & 0x1000) && !(D_802D3678[arg0] & 0x1000)) {
        if (D_802D39BA & 3) {
            D_802D39BA &= 0xFC;
            func_801C4D6C();
        } else {
            D_802D39BA = 0;
        }
        D_802D39B6 = 1;
    }
    D_802D3678[arg0] = arg1;
}
