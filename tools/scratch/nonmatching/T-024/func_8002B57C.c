/* T-052 DRAFT: 4 relocation-masked positional words differ; 368/368 bytes. */
typedef struct { u16 type; u8 status,error; } T052ContStatus;
extern T052ContStatus D_800684A8[4]; extern u8 D_80068518,D_80068520,D_800684E0[]; extern s32 D_800684A0;
extern s32 osContInit(void *,u8 *,void *);
void func_8002B57C(void) { s32 i; while(osContInit(D_800684E0,&D_80068518,D_800684A8)) {} D_800684A0=0; for(i=0;i<4;i++) if((D_80068518&(1<<i)) && !(D_800684A8[i].error&8)) { D_80068520|=1<<i; D_800684A0++; } }