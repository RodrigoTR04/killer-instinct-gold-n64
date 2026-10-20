/* T-092 DRAFT: 4 relocation-masked differing words; 424 bytes. */
extern s32 func_801CBF8C();
s32 func_801CC350(s32 *, s32);
extern s32 func_801CC3BC();

s32 func_801CC600(s32, s32);

extern s32 D_80066C40;
extern u8 *D_802927A4[];
extern u8 D_80295684;
extern u8 D_8029568C;
extern u8 *D_802D3E04;
extern u8 D_802D3E0D;


s32 func_801CC908(s32 arg0)
{
  s32 sp28;
  s32 sp24;
  s32 temp_v1;
  s32 var_a3;
  s32 sp2C;
  s32 var_v0;
  temp_v1 = 1 << arg0;
  if (!(D_802D3E0D & temp_v1))
  {
    sp24 = temp_v1;
    func_801CBF8C();
    if (!(D_802D3E0D & temp_v1))
    {
      return 1;
    }
  }
  var_v0 = func_801CC350(&sp2C, arg0);
  var_a3 = var_v0;
  if ((var_v0 != 5) && (var_v0 != 0))
  {
    func_801CC3BC(var_a3, arg0);
    var_v0 = func_801CC350(&sp2C, arg0);
    var_a3 = var_v0;
  }
  if (var_v0 == 5)
  {
    var_v0 = func_801CC58C(&sp2C, arg0);
    var_a3 = var_v0;
    if (var_v0 != 0)
    {
      func_801CC3BC(var_a3, arg0);
      var_v0 = func_801CC58C(&sp2C, arg0);
      var_a3 = var_v0;
    }
  }
  if ((var_v0 == 0) || (var_v0 == 5))
  {
    D_802D3E04 = &D_80295684;
    sp28 = func_801CC600(sp2C, arg0);
    var_a3 = sp28;
    if (sp28 != 0)
    {
      if (sp28 == 7)
      {
        D_802D3E04 = D_802927A4[arg0];
      }
      else
      {
        func_801CC3BC(var_a3, arg0);
      }
      sp28 = func_801CC600(sp2C, arg0);
      var_a3 = sp28;
    }
    if (sp28 == 0)
    {
      D_802D3E04 = &D_8029568C;
      sp28 = var_a3;
      func_8002F6F4(D_80066C40, 0x10A, D_8004A25C);
    }
  }
  if (var_a3 == 7)
  {
    D_802D3E04 = D_802927A4[arg0];
    D_802D3E14 = 1;
  }
  return var_a3;
}
