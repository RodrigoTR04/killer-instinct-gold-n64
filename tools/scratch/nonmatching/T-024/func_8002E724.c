/* DRAFT. Remaining diff: 699 differing words; 2364/2832 bytes */
typedef struct { s32 attack,decay,release; u8 attackVolume,decayVolume; } T024EnvelopeTimes;
typedef struct { u8 next,delay,group,fx; s8 key,detune; } T024EventKey;
typedef struct { T024EnvelopeTimes *envelope; T024EventKey *key; void *wavetable; u8 pan,volume; } T024EventSound;
typedef struct T024EventVoice { struct T024EventVoice *next,*prev; T024EventSound *sound; u8 synthVoice[0x1C]; float ratio,pitch; void **owner; s16 volume; u8 priority,pad37; s32 retries; u8 pan,fx,flags,state; } T024EventVoice;
typedef struct { u16 type; T024EventVoice *voice; union { s32 integer; float pitch; struct { s16 pad,id; } repeat; } value; void *bank; } T024VoiceEvent;
typedef struct { u8 pad[0x14]; u8 queue[0x24]; void *synth; u8 pad3C[0xC]; s32 maxVoices; } T024EventPlayer;
typedef struct { s16 priority,fx; u8 unity; } T024VoiceConfig;
extern T024EventVoice *D_80048274;
extern s16 D_80048280;
extern u16 *D_80069928;
extern void func_8002F234();
extern void func_8002F31C(void *,void *,u16);
extern s32 alSynAllocVoice(void *,void *,void *);
extern void alSynStartVoice(void *,void *,void *),alSynSetVol(void *,void *,s16,s32),alSynSetPan(void *,void *,u8),alSynSetPitch(void *,void *,float),alSynSetFXMix(void *,void *,u8);
extern void alEvtqPostEvent(void *,void *,s32),func_8002F2B0(void *);
extern s32 func_8002F3DC(s16 *,s16 *);
extern void *func_8002F6F4(void *,s16,void **);
extern void func_8002FA5C(void *,s16,s32);
void func_8002E724(T024EventPlayer *player,T024VoiceEvent *event) {
    T024VoiceEvent copied,posted;
    T024VoiceConfig config;
    T024EventVoice *voice,*next,*victim;
    T024EventSound *sound;
    T024EventKey *key;
    T024EnvelopeTimes *envelope;
    s16 active,freeCount;
    s32 allocated=0,full,volume,duration,pan,fx,stop=1;
    void *replacement;
    next=0;
    do {
        if(next) { copied=*event; copied.voice=next; event=&copied; }
        voice=event->voice;
        sound=voice->sound;
        if(!sound) { func_8002F3DC(&active,&freeCount); return; }
        key=sound->key;
        envelope=sound->envelope;
        next=voice->next;
        switch(event->type) {
        case 1:
            if(voice->state!=5 && voice->state!=4) return;
            config.fx=0; config.unity=0; config.priority=voice->priority;
            full=D_80048280>=player->maxVoices;
            if(!full || (voice->flags&0x10)) allocated=alSynAllocVoice(player->synth,voice->synthVoice,&config);
            if(!allocated) {
                if((voice->flags&0x12)||voice->retries>0) { voice->state=4; voice->retries--; alEvtqPostEvent(player->queue,event,0x8235); return; }
                if(full) {
                    victim=D_80048274;
                    do {
                        if(!(victim->flags&0x12)&&(victim->flags&4)&&victim->state!=3) {
                            posted.type=0x80; posted.voice=victim; victim->state=3; full=0;
                            alEvtqPostEvent(player->queue,&posted,1000); alSynSetVol(player->synth,victim->synthVoice,0,1000);
                        }
                        victim=victim->prev;
                    } while(full && victim);
                    if(!full) { voice->retries=2; alEvtqPostEvent(player->queue,event,1001); return; }
                }
                func_8002F234(voice); return;
            }
            voice->flags|=4; alSynStartVoice(player->synth,voice->synthVoice,sound->wavetable); voice->state=1; D_80048280++;
            volume=D_80069928[key->group&63]*(envelope->attackVolume*voice->volume*sound->volume/16129)/32767-1;
            duration=((float)envelope->attack/voice->pitch)/voice->ratio;
            if(volume<0) volume=0;
            alSynSetVol(player->synth,voice->synthVoice,0,0); alSynSetVol(player->synth,voice->synthVoice,volume,duration);
            pan=voice->pan+sound->pan-64; if(pan<0) pan=0; if(pan>127) pan=127;
            alSynSetPan(player->synth,voice->synthVoice,pan); alSynSetPitch(player->synth,voice->synthVoice,voice->pitch*voice->ratio);
            fx=(voice->fx+(key->fx&15))*8; if(fx<0) fx=0; if(fx>=128) fx=127;
            alSynSetFXMix(player->synth,voice->synthVoice,fx);
            posted.type=0x40; posted.voice=voice; alEvtqPostEvent(player->queue,&posted,((float)envelope->attack/voice->pitch)/voice->ratio);
            break;
        case 2: case 0x400: case 0x1000:
            if(event->type!=0x1000 || (voice->flags&2)) {
                switch(voice->state) {
                case 1:
                    func_8002F31C(player->queue,voice,0x40); duration=((float)envelope->release/voice->ratio)/voice->pitch;
                    alSynSetVol(player->synth,voice->synthVoice,0,duration);
                    if(duration) { posted.type=0x80; posted.voice=voice; alEvtqPostEvent(player->queue,&posted,duration); voice->state=2; }
                    else func_8002F234(voice);
                    break;
                case 4: case 5: func_8002F234(voice); break;
                }
                if(event->type==2) event->type=0x1000;
            }
            break;
        case 4:
            voice->pan=event->value.integer;
            if(voice->state==1) { pan=voice->pan+sound->pan-64; if(pan<0) pan=0; if(pan>127) pan=127; alSynSetPan(player->synth,voice->synthVoice,pan); }
            break;
        case 0x10:
            voice->pitch=event->value.pitch;
            if(voice->state==1) { alSynSetPitch(player->synth,voice->synthVoice,voice->pitch*voice->ratio); if(voice->flags&0x20) func_8002F2B0(voice); }
            break;
        case 0x100:
            voice->fx=event->value.integer;
            if(voice->state==1) { fx=(voice->fx+(key->fx&15))*8; if(fx<0) fx=0; if(fx>=128) fx=127; alSynSetFXMix(player->synth,voice->synthVoice,fx); }
            break;
        case 8: case 0x800: case 0x40:
            if(event->type==8) voice->volume=event->value.integer;
            if((event->type==0x40 && !(voice->flags&2)) || (event->type!=0x40 && voice->state==1)) {
                volume=D_80069928[key->group&63]*(envelope->decayVolume*voice->volume*sound->volume/16129)/32767-1;
                if(volume<0) volume=0;
                if(event->type==8) duration=1000;
                else if(event->type==0x800) duration=((float)envelope->release/voice->ratio)/voice->pitch;
                else duration=((float)envelope->decay/voice->ratio)/voice->pitch;
                alSynSetVol(player->synth,voice->synthVoice,volume,duration);
                if(event->type==0x40) { posted.type=2; posted.voice=voice; alEvtqPostEvent(player->queue,&posted,duration); if(voice->flags&0x20) func_8002F2B0(voice); }
            }
            break;
        case 0x80: func_8002F234(voice); break;
        case 0x200:
            if(voice->flags&0x10) {
                replacement=func_8002F6F4(event->bank,event->value.repeat.id,voice->owner);
                func_8002FA5C(replacement,8,voice->volume); func_8002FA5C(replacement,4,voice->pan); func_8002FA5C(replacement,0x100,voice->fx);
                { union { float f; s32 i; } pitch; pitch.f=voice->pitch; func_8002FA5C(replacement,0x10,pitch.i); }
            }
            break;
        }
        if(next && !(event->type&0x2D1)) stop=next->flags&1;
    } while(!stop && next && !(event->type&0x2D1));
}
