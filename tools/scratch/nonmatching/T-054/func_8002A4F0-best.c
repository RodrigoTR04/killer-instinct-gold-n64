extern void boot_dma(s32,s32,s32);

/* DRAFT. Remaining diff: 155 differing words; 916/920 bytes */
typedef struct { s32 voices,physical,updates,fx; void *dma,*heap; s32 rate; u8 type,pad[3]; void *params; } T024InitSynth;
typedef struct { s32 voices,events; u8 channels,pad[3]; void *heap; s32 init,osc,oscUpdate; } T024SeqConfig;
typedef struct { s32 voices,events,priority; void *heap; s16 groups; } T024SfxConfig;
typedef struct { s16 revision,count; void *bank; } T024BankFile;
typedef struct { u8 *offset; s32 length; } T024SeqEntry;
typedef struct { s16 revision,count; T024SeqEntry entries[1]; } T024SeqFile;
extern u8 D_80066C30[],D_80128350[],D_8F9FA0[],D_907580[],D_9AF4B0[],D_9B9AD0[],D_992AF0[];
extern void *D_80066C40,*D_800669C0,*D_800669C4,*D_80066A30,*D_80066A34;
extern T024SeqFile *D_80066C28;
extern u16 D_800669D0[];
extern void alHeapInit(void *,void *,s32),alBnkfNew(void *,void *),alSeqFileNew(void *,void *),alCSPNew(void *,void *),alCSPSetBank(void *,void *),func_8002AB90(void *,s32,void *),func_8002E4A0(void *);
extern void *alHeapDBAlloc(s32,s32,void *,s32,s32);
void func_8002A4F0(void) { T024SfxConfig sfx; T024BankFile *bank,*effects; T024InitSynth synth; T024SeqConfig music,secondary; s32 settings[3],size,i,length; alHeapInit(D_80066C30,D_80128350,0x4A380); synth.voices=44; synth.physical=22; synth.updates=50; synth.fx=1; synth.dma=0; synth.type=6; synth.rate=0; synth.heap=D_80066C30; settings[0]=0x5622; settings[1]=1; settings[2]=0x1000; func_8002AB90(&synth,12,settings); size=D_907580-D_8F9FA0; bank=alHeapDBAlloc(0,0,D_80066C30,1,size); boot_dma((s32)D_8F9FA0,(s32)bank,size); alBnkfNew(bank,D_907580); size=D_9B9AD0-D_9AF4B0; effects=alHeapDBAlloc(0,0,D_80066C30,1,size); boot_dma((s32)D_9AF4B0,(s32)effects,size); alBnkfNew(effects,D_9B9AD0); D_80066C40=effects->bank; D_80066C28=alHeapDBAlloc(0,0,D_80066C30,1,4); boot_dma((s32)D_992AF0,(s32)D_80066C28,4); size=D_80066C28->count*8+4; D_80066C28=alHeapDBAlloc(0,0,D_80066C30,1,size); boot_dma((s32)D_992AF0,(s32)D_80066C28,size); alSeqFileNew(D_80066C28,D_992AF0); D_80066A30=alHeapDBAlloc(0,0,D_80066C30,1,15000); for(i=0;i<48;i++) { length=D_80066C28->entries[i].length&0xFFFF; D_800669D0[i]=length; if(length&1) D_800669D0[i]=length+1; } music.voices=44; music.events=50; music.channels=16; music.heap=D_80066C30; music.init=0; music.osc=0; music.oscUpdate=0; D_800669C0=alHeapDBAlloc(0,0,D_80066C30,1,124); alCSPNew(D_800669C0,&music); alCSPSetBank(D_800669C0,bank->bank); func_8002A900(17); sfx.events=64; sfx.voices=64; sfx.priority=6; sfx.groups=8; sfx.heap=D_80066C30; func_8002E4A0(&sfx); D_80066A34=alHeapDBAlloc(0,0,D_80066C30,1,15000); secondary.voices=44; secondary.events=50; secondary.channels=16; secondary.heap=D_80066C30; secondary.init=0; secondary.osc=0; secondary.oscUpdate=0; D_800669C4=alHeapDBAlloc(0,0,D_80066C30,1,124); alCSPNew(D_800669C4,&secondary); alCSPSetBank(D_800669C4,bank->bank); }
