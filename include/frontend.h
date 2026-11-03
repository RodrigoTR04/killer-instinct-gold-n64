#ifndef FRONTEND_H
#define FRONTEND_H

#include "common.h"

/* Overlay frontend layouts, for the N64 o32 ABI. Unknown bytes stay reserved. */
typedef struct { s32 x, y; } FrontendPair;
/* Word view for builders using sw; the aligned union also permits sd. */
typedef struct { u32 w0, w1; } FrontendGfxWords;
typedef union {
    struct { u32 w0, w1; } words;
    u64 full;
} FrontendGfx;

typedef struct {
    s32 id;                         /* 00 */
    u32 frame;                      /* 04: animation/menu pulse clock */
    u8 reserved08[0xCC];
    f32 x, z, y, pitch, yaw;         /* D4..E4: scene camera */
    u8 reservedE8[0x10];
    u8 *matrices;                   /* F8: 64-byte matrix arena */
} FrontendRenderContext;

typedef struct {
    FrontendGfxWords *commands;
    f32 width;
} FrontendGlyph;                    /* transformed font's 8-byte glyph */
typedef struct {
    u8 *label, *value, *alternate;
} FrontendMenuItem;
typedef struct {
    u8 reserved00[0x10];
    void *text0, *text1;
} FrontendMenuText;

typedef struct {
    s16 x, y, z, angle, width;
    u8 animation;
    s8 alpha;
} FrontendCloud;                    /* 0C: signed fade byte */
typedef struct {
    s16 x, y, z;
    u16 flag;
    s16 s, t;
    u8 rgba[4];
} FrontendVertex;                   /* 16-byte vertex */
typedef struct FrontendSprite {
    u32 reserved00;
    s32 texture;
    u8 reserved08[0xA], clip[0x6C];
    u16 scale;
    s16 y;
    u8 reserved82[6];
    void (*draw)();
} FrontendSprite;
typedef struct {
    s32 x, y, scale;
    u8 flip, reserved0D[3];
} FrontendSpriteLayout;
typedef struct { u8 b[6]; } FrontendButtonMap;
typedef struct { char line1[8], line2[8]; } FrontendStatsText;
/* Two player input words, initialized to 0x1000 by mode/replay setup. */
typedef struct { u64 player[2]; } FrontendReplayInputs;

/* Score table stride and signed score halfword: BE910/BF788/BF988. */
typedef struct {
    u32 name;
    s16 score;
    u16 reserved06;
} FrontendScoreEntry;
typedef struct {
    FrontendScoreEntry *entries;
    u8 count, descending;
    u16 reserved06;
} FrontendScoreTable;
/* Seven words consumed by C17D0/C1990; counter meanings remain unresolved. */
typedef struct {
    u32 participants, countersA[2], countersB[2], result, minimum;
} FrontendMatchStats;
/* Layout views only: exported member symbols below remain separate symbols. */
typedef struct {
    s32 phase;
    u8 reserved04[4];
    FrontendPair cursorX, cursorY;
    u8 direction[2], cursor[2];
    u8 reserved1C[4];
    FrontendPair names;
    s32 scroll;
    u8 pending, active;
    u8 reserved2E[2];
    u64 scores[2];
    u8 completed;
    u8 reserved41[7];
    s32 timer[2], timeout, remaining;
    u8 state;
    u8 reserved59[3];
    u16 volume;
} FrontendNameState;                /* D_802D37D0..D_802D382D */
typedef struct {
    f32 scroll;
    u8 selection;
    u8 reserved05;
    u8 playerSelection[2];
    u8 mode;
    u8 phase, pulse;
    u8 reserved0B;
    s8 playerState[2];
    u8 replay;
    u8 transition;
    u8 flags;
    u8 reserved11[7];
    f32 scale[2];
    u8 status[3];
} FrontendMenuState;                /* D_802D39F8..D_802D3A1A */

typedef char FrontendContextSizeCheck[sizeof(FrontendRenderContext) == 0xFC ? 1 : -1];
typedef char FrontendNameSizeCheck[sizeof(FrontendNameState) == 0x60 ? 1 : -1];
typedef char FrontendMenuSizeCheck[sizeof(FrontendMenuState) == 0x24 ? 1 : -1];
typedef char FrontendScoreSizeCheck[sizeof(FrontendScoreEntry) == 8 ? 1 : -1];
typedef char FrontendGlyphSizeCheck[sizeof(FrontendGlyph) == 8 ? 1 : -1];
typedef char FrontendCloudSizeCheck[sizeof(FrontendCloud) == 12 ? 1 : -1];
typedef char FrontendVertexSizeCheck[sizeof(FrontendVertex) == 16 ? 1 : -1];

