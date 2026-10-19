/* DRAFT. Remaining diff: 16 linked differing words; 164/164 bytes. */
typedef struct { u8 pad[0x14]; u8 queue[0x14]; s16 eventType; u8 eventBody[0x22]; s32 interval,delta,time; } T024PlayerEvents;
extern void alEvtqPostEvent(void *,void *,s32);
extern s32 alEvtqNextEvent(void *,void *);
extern void func_8002E724(T024PlayerEvents *,void *);
void func_8002E680(T024PlayerEvents *p) { struct { s16 type; u8 data[14]; } event; s32 delta; do { if(p->eventType == 0x20) { event.type=0x20; alEvtqPostEvent(p->queue,&event,p->interval); } else func_8002E724(p,&p->eventType); delta=alEvtqNextEvent(p->queue,&p->eventType); p->delta=delta; } while(delta==0); p->time += delta; }
