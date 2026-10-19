/* DRAFT. Remaining diff: 10 differing words; 316/316 bytes */
extern u8 D_80044A24;
extern float D_800695CC,D_800695D0,D_800695D4,D_800695D8,D_800695DC,D_800695E0;
extern float D_80069740[][4][4],D_80069840[][4][4],D_800697C0[][4][4],D_80069600[][4][4],D_80069680[][4][4];
extern void guRotateRPYF(void *,float,float,float),guTranslateF(void *,float,float,float),guMtxCatF(void *,void *,void *);
void func_8002B9B4(void) { guRotateRPYF(D_80069740[D_80044A24],D_800695D8,0.0f,0.0f); guRotateRPYF(D_80069840[D_80044A24],0.0f,D_800695DC,D_800695E0); guTranslateF(D_800697C0[D_80044A24],0.0f-D_800695CC,0.0f-D_800695D0,0.0f-D_800695D4); guMtxCatF(D_800697C0[D_80044A24],D_80069840[D_80044A24],D_80069600[D_80044A24]); guMtxCatF(D_80069600[D_80044A24],D_80069740[D_80044A24],D_80069680[D_80044A24]); }
