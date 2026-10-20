/* DRAFT. Remaining diff: 10 differing words; 80/84 bytes */
extern s32 D_80048140[];
extern u8 D_80127CC9;
extern void *D_800669C0;
extern void alCSPSetVol(void *,s32);
void func_8002AA98(s32 volume) { s32 scaled = D_80048140[D_80127CC9] * volume; alCSPSetVol(D_800669C0,(s16)(scaled >> 16)); }
