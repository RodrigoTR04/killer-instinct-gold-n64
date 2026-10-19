/* DRAFT T-020: Same instructions and size except four pointer spill/reload offsets: 0x18(sp) instead of 0x1C(sp). */
typedef struct { u8 *start; u8 *end; } T020Range12100;
extern T020Range12100 D_80007208[];
extern void func_80012338(void *, void *, s32);
extern void boot_dma_chunked(void *, void *, s32);

void func_80012100(u8 arg0, u8 arg1) {
    T020Range12100 *range;
    range = &D_80007208[arg0];
    boot_dma_chunked(range->start, (void *)0x802D4000, range->end - range->start);
    func_80012338((void *)0x802D4000, (void *)0x801DB000, range->end - range->start);
    range = &D_80007208[arg1];
    boot_dma_chunked(range->start, (void *)0x802D4000, range->end - range->start);
    func_80012338((void *)0x802D4000, (void *)0x801E5000, range->end - range->start);
}
