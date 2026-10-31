#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18CC0/func_801C47E0.s")

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
