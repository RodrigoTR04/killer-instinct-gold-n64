/* T-105: nonmatching draft; see T-105/REPORT.md for measurement and remaining differences. */
extern void func_801BED0C(u32, u64);
extern s32 D_80127CFC[];

extern u8 D_80127D31;
extern u64 D_802D3800;


extern u64 D_802D3808;
void func_801CB998(u8 arg0) {
    s32 flags;

    flags = arg0;
    if (flags & 1) {
        func_801BED0C(D_80127CFC[D_80127D30[0]], D_802D3800);
    }
    if (flags & 2) {
        func_801BED0C(D_80127CFC[D_80127D31], D_802D3808);
    }
}
