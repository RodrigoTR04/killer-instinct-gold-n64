/* DRAFT. Remaining diff: 391 positional differing words; 1560/1576 bytes */
typedef struct { u32 command, value; } T03312B7CCommand;
extern u8 D_80044A24, D_8004AA28, D_8004AC88;
extern s8 D_8004A730, D_8004A5E0;
extern u16 D_8004ACFC;
extern s32 D_8004AD00, D_8004AD04;
extern u8 *D_8004AA3C;
extern s32 (*D_8004AEAC)(s32,s32,s32,s32);
extern u8 D_8004AA40, D_8004AAC0, D_8004AB40, D_8004ABC0;
extern void func_8001BB64(T03312B7CCommand **);
extern void func_8001346C(T03312B7CCommand **,u8,f32);
extern void guMtxCatF(void *,void *,void *), guMtxF2L(void *,void *);
extern void guRotateRPYF(void *,f32,f32,f32), guTranslateF(void *,f32,f32,f32);
void func_80012B7C(T03312B7CCommand **arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s16 temp_v0;
    s16 var_s0;
    T03312B7CCommand *temp_v1;
    T03312B7CCommand *temp_v1_10;
    T03312B7CCommand *temp_v1_11;
    T03312B7CCommand *temp_v1_12;
    T03312B7CCommand *temp_v1_13;
    T03312B7CCommand *temp_v1_14;
    T03312B7CCommand *temp_v1_15;
    T03312B7CCommand *temp_v1_16;
    T03312B7CCommand *temp_v1_17;
    T03312B7CCommand *temp_v1_18;
    T03312B7CCommand *temp_v1_19;
    T03312B7CCommand *temp_v1_20;
    T03312B7CCommand *temp_v1_21;
    T03312B7CCommand *temp_v1_22;
    T03312B7CCommand *temp_v1_23;
    T03312B7CCommand *temp_v1_24;
    T03312B7CCommand *temp_v1_25;
    T03312B7CCommand *temp_v1_26;
    T03312B7CCommand *temp_v1_2;
    T03312B7CCommand *temp_v1_3;
    T03312B7CCommand *temp_v1_4;
    T03312B7CCommand *temp_v1_5;
    T03312B7CCommand *temp_v1_6;
    T03312B7CCommand *temp_v1_7;
    T03312B7CCommand *temp_v1_8;
    T03312B7CCommand *temp_v1_9;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t9;
    u8 *temp_s2;
    u8 *temp_s2_2;

    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1[0].value = 0;
    temp_v1[0].command = 0xE7000000;
    func_8001BB64(arg0);
    temp_v1_2 = *arg0;
    *arg0 = temp_v1_2 + 1;
    temp_v1_2[0].value = (u32)0xC00;
    temp_v1_2[0].command = 0xBA000903;
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3[0].value = 0;
    temp_v1_3[0].command = 0xBA001701;
    temp_v1_4 = *arg0;
    *arg0 = temp_v1_4 + 1;
    temp_v1_4[0].value = (u32)1;
    temp_v1_4[0].command = 0xF9000000;
    guRotateRPYF(&D_8004AA40 + (D_80044A24 << 6), arg4, 0.0f, 0.0f);
    guRotateRPYF(&D_8004AB40 + (D_80044A24 << 6), 0.0f, arg5, arg6);
    guTranslateF((D_80044A24 << 6) + &D_8004AAC0, (f32) (0.0 - (f64) arg1), (f32) (0.0 - (f64) arg2), (f32) (0.0 - (f64) arg3));
    temp_t6 = D_80044A24 << 6;
    temp_s2 = &D_8004AB40 + temp_t6;
    guMtxCatF(temp_t6 + &D_8004AAC0, temp_s2, temp_s2);
    temp_t8 = D_80044A24 << 6;
    temp_s2_2 = &D_8004AB40 + temp_t8;
    guMtxCatF(temp_s2_2, &D_8004AA40 + temp_t8, temp_s2_2);
    temp_t9 = D_80044A24 << 6;
    guMtxF2L(&D_8004AB40 + temp_t9, &D_8004ABC0 + temp_t9);
    temp_v1_5 = *arg0;
    *arg0 = temp_v1_5 + 1;
    temp_v1_5[0].command = 0x01020040;
    temp_v1_5[0].value = (u32) (&D_8004ABC0 + (D_80044A24 << 6) + 0x80000000);
    temp_v1_6 = *arg0;
    *arg0 = temp_v1_6 + 1;
    temp_v1_6[0].value = 0x4AC40;
    temp_v1_6[0].command = 0x01030040;
    temp_v1_7 = *arg0;
    *arg0 = temp_v1_7 + 1;
    temp_v1_7[0].command = 0xB4000000;
    temp_v1_7[0].value = (u32) D_8004ACFC;
    if (D_8004AA28 == 0) {
        temp_v1_8 = *arg0;
        *arg0 = temp_v1_8 + 1;
        temp_v1_8[0].value = (u32)3;
        temp_v1_8[0].command = 0xBC000404;
        temp_v1_9 = *arg0;
        *arg0 = temp_v1_9 + 1;
        temp_v1_9[0].value = (u32)3;
        temp_v1_9[0].command = 0xBC000C04;
        temp_v1_10 = *arg0;
        *arg0 = temp_v1_10 + 1;
        temp_v1_10[0].value = (u32)0xFFFD;
        temp_v1_10[0].command = 0xBC001404;
        temp_v1_11 = *arg0;
        *arg0 = temp_v1_11 + 1;
        temp_v1_11[0].value = (u32)0xFFFD;
    } else {
        temp_v1_12 = *arg0;
        *arg0 = temp_v1_12 + 1;
        temp_v1_12[0].value = (u32)2;
        temp_v1_12[0].command = 0xBC000404;
        temp_v1_13 = *arg0;
        *arg0 = temp_v1_13 + 1;
        temp_v1_13[0].value = (u32)2;
        temp_v1_13[0].command = 0xBC000C04;
        temp_v1_14 = *arg0;
        *arg0 = temp_v1_14 + 1;
        temp_v1_14[0].value = (u32)0xFFFE;
        temp_v1_14[0].command = 0xBC001404;
        temp_v1_15 = *arg0;
        *arg0 = temp_v1_15 + 1;
        temp_v1_15[0].value = (u32)0xFFFE;
    }
    (*arg0)->command = 0xBC001C04;
    switch (D_8004AC88) {
    case 0:
        temp_v1_16 = *arg0;
        *arg0 = temp_v1_16 + 1;
        temp_v1_16[0].command = 0xF5680800;
        temp_v1_16[0].value = (u32)0x05018050;
        temp_v1_17 = *arg0;
        *arg0 = temp_v1_17 + 1;
        temp_v1_17[0].command = (((D_8004AD04 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((2 - D_8004AD00) & 0xFFF);
        temp_v1_17[0].value = (u32)0x0507E0FE;
        break;
    case 4:
    case 9:
        temp_v1_18 = *arg0;
        *arg0 = temp_v1_18 + 1;
        temp_v1_18[0].command = 0xF5101000;
        temp_v1_18[0].value = (u32)0x05018050;
        temp_v1_19 = *arg0;
        *arg0 = temp_v1_19 + 1;
        temp_v1_19[0].command = (((D_8004AD00 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((D_8004AD04 + 2) & 0xFFF);
        temp_v1_19[0].value = (u32)0x0507E0FE;
        break;
    case 6:
    case 12:
        temp_v1_20 = *arg0;
        *arg0 = temp_v1_20 + 1;
        temp_v1_20[0].command = 0xF5881000;
        temp_v1_20[0].value = (u32)0x05018060;
        temp_v1_21 = *arg0;
        *arg0 = temp_v1_21 + 1;
        temp_v1_21[0].command = (((D_8004AD04 + 2) & 0xFFF) << 0xC) | 0xF2000000 | ((2 - D_8004AD00) & 0xFFF);
        temp_v1_21[0].value = (u32)0x050FE0FE;
        break;
    }
    if (D_8004AA3C != 0) {
        temp_v1_22 = *arg0;
        *arg0 = temp_v1_22 + 1;
        temp_v1_22[0].command = 0x06000000;
        temp_v1_22[0].value = (u32) D_8004AA3C;
    }
    temp_v0 = ((s32 (*)(s32,s32,s32,s32,s32))D_8004AEAC)((s32)arg1,(s32)arg2,(s32)arg3,(s32)arg4,(s32)arg5);
    temp_v1_23 = *arg0;
    *arg0 = temp_v1_23 + 1;
    temp_v1_23[0].value = 0;
    temp_v1_23[0].command = 0xE7000000;
    temp_v1_24 = *arg0;
    *arg0 = temp_v1_24 + 1;
    temp_v1_24[0].value = 0;
    temp_v1_24[0].command = 0xB9000002;
    var_s0 = 0;
    if ((s32) *(temp_v0 + &D_8004A730) > 0) {
        do {
            func_8001346C(arg0, *(&D_8004A5E0 + (var_s0 * 7) + temp_v0), arg1);
            temp_v1_25 = *arg0;
            *arg0 = temp_v1_25 + 1;
            temp_v1_25[0].value = 0;
            temp_v1_25[0].command = 0xE7000000;
            temp_v1_26 = *arg0;
            var_s0 += 1;
            *arg0 = temp_v1_26 + 1;
            temp_v1_26[0].value = 0;
            temp_v1_26[0].command = 0xB9000002;
        } while (var_s0 < (s32) *(temp_v0 + &D_8004A730));
    }
}
