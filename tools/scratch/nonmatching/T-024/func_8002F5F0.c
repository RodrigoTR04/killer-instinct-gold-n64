/* DRAFT. Remaining diff: 50 differing words; 220/212 bytes */
typedef struct T024ReleasedVoice { struct T024ReleasedVoice *next,*prev; u8 pad[0x28]; struct T024ReleasedVoice **owner; u8 pad34[0xA]; u8 flags,state; } T024ReleasedVoice;
typedef struct { T024ReleasedVoice *head,*tail,*free; } T024ReleaseLists;
extern T024ReleaseLists D_80048270;
extern s16 D_80048280;
extern void alUnlink(void *);
void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
