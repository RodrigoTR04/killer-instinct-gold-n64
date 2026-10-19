/* DRAFT. Remaining diff: Same instructions; frame is 0x28 versus 0x30 and query buffer is sp+0x18 versus sp+0x20. */
extern s32 osContGetQuery();
extern s32 osContStartQuery();
extern s32 osRecvMesg();

u8 func_801CBBE0(s32 arg0, u8 *arg1) {
    u64 sp20[2];

    *arg1 = 0;
    osContStartQuery(arg0);
    osRecvMesg(arg0, 0, 1);
    osContGetQuery(sp20);
    if ((((u8 *)sp20)[2] & 1) && (((u8 *)sp20)[3] == 0)) {
        *arg1 |= 1;
    }
    if ((((u8 *)sp20)[6] & 1) && (((u8 *)sp20)[7] == 0)) {
        *arg1 |= 2;
    }
    if ((((u8 *)sp20)[10] & 1) && (((u8 *)sp20)[11] == 0)) {
        *arg1 |= 4;
    }
    if ((((u8 *)sp20)[14] & 1) && (((u8 *)sp20)[15] == 0)) {
        *arg1 |= 8;
    }
    return ((u8 *)sp20)[3];
}
