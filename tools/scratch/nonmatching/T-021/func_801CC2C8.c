/* DRAFT. Remaining diff: EEPROM result/control flow, global base and return-branch scheduling differ. */
s32 __osContDataCrc(void *);                        /* extern */
extern s32 osEepromLongRead();
s32 osEepromProbe();
extern u8 D_800684E0;
extern u8 D_802D3E16;

s32 func_801CC2C8(u8 *arg0) {
    s8 temp_v0;

    temp_v0 = osEepromProbe(&D_800684E0);
    D_802D3E16 = temp_v0;
    if (temp_v0 & 0xFF) {
        osEepromLongRead(&D_800684E0, 0, arg0, 0x200);
        if (arg0[0x1FF] != __osContDataCrc(arg0)) {
            return 1;
        }
        return 0;
    }
    return 1;
}
