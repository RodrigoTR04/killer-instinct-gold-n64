/* DRAFT. Remaining diff: 110 positional differing words; 480/476 bytes */
typedef struct { u8 width, height, flags, pad; } T033ImageSize;
typedef struct { s32 width, height; u8 pixels[1]; } T033PackedImage;
extern u8 D_A69A70[], D_A6A990[], D_A6AA70[], D_8030000F;
extern T033ImageSize D_80069E48[];
extern u8 D_80069F70[][0x120];
extern void boot_dma(void *, void *, s32), boot_dma_chunked(void *, void *, s32);
extern void func_80030440(u8 *, s32);

void func_80012390(void) {
    u32 base;
    s32 length;
    u8 *cursor;
    u32 end;
    s32 index;
    T033ImageSize *size;
    T033PackedImage *image;
    u8 *src, *dst;
    s32 count, i;
    length = D_A6A990 - D_A69A70;
    boot_dma_chunked(D_A69A70, (void *)0x80300000, length);
    cursor = &D_8030000F;
    end = length + 0x80300000;
    index = 0;
    while ((u32)(cursor + 8) < end) {
        if (*cursor * 0x01010101 == 0) break;
        func_80030440(cursor, index);
        cursor += (*cursor << 24) + (*cursor << 16) + (*cursor << 8) + *cursor;
        index++;
    }
    base = (u32)cursor & ~15;
    image = (T033PackedImage *)base;
    boot_dma(D_A6A990, (void *)base, D_A6AA70 - D_A6A990);
    if ((u32)image < (u32)(D_A6AA70 + base - (u32)D_A6A990)) {
        size = &D_80069E48[index];
        do {
            size->width = image->width;
            size->flags = 0;
            size->pad = 0;
            size->height = image->height;
            dst = D_80069F70[index];
            i = 0;
            src = (u8 *)image;
            size++;
            count = image->height * image->width;
            if (count > 0) {
                do {
                    i++;
                    dst++;
                    dst[-1] = src[8];
                    src++;
                    count = image->height * image->width;
                } while (i < count);
            }
            image = (T033PackedImage *)((u8 *)image + count + 8);
            index++;
        } while ((u32)image < (u32)(D_A6AA70 + base - (u32)D_A6A990));
    }
}
