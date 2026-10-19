/* DRAFT. Remaining diff: stack layout now matches; callee-saved register allocation differs (target keeps the buffer base in s4 and copies it to a separate loop pointer, hoists 0x20 into fp and &state.game_name/D_802956BC/&state into s7/s6/s5). Same instruction count. T034PfsState is OSPfsState-shaped (file_size, game_code, company_code, ext_name, game_name). */
extern u8 D_802D3D30;
extern s32 D_802D3E00;
extern u8 D_802D3E0E;
s32 func_801CBF8C(void);
void func_801CCEAC(u8 *dst, u8 *src, s32 len);
typedef struct {
    u32 file_size;
    u32 game_code;
    u16 company_code;
    char ext_name[4];
    char game_name[16];
} T034PfsState;

extern s32 func_80035DE0(void *, s32 *, s32 *);
extern s32 func_80035F10(void *, s32, T034PfsState *);
extern s32 func_801CC3BC(s32, s32);
extern void func_801CD100(u8 *, u32);
extern void func_801CD174(s32);
extern u8 D_802956BC[];

void func_801CD1F0(s32 arg0) {
    s32 ret;
    s32 maxFiles;
    s32 count;
    void *pfs;
    T034PfsState state;
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
    ret = func_80035DE0(pfs, &count, &maxFiles);
    if (ret != 0) {
        func_801CC3BC(ret, arg0);
        ret = func_80035DE0(pfs, &count, &maxFiles);
    }
    if (ret == 0) {
        if (count > 16) {
            count = 16;
        }
        for (i = 0; i < count; i++) {
            *entries = (u8 *)names;
            if (func_80035F10(pfs, i, &state) != 0) {
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
        D_802D3E0E = i;
    }
}
