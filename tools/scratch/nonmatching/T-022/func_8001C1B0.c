/* T-022 DRAFT: 74 instruction words differ; compiled 308 bytes, original 292 bytes */



void func_8001C1B0(u8 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 a = arg2 & 255, b = arg3 & 255;
    for (i = 0; i < arg1; i++) {
        u8 value = arg0[i][12+a];
        arg0[i][12+a] = arg0[i][12+b];
        arg0[i][12+b] = value;
    }
}
