typedef struct { u8 width, height, flags, pad; } T033ImageSize;
typedef struct { s32 width, height; u8 pixels[1]; } T033PackedImage;
extern u8 D_A69A70[], D_A6A990[], D_A6AA70[];
extern T033ImageSize D_80069E48[];
extern u8 D_80069F70[];
extern void boot_dma(s32, s32, s32), boot_dma_chunked(void *, void *, s32);
extern void func_80030440(u8 *, s32);

void func_80012390(void) {
    s32 length;
    u8 *cursor, *start;
    u32 limit;
    s32 index;
    u8 *src, *end, *dst;
    s32 count, i;
    length = D_A6A990 - D_A69A70;
    boot_dma_chunked(D_A69A70, (void *)0x80300000, length);
    cursor = (u8 *)0x80300000;
    limit = length + 0x80300000;
    index = 0;
    while ((u32)(cursor + 8) < limit) {
        if (((u32)cursor[4] << 24) + (cursor[5] << 16) + (cursor[6] << 8) + cursor[7] == 0) break;
        func_80030440(cursor, index);
        cursor += ((u32)cursor[4] << 24) + (cursor[5] << 16) + (cursor[6] << 8) + cursor[7];
        index++;
    }
    start = (u8 *)(((u32)cursor + 15) & ~15);
    cursor = start;
    src = D_A6A990;
    end = D_A6AA70;
    boot_dma((s32)src, (s32)cursor, end - src);
    while (cursor < end + (u32)start - (u32)src) {
        D_80069E48[index].width = ((T033PackedImage *)cursor)->width;
        D_80069E48[index].flags = 0;
        D_80069E48[index].pad = 0;
        D_80069E48[index].height = ((T033PackedImage *)cursor)->height;
        dst = &D_80069F70[index * 0x120];
        for (i = 0; i < ((T033PackedImage *)cursor)->height * ((T033PackedImage *)cursor)->width; i++) {
            *dst++ = ((T033PackedImage *)cursor)->pixels[i];
        }
        cursor += ((T033PackedImage *)cursor)->height * ((T033PackedImage *)cursor)->width;
        cursor += 8;
        index++;
    }
}
