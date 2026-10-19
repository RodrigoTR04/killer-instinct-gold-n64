/* T-019 nonmatching draft. Remaining diff: 544-byte reconstruction versus 556-byte target; command-pointer increments/stores are folded, changing scheduling and registers.
 */
#include "common.h"
typedef struct RenderState {
    s32 index, unk4;
    u8 pad8[0xCC];
    f32 unkD4, unkD8, unkDC, unkE0, unkE4;
    s32 width, height, mode, height2;
    void *unkF8;
} RenderState;
typedef struct DisplayCommand { u32 w0, w1; } DisplayCommand;
extern void osViBlack(s32);
extern u8 D_80044A24, D_80295721;
extern s32 D_8004A414;
extern u8 D_8004A298[], D_802D4000[];

typedef struct GraphicsTask {
    s32 unk0, unk4, unk8, unkC;
    void *framebuffer;
    s32 unk14, type, flags;
    void *boot; s32 bootSize;
    void *code; s32 codeSize;
    void *stack; s32 stackSize;
    void *output; s32 outputSize;
    s32 unk40, unk44;
    DisplayCommand *commands; s32 commandSize;
    void *yield; s32 yieldSize;
    void *queue, *message;
} GraphicsTask;
extern GraphicsTask D_8004A320[], *D_8004A318;
extern u8 D_8000C3C8[], D_8000CF50[], D_80042710[], D_800427E0[], D_80049770[], D_80068530[];
extern u8 D_8004A2D8[][32];
extern s32 osSendMesg(void *, void *, s32);
extern void osWritebackDCacheAll(void);
void func_801AD7D8(DisplayCommand *arg0, DisplayCommand **arg1, s32 arg2, s32 arg3, s32 *arg4) {
    DisplayCommand *p = *arg1;
    p->w0 = 0xE9000000; p->w1 = 0;
    p++; p->w0 = 0xB8000000; p->w1 = 0; p++;
    D_8004A318 = &D_8004A320[*arg4];
    D_8004A318->unk0 = arg2; D_8004A318->unk4 = arg3;
    osWritebackDCacheAll();
    D_8004A318->commands = arg0;
    D_8004A318->commandSize = (p - arg0) * 8;
    D_8004A318->type = 1; D_8004A318->flags = 2;
    D_8004A318->boot = D_80042710;
    D_8004A318->bootSize = D_800427E0 - D_80042710;
    D_8004A318->code = D_800427E0;
    D_8004A318->stack = D_80049770; D_8004A318->stackSize = 0x800;
    D_8004A318->output = D_80068530; D_8004A318->outputSize = 0x400;
    D_8004A318->unk40 = 0; D_8004A318->unk44 = 0;
    D_8004A318->yield = D_8000C3C8; D_8004A318->yieldSize = 0x900;
    D_8004A318->unkC = 0x63;
    D_8004A318->queue = D_8004A298;
    D_8004A318->message = D_8004A2D8[*arg4];
    D_8004A318->framebuffer = D_802D4000 + *arg4 * 0x96000;
    osSendMesg(D_8000CF50, D_8004A318, 1);
    if (D_80295721 > 0) D_80295721--; else osViBlack(0);
    *arg4 ^= 1; D_80044A24 = *arg4; D_8004A414++;
}


