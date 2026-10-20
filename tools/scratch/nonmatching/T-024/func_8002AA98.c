/* T-082 DRAFT: 2 relocation-masked differing words; target-sized. */
extern s32 D_80048140[];
extern u8 D_80127CC9;
extern void *D_800669C0;
extern void alCSPSetVol(void *,s32);
void func_8002AA98(s32 volume)
{
  s16 narrowed;
  s32 scaled = D_80048140[D_80127CC9] * volume;
  scaled = scaled >> 16;
  narrowed = (s16) scaled;
  alCSPSetVol(D_800669C0, narrowed);
}
