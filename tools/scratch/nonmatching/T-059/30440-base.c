/* T-054 DRAFT: 122 relocation-masked positional words differ; 488 emitted bytes. See T-054/REPORT.md. */

extern u8 D_80069E48[], D_80069F70[];
void func_80030440(u8 *image, s32 index) {
    s32 width = image[0];
    s32 height = image[1];
    s32 stride = (width + 7) & 0xFFF8;
    u8 *source = image + 8;
    s32 y;
    s32 x;
    u8 *out = D_80069F70 + index * 0x120;
    D_80069E48[index*4] = image[0];
    D_80069E48[index*4+1] = image[1];
    D_80069E48[index*4+2] = image[2];
    D_80069E48[index*4+3] = image[3];
    for (y = 0; y < height; y++) {
        s32 swap = (y & 1) ? 4 : 0;
        x = 0;
        while (x < width) {
            u8 run = *source++;
            s32 n = (run & 15) + 1;
            s32 j;
            for (j = 0; j < n; j++) out[y*stride + ((x+j)^swap)] = run & 0xF0;
            x += n;
        }
        while (x < stride) { out[y*stride + (x^swap)] = 0; x++; }
    }
    for (x = 0; x < stride; x++) out[y*stride+x] = 0;
}
