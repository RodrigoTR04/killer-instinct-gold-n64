#ifndef AUDIO_GAME_H
#define AUDIO_GAME_H

#include "common.h"
#include "libaudio/libaudio.h"
#include "boot.h"

/* SDK queue layout used by this game-facing layer (0x18 bytes). */
typedef struct {
    void *receiveWaiters, *sendWaiters;
    s32 validCount, first, capacity;
    void **messages;
} AudioMessageQueue;

/* Game-owned audio records; offsets below are for the N64 o32 ABI. */
typedef struct AudioDmaBuffer {
    struct AudioDmaBuffer *next, *prev;
    u32 address, frame;
    u8 *buffer;
} AudioDmaBuffer; /* 0x14 */
typedef struct {
    u8 initialized;
    AudioDmaBuffer *used, *free;
} AudioDmaPool; /* 0x0c */
typedef struct AudioFrame AudioFrame;
typedef struct {
    s16 type;
    AudioFrame *frame;
} AudioMessage;
typedef struct {
    s32 taskType, flags;
    void *boot;
    u32 bootSize;
    void *code;
    u32 codeSize;
    void *data;
    u32 dataSize;
    u8 reserved20[0x10];
    void *commands;
    u32 commandSize;
    s32 yield;
    u32 yieldSize;
} AudioRspTask; /* 0x40; the standard OSTask field offsets */
struct AudioFrame {
    void *buffer;                 /* 00 */
    s16 samples;
    u8 reserved06[2];
    s32 state;                    /* 08: scheduler message begins */
    u8 reserved0C[8];
    s32 type;                     /* 14 */
    u8 reserved18[8];
    AudioRspTask rsp;             /* 20 */
    AudioMessageQueue *queue;     /* 60 */
    void *message;               /* 64 */
    AudioMessage body;           /* 68: completion message */
    u8 reserved70[0x18];
};
/* Frame allocation is 0x88 bytes; the tail has no observed accesses. */
typedef struct {
    s32 rate;
    u32 frames;
    s32 commands;
} AudioSettings;

typedef struct GameAudioVoice GameAudioVoice;
struct GameAudioVoice {
    GameAudioVoice *next, *prev;
    ALSound *sound;               /* 08 */
    ALVoice synthVoice;           /* 0c */
    f32 ratio, pitch;             /* 28, 2c */
    GameAudioVoice **owner;       /* 30 */
    s16 volume;                  /* 34 */
    u8 priority, reserved37;
    s32 retries;                 /* 38 */
    u8 pan, fx, flags, state;/* 3c..3f */
};
typedef struct {
    s16 type;
    GameAudioVoice *voice;
    union {
        s32 value;
        f32 pitch;
        struct { s16 reserved, id; } repeat;
    } payload;
    void *bank;
} GameAudioEvent; /* 0x10, fits ALEvent */
typedef struct {
    ALPlayer node;               /* 00 */
    ALEventQueue queue;          /* 14 */
    GameAudioEvent event;        /* 28 */
    ALSynth *synth;              /* 38 */
    u32 reserved3C;
    GameAudioVoice *current, *voices; /* 40, 44 */
    s32 maxVoices, interval, delta, time; /* 48..54 */
} GameAudioPlayer;
typedef struct {
    u32 voices, events;
    s32 maxVoices;
    ALHeap *heap;
    u16 groups;
} GameAudioConfig;
typedef struct {
    GameAudioVoice *head, *tail, *free;
} GameAudioVoiceLists;

/* These typedefs check the embedded SDK layouts under the target compiler. */
typedef char AudioFrameSizeCheck[sizeof(AudioFrame) == 0x88 ? 1 : -1];
typedef char AudioVoiceSizeCheck[sizeof(GameAudioVoice) == 0x40 ? 1 : -1];
typedef char AudioPlayerSizeCheck[sizeof(GameAudioPlayer) == 0x58 ? 1 : -1];
typedef char AudioEventSizeCheck[sizeof(GameAudioEvent) == sizeof(ALEvent) ? 1 : -1];

typedef struct { u16 type; u8 data[14]; } GameAudioTickEvent;

/* Extended local event workspace used by the group-volume broadcaster. */
typedef struct {
    s16 type;
    GameAudioVoice *voice;
    s32 payload[4];
} GameAudioGroupEvent;
/* Prefix used by the cancellation walk; full items are 0x1c bytes. */
typedef struct GameAudioEventItem {
    struct GameAudioEventItem *next, *prev;
    s32 delta;
    u16 type, reserved;
    GameAudioVoice *voice;
    s32 payload[2];
} GameAudioEventItem;
typedef struct {
    GameAudioEventItem *free, *freeTail, *used, *usedTail;
    s32 count;
} GameAudioEventQueue;

extern AudioMessageQueue D_80066E18, D_80066E50, D_800683F8;
extern void *D_80066E30[8], *D_80066E68[8], *D_80068410[32];
extern BootDmaMessage D_80068178[32];
extern ALCSPlayer *D_800669C0, *D_800669C4;
extern ALSeqFile *D_80066C28;
extern u16 D_80048148, D_8004814C, D_800669D0[];
extern void *D_80066A30, *D_80066A34;
extern ALCSeq D_80066A38, D_80066B30;
extern ALGlobals D_80066E88;
extern s32 D_8006816C, D_80068170;
extern GameAudioPlayer *D_8004827C;
extern GameAudioVoice *D_80048278;
extern ALSynth *D_80048440;
extern GameAudioVoiceLists D_80048270;
extern s16 D_80048280;
extern u16 *D_80069928;
extern AudioDmaPool D_80068158;
extern AudioDmaBuffer D_80067ED8[];
/* Two Acmd lists followed by three AudioFrame pointers. */
typedef union {
    void *slots[5];
    struct {
        Acmd *commands[2];
        AudioFrame *frames[3];
    } typed;
} AudioManagerBuffers;
extern AudioManagerBuffers D_80066C50;
extern u32 D_80048150, D_80048154;
extern s32 D_80048158;
extern u32 D_80068164;
extern s32 D_80068168;

void func_8002A4F0(void);
void func_8002A888(void);
void func_8002A8C4(void);
void func_8002A900(s32);
void func_8002A9DC(s32);
void func_8002AA98(s32);
void func_8002AAEC(s32);
void func_8002AB40(void);
void func_8002AB64(void);
void func_8002AB90(ALSynConfig *, s32, AudioSettings *);
void func_8002AEE4(s32);
s32 func_8002B034(AudioFrame *, AudioFrame *);
void func_8002B1EC(AudioFrame *);
s32 func_8002B22C(s32, s32, void *);
ALDMAproc func_8002B3A8(AudioDmaPool **);
void func_8002B3E0(void);
void func_8002E4A0(GameAudioConfig *);
ALMicroTime func_8002E680(GameAudioPlayer *);
void func_8002E724(GameAudioPlayer *, void *);
void func_8002F234(GameAudioVoice *);
void func_8002F2B0(GameAudioVoice *);
void func_8002F31C(void *, void *, u16);
GameAudioVoice *func_8002F45C(void *, ALSound *);
void func_8002F5F0(GameAudioVoice *);
GameAudioVoice *func_8002F6F4(ALBank *, s16, GameAudioVoice **);
s32 func_8002F3DC(s16 *, s16 *);
void func_8002F6C4(GameAudioVoice *, u8);
s32 func_8002F6DC(GameAudioVoice *);
void func_8002F8F8(GameAudioVoice *);
void func_8002F944(u8);
void func_8002FA5C(GameAudioVoice *, s16, s32);
u16 func_8002FAA0(u8);
void func_8002FAC0(u8, u16);

#endif
