/* DRAFT. Remaining diff: 6 differing words; 192/192 bytes */
typedef struct T024EventItem { struct T024EventItem *next,*prev; s32 delta; u16 type; u16 pad; void *voice; } T024EventItem;
typedef struct { T024EventItem *free,*unused,*used; } T024EventQueue;
extern s32 osSetIntMask(s32);
extern void alUnlink(void *),alLink(void *,void *);
void func_8002F31C(void *queue,void *voice,u16 mask) { T024EventQueue *q=queue; T024EventItem *p,*next; s32 old=osSetIntMask(1); p=q->used; while(p) { next=p->next; if(voice==p->voice && (p->type&mask)) { if(next) next->delta+=p->delta; alUnlink(p); alLink(p,q); } p=next; } osSetIntMask(old); }
