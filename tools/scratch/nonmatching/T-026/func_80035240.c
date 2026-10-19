/* DRAFT. Remaining diff: 53 differing instruction words; emitted 208 / original 224 bytes (positional comparison). */
extern s32 func_8003BD24(s32, s32, u8);
s32 func_80035240(u8 *pak, u8 *bank, s32 table, u8 *page) {
    s32 result;
    u16 next;
    s32 value;
    if (page[0] != *bank) {
        *bank = page[0];
        result = func_8003BD24(table, 0, *bank);
        if (result != 0) return result;
    }
    next = *(u16 *)(table + page[1] * 2);
    *(u16 *)page = next;
    value = next;
    if (value >= pak[0x60] && page[0] < pak[0x64]) {
        if (page[1] > 0 && page[1] < 0x80) return 0;
    }
    if (value == 1) return 5;
    return 3;
}
