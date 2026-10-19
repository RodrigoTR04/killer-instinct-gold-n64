/* DRAFT. Remaining diff: 115 differing words; 428/480 bytes */
typedef struct { u32 voices,events; s32 priority; void *heap; u16 groups; } T024AudioConfig;
typedef struct { void *next,*client,*handler; u8 padC[8]; u8 queue[0x14],event[0x10]; void *synth; u8 pad3C[4]; void *current,*voices; s32 priority,interval,delta,time; } T024AudioPlayer;
extern u8 *D_8004827C;
extern void *D_80048278,*D_80048440;
extern u16 *D_80069928;
extern void *alHeapDBAlloc(s32,s32,void *,s32,s32);
extern void alEvtqNew(void *,void *,s32),alLink(void *,void *),alSynAddPlayer(void *,void *),func_8002E680(void *);
extern void alEvtqPostEvent(void *,void *,s32);
extern s32 alEvtqNextEvent(void *,void *);
void func_8002E4A0(T024AudioConfig *config) { T024AudioPlayer *p=(T024AudioPlayer *)D_8004827C; u32 i; s16 event; p->priority=config->priority; p->current=0; p->interval=0x80E8; p->voices=alHeapDBAlloc(0,0,config->heap,1,config->voices<<6); alEvtqNew(p->queue,alHeapDBAlloc(0,0,config->heap,1,config->events*0x1C),config->events); D_80048278=p->voices; for(i=1;i<config->voices;i++) alLink((u8 *)p->voices+(i<<6),(u8 *)p->voices+((i-1)<<6)); D_80069928=alHeapDBAlloc(0,0,config->heap,2,config->groups); for(i=0;i<config->groups;i++) D_80069928[i]=0x7FFF; p->synth=D_80048440; p->next=0; p->handler=func_8002E680; p->client=p; alSynAddPlayer(p->synth,p); event=0x20; alEvtqPostEvent(p->queue,&event,p->interval); p->delta=alEvtqNextEvent(p->queue,p->event); }
