/* DRAFT. Remaining diff: Same 184-byte body; cursor/global address registers and one lui schedule differ. */
typedef struct T029Gfx801B994C { u32 w0, w1; } T029Gfx801B994C;
extern void guTranslate(void *, f32, f32, f32);
extern void func_8002F6F4(s32, s32, void *);
extern s16 D_801F35AC;
extern u8 D_802C8800[];
extern s32 D_80066C40;
extern u8 D_8004A264[];
s32 func_801B994C(T029Gfx801B994C **arg0, s32 arg1, void *arg2, s32 arg3) {
    T029Gfx801B994C *command;
    guTranslate(arg2, 0.0f, 50.0f, 0.0f);
    command = *arg0;
    *arg0 = command + 1;
    command->w0 = 0xFA000000;
    command->w1 = (D_801F35AC & 0xFF) | ~0xFF;
    if (D_802C8800[1] == 0 && D_801F35AC >= 51) {
        func_8002F6F4(D_80066C40, 70, D_8004A264);
        D_802C8800[1] = 1;
    }
    return 1;
}
