/* DRAFT. Remaining diff: 14 differing words; 220/220 bytes */
typedef struct { u8 pad[4]; u8 size[4]; u8 data[1]; } T024CompressedHeader;
extern void func_8002A254(void),func_8002A1E0(void),func_80032750(void *);
extern s8 func_800327E8(void *,void *,void *,void *);
extern u8 D_80066188[],D_800665A0[],D_80066080[],D_80065C80[];
void func_8002A40C(T024CompressedHeader *header,s8 *out) { s32 size=header->size[3]+(header->size[0]<<24)+(header->size[1]<<16)+(header->size[2]<<8); s32 i; func_8002A254(); func_80032750(header->data); func_8002A1E0(); for(i=0;i<size;i++) *out++=func_800327E8(D_80066188,D_800665A0,D_80066080,D_80065C80); }
