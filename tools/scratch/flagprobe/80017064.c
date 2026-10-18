typedef int s32; typedef unsigned char u8;
extern s32 D_800698C4;

s32 func_80017064(s32 arg0, int arg1, s32 arg2, int arg3) {
    if (D_800698C4 > 0) {
        return 1;
    }
    if (arg2 >= 0xDAD) {
        return 1;
    }
    if (arg0 >= 0x329) {
        return 0;
    }
    if (arg0 >= -0x252) {
        return 1;
    }
    return 2;
}
