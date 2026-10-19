/* DRAFT. Remaining diff: 409 positional words differ; 1492/1652 bytes */
typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite24C;
typedef struct { s16 halfW,halfH,w,h; } T032Size24C;
extern T032Sprite24C D_8004CED0[];
extern u8 *D_8004CED4[];
extern u8 *D_800612D8[];
extern T032Size24C D_80061368[];
extern u8 D_80047BF0[],D_80047C38[],D_8F6AE0[],D_8F9FA0[];
extern u8 D_8004F3A0[],D_8004FE40[],D_800508E0[],D_80051D80[],D_80053220[],D_80053748[],D_80053C70[],D_80054198[],D_80054458[],D_80058478[],D_800587B8[],D_80058D58[],D_800590B8[],D_80059668[],D_80059CF8[],D_8005A388[],D_8005AEC8[],D_8005AFB8[],D_8005E3F8[];
extern s8 D_80061496;
extern s32 D_8004EA78;
extern void boot_dma(void *,void *,s32),func_800238C4(u8 *,void *),func_800268C0(u8 *,s32,void *,u8);
extern s32 boot_inflate(void *,void *,void *);
#define T032_LE24C(p) ((p)[0]+((p)[1]<<8)+((p)[2]<<16)+((p)[3]<<24))
#define T032_BE24C(p) ((p)[3]+((p)[0]<<24)+((p)[1]<<16)+((p)[2]<<8))
void func_80024CE0(void) {
    u8 *input=(u8 *)0x802D4000,*output,*base,*pack,*p;
    s32 size=D_8F9FA0-D_8F6AE0,i;
    u8 slot;
    D_80061496=0;
    boot_dma(D_8F6AE0,input,size);
    base=input+size; output=base;
    for (i=0;i<6;i++) {
        output+=boot_inflate(input+4,output,(void *)0x803A2000);
        input+=T032_BE24C(input);
    }
    D_8004EA78=4; D_8004CED0[4].pixels=(u16 *)D_800508E0; D_8004CED0[4].alpha=D_8004F3A0;
    func_800238C4(base+T032_LE24C(base+8),D_80047C38);
    D_8004EA78=5; D_8004CED0[5].pixels=(u16 *)D_80051D80; D_8004CED0[5].alpha=D_8004FE40;
    func_800238C4(base+T032_LE24C(base+12),D_80047C38);
    D_8004EA78=12; pack=base+T032_LE24C(base+4);
    D_8004CED4[12*7]=base;
    for (i=0;(u32)&D_800612D8[i]<(u32)D_80061368;i++) {
        D_80061368[i].halfW=0; D_80061368[i].halfH=0;
        D_80061368[i].w=16; D_80061368[i].h=1; D_800612D8[i]=D_80054458;
    }
    for (i=0;i<26;i++) {
        slot=D_80047BF0[i];
        if (slot || i==0) func_800268C0(pack,i,D_80054458+slot*0x360,slot);
    }
    pack+=T032_LE24C(pack+4); p=D_8005A388;
    for (i=0;i<10;i++,p+=0x120) func_800268C0(pack,i,p,i+19);
    func_800268C0(pack,10,D_80058478,29); func_800268C0(pack,11,D_8005AEC8,30);
    pack+=T032_LE24C(pack+4);
    func_800268C0(pack,0,D_800587B8,31); func_800268C0(pack,1,D_80058D58,32);
    func_800268C0(pack,2,D_800590B8,33); func_800268C0(pack,4,D_80059668,34); func_800268C0(pack,5,D_80059CF8,35);
    pack+=T032_LE24C(pack+4);
    D_8004EA78=12; D_8004CED0[12].pixels=(u16 *)D_80053220; D_8004CED0[12].alpha=D_80054198;
    func_800238C4(pack+T032_LE24C(pack+8),D_80047C38);
    D_8004EA78=13; D_8004CED0[13].pixels=(u16 *)D_80053748; D_8004CED0[13].alpha=D_80054198;
    func_800238C4(pack+T032_LE24C(pack+12),D_80047C38);
    D_8004EA78=14; D_8004CED0[14].pixels=(u16 *)D_80053C70; D_8004CED0[14].alpha=D_80054198;
    func_800238C4(pack+T032_LE24C(pack+16),D_80047C38);
    pack+=T032_LE24C(pack+4);
    D_8004EA78=30; D_8004CED0[30].pixels=(u16 *)D_8005E3F8; D_8004CED0[30].alpha=0;
    func_800238C4(pack+T032_LE24C(pack+28),D_80047C38);
    D_8004EA78=29; D_8004CED0[29].pixels=(u16 *)D_8005AFB8; D_8004CED0[29].alpha=0;
    func_800238C4(pack+T032_LE24C(pack+8),D_80047C38);
}
#undef T032_LE24C
#undef T032_BE24C
