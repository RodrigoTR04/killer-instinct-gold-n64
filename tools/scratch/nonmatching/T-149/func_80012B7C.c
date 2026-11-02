/* T-149 DRAFT: 327 differing words; 1572/1576 bytes in the full TU. */

extern u8 D_80044A24, D_8004AA28, D_8004AC88;

extern u16 D_8004ACFC;
extern s32 D_8004AD00, D_8004AD04;
extern u8 *D_8004AA3C;
extern s32 (*D_8004AEAC)(s32,s32,s32,s32);
extern u8 D_8004AA40, D_8004AAC0, D_8004AB40, D_8004ABC0;
extern void func_8001BB64(T033RenderCommand **);
extern void func_8001346C(T033RenderCommand **,u8,f32);
extern void guMtxCatF(void *,void *,void *), guMtxF2L(void *,void *);
extern void guRotateRPYF(void *,f32,f32,f32), guTranslateF(void *,f32,f32,f32);
void func_80012B7C(T033RenderCommand **arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    T033RenderCommand *command;
    s16 temp_v0;
    s32 var_s0;
    u8 *temp_s2;
    u8 *temp_s2_2;

    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xE7000000;
    command->value = 0;
    func_8001BB64(arg0);
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xBA000903;
    command->value = (u32)0xC00;
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xBA001701;
    command->value = 0;
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xF9000000;
    command->value = (u32)1;
    guRotateRPYF(&D_8004AA40 + (D_80044A24 << 6), arg4, 0.0f, 0.0f);
    guRotateRPYF(&D_8004AB40 + (D_80044A24 << 6), 0.0f, arg5, arg6);
    guTranslateF((D_80044A24 << 6) + &D_8004AAC0, (f32) (0.0 - (f64) arg1), (f32) (0.0 - (f64) arg2), (f32) (0.0 - (f64) arg3));
    var_s0 = D_80044A24 << 6;
    temp_s2 = &D_8004AB40 + var_s0;
    guMtxCatF(var_s0 + &D_8004AAC0, temp_s2, temp_s2);
    var_s0 = D_80044A24 << 6;
    temp_s2_2 = &D_8004AB40 + var_s0;
    guMtxCatF(temp_s2_2, &D_8004AA40 + var_s0, temp_s2_2);
    var_s0 = D_80044A24 << 6;
    guMtxF2L(&D_8004AB40 + var_s0, &D_8004ABC0 + var_s0);
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0x01020040;
    command->value = (u32) (&D_8004ABC0 + (D_80044A24 << 6) + 0x80000000);
    command = *arg0;
    *arg0 = command + 1;
    { extern u8 D_4AC40; command->value = (u32)&D_4AC40; }
    command->command = 0x01030040;
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xB4000000;
    command->value = (u32) D_8004ACFC;
    if (D_8004AA28 == 0) {
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC000404;
        command->value = (u32)3;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC000C04;
        command->value = (u32)3;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC001404;
        command->value = (u32)0xFFFD;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC001C04;
        command->value = (u32)0xFFFD;
    } else {
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC000404;
        command->value = (u32)2;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC000C04;
        command->value = (u32)2;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC001404;
        command->value = (u32)0xFFFE;
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xBC001C04;
        command->value = (u32)0xFFFE;
    }
    switch (D_8004AC88) {
    case 0:
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xF5680800;
        command->value = (u32)0x05018050;
        command = *arg0;
        *arg0 = command + 1;
    command->command = (((D_8004AD04 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((2 - D_8004AD00) & 0xFFF);
        command->value = (u32)0x0507E0FE;
        break;
    case 4:
    case 9:
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xF5101000;
        command->value = (u32)0x05018050;
        command = *arg0;
        *arg0 = command + 1;
    command->command = (((D_8004AD00 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((D_8004AD04 + 2) & 0xFFF);
        command->value = (u32)0x0507E0FE;
        break;
    case 6:
    case 12:
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0xF5881000;
        command->value = (u32)0x05018060;
        command = *arg0;
        *arg0 = command + 1;
    command->command = (((D_8004AD04 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((2 - D_8004AD00) & 0xFFF);
        command->value = (u32)0x050FE0FE;
        break;
    }
    if (D_8004AA3C != 0) {
        command = *arg0;
        *arg0 = command + 1;
    command->command = 0x06000000;
        command->value = (u32) D_8004AA3C;
    }
    temp_v0 = ((s32 (*)(s32,s32,s32,s32,s32))D_8004AEAC)((s32)arg1,(s32)arg2,(s32)arg3,(s32)arg4,(s32)arg5);
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xE7000000;
    command->value = 0;
    command = *arg0;
    *arg0 = command + 1;
    command->command = 0xB9000002;
    command->value = 0;
    var_s0 = 0;
    if ((s32) D_8004A730[temp_v0] > 0) {
        do {
            func_8001346C(arg0, ((u8 (*)[7])D_8004A5E0)[var_s0][temp_v0], arg1);
            command = *arg0;
            *arg0 = command + 1;
    command->command = 0xE7000000;
            command->value = 0;
            command = *arg0;
            var_s0 = (s16)(var_s0 + 1);
            *arg0 = command + 1;
    command->command = 0xB9000002;
            command->value = 0;
        } while (var_s0 < (s32) D_8004A730[temp_v0]);
    }
}
