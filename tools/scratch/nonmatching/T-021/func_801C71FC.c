/* DRAFT (T-056). 38 words off (was 39): pad-state struct. Remaining: target spills a3 at entry and reloads a2/a3 after the merge; ours spills only around the call. */
typedef struct {
    s32 hi;
    s32 buttons;
} T056PadPrev;

extern u8 D_80295720;
extern u8 D_802D39BA;
extern void func_801C4D6C(void);
extern T056PadPrev D_802D3678[];
extern s8 D_802D39B6;

void func_801C71FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 + 1 == D_80295720 && (arg3 & 0x1000) && !(D_802D3678[arg0].buttons & 0x1000)) {
        if (D_802D39BA & 3) {
            D_802D39BA &= 0xFC;
            func_801C4D6C();
        } else {
            D_802D39BA = 0;
        }
        D_802D39B6 = 1;
    }
    D_802D3678[arg0].hi = arg2;
    D_802D3678[arg0].buttons = arg3;
}
