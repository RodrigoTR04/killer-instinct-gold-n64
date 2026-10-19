/* DRAFT. Remaining diff: 105 differing instruction words; emitted 116 / original 420 bytes (positional comparison). */
/* The original is a hand-written paired color/depth clear with computed
 * tail jumps, unaligned doubleword stores, and a word-swapped mode. */
extern u8 *D_80061488, *D_8006148C;
void func_80032360(s32 offset, s32 length, u16 color, s32 swapped) {
    u16 *pixels = (u16 *)(D_80061488 + offset * 2);
    u8 *depth = D_8006148C + offset;
    while (length-- > 0) {
        if (swapped) {
            *(u16 *)((u32)pixels ^ 4) = color;
            *(u8 *)((u32)depth ^ 4) = 0xC0;
        } else { *pixels = color; *depth = 0xC0; }
        pixels++;
        depth++;
    }
}
