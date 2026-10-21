/* T-116 DRAFT: see T-116/REPORT.md for remaining instructions. */
extern s32 func_8001D7E4();
extern u8 D_8004CED0[];
extern s8 D_8004EA9A;
extern s32 D_8004F2C8;
extern u8 D_8007D900;
extern u8 D_800B0C60;

void func_801C48E4(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_v0;
  s32 *firstParameter;
  arg1 = (u16) arg1;
  arg2 = (u16) arg2;
  temp_v0 = (arg0 * 0x1C) + D_8004CED0;
  firstParameter = &arg1;
  *((void **) (temp_v0 + 0x38)) = (void *) ((arg0 * 0x11120) + (&D_8007D900));
  *((void **) (temp_v0 + 0x3C)) = (void *) ((arg0 * 0x8890) + (&D_800B0C60));
  D_8004F2C8 = 0;
  D_8004EA9A = 0;
  func_8001D7E4(arg0 + 2, *firstParameter, arg2, 0, 0);
}
