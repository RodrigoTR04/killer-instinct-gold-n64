/* T-118 draft: 27 differing words / 920 B in full TU context.
 * Keep settings before entry: declaration order affects IDO allocation.
 * Shared audio types retained from T-108. */
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
  ALSeqData *entry;
  s32 size;
  s32 length;
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
  size = (D_80066C28->seqCount * 8) + 4;
  D_80066C28 = alHeapDBAlloc(0, 0, D_80066C30, 1, size);
  boot_dma((s32) D_992AF0, (s32) D_80066C28, size);
  alSeqFileNew(D_80066C28, D_992AF0);
  D_80066A30 = alHeapDBAlloc(0, 0, D_80066C30, 1, 15000);
  for (i = 0, entry = D_80066C28->seqArray; entry != (D_80066C28->seqArray + 48); i++, entry++)
  {
    length = entry->len & 0xFFFF;
    D_800669D0[i] = length;
    if (length & 1)
    {
      D_800669D0[i] = length + 1;
    }
  }

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
