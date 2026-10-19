/* DRAFT. Remaining diff: 46 differing words; 176/184 bytes */
typedef struct T024MaskedVoice { struct T024MaskedVoice *next; u8 pad[0x3A]; u8 flags; } T024MaskedVoice;
extern T024MaskedVoice *D_80048270;
extern s32 osSetIntMask(s32);
extern u8 *D_8004827C;
extern void alEvtqPostEvent(void *,void *,s32);
void func_8002F944(s32 mask) { struct { s16 type; T024MaskedVoice *voice; } event; T024MaskedVoice *p=D_80048270; s32 old; mask &= 0xFF; old=osSetIntMask(1); while(p) { event.type=0x400; event.voice=p; if(mask==(p->flags&mask)) { p->flags &= ~0x10; alEvtqPostEvent(D_8004827C+0x14,&event,0); } p=p->next; } osSetIntMask(old); }
