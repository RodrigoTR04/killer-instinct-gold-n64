/* T-019 nonmatching draft. Remaining diff: 648-byte reconstruction versus 628-byte target; control-flow layout, argument spills and registers differ. One m2c structured-exit goto remains in this draft only.
 */
#include "common.h"

s32 func_8002FA3C(u8 *);                              void func_801ADC64(s32);                               void func_801ADE48(u8, u8, u8, u8);                        s32 func_801B3DB0(s32, s32, s32);                         void func_801B4300();                               u8 func_801BFCBC(s32, s32, s32, s32, s32);                              extern u8 D_8004A404;
extern u8 D_8004A407;
extern u8 D_80127D50;
extern s32 D_80295710;
extern u8 D_80295719;
extern u8 D_80295720;

void func_801AD114(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_t5;
    s32 temp_v1;
    u8 temp_v0;
    u8 temp_v1_2;

    temp_v0 = func_801BFCBC(arg0, arg1, arg2, arg3, D_80295719);
    temp_v1 = temp_v0 & 0xFF;
    D_80295719 = temp_v0;
    if (temp_v1 == 4) {
        func_8002FA3C(&D_80295719);
        if ((D_80127D50 != 1) && (D_80127D50 != 2)) {
            if (D_8004A404 == 2) {
                goto block_6;
            }
            temp_v1_2 = D_80295720;
            if ((arg0 == (2 - temp_v1_2)) && !((arg0 + 1) & D_8004A407)) {
                temp_a0 = temp_v1_2 - 1;
                if (D_8004A407 == 0) {
                    func_801B3DB0(temp_a0 & 0xFF, 1, 2);
                    D_80295710 = 5;
                } else {
                    func_801B4300(temp_a0);
                }
                func_801ADC64(D_80295710);
                D_80295719 = 0;
                return;
            }
            temp_t5 = (temp_v1_2 - 1) & 0xFF;
            if (D_8004A407 != 0) {
                func_801B3DB0(temp_t5, 2, 2);
                D_80295719 = 0;
                return;
            }
            func_801B4300(temp_t5);
            func_801ADC64(0);
            D_80295719 = 0;
            return;
        }
block_6:
        D_8004A407 = 0;
        func_801ADC64(0);
        return;
    }
    if ((temp_v1 == 5) || (temp_v1 == 6)) {
        func_8002FA3C(&D_80295719);
        if ((D_80127D50 == 1) || (D_80127D50 == 2)) {
            D_8004A407 &= 0xFB;
            func_801ADE48(0, 0, 1, 2);
            D_80295710 = 0xA;
        } else {
            D_80295710 = 5;
            if (D_8004A407 == 0) {
                if (D_80295720 != 0) {
                    func_801B3DB0((D_80295720 - 1) & 0xFF, 3, 2);
                } else {
                    func_801B3DB0((D_80295719 - 5) & 0xFF, 3, 2);
                    D_8004A407 = 7 - D_80295719;
                }
            } else {
                func_801B3DB0((2 - D_80295720) & 0xFF, 4, 2);
            }
        }
        func_801ADC64(D_80295710);
    }
}

