/* DRAFT. Remaining diff: 64 differing instruction words; emitted 256 / original 244 bytes (positional comparison). */
void func_80037780(u8 *instrument, s32 base, s32 unused, s32 samples) {
    s32 i;
    u8 *slot;
    if (instrument[3] == 0) {
        instrument[3] = 1;
        i = 0;
        if (*(s16 *)(instrument + 0xE) > 0) {
            slot = instrument;
            do {
                u8 *sound = (u8 *)(*(s32 *)(slot + 0x10) + base);
                *(u8 **)(slot + 0x10) = sound;
                if (sound[0xE] == 0) {
                    u8 *wave;
                    sound[0xE] = 1;
                    *(s32 *)sound += base;
                    wave = (u8 *)(*(s32 *)(sound + 8) + base);
                    *(s32 *)(sound + 4) += base;
                    *(u8 **)(sound + 8) = wave;
                    if (wave[9] == 0) {
                        u8 type = wave[8];
                        wave[9] = 1;
                        *(s32 *)wave += samples;
                        if (type == 0) {
                            s32 loop = *(s32 *)(wave + 0xC);
                            *(s32 *)(wave + 0x10) += base;
                            if (loop != 0) *(s32 *)(wave + 0xC) = loop + base;
                        } else if (type == 1) {
                            s32 loop = *(s32 *)(wave + 0xC);
                            if (loop != 0) *(s32 *)(wave + 0xC) = loop + base;
                        }
                    }
                }
                i++;
                slot += 4;
            } while (i < *(s16 *)(instrument + 0xE));
        }
    }
}
