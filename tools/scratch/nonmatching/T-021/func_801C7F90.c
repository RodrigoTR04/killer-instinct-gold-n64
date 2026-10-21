#include "frontend.h"
/* DRAFT (T-044). Remaining diff: 16 relocation-masked instruction words; see T-044/REPORT.md. */
extern u8 D_80127CC1,D_80127CC2[];
extern void func_801C7E4C(u8);
extern void func_801C7F10();
void func_801C7F90(void) { s32 i; D_80127CC0.fields.first=D_80127CC1=0; for(i=0;i<32;) D_80127CC2[i++]=0; D_80127CC1=2; func_801C7E4C(0); func_801C7E4C(1); func_801C7F10(); }
