#include "common.h"

typedef struct {
 u32 voices,events;
 s32 priority;
 void *heap;
 u16 groups;
 }
 T024AudioConfig;
 typedef struct {
 void *next,*client,*handler;
 u8 padC[8];
 u8 queue[0x14],event[0x10];
 void *synth;
 u8 pad3C[4];
 void *current,*voices;
 s32 priority,interval,delta,time;
 }
 T024AudioPlayer;
 extern void *D_8004827C;
 extern void *D_80048278,*D_80048440;
 extern u16 *D_80069928;
 extern void *alHeapDBAlloc(s32,s32,void *,s32,s32);
 extern void alEvtqNew(void *,void *,s32),alLink(void *,void *),alSynAddPlayer(void *,void *);
 extern void func_8002E680();
 extern void alEvtqPostEvent(void *,void *,s32);
 extern s32 alEvtqNextEvent(void *,void *);

void func_8002E4A0(T024AudioConfig *config)
{
  u32 i;
  u8 *voice;
  struct
  {
    s16 type;
    u8 data[14];
  } event;
  ((T024AudioPlayer *)D_8004827C)->priority = config->priority;
  ((T024AudioPlayer *)D_8004827C)->current = 0;
  ((T024AudioPlayer *)D_8004827C)->interval = 0x80E8;
  ((T024AudioPlayer *)D_8004827C)->voices = alHeapDBAlloc(0, 0, config->heap, 1, config->voices << 6);
  alEvtqNew(((T024AudioPlayer *)D_8004827C)->queue, alHeapDBAlloc(0, 0, config->heap, 1, config->events * 0x1C), config->events);
  D_80048278 = ((T024AudioPlayer *)D_8004827C)->voices;
  for (i = 1; i < config->voices; i++)
  {
    voice = (u8 *) ((T024AudioPlayer *)D_8004827C)->voices;
    alLink(&voice[i << 6], (&voice[i << 6]) - 64);
  }

  D_80069928 = alHeapDBAlloc(0, 0, config->heap, 2, config->groups);
  for (i = 0; i < config->groups; i++)
  {
    D_80069928[i] = 0x7FFF;
  }

  ((T024AudioPlayer *)D_8004827C)->synth = D_80048440;
  ((T024AudioPlayer *)D_8004827C)->next = 0;
  ((T024AudioPlayer *)D_8004827C)->handler = func_8002E680;
  ((T024AudioPlayer *)D_8004827C)->client = D_8004827C;
  alSynAddPlayer(((T024AudioPlayer *)D_8004827C)->synth, D_8004827C);
  event.type = 0x20;
  alEvtqPostEvent(((T024AudioPlayer *)D_8004827C)->queue, &event, ((T024AudioPlayer *)D_8004827C)->interval);
  ((T024AudioPlayer *)D_8004827C)->delta = alEvtqNextEvent(((T024AudioPlayer *)D_8004827C)->queue, ((T024AudioPlayer *)D_8004827C)->event);
}

typedef struct { u16 type; u8 data[14]; } T040Event;
typedef struct { s16 type; u8 body[0x22]; } T040NextEvent;
typedef struct { u8 pad[0x14]; u8 queue[0x14]; T040NextEvent nextEvent; s32 interval, delta, time; } T040Player;
extern void alEvtqPostEvent(void *, void *, s32);
extern s32 alEvtqNextEvent(void *, void *);
extern void func_8002E724(T040Player *, void *);

