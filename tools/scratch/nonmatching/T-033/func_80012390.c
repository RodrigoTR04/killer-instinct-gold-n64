/* T-143 DRAFT: 67 differing words; 468/476 bytes. */
typedef struct { u8 width, height, flags, pad; } T033ImageSize;
typedef struct { s32 width, height; u8 pixels[1]; } T033PackedImage;
extern u8 D_A69A70[], D_A6A990[], D_A6AA70[], D_8030000F;
extern T033ImageSize D_80069E48[];
extern u8 D_80069F70[][0x120];
extern void boot_dma(s32, s32, s32), boot_dma_chunked(void *, void *, s32);
extern void func_80030440(u8 *, s32);

void func_80012390(void) {
    s32 length;
    u8 *cursor;
    u32 end;
    s32 index;
    u8 *src, *dst;
    s32 count, i;
    length = D_A6A990 - D_A69A70;
    boot_dma_chunked(D_A69A70, (void *)0x80300000, length);
    cursor = (u8 *)0x80300000;
    end = length + 0x80300000;
    index = 0;
    while ((u32)(cursor + 8) < end) {
        if ((((u32)cursor[4] << 24) + (cursor[5] << 16) + (cursor[6] << 8) + cursor[7]) == 0) break;
        func_80030440(cursor, index);
        cursor += ((u32)cursor[4] << 24) + (cursor[5] << 16) + (cursor[6] << 8) + cursor[7];
        index++;
    }
    cursor = (u8 *)(((u32)cursor + 15) & ~15);
    boot_dma((s32)D_A6A990, (s32)cursor, (s32)D_A6AA70 - (s32)D_A6A990);
    end = (u32)(D_A6AA70 + (u32)cursor - (u32)D_A6A990);
    if ((u32)cursor < end) {
        do {
            D_80069E48[index].width = ((T033PackedImage *)cursor)->width;
            D_80069E48[index].flags = 0;
            D_80069E48[index].pad = 0;
            D_80069E48[index].height = ((T033PackedImage *)cursor)->height;
            dst = D_80069F70[index];
            i = 0;
            src = cursor;
            count = ((T033PackedImage *)cursor)->height * ((T033PackedImage *)cursor)->width;
            if (count > 0) {
                do {
                    i++;
                    dst++;
                    dst[-1] = src[8];
                    src++;
                    count = ((T033PackedImage *)cursor)->height * ((T033PackedImage *)cursor)->width;
                } while (i < count);
            }
            cursor += count;
            cursor += 8;
            index++;
        } while ((u32)cursor < end);
    }
}
