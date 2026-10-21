#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BE790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BE910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BEA74.s")

typedef struct { u32 name, score; } T100Score;
typedef struct { T100Score *entries; u8 count, descending; u16 pad; } T100ScoreTable;
extern T100ScoreTable D_80127D80[];
extern void func_801BEFFC(void);
void func_801BED0C(u32 text, u64 packed) {
    s32 i, j;
    if ((text >> 24) == 0) text |= 0x20000000;
    if (!(text & 0xFF0000)) text |= 0x200000;
    if (!(text & 0xFF00)) text |= 0x2000;
    text &= ~255;
    for (i = 1; i != 4; i++) {
        if (packed % 11 != 0) D_80127D80[i].entries[(packed % 11) - 1].name = text;
        packed /= 11;
    }
    j = 0;
    do {
        if (packed % 6 != 0) D_80127D80[i].entries[(packed % 6) - 1].name = text;
        i++; packed /= 6; j++;
    } while (j != 20);
    func_801BEFFC();
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BEEA4.s")

extern void func_801BE910(s32 *, s32, s32, s32);
extern s32 func_801BEEA4(s32, s32, s32);
extern s32 func_801BF0E8(s32 *, s32, s32);
extern s32 D_80127E50;
extern s32 D_80127EA0;
extern s32 D_80127EF0;
extern s32 D_80127F40;
extern s32 D_802D36D0[];
extern s32 D_802D3748[];

void func_801BEFFC(void) {
    s32 temp_s3;
    s32 var_s0;

    temp_s3 = func_801BF0E8(&D_80127F40, 0xA, func_801BF0E8(&D_80127EF0, 0xA, func_801BF0E8(&D_80127EA0, 0xA, 0)));
    func_801BE910(&D_80127E50, 0xA, 0, 0);
    var_s0 = 0;
    if (temp_s3 > 0) {
        do {
            func_801BEEA4(0, D_802D3748[var_s0], D_802D36D0[var_s0]);
            var_s0 += 1;
        } while (var_s0 != temp_s3);
    }
    if (var_s0 < 0xA) {
        do {
            func_801BEEA4(0, 1, 0);
            var_s0 += 1;
        } while (var_s0 < 0xA);
    }
}

s32 func_801BF0E8(s32 *arg0, s32 count, s32 used) {
    s32 i, j, value;
    s32 *score;
    i = 0;
    if (count > 0) {
        do {
            value = *arg0;
            j = 0;
            while (j < used && value != D_802D36D0[j]) {
                j++;
            }
            if (j == used) {
                D_802D36D0[j] = value;
                D_802D3748[j] = 10 - i;
                used++;
            } else {
                score = &D_802D3748[j];
                *score = (*score - i) + 10;
            }
            i++;
            arg0 += 2;
        } while (i != count);
    }
    return used;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF720.s")

extern s32 func_801BF720(s32);
u8 *func_801BF788(u8 *arg0, u8 *arg1, s32 count) {
    s32 i;
    s32 first;
    u16 packed;
    i = 0;
    if (count > 0) {
        do {
            packed = (arg0[0] << 8) + arg0[1];
            first = func_801BF720((packed >> 10) & 31) << 24;
            first |= (func_801BF720((packed >> 5) & 31) << 16);
            first |= func_801BF720(packed & 31) << 8;
            *(s32 *)arg1 = first;
            i++;
            arg1 += 8;
            arg0 += 3;
            *(s16 *)(arg1 - 4) = arg0[-1];
        } while (i != count);
    }
    return arg0;
}

extern u8 *func_801BF788(u8 *, u8 *, s32);
extern u8 D_80127F90;
extern u8 D_80128148;
extern u8 D_80128300;

void func_801BF850(u8 *arg0)
{
  u8 *next;
  u8 *next_2;
  u8 *first;
  u8 *second;
  u8 *cursor;
  cursor = func_801BF788(func_801BF788(func_801BF788(arg0, (u8 *)&D_80127EA0, 10), (u8 *)&D_80127EF0, 0xA), (u8 *)&D_80127F40, 0xA);
  /* Keep these loop statements joined: IDO schedules by source line. */
  first = &D_80127F90; do { next = func_801BF788(cursor, first, 5); first += 0x28; cursor = next; } while (((u32) first) < ((u32) (&D_80128148))); second = &D_80128148; do { next_2 = func_801BF788(cursor, second, 5); second += 0x28;  cursor = next_2; } while (second != (&D_80128300));
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF914.s")

extern s32 func_801BF914(s32);

u8 *func_801BF988(u8 *arg0, u8 *arg1, s32 count) {
    u32 packed;
    s32 i;
    i = 0;
    if (count > 0) {
        do {
            packed = func_801BF914((*(s32 *)arg1 >> 24) & 255) << 10;
            packed |= (func_801BF914((*(s32 *)arg1 >> 16) & 255) << 5);
            packed |= func_801BF914((*(s32 *)arg1 >> 8) & 255);
            arg0[0] = packed >> 8;
            /* Narrow the packed character word before storing its low byte. */
            arg0[1] = (u16) packed;
            i++;
            arg1 += 8;
            arg0 += 3;
            arg0[-1] = *(u16 *)(arg1 - 4);
        } while (i != count);
    }
    return arg0;
}

extern u8 *func_801BF988(u8 *, u8 *, s32);
extern u8 D_80127F90;
extern u8 D_80128148;
extern u8 D_80128300;

void func_801BFA40(u8 *arg0)
{
  u8 *next;
  u8 *next_2;
  u8 *first;
  u8 *second;
  int stride;
  u8 *cursor;
  stride = 0x28;
  cursor = func_801BF988(func_801BF988(func_801BF988(arg0, (u8 *)&D_80127EA0, 10), (u8 *)&D_80127EF0, 0xA), (u8 *)&D_80127F40, 0xA);
  /* Keep these loop statements joined: IDO schedules by source line. */
  first = &D_80127F90; do { next = func_801BF988(cursor, first, 5); first += stride; cursor = next; } while (((u32) first) < ((u32) (&D_80128148))); second = &D_80128148; do {
    next = second;
    next_2 = func_801BF988(cursor, next, 5);
    second += stride;
    cursor = next_2;
  }
  while (second != (&D_80128300));
}
