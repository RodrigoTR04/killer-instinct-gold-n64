/* DRAFT. Remaining diff: 3 linked differing words; 128/128 bytes. */
typedef struct T024Link { struct T024Link *next; struct T024Link *previous; } T024Link;
typedef struct { T024Link *free,*active,*allocated; } T024VoiceLists;
extern T024VoiceLists D_80048270;
s32 func_8002F3DC(s16 *allocated,s16 *freeCount) { T024Link *p=D_80048270.free,*q=D_80048270.allocated,*r=D_80048270.active; u16 n,m,k; n=0; while(p) { p=p->next; n++; } m=0; while(q) { q=q->next; m++; } k=0; while(r) { r=r->previous; k++; } *allocated=m; *freeCount=n; return k; }
