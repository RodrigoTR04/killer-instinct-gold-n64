/* T-045 DRAFT: 55 standalone relocation-masked positional words; 304/304 bytes, was 65 and 308/304. Keep the decoded top-byte mode as s32; avoid redundant mask/narrowing. */
typedef struct { s32 value[2]; } T033Pair;
typedef struct { u8 pad[8]; u8 *start, *end; } T033RomEntry;
extern T033Pair D_8004A3E8;
extern T033RomEntry D_800071F0;
extern s32 D_8004A3E0, D_8004A3E4, D_8004A3F0, D_8004A3F4, D_8004A3F8;
extern u8 D_8004A3FC, D_8004A3FD;
extern s32 D_801D87B0, D_801D87B8, D_801D87BC, D_801D87C0, D_801D87C4;
extern u32 D_801D87D4, D_801D87D8;
extern u8 D_801CD450[], D_802956F0[];
extern void func_801ABB20(void *);
extern void osInvalICache(void *, s32), osInvalDCache(void *, s32);
extern void boot_dma_chunked(void *, void *, s32), boot_inflate(void *, void *, void *);

void func_800121C8(void) {
    s32 mode;
    D_8004A3F8 = D_801D87D4 / 70U - 3;
    D_8004A3E4 = D_801D87B8;
    D_8004A3E8.value[0] = D_801D87BC;
    D_8004A3E8.value[1] = D_801D87C0;
    D_8004A3F0 = D_801D87C4;
    mode = D_801D87D8 >> 24;
    D_8004A3FD = D_801D87D8 >> 8;
    D_8004A3F4 = mode >= 2;
    D_8004A3E0 = D_801D87B0;
    D_8004A3FC = mode;
    osInvalICache(func_801ABB20, D_801CD450 - (u8 *)func_801ABB20);
    osInvalDCache(D_801CD450, D_802956F0 - D_801CD450);
    boot_dma_chunked(D_800071F0.start, (void *)0x802D6000, D_800071F0.end - D_800071F0.start);
    boot_inflate((void *)0x802D6000, func_801ABB20, (void *)0x802D4000);
    func_801ABB20(&D_8004A3E0);
}
