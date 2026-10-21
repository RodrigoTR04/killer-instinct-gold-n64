/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"

extern u8 D_80066C68[];
extern s32 D_8004815C[];
extern s32 osAiSetFrequency(s32);
extern void osCreateMesgQueue(void *, void *, s32);

extern void osStartThread(void *);

void func_8002AB90(ALSynConfig *config, s32 priority, AudioSettings *settings)
{
    typedef struct { s32 words[66]; } AudioFxParameters;
    s32 n;
    f32 exact;
    u32 i;
    void **slot;

    config->dmaproc = func_8002B3A8;
    config->outputRate = osAiSetFrequency(settings->rate);
    exact = (f32)settings->frames * (f32)config->outputRate / 60.0f;
    D_80068168 = (s32)exact;
    if ((f32)(u32)D_80068168 < exact) {
        D_80068168++;
    }
    n = D_80068168;
    if (n & 15) {
        n = (n & ~15) + 16;
        D_80068168 = n;
    }
    D_80068164 = n - 16;
    D_8006816C = n + 96;
    if (config->fxType == 6) {
        AudioFxParameters parameters;
        parameters = *(AudioFxParameters *)D_8004815C;
        config->params = parameters.words;
        alInit(&D_80066E88, config);
    } else {
        alInit(&D_80066E88, config);
    }
    D_80067ED8[0].prev = 0;
    D_80067ED8[0].next = 0;
    for (i = 0; i < 31; i++) {
        alLink((ALLink *)&D_80067ED8[i+1], (ALLink *)&D_80067ED8[i]);
        D_80067ED8[i].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 0x800);
    }
    D_80067ED8[31].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 0x800);
    for (slot = D_80066C50.slots; slot < D_80066C50.slots + 2; slot++) {
        *slot = alHeapDBAlloc(0, 0, config->heap, 1, settings->commands * 8);
    }
    D_80068170 = settings->commands;
    for (slot = D_80066C50.slots; slot != D_80066C50.slots + 3; slot++) {
        slot[2] = alHeapDBAlloc(0, 0, config->heap, 1, 0x88);
        ((AudioFrame *)slot[2])->body.type = 2;
        ((AudioFrame *)slot[2])->body.frame = slot[2];
        ((AudioFrame *)slot[2])->buffer = alHeapDBAlloc(0, 0, config->heap, 1, D_8006816C * 4);
    }
    osCreateMesgQueue(&D_80066E50, D_80066E68, 8);
    osCreateMesgQueue(&D_80066E18, D_80066E30, 8);
    osCreateMesgQueue(&D_800683F8, D_80068410, 32);
    osCreateThread(D_80066C68, 4, func_8002AEE4, 0, D_80067ED8, priority);
    osStartThread(D_80066C68);
}