void func_8002E680(T040Player *p) {
    T040NextEvent *next = &p->nextEvent;
    T040Event event;
    s32 delta;

    do {
        if (p->nextEvent.type == 0x20) {
            event.type = 0x20;
            alEvtqPostEvent(p->queue, &event, p->interval);
        } else {
            func_8002E724(p, next);
        }
        delta = alEvtqNextEvent(p->queue, next);
        p->delta = delta;
    } while (delta == 0);
    p->time += delta;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002E724.s")

typedef struct { u8 pad[0x14]; u8 queue[0x24]; void *synth; } T024VoicePlayer;
typedef struct { u8 pad[0xC]; u8 synthVoice[0x32]; u8 flags; } T024FreeVoice;
extern void *D_8004827C;
extern void alSynStopVoice(void *,void *),alSynFreeVoice(void *,void *);
extern void func_8002F5F0();
extern void func_8002F31C(void *,void *,u16);
void func_8002F234(T024FreeVoice *voice) {
    if (voice->flags & 4) {
        alSynStopVoice(((T024VoicePlayer *)D_8004827C)->synth,voice->synthVoice);
        alSynFreeVoice(((T024VoicePlayer *)D_8004827C)->synth,voice->synthVoice);
    }
    func_8002F5F0(voice);
    func_8002F31C(((T024VoicePlayer *)D_8004827C)->queue,voice,0xFFFF);
}

typedef struct { u8 pad[5]; s8 detune; } T024Sound;
typedef struct { u8 pad[4]; T024Sound *sound; } T024Instrument;
typedef struct { u8 pad[8]; T024Instrument *instrument; u8 padC[0x20]; float pitch; } T024PitchVoice;
typedef struct { s16 type; T024PitchVoice *voice; s32 pitch; s32 unused; } T040PitchEvent;
extern float alCents2Ratio(s32);
extern void alEvtqPostEvent(void *, void *, s32);
void func_8002F2B0(T024PitchVoice *voice) {
    T040PitchEvent event;
    f32 pitch;

    pitch = alCents2Ratio(voice->instrument->sound->detune) * voice->pitch;
    event.type = 0x10;
    event.voice = voice;
    event.pitch = *(s32 *)&pitch;
    alEvtqPostEvent(((T024VoicePlayer *)D_8004827C)->queue, &event, 0x8235);
}


typedef struct T024EventItem { struct T024EventItem *next,*prev; s32 delta; u16 type; u16 pad; void *voice; } T024EventItem;
typedef struct { T024EventItem *free,*unused,*used; } T024EventQueue;
extern s32 osSetIntMask(s32);
extern void alUnlink(void *),alLink(void *,void *);
void func_8002F31C(void *queue, void *voice, u16 mask) {
    T024EventQueue *q = queue;
    T024EventItem *p, *next;
    T024EventItem *pi, *ni;
    s32 old;

    old = osSetIntMask(1);
    p = q->used;
    while (p != 0) {
        next = p->next;
        pi = p;
        ni = next;
        if (voice == pi->voice && (pi->type & mask)) {
            if (ni != 0) ni->delta += pi->delta;
            alUnlink(p);
            alLink(p, q);
        }
        p = next;
    }
    osSetIntMask(old);
}


typedef struct T024Link { struct T024Link *next; struct T024Link *previous; } T024Link;
typedef struct { T024Link *free,*active,*allocated; } T024VoiceLists;
extern T024VoiceLists D_80048270;
s32 func_8002F3DC(s16 *allocated, s16 *freeCount) {
    u16 n, m, k;
    T024Link *p, *q, *r;

    p = D_80048270.free;
    q = D_80048270.allocated;
    r = D_80048270.active;
    for (n = 0; p; p = p->next) n++;
    for (m = 0; q; q = q->next) m++;
    for (k = 0; r; r = r->previous) k++;
    *allocated = m;
    *freeCount = n;
    return k;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F45C.s")

typedef struct T024ReleasedVoice {
 struct T024ReleasedVoice *next,*prev;
 u8 pad[0x28];
 struct T024ReleasedVoice **owner;
 u8 pad34[0xA];
 u8 flags,state;
} T024ReleasedVoice;

typedef struct {
 T024ReleasedVoice *head,*tail,*free;
} T024ReleaseLists;


extern s16 D_80048280;

extern void alUnlink(void *);

void func_8002F5F0(T024ReleasedVoice *voice) {
    if(voice==((T024ReleaseLists *)&D_80048270)->head) ((T024ReleaseLists *)&D_80048270)->head=voice->next;
    if(voice==((T024ReleaseLists *)&D_80048270)->tail) ((T024ReleaseLists *)&D_80048270)->tail=voice->prev;
    alUnlink(voice);
    if(((T024ReleaseLists *)&D_80048270)->free) {
        voice->next=((T024ReleaseLists *)&D_80048270)->free;
        voice->prev=0;
        ((T024ReleaseLists *)&D_80048270)->free->prev=voice;
        ((T024ReleaseLists *)&D_80048270)->free=voice;
    }
    else {
        voice->prev=0;
        voice->next=0;
        ((T024ReleaseLists *)&D_80048270)->free=voice;
    }
    if(voice->flags&4) D_80048280--;
    voice->state=0;
    if(voice->owner) {
        if(voice==*voice->owner) *voice->owner=0;
        voice->owner=0;
    }
}




typedef struct { u8 pad[0x36]; u8 value; } T024Value;
void func_8002F6C4(T024Value *p, u8 value) {
    if (p) p->value = value;
}

typedef struct { u8 pad[0x3F]; u8 value; } T024Result;
s32 func_8002F6DC(T024Result *p) {
    if (p) return p->value;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F6F4.s")

typedef struct { u8 pad[0x3E]; u8 flags; } T024VoiceFlags;
typedef struct { s16 type; T024VoiceFlags *voice; s32 unused[2]; } T040StopEvent;
extern void alEvtqPostEvent(void *, void *, s32);
void func_8002F8F8(T024VoiceFlags *voice) {
    T040StopEvent event;

    event.type = 0x400;
    event.voice = voice;
    if (voice) {
        voice->flags &= ~0x10;
        alEvtqPostEvent(((T024VoicePlayer *)D_8004827C)->queue, &event, 0);
    }
}


typedef struct T045MaskedVoice { struct T045MaskedVoice *next; u8 pad[0x3A]; u8 flags; } T045MaskedVoice;
typedef struct { s16 type; T045MaskedVoice *voice; s32 payload[2]; } T045MaskedEvent;
void func_8002F944(u8 mask) {
    s32 old;
    T045MaskedEvent event;
    T045MaskedVoice *p;
    old = osSetIntMask(1);
    p = (T045MaskedVoice *)D_80048270.free;
    while (p) {
        event.type = 0x400;
        event.voice = p;
        if ((p->flags & mask) == mask) {
            p->flags &= ~0x10;
            alEvtqPostEvent(((T024VoicePlayer *)D_8004827C)->queue, &event, 0);
        }
        p = p->next;
    }
    osSetIntMask(old);
}

extern void func_8002F944(u8);
void func_8002F9FC(void) {
    func_8002F944(1);
}

extern void func_8002F944(u8);
void func_8002FA1C(void) {
    func_8002F944(17);
}

extern void func_8002F944(u8);
void func_8002FA3C(void) {
    func_8002F944(3);
}

typedef struct { s16 type; s32 object; s32 value; s32 pad; } T024Event;
extern void *D_8004827C;
extern void alEvtqPostEvent(void *, void *, s32);
void func_8002FA5C(s32 object, s16 type, s32 value) {
    T024Event event;
    event.type=type;
    event.object=object;
    event.value=value;
    if (object) alEvtqPostEvent(((T024VoicePlayer *)D_8004827C)->queue,&event,0);
}

extern u16 *D_80069928;
u16 func_8002FAA0(u8 index) {
    return D_80069928[index];
}

typedef struct { u8 pad[2]; u8 group; } T045GroupSound;
typedef struct { u8 pad[4]; T045GroupSound *sound; } T045GroupInstrument;
typedef struct T045GroupVoice {
    struct T045GroupVoice *next;
    u8 pad[4];
    T045GroupInstrument *instrument;
} T045GroupVoice;
typedef struct {
    s16 type;
    T045GroupVoice *voice;
    s32 payload[4];
} T045GroupEvent;

void func_8002FAC0(u8 group, u16 volume) {
    T045GroupEvent event;
    T045GroupVoice *p = (T045GroupVoice *)D_80048270.free;

    D_80069928[group] = volume;
    while (p) {
        if ((p->instrument->sound->group & 0x3F) == group) {
            event.type = 0x800;
            event.voice = p;
            alEvtqPostEvent(((T024VoicePlayer *)D_8004827C)->queue, &event, 0);
        }
        p = p->next;
    }
}
