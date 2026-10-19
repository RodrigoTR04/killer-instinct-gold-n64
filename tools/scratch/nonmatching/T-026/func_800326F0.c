/* DRAFT. Remaining diff: 69 positional words; 276/72 bytes. Original uses native 64-bit register shifts/stores; O2/mips2 lowers C to word pairs. */
extern u64 D_80048420;
s32 func_800326F0(void) {
    u64 value = D_80048420;
    value = (((value << 63) >> 31) | ((value << 31) >> 32)) ^ ((value << 44) >> 32);
    value ^= (value >> 20) & 0xFFF;
    D_80048420 = value;
    return value;
}
