/* DRAFT. Remaining diff: 14 positional words; 56/60 bytes. Mixed f12/a0 input ABI and extra return stub differ. */
typedef struct { u8 pad[8]; f32 scale; } T026TempoScale;
typedef struct { u8 pad[0x18]; T026TempoScale *scale; u8 pad1[8]; s32 tempo; } T026Tempo;
void func_80037A30(T026Tempo *player, f32 value) {
    T026TempoScale *scale = player->scale;
    if (scale != 0) {
        player->tempo = value * scale->scale;
        return;
    }
    player->tempo = 0x1E8;
}
