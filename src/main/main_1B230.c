#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1B230/func_8002AB90.s")

typedef struct {
    s16 type;
    s32 samples;
} T024AudioMessage;

extern u8 D_80066E18[],D_80066E50[],D_80066E88[];

extern void *D_80066C50[];

extern u32 D_80048150;

extern s32 osRecvMesg(void *,void *,s32),func_8002B034(void *,s32);

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1B230/func_8002B034.s")

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

