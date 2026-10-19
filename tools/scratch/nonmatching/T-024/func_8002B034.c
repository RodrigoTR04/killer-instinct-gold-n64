/* DRAFT. Remaining diff: 30 differing words; 440/440 bytes */
typedef struct { void *buffer; s16 samples; u8 pad6[2]; s32 state; u8 padC[8]; s32 type; u8 pad18[8]; s32 taskType,flags; void *boot; u32 bootSize; void *code; u8 pad34[4]; void *data; u32 dataSize; u8 pad40[0x10]; void *commands; u32 commandSize; s32 yield; u32 yieldSize; void *queue,*message; u8 body[8]; } T024AudioTask;
extern void func_8002B3E0(void);
extern u32 osVirtualToPhysical(void *),osAiGetLength(void);
extern void osAiSetNextBuffer(void *,u32),osWritebackDCacheAll(void);
extern s32 func_80039C08(void *,s32 *,u32,s16),osSendMesg(void *,void *,s32);
extern s32 D_80048158,D_80068168;
extern u32 D_80068164;
extern u8 D_80042710[],D_800427E0[],D_80043BF0[],D_80049F70[],D_80066E50[],D_8000CF68[];
extern u8 *D_80066C50[];
s32 func_8002B034(T024AudioTask *task,T024AudioTask *previous) { u32 physical; s32 count; u8 *end; func_8002B3E0(); physical=osVirtualToPhysical(task->buffer); if(previous) osAiSetNextBuffer(previous->buffer,previous->samples*4); task->samples=(D_80068168-(osAiGetLength()>>2)+0x60)&0xFFF0; if((u32)task->samples<D_80068164) task->samples=D_80068164; end=(u8 *)func_80039C08(D_80066C50[D_80048158],&count,physical,task->samples); if(count==0) return 0; task->state=0; task->queue=D_80066E50; task->message=task->body; task->type=2; task->commands=D_80066C50[D_80048158]; task->commandSize=((end-D_80066C50[D_80048158])>>3)*8; task->taskType=2; task->boot=D_80042710; task->bootSize=D_800427E0-D_80042710; task->flags=2; task->code=D_80043BF0; task->data=D_80049F70; task->dataSize=0x800; task->yield=0; task->yieldSize=0x400; osWritebackDCacheAll(); osSendMesg(D_8000CF68,&task->state,1); D_80048158^=1; return 1; }
