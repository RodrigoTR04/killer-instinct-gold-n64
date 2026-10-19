/* DRAFT. Remaining diff: 45 differing words; 192/188 bytes */
typedef struct { void *unused,*start; } T024SequenceEntry;
extern T024SequenceEntry *D_80066C28;
extern u16 D_8004814C,D_800669D0[];
extern void *D_80066A34,*D_800669C4;
extern u8 D_80066B30[];
extern s32 alCSPGetState(void *);
extern void alCSPStop(void *);
extern void alCSeqNew(void *,void *),alCSPSetSeq(void *,void *);
void func_8002A9DC(u16 index) { if(index != D_8004814C) { boot_dma(D_80066C28[index].start,D_80066A34,D_800669D0[index]); D_8004814C=index; } alCSPStop(D_800669C4); while(alCSPGetState(D_800669C4)!=0) {} alCSeqNew(D_80066B30,D_80066A34); alCSPSetSeq(D_800669C4,D_80066B30); }
