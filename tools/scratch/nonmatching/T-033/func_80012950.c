/* T-052 DRAFT: 40 relocation-masked positional words differ; 312/316 bytes. */
extern void func_80012B24(u16 *, f32, f32, f32, f32, f32);
extern f32 D_800487A0;
extern u8 D_8004AA28;
extern s8 D_8004A984, D_8004AA29, D_8004AC8D, D_8004ACD4;
extern u8 D_8004ACD3, D_8004AD08;
extern s8 D_8004AD09, D_8004AE88, D_8004AE89;
extern u8 D_8004AC8E[], D_8004AC92[];
extern u8 *D_8004ACD8;
extern s32 D_8004ACF0, D_8004AD00, D_8004AD04;
extern f32 D_8004AC80, D_8004ACE0, D_8004AD0C, D_8004AD10;
extern u16 D_8004ACFC;

void func_80012950(s32 arg0) {
    D_8004AA28 = arg0;
    D_8004ACD3 = 0xFF;
    D_8004ACD4 = 0;
    D_8004AE88 = 0;
    D_8004AE89 = 0;
    D_8004ACF0 = 0;
    D_8004ACE0 = 0.0f;
    func_80012B24(&D_8004ACFC, 33.0f, 1.3333333730697632f, 2.0f, D_800487A0, 1.0f);
    D_8004AD00 = 0;
    D_8004AD04 = 0;
    D_8004AD09 = 0;
    D_8004AD08 = 0;
    D_8004AD0C = 0.0f;
    D_8004AD10 = 0.0f;
    D_8004AC80 = 0.0f;
    D_8004AC92[2] = 0;
    D_8004AC92[1] = 0;
    D_8004AC92[0] = 0;
    D_8004AC8E[2] = 0;
    D_8004AC8E[1] = 0;
    D_8004AC8E[0] = 0;
    if (D_8004AA28 == 0) D_8004ACD8 = (u8 *)0x803A4200;
    else D_8004ACD8 = (u8 *)0x801AAB20;
    D_8004A984 = 0;
    D_8004AA29 = 0;
    D_8004AC8D = 0;
}
