/* DRAFT. Remaining diff: 2 differing words; 76/76 bytes */
typedef struct { u8 pad[0x3E]; u8 flags; } T024VoiceFlags;
typedef struct { s16 type; T024VoiceFlags *voice; s32 unused[2]; } T024StopEvent;
extern u8 *D_8004827C;
extern void alEvtqPostEvent(void *,void *,s32);
void func_8002F8F8(T024VoiceFlags *voice) { T024StopEvent event; event.type=0x400; event.voice=voice; if (voice) { voice->flags &= 0xFFEF; alEvtqPostEvent(D_8004827C+0x14,&event,0); } }
