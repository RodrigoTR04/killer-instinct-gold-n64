#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CBBE0.s")

extern s32 osRecvMesg(void *, void *, s32);
extern void osDestroyThread(void *);
extern void func_8002B6EC(void);
extern void func_8002B710(void);
extern void func_8002F6F4(s32, s32, void *);
extern void func_801BFB10(void);
extern void func_801CBF50(void);
extern s32 func_801CCAB0(s32);
extern s32 func_801CCBCC(u8);
extern u8 func_801CCDE8(void);
extern void func_801CD078(s32, s32);
extern void func_801CD174(s32);
extern void func_801CD1F0(s32);
extern s32 D_80066C40;
extern u8 D_8004A25C[];
extern u8 D_80295722;
extern u8 D_802D3698;
extern u8 D_802D3699;
extern u8 D_802D3E14;
extern u8 D_802D3E15;
extern u8 D_802D3FC8;

void func_801CBCCC(void) {
    s32 msg;

    for (;;) {
        osRecvMesg(&D_802D3FC8, &msg, 1);
        D_802D3E14 = 0;
        if (msg == 1) {
            osDestroyThread(0);
        }
        if (msg == 8) {
            D_80295722 = 1;
            func_801CBF50();
        }
        D_802D3698 = 0;
        if (D_802D3699) {
            func_8002B710();
        }
        switch (msg & 0xFF) {
            case 2:
                func_801BFB10();
                break;
            case 9:
                func_801CCAB0(-1);
                break;
            case 3:
                func_801CCAB0(-1);
                func_801CCAB0(0);
                func_801CCAB0(1);
                func_8002F6F4(D_80066C40, 0x109, D_8004A25C);
                break;
            case 4:
                func_801CD1F0(msg >> 8);
                break;
            case 5:
                func_801CD078((u32)msg >> 16, (msg & 0xFF00) >> 8);
                break;
            case 6:
                func_801CD174(msg >> 8);
                break;
            case 7:
                D_802D3E15 = func_801CCDE8();
                break;
            case 10:
                func_801CCBCC(0);
                break;
            case 11:
                func_801CCBCC(1);
                break;
        }
        if (D_802D3699) {
            func_8002B6EC();
        }
        D_802D3698 = 1;
    }
}

extern s32 osCreateMesgQueue();
extern s32 osCreateThread();
extern s32 osSetEventMesg();
extern s32 osStartThread();
extern u8 D_8011E650;
extern u8 D_802D3E18;
extern u8 D_802D3FC8;
extern u8 D_802D3FE0;
extern void func_801CBCCC();

void func_801CBED0(void) {
    osCreateThread(&D_802D3E18, 0x49, &func_801CBCCC, 0, &D_8011E650, 2);
    osCreateMesgQueue(&D_802D3FC8, &D_802D3FE0, 2);
    osSetEventMesg(0xE, &D_802D3FC8, 8);
    osStartThread(&D_802D3E18);
}

extern s32 osSendMesg();
extern s32 osSetThreadPri();
extern u8 D_802D3E18;
extern u8 D_802D3FC8;

void func_801CBF50(void) {
    osSendMesg(&D_802D3FC8, 1, 1);
    osSetThreadPri(&D_802D3E18, 0x7F);
}

extern void func_8002B57C(void);
extern s32 func_800344B0();
extern void func_801CBBE0();
extern s32 func_801CC3BC();
s32 osEepromProbe();
extern u8 D_800684E0;
extern u8 D_802D3D30;
extern u8 D_802D3D98;
extern u8 D_802D3E0D;
extern u8 D_802D3E16;

