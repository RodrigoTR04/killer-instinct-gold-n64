/* DRAFT. Remaining diff: 77 positional words; 308/300 bytes. Continuation consumes s0-s6 live state; explicit C arguments differ. */
/* Continuation fragment: original inputs are in saved s0-s6 registers. */
typedef struct {
    u8 pad[0x14]; u32 source, state; u8 pad1[0x14];
    s32 (*dma)(s32, s32, s32); s32 dmaState; u8 pad2[8]; s32 pending, dmaArg;
} T026RawVoice;
u32 *func_8003FB20(u32 *commands, s32 length, T026RawVoice *voice, s16 input, s32 flags, s16 output, s32 count) {
    s32 offset = 0;
    if (length > 0) {
        s32 address = voice->dma(voice->dmaArg, length, voice->dmaState);
        s32 aligned;
        offset = address & 7;
        aligned = length + offset;
        commands[0] = (input & 0xFFFF) | 0x08000000;
        commands[1] = ((aligned - (aligned & 7)) + 8) & 0xFFFF;
        commands[2] = 0x04000000;
        commands[3] = address - offset;
        commands += 4;
    }
    if (flags & 2) {
        commands[0] = 0x0F000000;
        commands[1] = voice->state & 0x1FFFFFFF;
        commands += 2;
    }
    commands[0] = ((input + offset) & 0xFFFF) | 0x08000000;
    commands[1] = (output << 16) | ((count * 2) & 0xFFFF);
    commands[2] = ((flags & 0xFF) << 16) | 0x01000000;
    commands[3] = voice->source & 0x1FFFFFFF;
    voice->pending = 0;
    return commands + 4;
}
