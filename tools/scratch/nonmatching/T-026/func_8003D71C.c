/* DRAFT. Remaining diff: 16 differing instruction words; emitted 120 / original 120 bytes (positional comparison). */
void func_8003D71C(u8 *event, u8 *player) {
    u8 *data;
    u8 *sequence;
    f32 tempo;
    if (event[8] == 0xFF && (data = event + 4, event[9] == 0x51)) {
        sequence = *(u8 **)(player + 0x18);
        tempo = (f32)((data[7] << 16) | (data[8] << 8) | data[9]);
        if (sequence != 0) {
            *(s32 *)(player + 0x24) = tempo * *(f32 *)(sequence + 0x14);
            return;
        }
        *(s32 *)(player + 0x24) = 0x1E8;
    }
}
