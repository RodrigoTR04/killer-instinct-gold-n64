/* DRAFT. Remaining diff: 63 differing instruction words; emitted 68 / original 252 bytes (positional comparison). */
/* Assembly uses a computed jump into a tail of byte stores, plus sdl/swl
 * and XOR-4 addressing. Express the observable clear operation in C. */
extern u8 *D_8006148C;
void func_80032504(s32 offset, s32 length, s32 swapped) {
    u8 *dest = D_8006148C + offset;
    while (length-- > 0) {
        if (swapped) *(u8 *)((u32)dest ^ 4) = 0;
        else *dest = 0;
        dest++;
    }
}
