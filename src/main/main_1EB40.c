#include "audio_game.h"

void func_8002E4A0(GameAudioConfig *config)
{
  u32 i;
  u8 *voice;
  struct
  {
    s16 type;
    u8 data[14];
  } event;
  D_8004827C->maxVoices = config->maxVoices;
  D_8004827C->current = 0;
  D_8004827C->interval = 0x80E8;
  D_8004827C->voices = alHeapDBAlloc(0, 0, config->heap, 1, config->voices << 6);
  alEvtqNew(&D_8004827C->queue, alHeapDBAlloc(0, 0, config->heap, 1, config->events * 0x1C), config->events);
  D_80048278 = D_8004827C->voices;
  for (i = 1; i < config->voices; i++)
  {
    voice = (u8 *) D_8004827C->voices;
    alLink((ALLink *)&voice[i << 6], (ALLink *)((&voice[i << 6]) - 64));
  }

  D_80069928 = alHeapDBAlloc(0, 0, config->heap, 2, config->groups);
  for (i = 0; i < config->groups; i++)
  {
    D_80069928[i] = 0x7FFF;
  }

  D_8004827C->synth = D_80048440;
  D_8004827C->node.next = 0;
  D_8004827C->node.handler = (ALVoiceHandler)func_8002E680;
  D_8004827C->node.clientData = D_8004827C;
  alSynAddPlayer(D_8004827C->synth, &D_8004827C->node);
  event.type = 0x20;
  alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, D_8004827C->interval);
  D_8004827C->delta = alEvtqNextEvent(&D_8004827C->queue, (ALEvent *)&D_8004827C->event);
}

ALMicroTime func_8002E680(GameAudioPlayer *p) {
    GameAudioEvent *next = &p->event;
    GameAudioTickEvent event;
    s32 delta;

    do {
        if (p->event.type == 0x20) {
            event.type = 0x20;
            alEvtqPostEvent(&p->queue, (ALEvent *)&event, p->interval);
        } else {
            func_8002E724(p, next);
        }
        delta = alEvtqNextEvent(&p->queue, (ALEvent *)next);
        p->delta = delta;
    } while (delta == 0);
    p->time += delta;
    return delta;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002E724.s")

void func_8002F234(GameAudioVoice *voice) {
    if (voice->flags & 4) {
        alSynStopVoice(D_8004827C->synth,&voice->synthVoice);
        alSynFreeVoice(D_8004827C->synth,&voice->synthVoice);
    }
    func_8002F5F0(voice);
    func_8002F31C(&D_8004827C->queue,voice,0xFFFF);
}

void func_8002F2B0(GameAudioVoice *voice) {
    GameAudioEvent event;
    f32 pitch;

    pitch = alCents2Ratio(voice->sound->keyMap->detune) * voice->pitch;
    event.type = 0x10;
    event.voice = voice;
    event.payload.value = *(s32 *)&pitch;
    alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, 0x8235);
}

extern s32 osSetIntMask(s32);

void func_8002F31C(void *queue, void *voice, u16 mask) {
    GameAudioEventQueue *q = queue;
    GameAudioEventItem *p, *next;
    GameAudioEventItem *pi, *ni;
    s32 old;

    old = osSetIntMask(1);
    p = q->used;
    while (p != 0) {
        next = p->next;
        pi = p;
        ni = next;
        if (voice == pi->voice && (pi->type & mask)) {
            if (ni != 0) ni->delta += pi->delta;
            alUnlink((ALLink *)p);
            alLink((ALLink *)p, (ALLink *)q);
        }
        p = next;
    }
    osSetIntMask(old);
}

s32 func_8002F3DC(s16 *allocated, s16 *freeCount) {
    u16 n, m, k;
    GameAudioVoice *p, *q, *r;

    p = D_80048270.head;
    q = D_80048270.free;
    r = D_80048270.tail;
    for (n = 0; p; p = p->next) n++;
    for (m = 0; q; q = q->next) m++;
    for (k = 0; r; r = r->prev) k++;
    *allocated = m;
    *freeCount = n;
    return k;
}

