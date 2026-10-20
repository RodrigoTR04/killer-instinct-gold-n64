/* T-070: nonmatching, 303 differing words including size penalty; 1248 compiled bytes.
 * Compiles in the complete production TU through asm-processor; see T-070/REPORT.md. */
typedef struct { u32 name; u16 score, pad; } T023Score190;
typedef struct { T023Score190 *entries; u8 count, descending; u16 pad; } T023Table190;
extern s32 func_801BD640(s32, void *, s8 *, f32, f32, f32, u8, u8, u8, u8);
extern s32 func_801BDF94(s32, void *, s8 *, f32, f32, f32, u8, f32, f32);
extern s32 strlen(s8 *);
extern void func_801BF678(s8 *, s32);
extern void func_801C2D34(s32, s32, s32, s32, u32);
extern void func_801C47E0(u8, u16, void *, u16);
extern void func_801C48E4(u8, u16, s32);
extern void func_801C49A8(s32, u8, s32, s32, u32, s32, s32);
typedef struct { u32 id, ticks; u8 pad[0xF0]; u8 *matrices; } T070Render190;
extern T070Render190 D_802C9F70;
extern u8 D_800F4070[], D_802D37C0;
extern T023Table190 D_80127D80[];
extern s8 *D_80282DD0[];
extern s8 ***D_8028326C[];
extern s32 D_80282DEC, D_802956F4;
extern f64 D_80292BF0;
extern f32 D_802D37C4;
void func_801BF190(s32 list, s32 unused, s32 table) {
    s32 count, labelIndex, x, titleY, scoreY, titleX, pass, row, rowY, portrait;
    T023Table190 *header;
    T023Score190 *entry;
    s8 **label;
    s8 buffer[16];
    count = D_80127D80[table].count;
    if (table < 14) {
        if (D_802D37C4 < 1.0f) D_802D37C4 = (f64)D_802D37C4 + D_80292BF0;
        if (D_80282DEC != table) {
            D_802D37C4 = 0.0f;
            if (table >= 4) {
                portrait = (table - 4) & 0xFFFF;
                func_801C47E0((table + 124) & 255, 0, D_800F4070, portrait);
                D_802D37C0 ^= 1;
                func_801C48E4(D_802D37C0, portrait, 1);
            } else D_802D37C0 = 0;
        }
        D_80282DEC = table;
        if (table < 4) {
            labelIndex = table; x = -277; titleX = strlen(D_80282DD0[table]) * -34;
            titleY = scoreY = 260;
            func_801C2D34(list, 1000, -250, -600, D_802C9F70.ticks);
        } else {
            x = -540; titleY = 290; scoreY = 270; labelIndex = 4; titleX = -390;
            D_802956F4 += func_801BD640(list, (D_802956F4 << 6) + D_802C9F70.matrices, **D_8028326C[table - 4], (f32)(370 - strlen(**D_8028326C[table - 4]) * 21), -460.0f, -800.0f, 255, 255, 255, 255);
            portrait = table == 12 ? 13 : 15;
            func_801C49A8(list, D_802D37C0, 0x1F4000, 0x172000, (portrait << 12) / 10, 0, 0);
            table = (table - 4) * 2 + 4;
        }
        pass = 0; header = &D_80127D80[table]; label = &D_80282DD0[labelIndex];
        do {
            entry = header->entries; row = 0;
            D_802956F4 += func_801BDF94(list, (D_802956F4 << 6) + D_802C9F70.matrices, *label, (f32)titleX, (f32)scoreY, -600.0f, 0, -D_802D37C4, 0.0f);
            if (count > 0) {
                rowY = titleY;
                do {
                    buffer[0] = 'j'; buffer[5] = ' ';
                    buffer[1] = entry->name >> 24; buffer[2] = entry->name >> 16; buffer[3] = entry->name >> 8; buffer[4] = entry->name;
                    buffer[4] = ' ';
                    func_801BF678(buffer + 6, entry->score);
                    row++;
                    D_802956F4 += func_801BD640(list, (D_802956F4 << 6) + D_802C9F70.matrices, buffer, (f32)x, (f32)rowY, -600.0f, 255, 255, 255, 255);
                    rowY -= 60; entry++;
                } while (row != count);
            }
            header++; pass++; label++; titleY -= 450; scoreY -= 340;
        } while (pass < ((header >= D_80127D80 + 5) + 1));
    }
}
