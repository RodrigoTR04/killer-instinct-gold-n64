/* DRAFT. Remaining diff: Table initialization/store scheduling and loop pointer registers differ. */
typedef struct { u8 *entries; u8 count, descending; u16 pad; } T023Table790;
extern T023Table790 D_80127D80[];
extern void func_801BE910(u8 *, s32, s32, s32);
extern void func_801BEFFC(void);
extern s32 D_80127C30[];
extern u8 D_80127E50[], D_80127EA0[], D_80127EF0[], D_80127F40[], D_80127F90[], D_80128148[], D_80128300[];
void func_801BE790(void) {
    T023Table790 *table; u8 *a, *b; D_80127D80[0].entries = D_80127E50; D_80127D80[0].count = 10; D_80127D80[0].descending = 1; D_80127D80[1].entries = D_80127EA0; D_80127D80[1].count = 10; D_80127D80[1].descending = 1; D_80127D80[2].entries = D_80127EF0; D_80127D80[2].count = 10;
    D_80127D80[2].descending = 1; D_80127D80[3].entries = D_80127F40; D_80127D80[3].count = 10; D_80127D80[3].descending = 0; func_801BE910(D_80127EA0, 10, 11, 1); func_801BE910(D_80127EF0, 10, 11, 1); func_801BE910(D_80127F40, 10, 16, -3); a = D_80128148; b = D_80127F90; table = D_80127D80; do
    {
    table[4].entries = b; table[4].count = 5; table[4].descending = 1; func_801BE910(b, 5, 15, 2); table[5].entries = a; table[5].count = 5; table[5].descending = 1;
    func_801BE910(a, 5, 35, 5); a += 40; table += 2; b += 40; } while (a != D_80128300); D_80127C30[1] = D_80127C30[0] = 100; ((s32 *)D_80128300)[1] = ((s32 *)D_80128300)[0] = 0x2E2E2E00; func_801BEFFC(); }
