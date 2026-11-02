/* DRAFT (T-056). Full-TU pointer declarations reconciled (T-139); 2 words off: arg0 spill at sp+0x18 vs target sp+0x1C (same 0x20 frame). */
extern void osViBlack(u8);
extern void func_8002F9FC(void);
extern void func_801ADAD4(s32);
extern void func_80012A8C(u8);
extern s32 func_8002F6F4();
extern void func_8002A9DC(s32);
extern void func_8002A8C4(void);
extern void func_801C4D28(void);
extern void func_801C4D6C(void);
extern void func_80016078(void);
extern void (*D_800451EC[])(void);
extern void (*D_8004AA30)(void);
extern u8 D_8004A25C;
extern u8 D_8004AC88;
extern s32 D_80066C40;
extern s32 D_800698C4;
extern u8 D_80127CC1;
extern s32 *D_80291B5C[];
extern s32 *D_80291B74[];
extern s32 *D_80291BA0[];
extern f32 D_80291BCC[][12];
extern f32 D_80291DDC[][4];
extern u8 D_80291FDC[];
extern u8 D_80292048[];
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern s32 D_802C9F74;
extern s32 D_802D39B0;
extern u8 D_802D39BA;

void func_801C4E38(u8 arg0, u8 arg1) {
        D_802D3985 = arg0;
    D_802956F8 = D_802956FC = D_80295700 = 0;
    osViBlack(1);
    func_8002F9FC();
    func_801ADAD4(0x28);
    D_802D3986 = arg1;
    if (arg0 >= 11) {
        D_802D39BA = 8;
        return;
    }
    D_8004AC88 = D_802D3985;
    func_80012A8C(D_802D3985);
    D_800451EC[D_802D3985]();
    switch (arg0) {
        default:
            func_8002F6F4(D_80066C40, 0x15D, &D_8004A25C);
            break;
        case 9:
            func_8002A9DC(0x2C);
            func_8002A8C4();
            break;
        case 1:
        case 5:
            D_8004AA30 = func_80016078;
            if (arg0 == 5) {
                func_8002A9DC(0x2D);
                func_8002A8C4();
            } else {
                func_8002A9DC(0x2F);
            }
            break;
    }
    func_801C4BD0(D_80291FDC[D_802D3985]);
    func_801C4C64(D_80291BCC[D_802D3985], D_80291DDC[D_802D3985]);
    D_800698C4 = 0;
    func_801C4D28();
    D_802D39B0 = D_802C9F74;
    {
        u8 selector = D_80127CC1;
        D_802D39BA = D_80292048[selector];
        D_802D39A0 = D_80291B74[D_802D3985];
        D_802D39A4 = D_80291BA0[D_802D3985];
        D_802D39A8 = D_80291B5C[selector];
    }
    func_801C4D6C();
}
