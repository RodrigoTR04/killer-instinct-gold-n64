/* T-138 DRAFT: 63 differing words, 808/808 B. Command-word ordering and a structured argument view affect scheduling. Not matching. */
/* T-122 nonmatching: 150 differing words; 808 compiled bytes. See T-122/REPORT.md. */
/* DRAFT. Remaining diff: Display-list pointer/register allocation and command-store scheduling differ. */
#include "frontend.h"
extern s32 D_801F3D6C; extern s32 D_801F3D70; extern u8 D_802C9020[]; extern u8 D_802C9D20[]; extern s32 D_802C9F64; typedef struct { u8 pad[0xE8]; s32 x, y; } T138View;
void func_801BBE88(FrontendGfxWords **arg0, T138View *arg1) {
    s32 *height = &D_802C9F64; s32 temp_a2; FrontendGfxWords *g; { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xFD100000; q->w1 = &D_802C9D20; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE8000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5000100; q->w1 = (u32)0x07000000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE6000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF0000000; q->w1 = (u32)0x073FC000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xBA000E02; q->w1 = (u32)0x8000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xFD500000; q->w1 = &D_802C9020; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5500000; q->w1 = (u32)0x07018060; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE6000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF3000000; q->w1 = (u32)0x075FF100; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5481000; q->w1 = (u32)0x18060; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF2000000; q->w1 = (u32)0xFC0BC; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0x2F00BCC0; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xFCFFFFFF; q->w1 = (u32)0xFFFCF279; } if (*height != 0) {
        g = *arg0; *arg0 = g + 1; g->w0 = (s32) ((((D_801F3D70 * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((arg1->y * 4) & 0xFFF)); g->w1 = (u32) ((((D_801F3D6C * 4) & 0xFFF) << 0xC) | ((*height * 4) & 0xFFF)); g = *arg0; *arg0 = g + 1; g->w0 = 0; temp_a2 = arg1->y; g->w1 = (u32) ((((s32) (temp_a2 * 0x41) / (s32) (temp_a2 - *height)) & 0xFFFF) | 0xC80000); return; }
    g = *arg0; *arg0 = g + 1; g->w0 = (s32) ((((arg1->x * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((arg1->y * 4) & 0xFFF)); g->w1 = 0; g = *arg0; *arg0 = g + 1; g->w0 = 0; g->w1 = (u32)0xC80041; }
