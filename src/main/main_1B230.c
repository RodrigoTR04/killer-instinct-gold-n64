#include "audio_game.h"

extern u8 D_80066C68[];
extern s32 D_8004815C[];
extern s32 osAiSetFrequency(s32);
extern void osCreateMesgQueue(void *, void *, s32);

extern void osStartThread(void *);

void func_8002AB90(ALSynConfig *config, s32 priority, AudioSettings *settings)
{
    typedef struct { s32 words[66]; } AudioFxParameters;
    f32 exact;
    u32 i;

    config->dmaproc = func_8002B3A8;
    config->outputRate = osAiSetFrequency(settings->rate);
    exact = (f32)settings->frames * (f32)config->outputRate / 60.0f;
    D_80068168 = (s32)exact;
    if (D_80068168 < exact) {
        D_80068168++;
    }
    if (D_80068168 & 15) {
        D_80068168 = (D_80068168 & ~15) + 16;
    }
    D_80068164 = D_80068168 - 16;
    D_8006816C = D_80068168 + 96;
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
        alLink((ALLink *)&D_80067ED8[i + 1], (ALLink *)&D_80067ED8[i]);
        D_80067ED8[i].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 0x800);
    }
    D_80067ED8[i].buffer = alHeapDBAlloc(0, 0, config->heap, 1, 0x800);
    for (i = 0; i < 2; i++) {
        D_80066C50.slots[i] = alHeapDBAlloc(0, 0, config->heap, 1, settings->commands * 8);
    }
    D_80068170 = settings->commands;
    for (i = 0; i < 3; i++) {
        D_80066C50.slots[i + 2] = alHeapDBAlloc(0, 0, config->heap, 1, 0x88);
        ((AudioFrame *)D_80066C50.slots[i + 2])->body.type = 2;
        ((AudioFrame *)D_80066C50.slots[i + 2])->body.frame = D_80066C50.slots[i + 2];
        ((AudioFrame *)D_80066C50.slots[i + 2])->buffer = alHeapDBAlloc(0, 0, config->heap, 1, D_8006816C * 4);
    }
    osCreateMesgQueue(&D_80066E50, D_80066E68, 8);
    osCreateMesgQueue(&D_80066E18, D_80066E30, 8);
    osCreateMesgQueue(&D_800683F8, D_80068410, 32);
    osCreateThread(D_80066C68, 4, func_8002AEE4, 0, D_80067ED8, priority);
    osStartThread(D_80066C68);
}

extern s32 osRecvMesg(void *,void *,s32);

void func_8002AEE4(s32 unused)
{
    u16 done = 0;
    AudioFrame *previous = 0;
    AudioMessage *message;
    s32 ready = 1;
    u8 client[8];
    boot_subscribe_retrace(client, &D_80066E18);
    while (!done)
    {
        osRecvMesg(&D_80066E18, &message, 1);
        switch (message->type)
        {
            case 4:
                break;

            case 1:
                if (func_8002B034(D_80066C50.slots[(D_80048150 % 3) + 2], previous))
                {
                    if (!ready)
                    {
                        osRecvMesg(&D_80066E50, &message, 1);
                        func_8002B1EC(message->frame);
                        previous = message->frame;
                    }
                    ready = 0;
                }
                break;

            case 10:
                done = 1;
                break;
        }
    }

    alClose(&D_80066E88);
}

extern u32 osVirtualToPhysical(void *);
extern u32 osAiGetLength(void);
extern s32 osAiSetNextBuffer(void *, u32);
extern void osWritebackDCacheAll(void);
extern Acmd *func_80039C08(Acmd *, s32 *, s16 *, s32);
extern s32 osSendMesg(void *, void *, s32);

extern u8 D_80042710[];
extern u8 D_800427E0[];
extern u8 D_80043BF0[];
extern u8 D_80049F70[];

extern u8 boot_audio_queue[];

