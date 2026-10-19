/* DRAFT. Remaining diff: Clear-loop store order and global-address register allocation/scheduling differ. */
extern u8 D_80127CC0,D_80127CC1,D_80127CC2[];
extern void func_801C7E4C(u8);
extern void func_801C7F10();
void func_801C7F90(void) { s32 i; D_80127CC0=0; D_80127CC1=0; for(i=0;i<32;) D_80127CC2[i++]=0; D_80127CC1=2; func_801C7E4C(0); func_801C7E4C(1); func_801C7F10(); }