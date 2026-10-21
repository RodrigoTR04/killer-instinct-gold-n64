/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"
#include "boot.h"
extern u8 D_80066C30[],D_80128350[],D_8F9FA0[],D_907580[],D_9AF4B0[],D_9B9AD0[],D_992AF0[];
extern ALBank *D_80066C40;

void func_8002A900(s32 index) {
    u32 count;
    u32 limit;

    if (index != D_80048148) {
        boot_dma((s32)D_80066C28->seqArray[index].offset, (s32)D_80066A30, D_800669D0[index]);
        D_80048148 = index;
    }
    count = 0;
    limit = 0x3D0900;
    alCSPStop(D_800669C0);
    if (alCSPGetState(D_800669C0)) {
        for (;;) {
            count++;
            if (alCSPGetState(D_800669C0) == 0) break;
            if (count >= limit) break;
        }
    }
    alCSeqNew(&D_80066A38, D_80066A30);
    alCSPSetSeq(D_800669C0, &D_80066A38);
}
