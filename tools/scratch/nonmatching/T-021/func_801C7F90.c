/* T-116 DRAFT: see T-116/REPORT.md for remaining instructions. */
#include "frontend.h"
extern u8 D_80127CC1,D_80127CC2[];
extern void func_801C7E4C(u8);
extern void func_801C7F10();
void func_801C7F90(void) {
 u8 *second = &D_80127CC1;
 s32 i;
 s32 zero = 0;
 D_80127CC0.bytes[0]=zero;
 *second=zero;
 for(i=0;
i<32;
i++) D_80127CC2[i]=0;
 *second=2;
 func_801C7E4C(0);
 func_801C7E4C(1);
 func_801C7F10();
 }
