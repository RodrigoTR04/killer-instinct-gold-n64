/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"
extern s32 osSetIntMask(s32);

GameAudioVoice *func_8002F45C(void *unused, ALSound *sound)
{
  GameAudioVoice *voice;
  ALKeyMap *savedKey;
  ALKeyMap *key;
  s32 old;
  s32 pan;
  u8 flags;
  voice = ((GameAudioVoiceLists *)&D_80048270)->free;
  savedKey = sound->keyMap;
  key = savedKey;
  if (voice)
  {
    old = osSetIntMask(1);
    ((GameAudioVoiceLists *)&D_80048270)->free = voice->next;
    alUnlink((ALLink *)voice);
    if (((GameAudioVoiceLists *)&D_80048270)->head)
    {
      voice->next = ((GameAudioVoiceLists *)&D_80048270)->head;
      voice->prev = 0;
      ((GameAudioVoiceLists *)&D_80048270)->head->prev = voice;
      ((GameAudioVoiceLists *)&D_80048270)->head = voice;
    }
    else
    {
      voice->prev = 0;
      voice->next = 0;
      ((GameAudioVoiceLists *)&D_80048270)->head = voice;
      ((GameAudioVoiceLists *)&D_80048270)->tail = voice;
    }
    osSetIntMask(old);
    pan = ((sound->envelope->decayTime + 1) == 0) + 0x40;
    voice->state = 5;
    voice->priority = pan;
    voice->retries = 2;
    voice->sound = sound;
    voice->pitch = 1.0f;
    flags = key->keyMax & 0xF0;
    voice->flags = flags;
    voice->owner = 0;
    if (voice->flags & 0x20)
    {
      voice->ratio = alCents2Ratio((key->keyBase * 100) - 6000);
    }
    else
    {
      voice->ratio = alCents2Ratio(((key->keyBase * 100) + key->detune) - 6000);
    }
    if (pan != 0x40)
    {
      voice->flags |= 2;
    }
    voice->fx = 0;
    voice->pan = 0x40;
    voice->volume = 0x7FFF;
  }
  return voice;
}
