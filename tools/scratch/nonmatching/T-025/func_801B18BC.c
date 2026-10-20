/* DRAFT. Remaining diff: Large loop increment is hoisted into an extra saved register; register allocation, scheduling and trailing padding differ. */
typedef struct { u8 pad[0x10]; s32 state; } T025State;
extern void func_801C0610(s32);
extern void func_801C49A8(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_8029571A;
extern u8 D_802C8724;
s32 func_801B18BC(s32 arg0, T025State *arg1, s32 arg2, u32 arg3) {
    s32 i, x, n;
    if (arg3 >= 0xF1U) {
        D_8029571A++;
        arg1->state = -1;
    }
    func_801C0610(arg0);
    x = 0x82000;
    i = 0;
    do {
        if (D_802C8724 & (1 << i)) n = 12;
        else n = 15;
        func_801C49A8(arg0, i, 0x82000 + i * 0xC8000, 0x172000, (n << 12) / 10, 0, 0);
        i++;
        x += 0xC8000;
    } while (i != 3);
    return 0;
}
