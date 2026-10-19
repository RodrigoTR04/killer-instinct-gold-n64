/* DRAFT. Text matches byte-for-byte in isolation (DIFF 0), but the C switch emits its own jump table, while jtbl_802927C8 is owned by the assembly data file; in-tree the jump-table reference differs. Blocked on rodata ownership only. */
extern void func_801ADC64(s32);
extern void func_801B3DB0(u8, s32);
extern void func_801C1704(s32);
extern u8 D_8004A403;
extern u8 D_80127D50;

void func_801ADCFC(s32 arg0) {
    D_8004A403 = 0;
    func_801C1704(0);
    func_801C1704(1);
    switch (D_80127D50) {
        case 0:
            func_801B3DB0(arg0, 0);
            break;
        case 1:
            func_801B3DB0(arg0, 8);
            break;
        case 2:
            func_801B3DB0(arg0, 0x40);
            break;
        case 3:
            func_801ADC64(9);
            break;
        case 4:
            D_8004A403 = 1;
            func_801B3DB0(arg0, 7);
            break;
        default:
            func_801B3DB0(arg0, 6);
            break;
    }
}
