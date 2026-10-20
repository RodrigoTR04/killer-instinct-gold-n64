/* T-092 DRAFT: 13 relocation-masked differing words; 316 bytes. */

extern u8 D_8004AA28;
extern u8 D_8004AC88;
extern u8 D_8004AA28, D_8004AC88;
void func_8001BF1C(u8 **, s32, s32, f32);      /* extern */
extern f32 D_800489F0;
extern f32 D_800489F4;
extern u8 D_8004A4C8;
extern u8 D_801D7E00;
extern u8 D_801D8550;

void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2)
{
  u8 *var_s1;
  f32 temp_f0;
  f32 temp_f0_2;
  f32 temp_f22;
  f32 temp_f24;
  s32 var_s0;
  u8 *temp_v1;
  if (D_8004AA28 != 1)
  {
    temp_v1 = *arg0;
 *arg0 = temp_v1 + 8; *((s32 *) (((u8 *) temp_v1) + 0)) = 0x06000000; *((s32 *) (((u8 *) temp_v1) + 4)) = (s32) (*((s32 *) (((u8 *) (&D_8004A4C8)) + (arg1 * 0xC))));
    temp_f24 = D_800489F0;
    temp_f22 = D_800489F4;
    var_s1 = &D_801D7E00;
    var_s0 = 0;
    loop_2:
    temp_f0 = ((*((f32 *) (((u8 *) var_s1) + 0xF0))) * temp_f22) - temp_f24;

    if (temp_f0 <= arg2)
    {
      func_8001BF1C(arg0, arg1, var_s0, temp_f0);
      var_s0 += 1;
      var_s1 += 0x30;
      if (var_s0 < 0x28)
      {
        goto loop_2;
      }
    }
    var_s1 = &D_801D8550;
    var_s0 = 0x27;
    loop_5:
    temp_f0_2 = ((*((f32 *) (((u8 *) var_s1) + 0xF0))) * temp_f22) - temp_f24;

    if (arg2 < temp_f0_2)
    {
      func_8001BF1C(arg0, arg1, var_s0, temp_f0_2);
      var_s0 -= 1;
      var_s1 -= 0x30;
      if (var_s0 >= 0)
      {
        goto loop_5;
      }
    }
  }
}
