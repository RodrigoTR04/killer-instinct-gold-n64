/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"
#define T081_MIN(a,b) ((a)<(b)?(a):(b))
#define T081_MAX(a,b) ((a)>(b)?(a):(b))
void func_8002E724(GameAudioPlayer *player, void *eventData)
{
    GameAudioEvent *event = eventData;
    GameAudioEvent copied,posted;
    ALVoiceConfig config;
    GameAudioVoice *voice,*next,*victim;
    ALSound *sound;
    ALKeyMap *key;
    ALEnvelope *envelope;
    s16 active,freeCount;
    s32 allocated=0,full,volume,duration,pan,fx,stop=1;
    GameAudioVoice *replacement;
    next=0;
    do
    {
        if(next)
        {
            copied.voice=next;
            copied.type=event->type;
            copied.payload=event->payload;
            event=&copied;
        }
        voice=event->voice;
        sound=voice->sound;
        if(!sound)
        {
            func_8002F3DC(&active,&freeCount);
            return;
        }
        key=sound->keyMap;
        envelope=sound->envelope;
        next=voice->next;
        switch((u16)event->type)
        {
            case 1:
            if(voice->state!=5 && voice->state!=4) return;
            config.fxBus=0;
            config.unityPitch=0;
            config.priority=voice->priority;
            full=D_80048280>=player->maxVoices;
            if(!full || (voice->flags&0x10)) allocated=alSynAllocVoice(player->synth,&voice->synthVoice,&config);
            if(!allocated)
            {
                if((voice->flags&0x12)||voice->retries>0)
                {
                    voice->state=4;
                    voice->retries--;
                    alEvtqPostEvent(&player->queue, (ALEvent *)event,0x8235);
                    return;
                }
                if(full)
                {
                    victim=D_80048270.tail;
                    do
                    {
                        if(!(victim->flags&0x12)&&(victim->flags&4)&&victim->state!=3)
                        {
                            posted.type=0x80;
                            posted.voice=victim;
                            victim->state=3;
                            full=0;
                            alEvtqPostEvent(&player->queue, (ALEvent *)&posted,1000);
                            alSynSetVol(player->synth,&victim->synthVoice,0,1000);
                        }
                        victim=victim->prev;
                    }
                    while(full && victim);
                    if(!full)
                    {
                        voice->retries=2;
                        alEvtqPostEvent(&player->queue, (ALEvent *)event,1001);
                        return;
                    }
                }
                func_8002F234(voice);
                return;
            }
            voice->flags|=4;
            alSynStartVoice(player->synth,&voice->synthVoice,sound->wavetable);
            voice->state=1;
            D_80048280++;
            volume=((s16 *)D_80069928)[key->keyMin&63]*(sound->envelope->attackVolume*voice->volume*sound->sampleVolume/16129)/32767-1;
            duration=((float)sound->envelope->attackTime/voice->pitch)/voice->ratio;
            if(volume<0) volume=0;
            alSynSetVol(player->synth,&voice->synthVoice,0,0);
            alSynSetVol(player->synth,&voice->synthVoice,volume,duration);
            pan=voice->pan+sound->samplePan-64;
            alSynSetPan(player->synth,&voice->synthVoice,T081_MIN(T081_MAX(pan,0),127));
            alSynSetPitch(player->synth,&voice->synthVoice,voice->pitch*voice->ratio);
            fx=(voice->fx+(key->keyMax&15))*8;
            alSynSetFXMix(player->synth,&voice->synthVoice,T081_MIN(T081_MAX(fx,0),127));
            posted.type=0x40;
            posted.voice=voice;
            alEvtqPostEvent(&player->queue, (ALEvent *)&posted,((float)sound->envelope->attackTime/voice->pitch)/voice->ratio);
            break;
            case 2: case 0x400: case 0x1000:
            if((u16)event->type!=0x1000 || (voice->flags&2))
            {
                switch(voice->state)
                {
                    case 1:
                    func_8002F31C(&player->queue,voice,0x40);
                    duration=((float)sound->envelope->releaseTime/voice->ratio)/voice->pitch;
                    alSynSetVol(player->synth,&voice->synthVoice,0,duration);
                    if(duration)
                    {
                        posted.type=0x80;
                        posted.voice=voice;
                        alEvtqPostEvent(&player->queue, (ALEvent *)&posted,duration);
                        voice->state=2;
                    }
                    else func_8002F234(voice);
                    break;
                    case 4: case 5: func_8002F234(voice);
                    break;
                }
                if((u16)event->type==2) event->type=0x1000;
            }
            break;
            case 4:
            voice->pan=event->payload.value;
            if(voice->state==1)
            {
                pan=voice->pan+sound->samplePan-64;
                alSynSetPan(player->synth,&voice->synthVoice,T081_MIN(T081_MAX(pan,0),127));
            }
            break;
            case 0x10:
            voice->pitch=event->payload.pitch;
            if(voice->state==1)
            {
                alSynSetPitch(player->synth,&voice->synthVoice,voice->pitch*voice->ratio);
                if(voice->flags&0x20) func_8002F2B0(voice);
            }
            break;
            case 0x100:
            voice->fx=event->payload.value;
            if(voice->state==1)
            {
                fx=(voice->fx+(key->keyMax&15))*8;
                alSynSetFXMix(player->synth,&voice->synthVoice,T081_MIN(T081_MAX(fx,0),127));
            }
            break;
            case 0x8:
            voice->volume=event->payload.value;
            if (voice->state==1)
            {
                volume=((s16 *)D_80069928)[key->keyMin&63]*(sound->envelope->decayVolume*voice->volume*sound->sampleVolume/16129)/32767-1;
                if(volume<0) volume=0;
                duration=1000;
                alSynSetVol(player->synth,&voice->synthVoice,volume,duration);
            }
            break;
            case 0x800:
            if (voice->state==1)
            {
                volume=((s16 *)D_80069928)[key->keyMin&63]*(sound->envelope->decayVolume*voice->volume*sound->sampleVolume/16129)/32767-1;
                if(volume<0) volume=0;
                duration=((float)sound->envelope->releaseTime/voice->ratio)/voice->pitch;
                alSynSetVol(player->synth,&voice->synthVoice,volume,duration);
            }
            break;
            case 0x40:
            if (!(voice->flags&2))
            {
                volume=((s16 *)D_80069928)[key->keyMin&63]*(sound->envelope->decayVolume*voice->volume*sound->sampleVolume/16129)/32767-1;
                if(volume<0) volume=0;
                duration=((float)sound->envelope->decayTime/voice->ratio)/voice->pitch;
                alSynSetVol(player->synth,&voice->synthVoice,volume,duration);
                posted.type=2;
                posted.voice=voice;
                alEvtqPostEvent(&player->queue, (ALEvent *)&posted,duration);
                if(voice->flags&0x20) func_8002F2B0(voice);
            }
            break;
            case 0x80: func_8002F234(voice);
            break;
            case 0x200:
            if(voice->flags&0x10)
            {
                replacement=func_8002F6F4(event->bank,event->payload.repeat.id,voice->owner);
                func_8002FA5C(replacement,8,voice->volume);
                func_8002FA5C(replacement,4,voice->pan);
                func_8002FA5C(replacement,0x100,voice->fx);
                {
                    union
                    {
                        float f;
                        s32 i;
                    }
                    pitch;
                    pitch.f=voice->pitch;
                    func_8002FA5C(replacement,0x10,pitch.i);
                }
            }
            break;
        }
        if(next && !(event->type&0x2D1)) stop=next->flags&1;
    }
    while(!stop && next && !(event->type&0x2D1));
}
#undef T081_MIN
#undef T081_MAX
