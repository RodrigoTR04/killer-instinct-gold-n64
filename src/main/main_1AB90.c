#include "audio_game.h"
#include "boot.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002A4F0.s")

void func_8002A888(void) {
    if (alCSPGetState(D_800669C0) == 0) {
        alCSPPlay(D_800669C0);
        func_8002AA98(0x7FFF);
    }
}

void func_8002A8C4(void) {
    if (alCSPGetState(D_800669C4) == 0) {
        alCSPPlay(D_800669C4);
        func_8002AAEC(0x7FFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1AB90/func_8002A900.s")

void func_8002A9DC(s32 index) {
    if (index != D_8004814C) {
        boot_dma((s32)D_80066C28->seqArray[index].offset, (s32)D_80066A34, D_800669D0[index]);
        D_8004814C = index;
    }
    alCSPStop(D_800669C4);
    while (alCSPGetState(D_800669C4) != 0) {}
    alCSeqNew(&D_80066B30, D_80066A34);
    alCSPSetSeq(D_800669C4, &D_80066B30);
}

extern s32 D_80048140[];
extern u8 D_80127CC9;

void func_8002AA98(s32 volume)
{
    s16 narrowed;
    volume = D_80048140[D_80127CC9] * volume;
    volume >>= 16;
    narrowed = volume;
    alCSPSetVol(D_800669C0, narrowed);
}

void func_8002AAEC(s32 volume)
{
    s16 narrowed;
    volume = D_80048140[D_80127CC9] * volume;
    volume >>= 16;
    narrowed = volume;
    alCSPSetVol(D_800669C4, narrowed);
}

void func_8002AB40(void) {
    alCSPStop(D_800669C0);
}

void func_8002AB64(void) { alCSPStop(D_800669C4); }
