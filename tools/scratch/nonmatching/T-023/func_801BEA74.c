/* DRAFT. Remaining diff: 64-bit mixed-radix multiply/add sequencing and stack/register allocation differ. */
extern s32 func_801BEEA4(s32, s32, s32);
extern void func_801BEFFC(void);
extern u8 D_80127CC0[];
u64 func_801BEA74(u8 wins, u8 games, u8 health, u8 *a, u8 *b, s32 name, s32 character) {
    u64 result = 0;
    u64 multiplier = 11;
    s32 enabled = 1;
    s32 i, table;
    if (D_80127CC0[31] || D_80127CC0[29]) enabled = 0;
    if (character != 10) {
        result = func_801BEEA4(1, wins, name);
        result += func_801BEEA4(2, games, name) * multiplier;
        multiplier *= 11;
        result += func_801BEEA4(3, health, name) * multiplier;
        multiplier *= 11;
        if (enabled) {
            table = 4; i = 5;
            do {
                result += func_801BEEA4(table, *a, name) * multiplier;
                multiplier *= 6;
                result += func_801BEEA4(i, *b, name) * multiplier;
                multiplier *= 6;
                i += 2; table += 2; a++; b++;
            } while (i != 25);
        }
        if (result) func_801BEFFC();
    }
    return result;
}
