/* DRAFT. Remaining diff: 27 differing words; 172/172 bytes */
extern s32 D_80065C80[],D_80066188[],D_800665A0[];
extern u8 D_80066080[];
void func_8002A254(void) { s32 i,bit; s32 *next=D_80065C80; u8 *value=D_80066080; for(i=0;i<256;i++) { value[1]=i; *next++=i+1; value++; } for(i=0;i<258;i++) { D_800665A0[i]=1; for(bit=0;bit<8;bit++) if((1<<bit)&i) break; D_80066188[i]=1<<bit; } D_80066188[0]=257; D_800665A0[0]=0; }
