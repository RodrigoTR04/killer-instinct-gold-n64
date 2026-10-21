/* T-112: structural reconstruction; nonmatching, see REPORT.md. */
void func_80030440(u8 *image, s32 index) {
    u8 width, height;
    s32 stride, source, y, x;
    D_80069E48[index].width = width = image[0];
    D_80069E48[index].height = height = image[1];
    D_80069E48[index].spacing = image[2];
    D_80069E48[index].baseline = image[3];
    stride = (width + 7) & 0xFFF8;
    source = 8;
    for (y = 0;
    y < height;
    y++) {
        s32 swap = (y & 1) ? 4 : 0;
        x = 0;
        while (x < width) {
            s32 run = image[source++];
            s32 n = (run & 15) + 1;
            s32 j;
            for (j = 0;
            j < n;
            j++) D_80069F70[index*0x120 + ((x+j)^swap) + y*stride] = run & 0xF0;
            x += n;
        }
        while (x < stride) {
            D_80069F70[index*0x120 + (x^swap) + y*stride] = 0;
            x++;
        }
    }
    for (x = 0;
    x < stride;
    x++) D_80069F70[index*0x120 + x + y*stride] = 0;
}
