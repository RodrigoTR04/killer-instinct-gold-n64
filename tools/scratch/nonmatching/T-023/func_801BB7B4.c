/* DRAFT. Remaining diff: Audio-handle loads/types, saved temporaries and branch scheduling differ. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB7B4;
extern s32 func_8002F6DC();
extern s32 func_8002F6F4();
extern void func_8002F8F8();
extern void func_801AF5D4();
extern u8 D_8004A258;
extern s32 D_8004A25C;
extern u8 D_8004A407;
extern s32 D_8004A4B0;
extern s32 D_80066C40;
extern u8 D_80127CE8[];
extern u8 D_80127CF3[];
extern u8 D_801F2EB8[];
extern s32 D_8029571C;
extern u8 D_802C8CB8;
extern u8 D_802C8CB9;
extern u8 D_802C8CE0;
extern u8 D_802C8CEA;
extern u8 D_802C8CEB;
extern u8 D_802C8D06;
extern u8 D_802C8D0D;
extern u8 D_802C8D0E;
extern s8 D_802C9F69;

void func_801BB7B4(u8 arg0) {
    s32 sp18;
    s16 temp_a1;
    s16 temp_a1_2;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v1;
    u8 var_a2;

    var_v1 = 3;
    var_a2 = (arg0 + 1) & 0xFF;
    if ((D_802C8D06 == 6) || (D_802C8D06 == 7)) {
        var_v1 = (D_8004A407 ^ 3) & 0xFF;
    }
    if (D_802C8D06 == 6) {
        D_8004A4B0 = 2;
    }
    if (D_802C8D06 & 8) {
        if (((s32) D_802C8D0D < (s32) D_802C8CEA) && ((s32) D_802C8CEA < 0x10) && (func_8002F6DC(D_8004A25C, var_a2) == 0)) {
            if (*(s32 *)&D_8004A258 != 0) {
                func_8002F8F8(*(s32 *)&D_8004A258);
            }
            temp_a1 = *(s32 *)(D_801F2EB8 + (D_80127CE8[D_802C8D0D] * 0x8C));
            D_802C8D0D += 1;
            func_8002F6F4(D_80066C40, temp_a1, &D_8004A258);
        }
        if (((s32) D_802C8D0E < (s32) D_802C8CEB) && ((s32) D_802C8CEB < 0x10) && (func_8002F6DC(*(s32 *)&D_8004A258) == 0)) {
            if (D_8004A25C != 0) {
                func_8002F8F8(D_8004A25C);
            }
            temp_a1_2 = *(s32 *)(D_801F2EB8 + (D_80127CF3[D_802C8D0E] * 0x8C));
            D_802C8D0E += 1;
            func_8002F6F4(D_80066C40, temp_a1_2, &D_8004A25C);
        }
    } else {
        var_a1 = var_v1;
        if ((var_v1 & 1) && (var_a2 == 1) && (D_802C8CE0 & var_a2) && !(D_802C8D0D & 1) && (sp18 = var_v1, arg0 = var_a2, temp_v0 = func_8002F6DC(*(s32 *)&D_8004A258, (u8) var_a1, var_a2), var_a1 = sp18, var_a2 = arg0, (temp_v0 == 0))) {
            D_802C8D0D |= 1;
            func_8002F6F4(D_80066C40, *(s32 *)(D_801F2EB8 + (D_802C8CB8 * 0x8C)), &D_8004A258);
        } else if ((var_a1 & 2) && (var_a2 == 2) && (D_802C8CE0 & var_a2) && !(D_802C8D0D & 2) && (func_8002F6DC(*(s32 *)&D_8004A258, (u8) var_a1, var_a2) == 0)) {
            D_802C8D0D |= 2;
            func_8002F6F4(D_80066C40, *(s32 *)(D_801F2EB8 + (D_802C8CB9 * 0x8C)), &D_8004A258);
        }
    }
    temp_t7 = D_802C8CE0 & 3;
    if (((temp_t7 == 3) && !(D_802C8D0D & 4)) || ((temp_t7 != 0) && (D_802C8D06 == 6)) || ((temp_t7 == 3) && (D_802C8D06 & 8))) {
        func_801AF5D4(0x80);
        D_802C9F69 = 1;
        D_802C8D0D |= 4;
        D_8029571C = 2;
        D_802C8CE0 |= 3;
    }
}
