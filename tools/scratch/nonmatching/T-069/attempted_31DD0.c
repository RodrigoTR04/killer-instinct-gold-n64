/* Rejected diagnostic candidate, not a retained improvement or validated implementation.
 * Adds top/padding clears and typed sprite/bounds access; still 355 words off. */
typedef struct { u16 *pixels; u8 *data; s16 halfWidth,halfHeight,width,height,width2,height2; u8 pad[4]; s16 flags,palette; } T069Sprite;
extern T069Sprite D_8004CED0[];
typedef struct { u16 left,right; } T069Bounds;
/* DRAFT. Remaining diff: 356 differing instruction words; emitted 1020 / original 1424 bytes (positional comparison). */
/* Additive sprite compositor. Byte color and RGB555 color planes use the
 * same packed run stream; alternate rows are word-swapped. */
extern s32 D_8004EA78;
extern u16 *D_800482D0[];
extern T069Bounds *D_8004F2C8;
void func_80031DD0(u8 *input, s32 horizontal, u32 vertical) {
    T069Sprite *sprite = &D_8004CED0[D_8004EA78];
    u8 *intensity = sprite->data;
    u16 *color = sprite->pixels;
    u16 *palette = D_800482D0[sprite->palette];
    s32 stride = sprite->width2;
    s32 top = vertical >> 16;
    s32 height = input[6] + (input[7]<<8);
    s32 y;
    s32 pitch=(sprite->width+7)&~7;
    s32 row;
    for (row=0;row<top;row++) {
        s32 k;
        for(k=pitch;k<stride;k+=8) *(u64 *)(intensity+row*stride+k)=0;
        if(D_8004F2C8) D_8004F2C8++;
    }
    input += 8;
    for (y = top; y < top+height; y++) {
        u8 *end = input + *input;
        s32 x = 0;
        s32 swap = (y&1) ? 4 : 0;
        s32 extent = 0;
        s32 k;
        for(k=pitch;k<stride;k+=8) {
            *(u64 *)(intensity+y*stride+k)=0;
            *(u64 *)(color+y*stride+k)=0;
            *(u64 *)(color+y*stride+k+4)=0;
        }
        input++;
        if (input != end) {
            x = horizontal + *input++;
            if (D_8004F2C8 != 0 && D_8004F2C8->left > x) D_8004F2C8->left = x;
            extent = x;
            while (input != end) {
                u8 code = *input++;
                s32 value = code&0xF0;
                s32 second = -1;
                s32 run;
                s32 pass;
                if (code == 0) { run = *input++; x += run; extent += run; continue; }
                if (!(code&8)) { run = code&7; if (run == 0) run = *input++; }
                else { s32 delta = code&7; if (delta&4) delta = -(delta&3)-2; second = value + ((delta+1)<<4); run = 1; }
                for (pass = 0; pass < 2; pass++) {
                    u16 source = palette[value>>4];
                    s32 n = run;
                    extent += run;
                    do {
                        u8 *dest = (u8 *)((u32)(intensity+y*stride+x)^swap);
                        u16 *rgb = (u16 *)((u32)(color+y*stride+x)^swap);
                        if (*dest == 0) { *dest = value; *rgb = source; }
                        else {
                            u32 sum = *rgb + source;
                            u32 carry = (*rgb ^ source ^ sum)&0x10840;
                            s32 alpha = *dest + value;
                            if (alpha&0xFF00) alpha = 0xFF;
                            *dest = alpha;
                            *rgb = sum | (carry-(carry>>5));
                        }
                        x++;
                    } while (--n != 0);
                    if (second < 0) break;
                    value = second; second = -1; run = 1;
                }
            }
        }
        if (D_8004F2C8 != 0) {
            if (D_8004F2C8->right > extent) D_8004F2C8->right = extent;
            D_8004F2C8++;
        }
    }
}