s32 func_801CBF8C(void) {
    s32 ret;
    u8 old;
    u8 changed;

    ret = 0;
    changed = 0;
    old = D_802D3E0D;
    func_801CBBE0(&D_800684E0, &D_802D3E0D);
    D_802D3E16 = osEepromProbe(&D_800684E0);
    if ((D_802D3E0D & 2) && ((old ^ D_802D3E0D) & 2) == 2) {
        ret = func_800344B0(&D_800684E0, &D_802D3D98, 1);
        if (ret != 0) {
            D_802D3E0D ^= 2;
            ret = func_801CC3BC(ret, 1);
        }
        changed = 1;
    }
    if ((D_802D3E0D & 1) && ((old ^ D_802D3E0D) & 1) == 1) {
        ret = func_800344B0(&D_800684E0, &D_802D3D30, 0);
        changed = 1;
        if (ret != 0) {
            D_802D3E0D ^= 1;
            ret = func_801CC3BC(ret, 0);
        }
    }
    if (changed) {
        func_8002B57C();
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC1A4.s")

s32 __osContDataCrc();

extern s32 osEepromLongWrite();

s32 osEepromProbe();

extern u8 D_800684E0;
extern u8 D_802D3E16;

void func_801CC264(u8 *arg0) {
    D_802D3E16 = osEepromProbe(&D_800684E0);
    arg0[0x1FF] = __osContDataCrc(arg0);
    if (D_802D3E16 != 0) {
        osEepromLongWrite(&D_800684E0, 0, arg0, 0x200);
    }
}

extern s32 osEepromLongRead();

s32 func_801CC2C8(u8 *arg0) {
    s8 v;
    u32 crc;

    v = osEepromProbe(&D_800684E0);
    D_802D3E16 = v;
    if (D_802D3E16) {
        osEepromLongRead(&D_800684E0, 0, arg0, 512);
    } else {
        return 1;
    }
    crc = __osContDataCrc(arg0);
    if ((arg0[511] - crc) != 0) {
        return 1;
    }
    return 0;
}

extern s32 func_80034630();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

s32 func_801CC350(s32 *arg0, s32 arg1) {
    return func_80034630((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC3BC.s")

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

s32 func_801CC524(s32 arg0, s32 arg1) {
    return func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 0, 0, 0x300, &D_802D3A30);
}

extern s32 func_80035690();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

void func_801CC58C(s32 arg0, s32 arg1) {
    func_80035690((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, 0x300, arg0);
}

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

s32 func_801CC600(s32 arg0, s32 arg1) {
    return func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 1, 0, 0x300, &D_802D3A30);
}

extern s32 func_801CC0CC();
extern u8 *D_802D3E04;
const u8 D_80295618[] = "LOADING DATA";
const u8 D_80295628[] = "NO KI DATA ON CONTROLLER PAK";

s32 func_801CC668(s32 arg0) {
    s32 handle;
    s32 err;

    if (!(D_802D3E0D & (1 << arg0))) {
        func_801CBF8C();
        if (!(D_802D3E0D & (1 << arg0))) {
            return 1;
        }
    }
    D_802D3E04 = D_80295618;
    err = func_801CC350(&handle, arg0);
    if (err != 0) {
        if (err != 5) {
            func_801CC3BC(err, arg0);
            err = func_801CC350(&handle, arg0);
        } else {
            D_802D3E04 = D_80295628;
        }
    }
    if (err == 0) {
        err = func_801CC524(handle, arg0);
        if (err != 0) {
            func_801CC3BC(err, arg0);
            err = func_801CC524(handle, arg0);
        }
    }
    if (err == 0) {
        if (func_801CC0CC(&D_802D3A30, 0x300) != 0) {
            err = 1;
        }
    }
    return err;
}


typedef struct {
    u8 unk0;
    u8 pad1[7];
    u64 unk8;
    u64 unk10[12];
} T034SaveHeader;

extern s32 func_801CC2C8(u8 *);
extern void func_801C8868(void *);
extern void func_801BF850(void *);
extern void func_801C8C24(void *);
extern void func_801C8F28(void *);
extern s32 func_801CC668(s32);
extern void func_801C8A38(void *, s32);
extern void func_801C7A98(void);
extern u8 D_80127D58[];
extern u8 D_8012834C;
const u8 D_80295648[] = "LOADED CONTROLLER PAK DATA";
extern u8 D_802D3AA0[];
extern u8 D_802D3ACF;
extern u8 D_802D3AD0[];
extern u8 D_802D3AF4[];
extern u8 D_802D3C98[];
extern u8 *D_802D3E04;

s32 func_801CC784(void) {
    s32 i;

    if (func_801CC2C8(D_802D3AA0) == 0) {
        D_8012834C = D_802D3ACF;
        func_801C8868(D_802D3AA0);
        func_801BF850(D_802D3AF4);
        func_801C8C24(D_802D3AD0);
        func_801C8F28(D_802D3C98);
    } else {
        return 1;
    }
    if (func_801CC668(0) == 0) {
        D_802D3E04 = D_80295648;
        for (i = 0; i < 12; i++) {
            D_80127D58[i] = ((T034SaveHeader *)&D_802D3A30)->unk10[i] & 0xFF;
        }
        func_801C8A38(D_802D3AA0, 0);
    }
    func_801C7A98();
    return 0;
}


const u8 D_80295664[] = "LOADED CONTROLLER PAK 2 DATA";

void func_801CC878(void) {
    s32 i;

    if (func_801CC668(1) == 0) {
        D_802D3E04 = D_80295664;
        for (i = 0; i < 12; i++) {
            D_80127D58[i + 16] = ((T034SaveHeader *)&D_802D3A30)->unk10[i] & 0xFF;
        }
        func_801C8A38(D_802D3AA0, 1);
        func_801C7A98();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC908.s")

extern void func_801BFA40(void *, void *);
extern void func_801C86A8(void *);
extern void func_801C8AE0(void *);
extern void func_801C8DBC(void *);
extern void func_801CC1A4(void *, s32);
extern void func_801CC908(s32);
extern u8 D_80127D58[];
extern u8 D_8012834C;
extern u8 D_802D3AA0[];
extern u8 D_802D3ACF;
extern u8 D_802D3AD0[];
extern u8 D_802D3AF4[];
extern u8 D_802D3C98[];

s32 func_801CCAB0(s32 arg0) {
    s32 i;

    ((T034SaveHeader *)&D_802D3A30)->unk0 = 2;
    ((T034SaveHeader *)&D_802D3A30)->unk8 = 0;
    if (arg0 >= 0) {
        for (i = 0; i < 12; i++) {
            ((T034SaveHeader *)&D_802D3A30)->unk10[i] = D_80127D58[i + arg0 * 16];
        }
    }
    func_801BFA40(D_802D3AF4, &D_802D3A30);
    func_801C86A8(D_802D3AA0);
    D_802D3ACF = D_8012834C;
    func_801C8DBC(D_802D3C98);
    func_801C8AE0(D_802D3AD0);
    if (arg0 < 0) {
        func_801CC264(D_802D3AA0);
    }
    if (arg0 >= 0) {
        func_801CC1A4(&D_802D3A30, 0x300);
        func_801CC908(arg0);
    }
    return 0;
}



s32 func_801CBF8C(void);
s32 func_801CCAB0(s32 arg0);
extern u8 *D_802D3E04;
extern s32 func_801CC3BC(s32, s32);
extern void func_801CC1A4(void *, s32);
extern u8 D_80127D58[];
extern u8 *D_802927A4[];
const u8 D_80295698[] = "SAVING PLAYER 2";
const u8 D_802956A8[] = "SAVED PLAYER 2 DATA";
extern u8 D_802D3E0D;

s32 func_801CCBCC(u8 arg0) {
    s32 sp3C;
    s32 ret;
    s32 i;

    func_801CBF8C();
    if (!(D_802D3E0D & (1 << arg0))) {
        return 1;
    }
    ret = func_801CC350(&sp3C, arg0);
    if (ret != 5 && ret != 0) {
        func_801CC3BC(ret, arg0);
        ret = func_801CC350(&sp3C, arg0);
    }
    if (ret == 5) {
        func_801CCAB0(arg0);
        return 0;
    }
    if (ret == 0) {
        D_802D3E04 = D_80295698;
        if (func_801CC524(sp3C, arg0) == 0) {
            for (i = 0; i < 12; i++) {
                if (((T034SaveHeader *)&D_802D3A30)->unk10[i] < D_80127D58[i + arg0 * 16]) {
                    ((T034SaveHeader *)&D_802D3A30)->unk10[i] = D_80127D58[i + arg0 * 16];
                }
            }
            func_801CC1A4(&D_802D3A30, 0x300);
            ret = func_801CC600(sp3C, arg0);
            if (ret != 0 && ret != 7) {
                func_801CC3BC(ret, arg0);
                ret = func_801CC600(sp3C, arg0);
            }
            if (ret == 0) {
                D_802D3E04 = D_802956A8;
            }
            if (ret == 7) {
                D_802D3E04 = D_802927A4[arg0];
            }
        }
    }
    return 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCD74.s")

extern void osContGetReadData(u16 *);
extern s32 osContStartReadData(void *);

extern u8 D_800684E0;
extern u8 D_802D3E0D;

u8 func_801CCDE8(void) {
    u16 sp18[12];

    if (D_802D3E0D == 0) {
        func_801CBF8C();
        if (D_802D3E0D == 0) {
            return 0;
        }
    }
    osContStartReadData(&D_800684E0);
    osRecvMesg(&D_800684E0, 0, 1);
    osContGetReadData(sp18);
    if ((sp18[0] & 0x1000) && (D_802D3E0D & 1)) {
        return 1;
    }
    if ((sp18[3] & 0x1000) && (D_802D3E0D & 2)) {
        return 2;
    }
    return 0;
}

void func_801CCEAC(u8 *dst, u8 *src, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        *dst = *src + 0x20;
        if (*dst >= 0x3A) {
            *dst += 7;
        }
        if (*dst >= 0x5B || *dst < 0x30) {
            *dst = ' ';
        }
        dst++;
        src++;
    }
}


extern s32 osSendMesg();
extern s32 D_802D3E00;
extern u8 D_802D3E0E;
extern u8 D_802D3FC8;

u8 func_801CD038(s32 arg0, s32 arg1) {
    D_802D3E00 = arg0;
    osSendMesg(&D_802D3FC8, (arg1 << 8) + 4, 1);
    return D_802D3E0E;
}

typedef struct {
    u32 file_size;
    u32 game_code;
    u16 company_code;
    u8 ext_name[4];
    u8 game_name[16];
} T056PfsState;

extern s32 func_80035F10(void *, s32, T056PfsState *);
extern s32 func_800361C0(void *, u16, u32, u8 *, u8 *);

void func_801CD078(s32 arg0, s32 arg1) {
    T056PfsState state;
    void *pfs;

    pfs = (arg1 * 0x68) + &D_802D3D30;
    if (func_80035F10(pfs, arg0, &state) == 0) {
        func_800361C0(pfs, state.company_code, state.game_code, state.game_name, state.ext_name);
        func_8002F6F4(D_80066C40, 0x10A, D_8004A25C);
    }
}

void func_801CD100(s8 *arg0, u32 arg1) {
    s32 var_v0;

    for (var_v0 = 3; var_v0 >= 0; var_v0--) {
        if ((var_v0 != 3) && (arg1 == 0)) {
            arg0[var_v0] = 0x20;
        } else {
            arg0[var_v0] = (arg1 % 10U) + 0x30;
        }

        arg1 = arg1 / 10U;
    }
}

s32 func_8003C750(void *, s32 *);
extern s32 func_801CC3BC();
extern u8 D_802D3D30;
extern s32 D_802D3E10;

void func_801CD174(s32 arg0) {
    s32 var_v0;
    struct { void *ptr; s32 value; } local;

    local.ptr = (arg0 * 0x68) + &D_802D3D30;

    var_v0 = func_8003C750(local.ptr, &local.value);
    if (var_v0 != 0) {
        func_801CC3BC(var_v0, arg0);
        var_v0 = func_8003C750(local.ptr, &local.value);
    }
    if (var_v0 == 0) {
        D_802D3E10 = (s32) (local.value + 0xFF) >> 8;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CD1F0.s")

s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);s32 func_801CCD74(s32 *);
s32 func_801CD3BC(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 sp3C;

    if (func_801CCD74(&sp3C) != 0) {
        return func_801BE540(arg0, arg1, sp3C, arg2, arg3, -1800.0f, 0xFF, 0, 0, 0xFF, 1.0f);
    }
    return 0;
}
