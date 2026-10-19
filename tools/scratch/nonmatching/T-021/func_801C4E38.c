/* DRAFT. Remaining diff: Compile blocked by unresolved types/prototypes: extern s32 func_801C4C64(); */
extern s32 func_80012A8C();
extern s32 func_8002A8C4();
extern s32 func_8002A9DC();
extern s32 func_8002F6F4();
extern s32 func_8002F9FC();
extern s32 func_801ADAD4();
extern void func_801C4BD0();
extern s32 func_801C4C64();
extern s32 func_801C4D28();
extern s32 func_801C4D6C();
extern s32 osViBlack();
extern u8 D_800451EC;
extern u8 D_8004A25C;
extern u8 *D_8004AA30;
extern u8 D_8004AC88;
extern s32 D_80066C40;
extern s32 D_800698C4;
extern u8 D_80127CC1;
extern u8 D_80291B5C;
extern u8 D_80291B74;
extern u8 D_80291BA0;
extern u8 D_80291BCC;
extern u8 D_80291DDC;
extern u8 D_80291FDC;
extern u8 D_80292048;
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern s32 D_802C9F74;
extern u8 D_802D3985;
extern u8 D_802D3986;
extern s32 D_802D39A0;
extern s32 D_802D39A4;
extern s32 D_802D39A8;
extern s32 D_802D39B0;
extern u8 D_802D39BA;
extern u8 func_80016078;

void func_801C4E38(u8 arg0, u8 arg1) {
    s32 sp1C;
    s32 temp_t2;

    D_802D3985 = arg0;
    D_80295700 = 0;
    D_802956FC = 0;
    D_802956F8 = 0;
    osViBlack(1);
    func_8002F9FC();
    func_801ADAD4(0x28);
    D_802D3986 = arg1;
    if ((s32) arg0 >= 0xB) {
        D_802D39BA = 8;
        return;
    }
    sp1C = (s32) arg0;
    D_8004AC88 = D_802D3985;
    func_80012A8C(D_802D3985 & 0xFF);
    *(&D_800451EC + (D_802D3985 * 4))();
    switch (arg0) {                                 /* irregular */
    default:
        func_8002F6F4(D_80066C40, 0x15D, &D_8004A25C);
        break;
    case 9:
        func_8002A9DC(0x2C);
        func_8002A8C4();
        break;
    case 1:
    case 5:
        D_8004AA30 = &func_80016078;
        if (arg0 == 5) {
            func_8002A9DC(0x2D);
            func_8002A8C4();
        } else {
            func_8002A9DC(0x2F);
        }
        break;
    }
    func_801C4BD0(*(&D_80291FDC + D_802D3985));
    func_801C4C64((D_802D3985 * 0x30) + &D_80291BCC, (D_802D3985 * 0x10) + &D_80291DDC, D_802D3985);
    D_800698C4 = 0;
    func_801C4D28();
    temp_t2 = D_802D3985 * 4;
    D_802D39B0 = D_802C9F74;
    D_802D39BA = *(&D_80292048 + D_80127CC1);
    D_802D39A0 = *(&D_80291B74 + temp_t2);
    D_802D39A4 = *(&D_80291BA0 + temp_t2);
    D_802D39A8 = *(&D_80291B5C + (D_80127CC1 * 4));
    func_801C4D6C();
}