extern void func_801CC784(void);
extern void func_801CC878(void);
extern void func_801BEFFC(void);
extern void func_801ADAD4(s32);
extern FrontendPair D_80128300, D_802D37D8, D_802D37E0, D_802D37F0;
extern s32 D_80295700, D_802956FC, D_802956F8;
extern s32 D_802D37D0, D_802D37F8, D_802D3820, D_802D3824;
extern u8 D_802D37EA[];
extern void func_801ADC64(s32);
extern void func_801AF5D4(s32);
extern void func_801AF5EC(s32);
extern FrontendRenderContext D_802C9F70;
extern FrontendGlyph D_80282A70[], D_80282C48[];
extern void guTranslate(void *, f32, f32, f32);
extern s32 D_802956F4, D_802CA068;
extern u8 D_8029C4B0[], D_8029C8B0[];
extern void func_801BF190(s32, s32, s32);
extern void func_801BFC08(s32);
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u8 D_80128310[][11], D_80128328[][11];
extern void guRotate(void *, f32, f32, f32, f32);
extern u8 D_80285168[];
extern u8 D_802855C8;
/* Legacy wrappers pass the list as an integer; keep their existing ABI. */
extern void func_801C35D8();
extern u8 D_80290DF8;
extern u8 D_80290F0C;
extern void func_801C3758(FrontendGfxWords **, FrontendCloud *, s32);
extern u8 D_800F4070[];
extern s32 D_80290D88;
extern u32 D_80290F90[];
extern u8 *D_802D38E0;
extern FrontendButtonMap D_80127C68[];
extern u16 D_80127CA8[][6];
extern u16 D_802923AC[];
extern void func_801C7A98(void);
extern u8 func_801CD038(s32, s32);
extern s8 D_801CD454, D_802923F5;
extern void *D_802925AC, *D_802926AC;
extern const u8 D_802952E0[], D_802952FC[];
extern s32 D_802956F8, D_802956FC, D_80295700, D_802CA064;
extern u64 D_802D3678[2];
extern f32 D_802D39F8;
/* lbu in 90D4/9698/9B14/AA00; these are unsigned state bytes. */
extern u8 D_802D39FC, D_802D3A01, D_802D3A02, D_802D3A07;
extern u8 D_802D3A00, D_802D3A06, D_802D3E15;
/* K&R definition/callers retain promoted integer arguments. */
extern void func_801C78B0();
extern u8 D_80127D30[8];
extern u8 D_80127D31;
extern u8 D_80127D58[];
typedef union {
    struct { u8 first, second, values[32]; } fields;
    u8 bytes[34];
} FrontendSettings;
extern FrontendSettings D_80127CC0;
extern void *memcpy(void *, const void *, u32);
extern u8 D_80127D20[];
extern u8 D_80127D28[];
extern const char D_8029531C[];
extern FrontendStatsText D_802D3A20;
extern u8 D_80127C40[];
extern u8 D_80127C48[];
extern u8 D_80127C58[];
typedef struct { u8 first, second; } FrontendModes;
extern FrontendModes D_80292674;
extern u8 D_80292728[];
extern u8 D_80292730[];
extern u8 D_8029273C[];

void func_801C7CD0(u8);
void func_801C7E4C(u8);
void func_801C7E98(u8, u8);
void func_801C7F10(void);
void func_801C7F90(void);
void func_801C8004(void);
s32 func_801C86A8(u8 *);
s32 func_801C8868(u8 *);
void func_801C8A38(u8 *, s32);
void func_801C8DBC(u8 *);
void func_801C8F28(u8 *);
char *func_801C9584(u8, u8);
void func_801CA784(s32);
void func_801CA7E4(s32);
void func_801CA91C(s32);
void func_801CBA2C(void);

/* Matrix-font calls use promoted color arguments; callees read low bytes. */
s32 func_801BD640(FrontendGfxWords **, void *, void *, f32, f32, f32, s32, s32, s32, s32);
s32 func_801BDA6C(FrontendGfxWords **, void *, void *, f32, f32, f32, s32, s32, s32, s32, f32);
s32 func_801BDF94(FrontendGfxWords **, void *, void *, f32, f32, f32, s32, f32, f32);
s32 func_801BE540(FrontendGfxWords **, void *, void *, f32, f32, f32, s32, s32, s32, s32, f32);
s32 func_801BE660(FrontendGfxWords **, void *, void *, f32, f32, f32, f32);

#endif
