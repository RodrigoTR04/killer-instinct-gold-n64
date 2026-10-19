#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002E4A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002E680.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002E724.s")

typedef struct { u8 pad[0x14]; u8 queue[0x24]; void *synth; } T024VoicePlayer;
typedef struct { u8 pad[0xC]; u8 synthVoice[0x32]; u8 flags; } T024FreeVoice;
extern T024VoicePlayer *D_8004827C;
extern void alSynStopVoice(void *,void *),alSynFreeVoice(void *,void *);
extern void func_8002F5F0(T024FreeVoice *);
extern void func_8002F31C(void *,void *,u16);
void func_8002F234(T024FreeVoice *voice) {
    if (voice->flags & 4) {
        alSynStopVoice(D_8004827C->synth,voice->synthVoice);
        alSynFreeVoice(D_8004827C->synth,voice->synthVoice);
    }
    func_8002F5F0(voice);
    func_8002F31C(D_8004827C->queue,voice,0xFFFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F2B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F31C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F3DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F45C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F5F0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F8F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002F944.s")

extern void func_8002F944(s32);
void func_8002F9FC(void) {
    func_8002F944(1);
}

extern void func_8002F944(s32);
void func_8002FA1C(void) {
    func_8002F944(17);
}

extern void func_8002F944(s32);
void func_8002FA3C(void) {
    func_8002F944(3);
}

typedef struct { s16 type; s32 object; s32 value; s32 pad; } T024Event;
extern T024VoicePlayer *D_8004827C;
extern void alEvtqPostEvent(void *, void *, s32);
void func_8002FA5C(s32 object, s16 type, s32 value) {
    T024Event event;
    event.type=type;
    event.object=object;
    event.value=value;
    if (object) alEvtqPostEvent(D_8004827C->queue,&event,0);
}

extern u16 *D_80069928;
u16 func_8002FAA0(u8 index) {
    return D_80069928[index];
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1EB40/func_8002FAC0.s")
