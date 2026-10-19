/* DRAFT. Remaining diff: 30 differing words; 516/516 bytes */
typedef struct { u8 next,delay,group,flags; } T024ChainKey;
typedef struct { void *envelope; T024ChainKey *key; } T024ChainSound;
typedef struct { u8 pad[0xC]; T024ChainSound **sounds; } T024SoundBank;
typedef struct { u8 pad[0x30]; void **owner; u8 pad34[0xA]; u8 flags; } T024ChainVoice;
typedef struct { s16 type; T024ChainVoice *voice; s32 id; T024SoundBank *bank; } T024ChainEvent;
extern u8 *D_8004827C;
extern T024ChainVoice *func_8002F45C(void *,void *);
extern void alEvtqPostEvent(void *,void *,s32);
void *func_8002F6F4(T024SoundBank *bank,s16 id,void **owner) { s16 repeat=0; s32 delay=0,step,repeatTime; T024ChainVoice *last=0,*voice; T024ChainSound *sound; T024ChainEvent start,event; if(id==0) return 0; do { sound=bank->sounds[id+3]; voice=func_8002F45C(bank,sound); if(voice) { *(void **)(D_8004827C+0x40)=voice; start.type=1; start.voice=voice; step=sound->key->delay*0x8235; if(voice->flags&0x10) { voice->flags&=0xFFEF; alEvtqPostEvent(D_8004827C+0x14,&start,delay+1); repeatTime=step+1; repeat=id; } else alEvtqPostEvent(D_8004827C+0x14,&start,step+1); last=voice; } delay+=step; id=sound->key->next+((sound->key->group&0xC0)*4); } while(id && voice); if(last) { last->flags|=1; last->owner=owner; if(repeat) { last->flags|=0x10; event.type=0x200; event.voice=last; event.bank=bank; event.id=repeat; alEvtqPostEvent(D_8004827C+0x14,&event,repeatTime); } } if(owner) *owner=last; return last; }
