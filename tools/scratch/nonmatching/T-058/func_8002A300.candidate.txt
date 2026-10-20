/* T-052 DRAFT: 7 relocation-masked positional words differ; 268/268 bytes. */
extern void func_8002A254(void),func_8002A1E0(void),func_80032750(void *);
extern s8 func_800327E8(void *,void *,void *,void *);
extern u8 D_80066188[],D_800665A0[],D_80066080[],D_80065C80[];
void func_8002A300(void *data,s8 *out,s32 count) { s32 i; s32 value=0,delta,runLength; func_8002A254(); func_80032750(data); func_8002A1E0(); for(i=0;i<count;i++) { delta=func_800327E8(D_80066188,D_800665A0,D_80066080,D_80065C80); if(delta==0) { runLength=func_800327E8(D_80066188,D_800665A0,D_80066080,D_80065C80); i+=runLength; if(runLength>=0) do { runLength--; *out++=value; } while(runLength>=0); } else { value-=delta; *out++=value; } } }
