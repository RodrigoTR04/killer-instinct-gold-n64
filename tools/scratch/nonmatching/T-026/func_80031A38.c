/* DRAFT. Remaining diff: 229 differing instruction words; emitted 680 / original 920 bytes (positional comparison). */
/* RLE sprite decoder. The original uses sdl/sd and a private helper entry
 * for the second packed nibble; byte writes express the same image layout. */
extern s32 D_8004EA78;
void func_80031A38(u8 *input) {
    T022Sprite *sprite = &D_8004CED0[D_8004EA78];
    u8 *out = sprite->data;
    s32 width = input[4] + (input[5]<<8);
    s32 height = input[6] + (input[7]<<8);
    s32 stride = (width+7)&0xFFF8;
    s32 y;
    sprite->halfWidth = input[0] + (input[1]<<8);
    sprite->halfHeight = input[2] + (input[3]<<8);
    sprite->height = height; sprite->width = width; sprite->width2 = stride;
    input += 8;
    for (y = 0; y < height; y++) {
        u8 *rowEnd = input + *input;
        s32 x = 0;
        s32 swap = (y&1) ? 4 : 0;
        input++;
        if (input != rowEnd) {
            s32 skip = *input++;
            while (x < skip) out[y*stride + ((x++)^swap)] = 0;
            while (input != rowEnd) {
                u8 code = *input++;
                s32 value, run, second = -1;
                if (code == 0) {
                    run = *input++;
                    while (run-- != 0) out[y*stride + ((x++)^swap)] = 0;
                    continue;
                }
                value = code&0xF0;
                if (!(code&8)) { run = code&7; if (run == 0) run = *input++; }
                else {
                    s32 delta = code&7;
                    if (delta&4) delta = -(delta&3)-2;
                    delta++;
                    second = value + (delta<<4); run = 1;
                }
                do { out[y*stride + ((x++)^swap)] = value; } while (--run != 0);
                if (second >= 0) out[y*stride + ((x++)^swap)] = second;
            }
        }
        while (x < stride) out[y*stride + ((x++)^swap)] = 0;
    }
}
