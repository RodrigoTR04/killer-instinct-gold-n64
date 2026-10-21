/* T-102 DRAFT: 91 differing words, 456/460 bytes; saved-register and cursor scheduling remain. */
extern u8 D_802D3D30;
extern s32 D_802D3E00;
extern u8 D_802D3E0E;
s32 func_801CBF8C(void);
void func_801CCEAC(u8 *dst, u8 *src, s32 len);


extern s32 osPfsNumFiles(void *, s32 *, s32 *);

extern s32 func_801CC3BC(s32, s32);

extern void func_801CD174(s32);
extern u8 D_802956BC[];

void func_801CD1F0(s32 arg0) {
    s32 ret;
    s32 maxFiles;
    s32 count;
    void *pfs;
    T056PfsState state;
    u8 **entries;
    s32 i;
    u8 **names;
    u8 *str;

    D_802D3E0E = 0;
    entries = (u8 **)D_802D3E00;
    names = entries + 16;
    str = (u8 *)(entries + 32);
    entries[0] = 0;
    if (func_801CBF8C() != 0) {
        return;
    }
    func_801CD174(arg0);
    pfs = &D_802D3D30 + arg0 * 0x68;
    ret = osPfsNumFiles(pfs, &count, &maxFiles);
    if (ret != 0) {
        func_801CC3BC(ret, arg0);
        ret = osPfsNumFiles(pfs, &count, &maxFiles);
    }
    if (ret == 0) {
        if (count > 16) {
            count = 16;
        }
        for (ret = 0; ret < count; ret++) {
            *entries = (u8 *)names;
            if (osPfsFileState(pfs, ret, &state) != 0) {
                *names = D_802956BC;
            } else {
                *names = str;
                *str++ = 'j';
                func_801CCEAC(str, (u8 *)state.game_name, 16);
                str[18] = ' ';
                str[17] = ' ';
                str[16] = ' ';
                str += 19;
                func_801CCEAC(str, (u8 *)state.ext_name, 4);
                str[4] = 'j';
                str += 5;
                func_801CD100(str, (state.file_size + 0xFF) >> 8);
                str[4] = 0;
                str += 5;
            }
            entries++;
            names++;
        }
        D_802D3E0E = ret;
    }
}
