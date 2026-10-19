/* DRAFT. Remaining diff: 131 differing instruction words; emitted 496 / original 548 bytes (positional comparison). */
typedef struct { u8 nop, tx, rx, command; u16 address; u8 data[32]; u8 crc, end; } T026Transfer3C3C0;
extern void __osSiGetAccess(void), __osSiRelAccess(void), osRecvMesg(s32, void *, s32);
extern s32 __osSiRawStartDma(s32, void *), func_80034554(s32, s32);
extern u8 __osContDataCrc(u8 *);
extern u8 D_8006F080[], D_8006F0C0[];
extern s8 D_8006F110;
extern void func_8003C5E4(s32, u16, u8 *);
s32 func_8003C3C0(s32 queue, s32 channel, s32 address, void *buffer, s32 force) {
    T026Transfer3C3C0 reply;
    s32 retries = 2;
    s32 result;
    u8 *p;
    address &= 0xFFFF;
    if (force != 1 && address < 7 && address != 0) return 0;
    __osSiGetAccess();
    D_8006F110 = 3;
    func_8003C5E4(channel, address & 0xFFFF, buffer);
    __osSiRawStartDma(1, D_8006F080);
    osRecvMesg(queue, 0, 1);
    do {
        p = D_8006F080;
        do { *(s32 *)p = 0xFF; p += 4; } while ((u32)p < (u32)D_8006F0C0);
        D_8006F080[0x3C] = 0;
        __osSiRawStartDma(0, D_8006F080);
        osRecvMesg(queue, 0, 1);
        reply = *(T026Transfer3C3C0 *)(D_8006F080 + channel);
        result = (reply.rx & 0xC0) >> 4;
        if (result == 0) {
            if (reply.crc != __osContDataCrc(buffer)) {
                result = func_80034554(queue, channel);
                if (result != 0) { __osSiRelAccess(); return result; }
                result = 4;
            }
        }
    } while (result == 4 && --retries >= 0);
    __osSiRelAccess();
    return result;
}
