/* T-085 DRAFT: 115 -> 33 differing words in owning TU; 480/480 bytes. */
typedef struct { u32 voices,events; s32 priority; void *heap; u16 groups; } T024AudioConfig;
typedef struct { void *next,*client,*handler; u8 padC[8]; u8 queue[0x14],event[0x10]; void *synth; u8 pad3C[4]; void *current,*voices; s32 priority,interval,delta,time; } T024AudioPlayer;
extern T024AudioPlayer *D_8004827C;
extern void *D_80048278,*D_80048440;
extern u16 *D_80069928;
extern void *alHeapDBAlloc(s32,s32,void *,s32,s32);
extern void alEvtqNew(void *,void *,s32),alLink(void *,void *),alSynAddPlayer(void *,void *),func_8002E680(void *);
extern void alEvtqPostEvent(void *,void *,s32);
extern s32 alEvtqNextEvent(void *,void *);
void func_8002E4A0(T024AudioConfig *config) { u32 i; T024AudioPlayer *p; u8 *voice; struct { s16 type; u8 data[14]; } event; D_8004827C->priority=config->priority; D_8004827C->current=0; D_8004827C->interval=0x80E8; D_8004827C->voices=alHeapDBAlloc(0,0,config->heap,1,config->voices<<6); alEvtqNew(D_8004827C->queue,alHeapDBAlloc(0,0,config->heap,1,config->events*0x1C),config->events); D_80048278=D_8004827C->voices; for(i=1;i<config->voices;i++) { voice=(u8 *)D_8004827C->voices+(i<<6); alLink(voice,voice-64); } D_80069928=alHeapDBAlloc(0,0,config->heap,2,config->groups); for(i=0;i<config->groups;i++) D_80069928[i]=0x7FFF; D_8004827C->synth=D_80048440; D_8004827C->next=0; D_8004827C->handler=func_8002E680; D_8004827C->client=D_8004827C; alSynAddPlayer(D_8004827C->synth,D_8004827C); event.type=0x20; alEvtqPostEvent(D_8004827C->queue,&event,D_8004827C->interval); D_8004827C->delta=alEvtqNextEvent(D_8004827C->queue,D_8004827C->event); }