GameAudioVoice *func_8002F45C(void *unused, ALSound *sound)
{
  GameAudioVoice *voice;
  ALKeyMap *savedKey;
  ALKeyMap *key;
  s32 old;
  s32 pan;
  s32 value;
  voice = D_80048270.free;
  savedKey = sound->keyMap;
  key = savedKey;
  if (voice)
  {
    old = osSetIntMask(1);
    D_80048270.free = voice->next;
    alUnlink((ALLink *)voice);
    if (D_80048270.head)
    {
      voice->next = D_80048270.head;
      voice->prev = 0;
      D_80048270.head->prev = voice;
      D_80048270.head = voice;
    }
    else
    {
      voice->prev = 0;
      voice->next = 0;
      D_80048270.head = voice;
      D_80048270.tail = voice;
    }
    osSetIntMask(old);
    value = sound->envelope->decayTime == -1;
    pan = value + 0x40;
    value = 6000; /* Center pitch around 6000 cents. */
    voice->priority = pan;
    voice->state = 5;
    voice->retries = 2;
    voice->sound = sound;
    voice->pitch = 1.0f;
    voice->flags = key->keyMax & 0xF0;
    voice->owner = 0;
    if (voice->flags & 0x20)
    {
      voice->ratio = alCents2Ratio((key->keyBase * 100) - value);
    }
    else
    {
      voice->ratio = alCents2Ratio(((key->keyBase * 100) + key->detune) - value);
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

void func_8002F5F0(GameAudioVoice *voice) {
    if(voice==D_80048270.head) D_80048270.head=voice->next;
    if(voice==D_80048270.tail) D_80048270.tail=voice->prev;
    alUnlink((ALLink *)voice);
    if(D_80048270.free) {
        voice->next=D_80048270.free;
        voice->prev=0;
        D_80048270.free->prev=voice;
        D_80048270.free=voice;
    }
    else {
        voice->prev=0;
        voice->next=0;
        D_80048270.free=voice;
    }
    if(voice->flags&4) D_80048280--;
    voice->state=0;
    if(voice->owner) {
        if(voice==*voice->owner) *voice->owner=0;
        voice->owner=0;
    }
}

void func_8002F6C4(GameAudioVoice *p, u8 value) {
    if (p) p->priority = value;
}

s32 func_8002F6DC(GameAudioVoice *p) {
    if (p) return p->state;
    return 0;
}

GameAudioVoice *func_8002F6F4(ALBank *bank, s16 id, GameAudioVoice **owner)
{
  GameAudioVoice *voice;
  ALSound *sound;
  ALKeyMap *key;
  GameAudioVoice *last = 0;
  s16 repeat = 0;
  s32 repeatTime;
  s32 step;
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

void func_8002F8F8(GameAudioVoice *voice) {
    GameAudioEvent event;

    event.type = 0x400;
    event.voice = voice;
    if (voice) {
        voice->flags &= ~0x10;
        alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, 0);
    }
}

void func_8002F944(u8 mask) {
    s32 old;
    GameAudioEvent event;
    GameAudioVoice *p;
    old = osSetIntMask(1);
    p = D_80048270.head;
    while (p) {
        event.type = 0x400;
        event.voice = p;
        if ((p->flags & mask) == mask) {
            p->flags &= ~0x10;
            alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, 0);
        }
        p = p->next;
    }
    osSetIntMask(old);
}

void func_8002F9FC(void) {
    func_8002F944(1);
}

void func_8002FA1C(void) {
    func_8002F944(17);
}

void func_8002FA3C(void) {
    func_8002F944(3);
}

void func_8002FA5C(GameAudioVoice *object, s16 type, s32 value) {
    GameAudioEvent event;
    event.type=type;
    event.voice=object;
    event.payload.value=value;
    if (object) alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event,0);
}

u16 func_8002FAA0(u8 index) {
    return D_80069928[index];
}

void func_8002FAC0(u8 group, u16 volume) {
    GameAudioGroupEvent event;
    GameAudioVoice *p = D_80048270.head;

    D_80069928[group] = volume;
    while (p) {
        if ((p->sound->keyMap->keyMin & 0x3F) == group) {
            event.type = 0x800;
            event.voice = p;
            alEvtqPostEvent(&D_8004827C->queue, (ALEvent *)&event, 0);
        }
        p = p->next;
    }
}
