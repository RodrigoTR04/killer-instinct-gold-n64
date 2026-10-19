/* DRAFT. Remaining diff: 21 differing words; 100/108 bytes */
typedef struct { u8 pad[5]; s8 detune; } T024Sound;
typedef struct { u8 pad[4]; T024Sound *sound; } T024Instrument;
typedef struct { u8 pad[8]; T024Instrument *instrument; u8 padC[0x20]; float pitch; } T024PitchVoice;
typedef struct { s16 type; T024PitchVoice *voice; float pitch; } T024PitchEvent;
extern float alCents2Ratio(s32);
extern u8 *D_8004827C;
extern void alEvtqPostEvent(void *,void *,s32);
void func_8002F2B0(T024PitchVoice *voice) { T024PitchEvent event; float pitch; pitch=alCents2Ratio(voice->instrument->sound->detune); event.type=0x10; event.voice=voice; pitch *= voice->pitch; event.pitch=pitch; alEvtqPostEvent(D_8004827C+0x14,&event,0x8235); }
