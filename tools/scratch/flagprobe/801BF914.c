typedef int s32; typedef unsigned u32;
s32 func_801BF914(u32 arg0) {

    if ((arg0 >= 0x41U) && (arg0 < 0x5BU)) {
        return arg0 - 0x41;
    }
    switch (arg0) {
    case 0x20:
        return 0x1B;
    case 0x2E:
        return 0x1C;
    case 0x2F:
        return 0x1D;
    case 0x3A:
        return 0x1E;
    case 0x2C:
        return 0x1F;
    default:
        return 0x1B;
    }

}
