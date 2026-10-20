/* T-052 DRAFT: 24 relocation-masked positional words differ; 220/220 bytes. */
typedef struct { void *unused,*start; } T024MusicEntry;
extern T024MusicEntry *D_80066C28;
extern u16 D_80048148,D_800669D0[];
extern void *D_80066A30,*D_800669C0;
extern u8 D_80066A38[];
extern s32 alCSPGetState(void *);
extern void alCSPStop(void *),alCSPPlay(void *);
extern void alCSeqNew(void *,void *),alCSPSetSeq(void *,void *);
void func_8002A900(s32 index) { u32 count=0;  if(index != D_80048148) { boot_dma(D_80066C28[index].start,D_80066A30,D_800669D0[index]); D_80048148=index; } alCSPStop(D_800669C0); if(alCSPGetState(D_800669C0)!=0) { do { count++; } while(alCSPGetState(D_800669C0)!=0 && count<0x3D0900); } alCSeqNew(D_80066A38,D_80066A30); alCSPSetSeq(D_800669C0,D_80066A38); }
