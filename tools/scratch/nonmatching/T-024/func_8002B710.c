/* DRAFT. Remaining diff: 34 differing words; 180/196 bytes */
extern u8 D_800684E0[],D_8006851C[],D_800684B8[],D_800684BC,D_800684C2,D_800684C8,D_800684CE,D_80068520;
extern void *D_800684D0[];
extern void osContGetReadData(void *);
extern s32 osRecvMesg(void *,void *,s32);
void *func_8002B710(void) { osRecvMesg(D_800684E0,D_8006851C,1); osContGetReadData(D_800684B8); D_80068520=0; if(!D_800684BC) D_80068520=1; if(!D_800684C2) D_80068520|=2; if(!D_800684C8) D_80068520|=4; if(!D_800684CE) D_80068520|=8; return D_800684D0; }
