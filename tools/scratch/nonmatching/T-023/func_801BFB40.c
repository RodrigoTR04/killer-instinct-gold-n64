/* DRAFT. Remaining diff: Struct-copy/global initialization scheduling and base registers differ. */
typedef struct { s32 x, y; } T023PairB40;
typedef struct { s32 value; } T023WordB40;
extern void func_801ADAD4(s32, T023PairB40 *, T023PairB40 *, T023PairB40 *);
extern T023PairB40 D_80128300, D_802D37D8, D_802D37E0, D_802D37F0;
extern T023WordB40 D_80295700, D_802956FC;
extern s32 D_802956F8;
extern s32 D_802D37D0, D_802D37F8, D_802D3820, D_802D3824;
extern u8 D_802D37EA[];
void func_801BFB40(u8 arg0) {
    D_802D37D0 = -1;
    D_802D37EA[1] = 0;
    D_802D37EA[0] = 0;
    D_802D37D8.y = 40;
    D_802D37D8.x = 40;
    D_802D37E0.y = 32;
    D_802D37E0.x = 32;
    D_802D37F0 = D_80128300;
    D_802D37F8 = 0;
    D_802D3820 = 2560;
    D_802D3824 = 2560;
    if (arg0) func_801ADAD4(42, &D_802D37E0, &D_802D37F0, &D_80128300);
    D_80295700.value = 0;
    D_802956FC.value = 0;
    D_802956F8 = 0;
}
