/* DRAFT. Remaining diff: 18 differing words; 264/264 bytes */
extern u8 D_800614D0,D_80061CD4,D_80061CD5;
extern s16 D_80061CD6;
extern float D_80061528,D_8006152C,D_80061530,D_80061CC8[];
extern void func_8002970C(s32,s32);
s32 func_80028600(s32 count,float scaleX,float scaleY,s32 mode) { float *p; s32 i,j; D_800614D0=count; D_80061528=205.0f/scaleX; D_80061530=205.0f/scaleY; D_8006152C=D_80061528*14.0f; D_80061CD4=mode; D_80061CD5=1; D_80061CD6=1; p=D_80061CC8; do { *p++=0.0f; } while((u32)p<(u32)&D_80061CD4); for(i=0;i<D_800614D0;i++) for(j=0;j<20;j++) func_8002970C(i,j); }
