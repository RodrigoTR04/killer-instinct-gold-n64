/* DRAFT. Remaining diff: 35 differing instruction words; emitted 212 / original 220 bytes (positional comparison). */
extern void func_8003431C(s32);
extern void func_800343F4(s8 *, void *);
extern s32 __osSiRawStartDma(s32, void *);
extern void osRecvMesg(s32, void *, s32);
extern u8 D_8006F080[];
s32 func_80034554(s32 queue, s32 channel) {
    u8 replies[16];
    s8 mask;
    s32 message;
    s32 result;
    u8 *reply;
    u8 status;
    s32 present;
    func_8003431C(0xFF);
    __osSiRawStartDma(1, D_8006F080);
    osRecvMesg(queue, &message, 1);
    result = __osSiRawStartDma(0, D_8006F080);
    osRecvMesg(queue, &message, 1);
    func_800343F4(&mask, replies);
    reply = replies + channel * 4;
    status = reply[2];
    present = status & 1;
    if (present != 0 && (status & 2)) return 2;
    if (reply[3] != 0 || present == 0) return 1;
    if (status & 4) return 4;
    return result;
}
