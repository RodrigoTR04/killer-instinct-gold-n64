/* T-099 DRAFT: 7 relocation-masked differing words; target-sized. See T-099/REPORT.md. */
typedef struct { u16 buttons; s8 x, y; } T023Pad270;
extern void func_8002B6EC(void);
extern T023Pad270 **func_8002B710(void);
extern u8 D_80068520, D_802D3698, D_802D3699;
extern s32 D_80282A60;
extern T023Pad270 **D_802D3670;
u64 func_801BD270(s32 player) {
    u16 buttons;
    s8 x;
    s16 y;
    u64 result;
    T023Pad270 *pad;
    if (player == 0 && D_802D3698) {
        D_802D3699 = 1;
        D_802D3670 = func_8002B710();
        if (D_80068520 & 15) D_80282A60 = 2;
        else D_80282A60 = 0;
        func_8002B6EC();
    }
    if (!D_802D3698 || !(D_80068520 & (1 << player))) return 0;
    pad = D_802D3670[player];
    x = pad->x; buttons = pad->buttons; y = pad->y;
    if (x >= 49) buttons |= 0x100;
    else if (x < -48) buttons |= 0x200;
    if (y >= 33) buttons |= 0x800;
    else if (y < -32) buttons |= 0x400;
    result = x & 0xFFFF;
    result = (result << 32) + ((y << 16) & 0xFFFF0000);
    result += buttons;
    return result;
}
