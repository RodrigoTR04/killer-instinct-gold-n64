/* T-089 DRAFT: 18 -> 2 differing words in TU context. */
typedef struct {
 u8 next,delay,group,flags;
 }
 T024ChainKey;
 typedef struct {
 void *envelope;
 T024ChainKey *key;
 }
 T024ChainSound;
 typedef struct {
 u8 pad[0xC];
 T024ChainSound **sounds;
 }
 T024SoundBank;
 typedef struct {
 u8 pad[0x30];
 void **owner;
 u8 pad34[0xA];
 u8 flags;
 }
 T024ChainVoice;
 typedef struct {
 s16 type;
 T024ChainVoice *voice;
 s32 id;
 T024SoundBank *bank;
 }
 T024ChainEvent;
 extern T024ChainVoice *func_8002F45C(void *,void *);
 extern void alEvtqPostEvent(void *,void *,s32);

void *func_8002F6F4(T024SoundBank *bank, s16 id, void **owner)
{
  T024ChainVoice *voice;
  T024ChainSound *sound;
  s32 step;
  T024ChainVoice *last = 0;
  s16 repeat = 0;
  s32 repeatTime;
  T024ChainKey *key;
  s32 delay = 0;
  T024ChainEvent start;
  T024ChainEvent event;
  if (id == 0)
  {
    return 0;
  }
  do
  {
    sound = bank->sounds[id + 3];
    voice = func_8002F45C(bank, sound);
    if (voice)
    {
      *((void **) (((u8 *) D_8004827C) + 0x40)) = voice;
      start.type = 1;
      start.voice = voice;
      step = sound->key->delay * 0x8235;
      if (voice->flags & 0x10)
      {
        voice->flags &= 0xFFEF;
        alEvtqPostEvent(D_8004827C->queue, &start, delay + 1);
        repeatTime = step + 1;
        repeat = id;
      }
      else
      {
        alEvtqPostEvent(D_8004827C->queue, &start, step + 1);
      }
      last = voice;
    }
    delay += step;
    key = sound->key;
    id = key->next + ((key->group & 0xC0) * 4);
  }
  while (id && voice);
  if (last)
  {
    last->flags |= 1;
    last->owner = owner;
    if (repeat)
    {
      last->flags |= 0x10;
      event.type = 0x200;
      event.voice = last;
      event.bank = bank;
      event.id = repeat;
      alEvtqPostEvent(D_8004827C->queue, &event, repeatTime);
    }
  }
  if (owner)
  {
    *owner = last;
  }
  return last;
}
