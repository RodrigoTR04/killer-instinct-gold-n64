/* T-100 improved draft; measurements and remaining causes in T-100/REPORT.md. */
typedef struct { u8 *data; s32 offset; } T032Cache245;
extern T032Cache245 D_8004D278[];
extern T032Cache245 D_8004D290[][6], D_8004EA60[][6];
extern s8 D_8004F398;
#define T032_END245(p) ((u32)((p) + ((p)[7] << 24) + (p)[4] + ((p)[5] << 8) + ((p)[6] << 16)))
void func_800245B4(s32 player, u32 start, s32 size) {
    u32 rangeStart = start;
    T032Cache245 *bank = &D_8004D278[player];
    T032Cache245 (*row)[6] = D_8004D290;
    T032Cache245 *entry = &D_8004D290[0][player];
    u8 *p = bank->data;
    if (p && ((u32)((p) + ((p)[7] << 24) + (p)[4] + ((p)[5] << 8) + ((p)[6] << 16))) >= rangeStart && (u32)p < rangeStart + size) {
        bank->data = p; bank->offset = bank->offset;
    }
    do {
        start = (u32)entry[0].data; p = (u8 *)start; row++;
        if (p && ((u32)((p) + ((p)[7] << 24) + (p)[4] + ((p)[5] << 8) + ((p)[6] << 16))) >= rangeStart && (u32)p < rangeStart + size) entry[0] = *bank;
        p = entry[3].data;
        if (p && ((u32)((p) + ((p)[7] << 24) + (p)[4] + ((p)[5] << 8) + ((p)[6] << 16))) >= rangeStart && (u32)p < rangeStart + size) entry[3] = *bank;
        entry += 6;
    } while (row != D_8004EA60);
    D_8004F398 = 1;
}
#undef T032_END245
