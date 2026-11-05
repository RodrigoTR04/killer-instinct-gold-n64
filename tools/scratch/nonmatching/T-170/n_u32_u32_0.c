/* func_801BB7B4 draft. Declarations use the owning unit's existing views. */
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

void func_801BB7B4(u32 arg0) {
    s32 mask;
    u32 next;

    mask = 3;
    next = arg0 + 1;
    if ((D_802C8D06 == 6) || (D_802C8D06 == 7)) {
        mask = (D_8004A407 ^ 3) & 0xFF;
    }
    if (D_802C8D06 == 6) {
        D_8004A4B0 = 2;
    }
    if (D_802C8D06 & 8) {
        if (((s32) D_802C8D0D < (s32) D_802C8CEA[0]) && ((s32) D_802C8CEA[0] < 0x10) && (func_8002F6DC(*(s32 *) D_8004A25C) == 0)) {
            u8 *p;
            s16 sound;
            s32 handle;
            if (*(s32 *) D_8004A258 != 0) {
                func_8002F8F8(*(s32 *) D_8004A258);
            }
            p = &D_802C8D0D;
            handle = D_80066C40;
            sound = D_801F2EB8[D_80127CE8[0][*p]].sound;
            *p = *p + 1;
            func_8002F6F4(handle, sound, D_8004A258);
        }
        if (((s32) D_802C8D0E < (s32) D_802C8CEB[0]) && ((s32) D_802C8CEB[0] < 0x10) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            u8 *p;
            s16 sound;
            s32 handle;
            if (*(s32 *) D_8004A25C != 0) {
                func_8002F8F8(*(s32 *) D_8004A25C);
            }
            p = &D_802C8D0E;
            handle = D_80066C40;
            sound = D_801F2EB8[D_80127CF3[*p]].sound;
            *p = *p + 1;
            func_8002F6F4(handle, sound, D_8004A25C);
        }
    } else {
        if ((mask & 1) && (next == 1) && (D_802C8CE0 & next) && !(D_802C8D0D & 1) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            D_802C8D0D |= 1;
            func_8002F6F4(D_80066C40, D_801F2EB8[D_802C8CB8[0]].sound, D_8004A258);
        } else if ((mask & 2) && (next == 2) && (D_802C8CE0 & next) && !(D_802C8D0D & 2) && (func_8002F6DC(*(s32 *) D_8004A258) == 0)) {
            D_802C8D0D |= 2;
            func_8002F6F4(D_80066C40, D_801F2EB8[D_802C8CB8[1]].sound, D_8004A258);
        }
    }
    if ((((D_802C8CE0 & 3) == 3) && !(D_802C8D0D & 4)) || (((D_802C8CE0 & 3) != 0) && (D_802C8D06 == 6)) || (((D_802C8CE0 & 3) == 3) && (D_802C8D06 & 8))) {
        func_801AF5D4(0x80);
        D_802C9F69 = 1;
        D_802C8D0D |= 4;
        D_8029571C = 2;
        D_802C8CE0 |= 3;
    }
}
