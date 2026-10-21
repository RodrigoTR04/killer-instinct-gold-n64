/* T-099 DRAFT: 4 relocation-masked differing words; target-sized. See T-099/REPORT.md. */
typedef struct { s32 pad;
 s32 loop;
 } T024Envelope;

typedef struct { u8 next,delay,group,flags;
 u8 key;
 s8 detune;
 } T024KeyMap;

typedef struct { T024Envelope *envelope;
 T024KeyMap *key;
 } T024SoundDef;

typedef struct T024AllocatedVoice { struct T024AllocatedVoice *next,*prev;
 T024SoundDef *sound;
 u8 pad[0x1C];
 float ratio,pitch;
 void *owner;
 s16 volume;
 u8 pan,pad37;
 s32 state;
 u8 priority,fx,flags,status;
 } T024AllocatedVoice;

typedef struct { T024AllocatedVoice *head,*tail,*free;
 } T024AllocationLists;



extern s32 osSetIntMask(s32);

extern void alUnlink(void *);

extern float alCents2Ratio(s32);

T024AllocatedVoice *func_8002F45C(void *unused, T024SoundDef *sound)
{
  T024AllocatedVoice *voice;
  T024KeyMap *savedKey;
  T024KeyMap *key;
  s32 old;
  s32 pan;
  u8 flags;
  voice = ((T024AllocationLists *)&D_80048270)->free;
  savedKey = sound->key;
  key = savedKey;
  if (voice)
  {
    old = osSetIntMask(1);
    ((T024AllocationLists *)&D_80048270)->free = voice->next;
    alUnlink(voice);
    if (((T024AllocationLists *)&D_80048270)->head)
    {
      voice->next = ((T024AllocationLists *)&D_80048270)->head;
      voice->prev = 0;
      ((T024AllocationLists *)&D_80048270)->head->prev = voice;
      ((T024AllocationLists *)&D_80048270)->head = voice;
    }
    else
    {
      voice->prev = 0;
      voice->next = 0;
      ((T024AllocationLists *)&D_80048270)->head = voice;
      ((T024AllocationLists *)&D_80048270)->tail = voice;
    }
    osSetIntMask(old);
    pan = ((sound->envelope->loop + 1) == 0) + 0x40;
    voice->status = 5;
    voice->pan = pan;
    voice->state = 2;
    voice->sound = sound;
    voice->pitch = 1.0f;
    flags = key->flags & 0xF0;
    voice->flags = flags;
    voice->owner = 0;
    if (voice->flags & 0x20)
    {
      voice->ratio = alCents2Ratio((key->key * 100) - 6000);
    }
    else
    {
      voice->ratio = alCents2Ratio(((key->key * 100) + key->detune) - 6000);
    }
    if (pan != 0x40)
    {
      voice->flags |= 2;
    }
    voice->fx = 0;
    voice->priority = 0x40;
    voice->volume = 0x7FFF;
  }
  return voice;
}
