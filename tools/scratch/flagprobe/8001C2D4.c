typedef unsigned char u8;
void func_8001C2D4(u8 **arg0, int arg1, int arg2) {
    int i, j;
    for (i = 0; i < arg1; i++) {
        for (j = 0; j < 3; j++) {
            u8 *p = arg0[i] + j;
            p[12] += ((255 - p[12]) * arg2) / 255;
        }
    }
}
