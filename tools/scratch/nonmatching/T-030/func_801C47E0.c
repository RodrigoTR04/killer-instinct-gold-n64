/* T-105: nonmatching draft; see T-105/REPORT.md for measurement and remaining differences. */
#include "common.h"

extern void func_8001CD50(void);
extern s32 func_800216D4(s32, s32, void *, u16);
extern u8 D_8004EA9C, D_8004EA9E, D_802D3970;

s32 func_801C47E0(u8 arg0, u8 arg1, u8 *arg2, u16 arg3) {
    s32 offset;
    u8 oldC;
    u8 oldE;
    s32 bank;


    bank = arg0;
    oldC = D_8004EA9C;
    oldE = D_8004EA9E;
    D_802D3970 = arg1;
    D_8004EA9C = bank & 0x7F;
    D_8004EA9E = arg1;
    func_8001CD50();
    osUnmapTLB(0);
    offset = (0x1000 - (u32)arg2) & 0xFFF;
    osMapTLB(0, 0, 0, ((u32)arg2 + offset) & 0x07FFFFFF, -1, -1);
    offset += 0x20;
    offset = (offset + func_800216D4(0, bank, arg2 + offset, arg3) + 7) & ~7;
    D_8004EA9C = oldC;
    D_8004EA9E = oldE;
    return offset;
}
