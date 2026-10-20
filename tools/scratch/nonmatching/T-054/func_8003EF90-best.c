
/* DRAFT. Remaining diff: 263 differing instruction words; emitted 892 / original 1056 bytes (positional comparison). */
typedef struct { u8 pad[0x14]; void *state; u8 pad1[8]; f32 position; s32 count; } T026Chorus;
typedef struct { s32 cutoff; u8 pad[0x24]; void *state; } T026Lowpass;
typedef struct { u32 input, output; s16 gain, feedback, feedforward; u8 pad[2]; f32 rate, increment, phase, depth; T026Lowpass *lowpass; T026Chorus *chorus; } T026FxSection;
typedef struct { s32 pad; void *pull; u8 pad1[0xC]; s16 *base, *write; u32 length; T026FxSection *sections; u8 count; u8 pad2[3]; void *param; } T026Effect;
extern s32 D_80048480[], D_800484E8[], D_80048570[], D_80048598[], D_800485C0[], D_800485E8[];
extern f32 D_800495C8;
extern f64 D_800495D0;
extern void alFxParam(void), alFxPull(void), func_80042198(void), init_lpfilter(void *);
extern void alFilterNew(void *, s32, void *, s32);
extern void *alHeapDBAlloc(s32, s32, void *, u32, s32);
void func_8003EF90(T026Effect *effect, u8 *config, void *heap) {
    s32 *params = D_800485E8;
    s32 *cursor;
    u32 i;
    alFilterNew(effect, 0, alFxParam, 5);
    effect->pull = alFxPull;
    effect->param = func_80042198;
    switch (config[0x1C]) {
    case 1: params = D_80048480; break;
    case 2: params = D_800484E8; break;
    case 5: params = D_80048570; break;
    case 3: params = D_80048598; break;
    case 4: params = D_800485C0; break;
    case 6: params = *(s32 **)(config+0x20); break;
    }
    cursor = params + 2;
    effect->count = params[0]; effect->length = params[1];
    effect->sections = alHeapDBAlloc(0, 0, heap, effect->count, 0x28);
    effect->base = alHeapDBAlloc(0, 0, heap, effect->length, 2);
    effect->write = effect->base;
    for (i = 0; i < effect->length; i = (i+1)&0xFFFF) effect->base[i] = 0;
    for (i = 0; i < effect->count; i = (i+1)&0xFFFF) {
        T026FxSection *section = &effect->sections[i];
        s32 rate;
        section->input = *cursor++; section->output = *cursor++;
        section->feedback = *cursor++; section->gain = *cursor++; section->feedforward = *cursor++;
        rate = *cursor++;
        if (rate != 0) {
            section->rate = (f32)rate / D_800495C8;
            section->increment = 1.0f; section->phase = 0;
            section->depth = ((f64)(f32)*cursor++ / D_800495D0) * (f64)(u32)(section->output-section->input);
            section->chorus = alHeapDBAlloc(0, 0, heap, 1, 0x34);
            section->chorus->state = alHeapDBAlloc(0, 0, heap, 1, 0x20);
            section->chorus->position = 0; section->chorus->count = 1;
        } else { section->chorus = 0; cursor++; }
        if (*cursor != 0) {
            section->lowpass = alHeapDBAlloc(0, 0, heap, 1, 0x30);
            section->lowpass->state = alHeapDBAlloc(0, 0, heap, 1, 8);
            *(s16 *)&section->lowpass->cutoff = *cursor++;
            init_lpfilter(section->lowpass);
        } else { section->lowpass = 0; cursor++; }
    }
}
