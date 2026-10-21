/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"
extern s32 osSetIntMask(s32);

GameAudioVoice *func_8002F6F4(ALBank *bank, s16 id, GameAudioVoice **owner)
{
  GameAudioVoice *voice;
  ALSound *sound;
  s32 step;
  GameAudioVoice *last = 0;
  s16 repeat = 0;
  s32 repeatTime;
  ALKeyMap *key;
  s32 delay = 0;
  GameAudioEvent start;
  GameAudioEvent event;
  if (id == 0)
  {
    return 0;
  }
  do
  {
    sound = bank->instArray[0]->soundArray[id - 1];
    voice = func_8002F45C(bank, sound);
    if (voice)
    {
      D_8004827C->current = voice;
      start.type = 1;
      start.voice = voice;
      step = sound->keyMap->velocityMax * 0x8235;
      if (voice->flags & 0x10)
      {
        voice->flags &= 0xFFEF;
        alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&start, delay + 1);
        repeatTime = step + 1;
        repeat = id;
      }
      else
      {
        alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&start, step + 1);
      }
      last = voice;
    }
    delay += step;
    key = sound->keyMap;
    id = key->velocityMin + ((key->keyMin & 0xC0) * 4);
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
      event.payload.value = repeat;
      alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, repeatTime);
    }
  }
  if (owner)
  {
    *owner = last;
  }
  return last;
}
