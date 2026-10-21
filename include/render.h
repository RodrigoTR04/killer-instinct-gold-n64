#ifndef RENDER_H
#define RENDER_H
#include "common.h"

/* RSP records: eight-byte alignment is required by matrix callers. */
typedef union {
    s32 words[4][4];
    s64 alignment;
} RenderMtx;
typedef float RenderMatrixF[4][4];
typedef struct { u32 w0, w1; } RenderGfx;
typedef struct {
    s16 position[3], flag, uv[2];
    u8 color[4];
} RenderVertex;
/* Packed stage tags have variable lengths (9, 4, 2, or 3 bytes).
 * These views describe individual records, never a fixed-stride array. */
typedef struct { u8 tag, command[8]; } RenderStageRaw;
typedef struct { u8 tag, header[3]; } RenderStageTexture;
typedef struct { u8 tag, indices; } RenderStageTriangle;
typedef struct { u8 tag, offset, count; } RenderStageVertices;
/* Parallel texture length table: decoder in bits 15:13, count in 12:0. */
typedef struct { u16 encodedLength; } RenderTextureRecord;
typedef struct { u8 width, height, spacing, baseline; } RenderGlyph;
typedef struct { u8 r, g, b, a; } RenderColor;
typedef struct { RenderGlyph glyph; u8 reserved[4]; u8 runs[1]; } RenderGlyphImage;
typedef struct { float x,y,z,pitch,yaw; } RenderCameraPose;
/* D_800695B0..D_800695E0; globals retain their original linker names. */
typedef struct {
    s32 limit;
    s8 mode;
    u8 reserved[3];
    RenderCameraPose target;
    RenderCameraPose current;
    float roll;
} RenderCameraState;
typedef struct { s32 x,y,z; float worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } RenderWorldPoint;
typedef struct { s32 pad, x, y, z; u8 pad10[0x58]; s32 a, b; u32 distance; } RenderCameraInput;
typedef struct { u8 pad[0xC]; float x, z, y; } RenderCameraOutput;


/* Partial views of the larger objects used by the state machine. */
typedef struct {
    s32 x, y, z;
    float worldX, worldY, worldZ;
} RenderCameraObject;
typedef struct {
    float x, y, z, pitch, yaw, velocity, acceleration, pad, limit, pad24;
} RenderCameraPreset;
typedef struct {
    u8 reserved[0x29];
    u8 first, second;
} RenderCameraFade;
typedef struct {
    u8 reserved[0x10];
    s32 first;
    u8 middle[0xFC];
    s32 second;
} RenderCameraTracking;

extern void func_8002B7E0(void);
extern void func_8002B91C(float, float, float, float, float);
extern void func_8002B9B4(void);
extern void func_8002BAF0(RenderWorldPoint *);
extern void func_8002BB74(s32, s32, s32, float *, float *, float *);
extern void func_8002BBD0(RenderCameraObject *, RenderCameraObject *);
extern void func_8002DF98(float [4][4], float, float, float, float,
                         float *, float *, float *, float *);
extern void func_8002E08C(RenderCameraInput *, RenderCameraOutput *);
extern void func_8002FFDC(u8 *, s32, u8 *, s32, u32 *, RenderVertex *, u8 *);
extern void func_80030020(void **, void **, u16 *, u16);
extern void func_80030218(void);
extern void func_80030220(s16 *, s16 *, s32);
extern void func_8003037C(s16 *, s16 *, s32);
extern void func_80030440(u8 *, s32);
extern void func_800306B8(RenderGfx **, s32, s32, u8 *, s32, s32);
extern void func_8002B95C(u16 *,float,float,float,float,float);
extern void func_8002B8B0(s32);
extern float D_80048D70;
extern float D_800695B8;
extern float D_800695BC;
extern float D_800695C0;
extern float D_800695C4;
extern float D_800695C8;
extern float D_800695E0;
extern s32 D_800698C4;
extern u8 D_8004AC88;
extern s32 D_800695B0;
extern s8 D_800695B4;
extern float D_80069700[4][4];
extern void guPerspectiveF(float [4][4],u16 *,float,float,float,float,float);
extern u8 D_80044A24;
extern float D_800695CC;
extern float D_800695D0;
extern float D_800695D4;
extern float D_800695D8;
extern float D_800695DC;
extern float D_80069740[][4][4];
extern float D_80069840[][4][4];
extern float D_800697C0[][4][4];
extern float D_80069600[][4][4];
extern float D_80069680[][4][4];
extern void guRotateRPYF(void *,float,float,float),guTranslateF(void *,float,float,float),guMtxCatF(void *,void *,void *);
extern float D_8004AC84;
extern float D_8004AC80;
extern float D_80048EDC;
extern float sqrtf(float);
extern void func_8002DCC8(float, float, float, u32 *);
extern void func_8002DDD4(float, float, float, s32 *, s32 *);

extern RenderCameraPreset D_80044BCC[];
extern RenderCameraPose D_80044AC8[];
extern float D_80044BD8[];
extern u8 D_80044DD4[];
extern RenderCameraFade D_801C4198;
extern RenderCameraTracking D_801D3430;
extern RenderVertex D_80048290;
extern RenderColor D_800482A0[];
extern s32 D_800482B8[];
extern RenderGlyph D_80069E48[];
extern u8 D_80069F70[], D_80069930;
extern void func_8002FB80(u8 *, s32, u32, u32 *, u8 *);
extern void func_8002FDA0(u8 *, s32, RenderVertex *);
extern void func_800300DC(void *, void *, s32);
extern void func_8002A40C(void *, void *, s32);
extern s32 func_80030EF0(u8);
extern s32 guRandom(void);
extern void func_8002D9C4(RenderCameraPose *, s32, s32, s32);
extern double func_8002E150(double);
extern void func_8002DBDC(float, float *);
extern void func_8002DC48(float *);
typedef char RenderCameraStateSizeCheck[sizeof(RenderCameraState) == 0x34 ? 1 : -1];
typedef char RenderMtxSizeCheck[sizeof(RenderMtx) == 64 ? 1 : -1];
typedef char RenderVertexSizeCheck[sizeof(RenderVertex) == 16 ? 1 : -1];
typedef char RenderGlyphSizeCheck[sizeof(RenderGlyph) == 4 ? 1 : -1];
#endif
