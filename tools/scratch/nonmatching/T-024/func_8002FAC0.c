/* DRAFT. Remaining diff: 41 differing words; 168/180 bytes */
typedef struct { u8 pad[2]; u8 group; } T024GroupSound;
typedef struct { u8 pad[4]; T024GroupSound *sound; } T024GroupInstrument;
typedef struct T024GroupVoice { struct T024GroupVoice *next; u8 pad[4]; T024GroupInstrument *instrument; } T024GroupVoice;
extern T024GroupVoice *D_80048270;
extern u16 *D_80069928;
extern u8 *D_8004827C;
extern void alEvtqPostEvent(void *,void *,s32);
void func_8002FAC0(s32 group,s32 volume) { struct { s16 type; T024GroupVoice *voice; } event; T024GroupVoice *p=D_80048270; group &= 0xFF; D_80069928[group]=volume; while(p) { if(group==(p->instrument->sound->group&0x3F)) { event.type=0x800; event.voice=p; alEvtqPostEvent(D_8004827C+0x14,&event,0); } p=p->next; } }
