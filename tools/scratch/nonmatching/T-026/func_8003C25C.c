/* DRAFT. Remaining diff: 88 differing instruction words; emitted 336 / original 356 bytes (positional comparison). */
typedef struct { u8 nop, tx, rx, command; u16 address; u8 data[32]; u8 crc, end; } T026ReadCommand;
extern u8 D_8006F080[], D_8006F0C0[];
extern u8 __osContAddressCrc(u16);
void func_8003C25C(s32 channel, u16 address) {
    T026ReadCommand request;
    u8 *p = D_8006F080;
    s32 i;
    do { *(s32 *)p = 0; p += 4; } while ((u32)p < (u32)D_8006F0C0);
    D_8006F080[0x3C] = 1;
    request.nop = 0xFF; request.tx = 3; request.rx = 0x21; request.command = 2;
    request.address = __osContAddressCrc(address) | (address << 5);
    request.crc = 0xFF;
    for (i = 0; i < 32; i++) request.data[i] = 0xFF;
    p = D_8006F080;
    if (channel != 0) for (i = 0; i < channel; i++) *p++ = 0;
    *(T026ReadCommand *)p = request;
    p[0x28] = 0xFE;
}
