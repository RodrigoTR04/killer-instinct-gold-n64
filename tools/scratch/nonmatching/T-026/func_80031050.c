/* DRAFT. Remaining diff: 30 positional words; 120/112 bytes. Shared continuation at 80031188 needs private saved-register ABI. */
/* Entry fragment continues at func_80031188 with private live registers. */
extern s32 D_8004EA78;
extern void func_80031188(s32, s32, s32, s16, s16);
void func_80031050(s32 first, s32 second, s32 third) {
    u8 *entry = (u8 *)D_8004CED0;
    s32 count = D_8004EA78;
    while (count != 0) { count--; entry += 0x1C; }
    func_80031188(first, second, third, *(s16 *)(entry + 0x10), *(s16 *)(entry + 0xC));
}
