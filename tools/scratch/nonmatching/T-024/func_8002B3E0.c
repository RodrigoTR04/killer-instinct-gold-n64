/* DRAFT. Remaining diff: 13 differing words; 280/280 bytes */
typedef struct T024DmaBuffer { struct T024DmaBuffer *next,*prev; u32 address,frame; void *buffer; } T024DmaBuffer;
typedef struct { u8 initialized; T024DmaBuffer *used,*free; } T024DmaPool;
extern T024DmaPool D_80068158;
extern u32 D_80048150,D_80048154;
extern u8 D_800683F8[];
extern s32 osRecvMesg(void *,void *,s32);
extern void alUnlink(void *),alLink(void *,void *);
void func_8002B3E0(void) { void *message; u32 i; T024DmaBuffer *p,*next; for(i=0;i<D_80048154;i++) osRecvMesg(D_800683F8,&message,0); p=D_80068158.used; while(p) { next=p->next; if(p->frame+1<D_80048150) { if(p==D_80068158.used) D_80068158.used=next; alUnlink(p); if(D_80068158.free) alLink(p,D_80068158.free); else { D_80068158.free=p; p->next=0; p->prev=0; } } p=next; } D_80048154=0; D_80048150++; }
