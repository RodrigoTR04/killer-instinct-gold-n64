/* DRAFT. Remaining diff: Same 596-byte body; three operands use a0 instead of a2 after guTranslate. */
typedef struct T029Gfx801B6528 { u32 w0, w1; } T029Gfx801B6528;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_802C8CE0, D_802C8D06, D_802C8CE8;
extern s16 D_802C8CE2;
extern s32 D_802C8CDC, D_802C8CD4;
extern u8 D_80128340[];
extern u8 D_801F2E80[];
extern u8 D_801F2EB4[];
extern u8 D_80290BE0[];
typedef struct T029Card { u8 pad[12]; s32 index; } T029Card;
s32 func_801B6528(T029Gfx801B6528 **arg0, void *arg1, void *arg2, s32 arg3) {

    T029Gfx801B6528 *command;
    f32 y;
    s32 index;
    if (D_8004A407 == 0 || D_802C8CE0 == 0 || D_802C8D06 == 6) return 0;
    if (D_802C8CE0 != 3) {
        index = ((T029Card *)arg1)->index;
        y = (index - (u8)D_8012834B) * 70 - D_802C8CE2;
        if (D_802C8CE2 > 0 && index == 0) D_802C8CE2 = D_802C8CE2 - D_802C8CE8 * 9 - 8;
        D_802C8CDC = D_802C8CD4 + 1;
    } else {
        D_802C8CE2 += 3;
        index = ((T029Card *)arg1)->index;
        if ((u8)D_8012834B >= index) y = (index - (u8)D_8012834B) * 70 - D_802C8CE2;
        else y = (index - (u8)D_8012834B) * 70 + D_802C8CE2;
    }
    guTranslate(arg2, 0.0f, y, 0.0f);
    command = *arg0; *arg0 = command + 1;
    command->w0 = 0x06000000; command->w1 = (u32)D_801F2E80;
    if (((T029Card *)arg1)->index < (u8)D_8012834B) {
        command = *arg0; *arg0 = command + 1;
        command->w0 = 0xFA000000; command->w1 = 0x373737FF;
    }
    command = *arg0; *arg0 = command + 1;
    command->w0 = 0xFD100000;
    command->w1 = *(u32 *)(D_801F2EB4 + D_80128340[((T029Card *)arg1)->index] * 140);
    command = *arg0; *arg0 = command + 1;
    command->w0 = 0x03800010; command->w1 = (u32)D_80290BE0;
    return 1;
}
