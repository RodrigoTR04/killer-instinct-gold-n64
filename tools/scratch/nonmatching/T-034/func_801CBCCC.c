/* DRAFT. Text matches byte-for-byte in isolation (DIFF 0 apart from alignment nops), but the switch needs its own jump table, while jtbl_802956C4 is owned by the assembly data file. Blocked on rodata ownership only. */
extern s32 osRecvMesg(void *, void *, s32);
extern void osDestroyThread(void *);
extern void func_8002B6EC(void);
extern void func_8002B710(void);
extern void func_8002F6F4(s32, s32, void *);
extern void func_801BFB10(void);
extern void func_801CBF50(void);
extern s32 func_801CCAB0(s32);
extern s32 func_801CCBCC(u8);
extern u8 func_801CCDE8(void);
extern void func_801CD078(s32, s32);
extern void func_801CD174(s32);
extern void func_801CD1F0(s32);
extern s32 D_80066C40;
extern u8 D_8004A25C[];
extern u8 D_80295722;
extern u8 D_802D3698;
extern u8 D_802D3699;
extern u8 D_802D3E14;
extern u8 D_802D3E15;
extern u8 D_802D3FC8[];

void func_801CBCCC(void) {
    s32 msg;

    for (;;) {
        osRecvMesg(D_802D3FC8, &msg, 1);
        D_802D3E14 = 0;
        if (msg == 1) {
            osDestroyThread(0);
        }
        if (msg == 8) {
            D_80295722 = 1;
            func_801CBF50();
        }
        D_802D3698 = 0;
        if (D_802D3699) {
            func_8002B710();
        }
        switch (msg & 0xFF) {
            case 2:
                func_801BFB10();
                break;
            case 9:
                func_801CCAB0(-1);
                break;
            case 3:
                func_801CCAB0(-1);
                func_801CCAB0(0);
                func_801CCAB0(1);
                func_8002F6F4(D_80066C40, 0x109, D_8004A25C);
                break;
            case 4:
                func_801CD1F0(msg >> 8);
                break;
            case 5:
                func_801CD078((u32)msg >> 16, (msg & 0xFF00) >> 8);
                break;
            case 6:
                func_801CD174(msg >> 8);
                break;
            case 7:
                D_802D3E15 = func_801CCDE8();
                break;
            case 10:
                func_801CCBCC(0);
                break;
            case 11:
                func_801CCBCC(1);
                break;
        }
        if (D_802D3699) {
            func_8002B6EC();
        }
        D_802D3698 = 1;
    }
}
