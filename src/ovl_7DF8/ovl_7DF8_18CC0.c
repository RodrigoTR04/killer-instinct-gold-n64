#include "common.h"

extern void osUnmapTLB(s32);
extern void osMapTLB(s32, u32, void *, u32, u32, s32);
extern void func_8001CD50(void);
extern s32 func_800216D4(s32, s32, void *, u16);
extern u8 D_8004EA9C, D_8004EA9E, D_802D3970;

s32 func_801C47E0(u8 arg0, u8 arg1, u8 *arg2, u16 arg3) {
    s32 offset;
    u8 oldC;
    u8 oldE;
    s32 bank;

    bank = arg0;
    oldC = D_8004EA9C;
    oldE = D_8004EA9E;
    D_802D3970 = arg1;
    D_8004EA9C = bank & 0x7F;
    D_8004EA9E = arg1;
    func_8001CD50();
    osUnmapTLB(0);

    offset = 0x1000U - ((u32)arg2 & 0xFFF);
    offset &= 0xFFF;
    osMapTLB(0, 0, 0, ((u32)arg2 + offset) & 0x07FFFFFF, -1, -1);
    offset += 0x20;

    bank = func_800216D4(0, bank, arg2 + offset, arg3);
    offset = (offset + bank + 7) & ~7;
    D_8004EA9C = oldC;
    D_8004EA9E = oldE;
    return offset;
}

extern s32 func_8001D7E4(s32, u32, u32, u8, u8);
extern u8 D_8004CED0[];
extern s8 D_8004EA9A;
extern s32 D_8004F2C8;
extern u8 D_8007D900;
extern u8 D_800B0C60;

void func_801C48E4(s32 arg0, u16 arg1, u16 arg2)
{
  u8 *entry;
  entry = (arg0 * 0x1C) + D_8004CED0;
  *((void **) (entry + 0x38)) = (void *) ((arg0 * 0x11120) + (&D_8007D900));
  *((void **) (entry + 0x3C)) = (void *) ((arg0 * 0x8890) + (&D_800B0C60));
  D_8004F2C8 = 0;
  D_8004EA9A = 0;
  func_8001D7E4(arg0 + 2, arg1, arg2, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18CC0/func_801C49A8.s")
