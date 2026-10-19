/* DRAFT. Remaining diff: Same 368-byte body; command constants, address arithmetic and temporary registers differ. */
typedef struct T029Gfx801B6A68 { u32 w0, w1; } T029Gfx801B6A68;
extern u8 D_802C8D08[];
extern u8 D_802C8808[];
extern u8 D_801F34B0[];
typedef struct T029Texture { u8 pad[8]; void *data; } T029Texture;
s32 func_801B6A68(T029Gfx801B6A68 **arg0, T029Texture *arg1, s32 arg2) {
    T029Gfx801B6A68 *command0;
    T029Gfx801B6A68 *command1;
    T029Gfx801B6A68 *command2;
    T029Gfx801B6A68 *command3;
    T029Gfx801B6A68 *command4;
    T029Gfx801B6A68 *command5;
    T029Gfx801B6A68 *command6;
    T029Gfx801B6A68 *command7;
    T029Gfx801B6A68 *command8;
    T029Gfx801B6A68 *command9;
    T029Gfx801B6A68 *command10;

    if (arg1->data != 0) {
        command0 = *arg0; *arg0 = command0 + 1;
        command0->w0 = 0xE7000000; command0->w1 = 0;
        command1 = *arg0; *arg0 = command1 + 1;
        command1->w0 = 0xFD100000;
        command1->w1 = (u32)(D_802C8808 + (arg2 << 9) + D_802C8D08[arg2] * 2);
        command2 = *arg0; *arg0 = command2 + 1;
        command2->w0 = 0xE8000000; command2->w1 = 0;
        command3 = *arg0; *arg0 = command3 + 1;
        command3->w0 = 0xF5000100; command3->w1 = 0x07000000;
        command4 = *arg0; *arg0 = command4 + 1;
        command4->w0 = 0xE6000000; command4->w1 = 0;
        command5 = *arg0; *arg0 = command5 + 1;
        command5->w0 = 0xF0000000; command5->w1 = 0x073FC000;
        command6 = *arg0; *arg0 = command6 + 1;
        command6->w0 = 0xE7000000; command6->w1 = 0;
        command7 = *arg0; *arg0 = command7 + 1;
        command7->w0 = 0xBA000E02; command7->w1 = 0x8000;
        command8 = *arg0; *arg0 = command8 + 1;
        command8->w0 = 0x06000000; command8->w1 = (u32)D_801F34B0;
        return 2;
    }
    command9 = *arg0; *arg0 = command9 + 1;
    command9->w0 = 0xBA000E02; command9->w1 = 0;
    command10 = *arg0; *arg0 = command10 + 1;
    command10->w0 = 0x06000000; command10->w1 = (u32)D_801F34B0;
    return 0;
}
