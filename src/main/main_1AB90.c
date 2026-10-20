#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002A4F0.s")

extern void *D_800669C0;
extern s32 alCSPGetState(void *);
extern void alCSPPlay(void *);
extern void func_8002AA98(s32);
void func_8002A888(void) {
    if (alCSPGetState(D_800669C0) == 0) {
        alCSPPlay(D_800669C0);
        func_8002AA98(0x7FFF);
    }
}

extern void *D_800669C4;
extern s32 alCSPGetState(void *);
extern void alCSPPlay(void *);
extern void func_8002AAEC(s32);
void func_8002A8C4(void) {
    if (alCSPGetState(D_800669C4) == 0) {
        alCSPPlay(D_800669C4);
        func_8002AAEC(0x7FFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002A900.s")

typedef struct {
    void *unused;
    void *start;
} T052SequenceEntry;

extern T052SequenceEntry *D_80066C28;
extern u16 D_8004814C, D_800669D0[];
extern void *D_80066A34;
extern u8 D_80066B30[];
extern void alCSPStop(void *);
extern void alCSeqNew(void *, void *), alCSPSetSeq(void *, void *);
extern void boot_dma(s32, s32, s32);

void func_8002A9DC(s32 index) {
    if (index != D_8004814C) {
        boot_dma((s32)D_80066C28[index].start, (s32)D_80066A34, D_800669D0[index]);
        D_8004814C = index;
    }
    alCSPStop(D_800669C4);
    while (alCSPGetState(D_800669C4) != 0) {}
    alCSeqNew(D_80066B30, D_80066A34);
    alCSPSetSeq(D_800669C4, D_80066B30);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002AA98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002AAEC.s")

extern void *D_800669C0;
extern void alCSPStop(void *);
void func_8002AB40(void) {
    alCSPStop(D_800669C0);
}

extern void *D_800669C4;
extern void alCSPStop(void *);
void func_8002AB64(void) { alCSPStop(D_800669C4); }
