/* T-144 draft: 65 differing words, 628/632 bytes in the full owning unit. */
void func_80030440(u8 *image, s32 index) {
    s32 stride, source, y, x;
    D_80069E48[index].width = image[0];
    D_80069E48[index].height = image[1];
    D_80069E48[index].spacing = image[2];
    D_80069E48[index].baseline = image[3];
    stride = (D_80069E48[index].width + 7) & 0xFFF8;
    source = 8;
    for (y = 0;
    y < D_80069E48[index].height;
    y++) {
        s32 swap;
        if ((y & 1) == 0) swap = 0; else swap = 4;
        x = 0;
        while (x < D_80069E48[index].width) {
            s32 run;
            s32 n;
            s32 j;
            run = image[source] & 0xF0;
            n = (image[source++] & 15) + 1;
            for (j = 0;
            j < n;
            j++) D_80069F70[index * 0x120 + ((x+j)^swap) + y*stride] = run;
            x += n;
        }
        while (x < stride) {
            D_80069F70[index * 0x120 + (x^swap) + y*stride] = 0;
            x++;
        }
    }
    for (x = 0;
    x < stride;
    x++) D_80069F70[index * 0x120 + x + y*stride] = 0;
}
