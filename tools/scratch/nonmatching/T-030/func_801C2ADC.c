/* T-100 improved draft; measurements and remaining causes in T-100/REPORT.md. */
#include "common.h"

extern void func_8002F6F4();
extern void func_801ADC64(s32);
extern u8 D_8004A26C[], D_8004A270[];
extern s32 D_80066C40;
extern s8 D_80127D38, D_8012834C, D_8029571A;
extern u8 D_80127D58[32];
extern u16 D_8028557C[5][7];
extern u64 D_802D3678[];
extern u8 D_802D3874, D_802D38CC[5];

void func_801C2ADC(s32 player, u64 buttons) {     u64 *state;     u64 pressed;     u32 i;     u8 *cursor;     u16 *sequence;     s32 j;     if ((buttons & 0x1000) && !(D_802D3678[player] & 0x1000) && D_802D3874 == 0) {         D_802D3874 = 1;         D_8029571A = 0;     }     state = &D_802D3678[player];     pressed = buttons & 0xFFFF;     if (pressed && !(*state & 0xFFFF)) {         cursor = D_802D38CC;         sequence = D_8028557C[0];         for (i = 0; i != 5; i++, sequence += 7, cursor++) {             if (pressed == sequence[*cursor]) (*cursor)++;             else *cursor = 0;             if (sequence[*cursor] == 0) {                 switch (i) {                 case 0:                     func_8002F6F4(D_80066C40, 0x8B, D_8004A26C);                     D_80127D38 = 1;                     break;                 case 1: func_801ADC64(4); break;                 case 2:                     D_8012834C = 6;                     func_8002F6F4(D_80066C40, 0x17D, D_8004A26C);                     func_8002F6F4(D_80066C40, 0x17D, D_8004A270);                     break;                 case 3:                     for (j = 0; j < 32; j++) D_80127D58[j] = 120;                     func_8002F6F4(D_80066C40, 0x17A, D_8004A26C);                     func_8002F6F4(D_80066C40, 0x17A, D_8004A26C);                     break;                 case 4: break;                 }                 *cursor = 0;             }         }     }     *state = buttons; }
