/* DRAFT. Remaining diff: 210 differing words; 816/852 bytes */
typedef struct { s32 voices,physical,updates,fx; void *dma,*heap; s32 rate; u8 type,pad[3]; void *params; } T024SynthConfig;
typedef struct { s32 rate,frames,commands; } T024AudioSettings;
typedef struct T024DmaInit { struct T024DmaInit *next,*prev; u32 address,frame; void *buffer; } T024DmaInit;
typedef struct { void *buffer; u8 pad[0x64]; s32 type; void *self; u8 tail[0x18]; } T024AudioFrame;
extern u8 D_8004815C[],D_80066E88[],D_80066E50[],D_80066E68[],D_80066E18[],D_80066E30[],D_800683F8[],D_80068410[],D_80066C68[];
extern T024DmaInit D_80067ED8[];
extern void *D_80066C50[];
extern s32 D_80068164,D_80068168,D_8006816C,D_80068170;
extern void func_8002AEE4(s32),func_8002B3A8(void);
extern s32 osAiSetFrequency(s32);
extern void alInit(void *,void *),alLink(void *,void *),osStartThread(void *),osCreateThread(void *,s32,void *,s32,void *,s32);
extern void *alHeapDBAlloc(s32,s32,void *,s32,s32);
void func_8002AB90(T024SynthConfig *config,s32 priority,T024AudioSettings *settings) { typedef struct { u32 words[66]; } T024Parameters; T024Parameters parameters; s32 n; float exact; u32 i; T024AudioFrame *frame; config->dma=func_8002B3A8; config->rate=osAiSetFrequency(settings->rate); exact=(float)settings->frames*(float)config->rate/60.0f; n=exact; D_80068168=n; if((float)n<exact) D_80068168=++n; if(n&15) { n=(n&~15)+16; D_80068168=n; } D_80068164=n-16; D_8006816C=n+96; if(config->type==6) { parameters=*(T024Parameters *)D_8004815C; config->params=&parameters; alInit(D_80066E88,config); } else alInit(D_80066E88,config); D_80067ED8[0].prev=0; D_80067ED8[0].next=0; for(i=0;i<31;i++) { alLink(&D_80067ED8[i+1],&D_80067ED8[i]); D_80067ED8[i].buffer=alHeapDBAlloc(0,0,config->heap,1,0x800); } D_80067ED8[31].buffer=alHeapDBAlloc(0,0,config->heap,1,0x800); for(i=0;i<2;i++) D_80066C50[i]=alHeapDBAlloc(0,0,config->heap,1,settings->commands*8); D_80068170=settings->commands; for(i=0;i<3;i++) { frame=alHeapDBAlloc(0,0,config->heap,1,0x88); D_80066C50[i+2]=frame; frame->type=2; frame->self=frame; frame->buffer=alHeapDBAlloc(0,0,config->heap,1,D_8006816C*4); } osCreateMesgQueue(D_80066E50,D_80066E68,8); osCreateMesgQueue(D_80066E18,D_80066E30,8); osCreateMesgQueue(D_800683F8,D_80068410,32); osCreateThread(D_80066C68,4,func_8002AEE4,0,D_80067ED8,priority); osStartThread(D_80066C68); }
