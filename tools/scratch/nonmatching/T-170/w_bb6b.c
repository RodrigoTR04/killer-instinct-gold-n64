/* func_801BB7B4 draft. Declarations use the owning unit's existing views
 * (D_8004A25C[] u8 array, func_8002F6F4(s32, s32, void *)); the voice slot is
 * read as a word out of the handoff array. */
extern u8 D_80127CF3[];
typedef struct { s16 sound; u8 pad[0x8A]; } T023Sound801BB7B4;
extern T023Sound801BB7B4 D_801F2EB8[];
extern u8 D_8004A258[];
extern s32 D_8004A4B0;
extern u8 D_802C8CEB[];
extern u8 D_802C8D0D;
extern u8 D_802C8D0E;
extern u8 D_802C9F69;
extern s32 D_8029571C;
extern s32 func_8002F6DC(s32);
extern void func_8002F8F8(s32);

void func_801BB7B4(u8 arg0) {
    s16 temp_a1;
    s16 temp_a1_2;
    s32 temp_t7;
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
        if (((s32) D_802C8D0D < (s32) D_802C8CEA[0]) && ((s32) D_802C8CEA[0] < 0x10) && (func_8002F6DC(*(s32 *) D_8004A25C) == 0)) {
            if (*(s32 *) D_8004A258 != 0) {
                func_8002F8F8(*(s32 *) D_8004A258);
            }
            temp_a1 = D_801F2EB8[D_80127CE8[D_802C8D0D][0]].sound;
            D_802C8D0D = D_802C8D0D + 1;
            func_8002F6F4(D_80066C40, temp_a1, D_8004A258);
        }
        if (((s32) D_802C8D0E < (s32) D_802C8CEB[0]) && ((s32) D_802C8CEB[0] < 0x10) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            if (*(s32 *) D_8004A25C != 0) {
                func_8002F8F8(*(s32 *) D_8004A25C);
            }
            temp_a1_2 = D_801F2EB8[D_80127CF3[D_802C8D0E]].sound;
            D_802C8D0E += 1;
            func_8002F6F4(D_80066C40, temp_a1_2, D_8004A25C);
        }
    } else {
        var_a1 = var_v1;
        if ((var_v1 & 1) && (var_a2 == 1) && (D_802C8CE0 & var_a2) && !(D_802C8D0D & 1) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            D_802C8D0D |= 1;
            func_8002F6F4(D_80066C40, D_801F2EB8[D_802C8CB8[0]].sound, D_8004A258);
        } else if ((var_a1 & 2) && (var_a2 == 2) && (D_802C8CE0 & var_a2) && !(D_802C8D0D & 2) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            D_802C8D0D |= 2;
            func_8002F6F4(D_80066C40, D_801F2EB8[D_802C8CB9].sound, D_8004A258);
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
