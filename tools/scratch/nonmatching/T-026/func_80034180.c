/* DRAFT. Remaining diff: 70 differing instruction words; emitted 404 / original 412 bytes (positional comparison). */
extern void __osSiGetAccess(void), __osSiRelAccess(void), func_8003431C(s32);
extern s32 __osSiRawStartDma(s32, void *);
extern void osRecvMesg(s32, void *, s32), func_800343F4(s8 *, void *);
extern u8 D_8006F080[], D_8006F111;
extern s8 D_8006F110;
s32 func_80034180(s32 queue, s8 *present) {
    u8 replies[16];
    s8 mask;
    s32 message;
    s32 result;
    s32 tries = 3;
    s32 i = 0;
    s8 detected = 0;
    __osSiGetAccess();
    do {
        func_8003431C(0);
        __osSiRawStartDma(1, D_8006F080);
        osRecvMesg(queue, &message, 1);
        result = __osSiRawStartDma(0, D_8006F080);
        osRecvMesg(queue, &message, 1);
        func_800343F4(&mask, replies);
        while (i < D_8006F111) {
            if (!(replies[i*4+2] & 4)) { tries--; break; }
            i++;
        }
        if (i == D_8006F111) tries = 0;
        i = 0;
    } while (tries > 0);
    do {
        if (replies[i*4+3] == 0 && (replies[i*4+2] & 1)) detected = (detected | (1 << i)) & 0xFF;
        i++;
    } while (i < D_8006F111);
    __osSiRelAccess();
    D_8006F110 = 0xFF;
    *present = detected;
    return result;
}
