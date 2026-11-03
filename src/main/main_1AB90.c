#include "audio_game.h"
#include "boot.h"

extern u8 D_80066C30[],D_80128350[],D_8F9FA0[],D_907580[],D_9AF4B0[],D_9B9AD0[],D_992AF0[];
extern ALBank *D_80066C40;

void func_8002A4F0(void)
{
  GameAudioConfig sfx;
  ALBankFile *bank;
  ALBankFile *effects;
  s32 i;
  ALSynConfig synth;
  ALSeqpConfig music;
  ALSeqpConfig secondary;
  AudioSettings settings;
  s32 size;
  u32 seqSize;
  alHeapInit(D_80066C30, D_80128350, 0x4A380);
  synth.maxVVoices = 44;
  synth.maxPVoices = 22;
  synth.maxUpdates = 50;
  synth.maxFXbusses = 1;
  synth.dmaproc = 0;
  synth.fxType = 6;
  synth.outputRate = 0;
  synth.heap = D_80066C30;
  settings.rate = 0x5622;
  settings.frames = 1;
  settings.commands = 0x1000;
  func_8002AB90(&synth, 12, &settings);
  size = D_907580 - D_8F9FA0;
  bank = alHeapDBAlloc(0, 0, D_80066C30, 1, size);
  boot_dma((s32) D_8F9FA0, (s32) bank, size);
  alBnkfNew(bank, D_907580);
  size = D_9B9AD0 - D_9AF4B0;
  effects = alHeapDBAlloc(0, 0, D_80066C30, 1, size);
  boot_dma((s32) D_9AF4B0, (s32) effects, size);
  alBnkfNew(effects, D_9B9AD0);
  D_80066C40 = effects->bankArray[0];
  D_80066C28 = alHeapDBAlloc(0, 0, D_80066C30, 1, 4);
  boot_dma((s32) D_992AF0, (s32) D_80066C28, 4);
  seqSize = (D_80066C28->seqCount * 8) + 4;
  D_80066C28 = alHeapDBAlloc(0, 0, D_80066C30, 1, (D_80066C28->seqCount * 8) + 4);
  boot_dma((s32) D_992AF0, (s32) D_80066C28, seqSize);
  alSeqFileNew(D_80066C28, D_992AF0);
  D_80066A30 = alHeapDBAlloc(0, 0, D_80066C30, 1, 15000);
for (i=0; i<48; i++) { D_800669D0[i] = D_80066C28->seqArray[i].len; if (D_800669D0[i] & 1) D_800669D0[i]++; }
  music.maxVoices = 44;
  music.maxEvents = 50;
  music.maxChannels = 16;
  music.heap = D_80066C30;
  music.initOsc = 0;
  music.updateOsc = 0;
  music.stopOsc = 0;
  D_800669C0 = alHeapDBAlloc(0, 0, D_80066C30, 1, 124);
  alCSPNew(D_800669C0, &music);
  alCSPSetBank(D_800669C0, bank->bankArray[0]);
  func_8002A900(17);
  sfx.events = 64;
  sfx.voices = 64;
  sfx.maxVoices = 6;
  sfx.groups = 8;
  sfx.heap = D_80066C30;
  func_8002E4A0(&sfx);
  D_80066A34 = alHeapDBAlloc(0, 0, D_80066C30, 1, 15000);
  secondary.maxVoices = 44;
  secondary.maxEvents = 50;
  secondary.maxChannels = 16;
  secondary.heap = D_80066C30;
  secondary.initOsc = 0;
  secondary.updateOsc = 0;
  secondary.stopOsc = 0;
  D_800669C4 = alHeapDBAlloc(0, 0, D_80066C30, 1, 124);
  alCSPNew(D_800669C4, &secondary);
  alCSPSetBank(D_800669C4, bank->bankArray[0]);
}

void func_8002A888(void) {
    if (alCSPGetState(D_800669C0) == 0) {
        alCSPPlay(D_800669C0);
        func_8002AA98(0x7FFF);
    }
}

void func_8002A8C4(void) {
    if (alCSPGetState(D_800669C4) == 0) {
        alCSPPlay(D_800669C4);
        func_8002AAEC(0x7FFF);
    }
}

void func_8002A900(s32 index) {
    u32 count;
    u32 limit;
    u16 *current = &D_80048148;

    count = 0;
    if (index != *current) {
        boot_dma((s32)D_80066C28->seqArray[index].offset, (s32)D_80066A30, D_800669D0[index]);
        *current = index;
    }
    limit = 0x3D0900;
    alCSPStop(D_800669C0);
    if (alCSPGetState(D_800669C0)) {
        for (;;) {
            count++;
            if (alCSPGetState(D_800669C0) == 0) break;
            if (count >= limit) break;
        }
    }
    alCSeqNew(&D_80066A38, D_80066A30);
    alCSPSetSeq(D_800669C0, &D_80066A38);
}

void func_8002A9DC(s32 index) {
    if (index != D_8004814C) {
        boot_dma((s32)D_80066C28->seqArray[index].offset, (s32)D_80066A34, D_800669D0[index]);
        D_8004814C = index;
    }
    alCSPStop(D_800669C4);
    while (alCSPGetState(D_800669C4) != 0) {}
    alCSeqNew(&D_80066B30, D_80066A34);
    alCSPSetSeq(D_800669C4, &D_80066B30);
}

extern s32 D_80048140[];
extern u8 D_80127CC9;

void func_8002AA98(s32 volume)
{
    s16 narrowed;
    volume = D_80048140[D_80127CC9] * volume;
    volume >>= 16;
    narrowed = volume;
    alCSPSetVol(D_800669C0, narrowed);
}

void func_8002AAEC(s32 volume)
{
    s16 narrowed;
    volume = D_80048140[D_80127CC9] * volume;
    volume >>= 16;
    narrowed = volume;
    alCSPSetVol(D_800669C4, narrowed);
}

void func_8002AB40(void) {
    alCSPStop(D_800669C0);
}

void func_8002AB64(void) { alCSPStop(D_800669C4); }