s32 func_8002B034(AudioFrame *task, AudioFrame *previous)
{
  u32 physical;
  AudioRspTask *rsp;
  s32 count;
  u8 *end;
  func_8002B3E0();
  physical = osVirtualToPhysical(task->buffer);
  if (previous)
  {
    osAiSetNextBuffer(previous->buffer, previous->samples * 4);
  }
  task->samples = ((D_80068168 - (osAiGetLength() >> 2)) + 0x60) & 0xFFF0;
  if (((u32) task->samples) < D_80068164)
  {
    task->samples = D_80068164;
  }
  end = (u8 *) func_80039C08(D_80066C50.slots[D_80048158], &count, (s16 *)physical, task->samples);
  if (count == 0)
  {
    return 0;
  }
  task->state = 0;
  task->queue = &D_80066E50;
  task->message = &task->body;
  task->type = 2;
  task->rsp.commands = D_80066C50.slots[D_80048158];
  task->rsp.commandSize = ((end - (u8 *)D_80066C50.slots[D_80048158]) >> 3) * 8;
  task->rsp.taskType = 2;
  task->rsp.boot = D_80042710;
  task->rsp.bootSize = D_800427E0 - D_80042710;
  task->rsp.flags = 2;
  task->rsp.code = D_80043BF0;
  task->rsp.data = D_80049F70;
  task->rsp.dataSize = 0x800;
  /* Keep the RSP task view for the two yield-buffer fields. */
  (rsp = &task->rsp)->yield = 0;
  rsp->yieldSize = 0x400;
  osWritebackDCacheAll();
  osSendMesg(boot_audio_queue, &task->state, 1);
  D_80048158 ^= 1;
  return 1;
}

extern u32 osAiGetLength(void);
extern s32 D_80048264;
void func_8002B1EC(AudioFrame *unused)
{
    s32 zero;
    zero = 0;
    if ((osAiGetLength() >> 2) == zero)
    {
        if (D_80048264 == zero)
        {
            D_80048264 = zero;
        }
    }
}

extern s32 osPiStartDma(void *, s32, s32, u32, void *, u32, void *);

/* The SDK audio-example DMA callback: reuse a buffer that covers the request or start a new transfer. */
s32 func_8002B22C(s32 address, s32 length, void *unused)
{
    void *foundBuffer;
    s32 delta, addrEnd, buffEnd;
    AudioDmaBuffer *dmaPtr, *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = D_80068158.used;
    addrEnd = address + length;
    while (dmaPtr) {
        buffEnd = dmaPtr->address + 0x800;
        if (dmaPtr->address > (u32)address) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->frame = D_80048150;
            foundBuffer = dmaPtr->buffer + address - dmaPtr->address;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->next;
    }
    dmaPtr = D_80068158.free;
    D_80068158.free = dmaPtr->next;
    alUnlink((ALLink *)dmaPtr);
    if (lastDmaPtr) {
        alLink((ALLink *)dmaPtr, (ALLink *)lastDmaPtr);
    } else if (D_80068158.used) {
        lastDmaPtr = D_80068158.used;
        D_80068158.used = dmaPtr;
        dmaPtr->next = lastDmaPtr;
        dmaPtr->prev = 0;
        lastDmaPtr->prev = dmaPtr;
    } else {
        D_80068158.used = dmaPtr;
        dmaPtr->next = 0;
        dmaPtr->prev = 0;
    }
    foundBuffer = dmaPtr->buffer;
    delta = address & 1;
    address -= delta;
    dmaPtr->address = address;
    dmaPtr->frame = D_80048150;
    osPiStartDma(&D_80068178[D_80048154++], 0, 0, address, foundBuffer, 0x800, &D_800683F8);
    return osVirtualToPhysical(foundBuffer) + delta;
}

ALDMAproc func_8002B3A8(AudioDmaPool **state) {
    if (!D_80068158.initialized) {
        D_80068158.used = 0;
        D_80068158.free = &D_80067ED8[0];
        D_80068158.initialized = 1;
    }
    *state = &D_80068158;
    return func_8002B22C;
}

extern s32 osRecvMesg(void *, void *, s32);

void func_8002B3E0(void) {
    u32 i;
    void *iomsg;
    AudioDmaBuffer *dmaPtr, *nextPtr;

    for (i = 0; i < D_80048154; i++) {
        osRecvMesg(&D_800683F8, &iomsg, 0);
    }
    dmaPtr = D_80068158.used;
    while (dmaPtr) {
        nextPtr = dmaPtr->next;
        if (dmaPtr->frame + 1 < D_80048150) {
            if (D_80068158.used == dmaPtr) {
                D_80068158.used = dmaPtr->next;
            }
            alUnlink((ALLink *)dmaPtr);
            if (D_80068158.free) {
                alLink((ALLink *)dmaPtr, (ALLink *)D_80068158.free);
            } else {
                D_80068158.free = dmaPtr;
                dmaPtr->next = 0;
                dmaPtr->prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    D_80048154 = 0;
    D_80048150++;
}

