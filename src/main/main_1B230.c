#include "common.h"
#include "libaudio/abi.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1B230/func_8002AB90.s")

typedef struct {
    s16 type;
    s32 samples;
} T024AudioMessage;

extern u8 D_80066E18[],D_80066E50[],D_80066E88[];

extern void *D_80066C50[];

extern u32 D_80048150;

struct T095AudioTask;
extern s32 osRecvMesg(void *,void *,s32);
extern s32 func_8002B034(struct T095AudioTask *, s32);

extern void boot_subscribe_retrace(void *, void *);
extern void func_8002B1EC(s32),alClose(void *);

void func_8002AEE4(s32 unused)
{
    u16 done = 0;
    s32 samples = 0;
    T024AudioMessage *message;
    s32 ready = 1;
    u8 client[8];
    boot_subscribe_retrace(client, D_80066E18);
    while (!done)
    {
        osRecvMesg(D_80066E18, &message, 1);
        switch (message->type)
        {
            case 4:
                break;

            case 1:
                if (func_8002B034(D_80066C50[(D_80048150 % 3) + 2], samples))
                {
                    if (!ready)
                    {
                        osRecvMesg(D_80066E50, &message, 1);
                        func_8002B1EC(message->samples);
                        samples = message->samples;
                    }
                    ready = 0;
                }
                break;

            case 10:
                done = 1;
                break;
        }
    }

    alClose(D_80066E88);
}

typedef struct {
  s32 taskType;
  s32 flags;
  void *boot;
  u32 bootSize;
  void *code;
  u8 pad34[4];
  void *data;
  u32 dataSize;
  u8 pad40[0x10];
  void *commands;
  u32 commandSize;
  s32 yield;
  u32 yieldSize;
} T095RspTask;
typedef struct T095AudioTask
{
  void *buffer;
  s16 samples;
  u8 pad6[2];
  s32 state;
  u8 padC[8];
  s32 type;
  u8 pad18[8];
  T095RspTask rsp;
  void *queue;
  void *message;
  u8 body[8];
} T095AudioTask;
extern void func_8002B3E0(void);
extern u32 osVirtualToPhysical(void *);
extern u32 osAiGetLength(void);
extern s32 osAiSetNextBuffer(void *, u32);
extern void osWritebackDCacheAll(void);
extern Acmd *func_80039C08(Acmd *, s32 *, s16 *, s32);
extern s32 osSendMesg(void *, void *, s32);
extern s32 D_80048158;
extern s32 D_80068168;
extern u32 D_80068164;
extern u8 D_80042710[];
extern u8 D_800427E0[];
extern u8 D_80043BF0[];
extern u8 D_80049F70[];
extern u8 D_80066E50[];
extern u8 boot_audio_queue[];

s32 func_8002B034(T095AudioTask *task, s32 previousAddress)
{
  u32 physical;
  T095RspTask *rsp;
  s32 count;
  u8 *end;
  func_8002B3E0();
  physical = osVirtualToPhysical(task->buffer);
  if (previousAddress)
  {
    osAiSetNextBuffer(((T095AudioTask *)previousAddress)->buffer, ((T095AudioTask *)previousAddress)->samples * 4);
  }
  task->samples = ((D_80068168 - (osAiGetLength() >> 2)) + 0x60) & 0xFFF0;
  if (((u32) task->samples) < D_80068164)
  {
    task->samples = D_80068164;
  }
  end = (u8 *) func_80039C08(D_80066C50[D_80048158], &count, (s16 *)physical, task->samples);
  if (count == 0)
  {
    return 0;
  }
  task->state = 0;
  task->queue = D_80066E50;
  task->message = task->body;
  task->type = 2;
  task->rsp.commands = D_80066C50[D_80048158];
  task->rsp.commandSize = ((end - (u8 *)D_80066C50[D_80048158]) >> 3) * 8;
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
void func_8002B1EC(s32 unused)
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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1B230/func_8002B22C.s")

typedef struct T024DmaBuffer { struct T024DmaBuffer *next,*prev; u32 address,frame; void *buffer; } T024DmaBuffer;
typedef struct { u8 initialized; T024DmaBuffer *used,*free; } T024DmaPool;
extern T024DmaPool D_80068158;
extern T024DmaBuffer D_80067ED8[];
extern s32 func_8002B22C(s32, s32, void *);

void *func_8002B3A8(T024DmaPool **state) {
    if (!D_80068158.initialized) {
        D_80068158.used = 0;
        D_80068158.free = &D_80067ED8[0];
        D_80068158.initialized = 1;
    }
    *state = &D_80068158;
    return func_8002B22C;
}

extern u32 D_80048150, D_80048154;
extern u8 D_800683F8[];
extern s32 osRecvMesg(void *, void *, s32);
extern void alUnlink(void *), alLink(void *, void *);

void func_8002B3E0(void) {
    u32 i;
    void *iomsg;
    T024DmaBuffer *dmaPtr, *nextPtr;

    for (i = 0; i < D_80048154; i++) {
        osRecvMesg(D_800683F8, &iomsg, 0);
    }
    dmaPtr = D_80068158.used;
    while (dmaPtr) {
        nextPtr = dmaPtr->next;
        if (dmaPtr->frame + 1 < D_80048150) {
            if (D_80068158.used == dmaPtr) {
                D_80068158.used = dmaPtr->next;
            }
            alUnlink(dmaPtr);
            if (D_80068158.free) {
                alLink(dmaPtr, D_80068158.free);
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

