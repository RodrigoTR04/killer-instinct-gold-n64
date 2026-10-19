/* DRAFT. Remaining diff: 130 differing instruction words; emitted 496 / original 556 bytes (positional comparison). */
typedef struct { u8 nop, tx, rx, command; u16 address; u8 data[32]; u8 crc, end; } T026Transfer3C030;
extern void __osSiGetAccess(void), __osSiRelAccess(void), osRecvMesg(s32, void *, s32);
extern s32 __osSiRawStartDma(s32, void *), func_80034554(s32, s32);
extern u8 __osContDataCrc(u8 *);
extern u8 D_8006F080[], D_8006F0C0[];
extern s8 D_8006F110;
extern void func_8003C25C(s32, u16);
s32 func_8003C030(s32 queue, s32 channel, s32 address, void *buffer) {
    T026Transfer3C030 reply;
    s32 retries = 2;
    s32 result;
    u8 *p;
    __osSiGetAccess();
    D_8006F110 = 2;
    func_8003C25C(channel, address & 0xFFFF);
    __osSiRawStartDma(1, D_8006F080);
    osRecvMesg(queue, 0, 1);
    do {
        p = D_8006F080;
        do { *(s32 *)p = 0xFF; p += 4; } while ((u32)p < (u32)D_8006F0C0);
        D_8006F080[0x3C] = 0;
        __osSiRawStartDma(0, D_8006F080);
        osRecvMesg(queue, 0, 1);
        reply = *(T026Transfer3C030 *)(D_8006F080 + channel);
        result = (reply.rx & 0xC0) >> 4;
        if (result == 0) {
            if (reply.crc != __osContDataCrc(reply.data)) {
                result = func_80034554(queue, channel);
                if (result != 0) { __osSiRelAccess(); return result; }
                result = 4;
            } else {
                s32 i;
                for (i = 0; i < 32; i++) ((u8 *)buffer)[i] = reply.data[i];
            }
        }
    } while (result == 4 && --retries >= 0);
    __osSiRelAccess();
    return result;
}
