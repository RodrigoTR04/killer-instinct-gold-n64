typedef struct { u8 *data; s32 offset; } T032Cache245;
extern T032Cache245 D_8004D290[][6], D_8004EA60[][6];
extern s8 D_8004F398;

void func_800245B4(s32 player, void *start, s32 size) {
    u32 rangeStart = (u32)start;
    T032Cache245 *bank = &((T032Cache245 *)&D_8004D278)[player];
    T032Cache245 (*limit)[6] = D_8004EA60;
    u8 *p = bank->data;

    if (p && (u32)(p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24)) >= rangeStart && (u32)p < rangeStart + size) {
        s32 off = bank->offset;
        bank->data = p;
        bank->offset = off;
    }
    {
        T032Cache245 (*row)[6] = D_8004D290;
        T032Cache245 *entry = &D_8004D290[0][player];

        do {
            p = entry->data;
            row++;
            if (p && (u32)(p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24)) >= rangeStart && (u32)p < rangeStart + size) {
                *entry = *bank;
            }
            p = entry[3].data;
            if (p && (u32)(p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24)) >= rangeStart && (u32)p < rangeStart + size) {
                entry[3] = *bank;
            }
            entry += 6;
        } while (row != limit);
    }
    D_8004F398 = 1;
}
