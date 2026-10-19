/* T-019 nonmatching draft. Remaining diff: 428-byte body; segmented-address materialization is hoisted into the float conversion sequence, changing scheduling and later registers.
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

extern u32 D_2000000;

extern u8 D_802D4000[];
extern DisplayCommand D_80290BF0[], D_801CD490[];
extern s16 D_80290BE0[];
extern s32 D_802956F4;
void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
    
    { DisplayCommand *p1 = (*arg0)++;
    p1->w1 = 0;
    p1->w0 = 0xBC000006;
    }
    { DisplayCommand *p2 = (*arg0)++;
    p2->w0 = 0xBC000806;
    p2->w1 = (u32)(D_802D4000 + arg1->index * 0x96000) + 0x80000000;
    }
    arg1->unkF8 = (u8 *)arg1 + arg1->index * 0x4B00 + 0x100;
    D_802956F4 = 0;
    D_80290BE0[0] = arg1->width * 2;
    D_80290BE0[1] = arg1->height * 2;
    D_80290BE0[4] = arg1->width * 2;
    D_80290BE0[5] = arg1->height * 2;
    { DisplayCommand *p3 = (*arg0)++;
    p3->w1 = (u32)D_80290BF0;
    p3->w0 = 0x06000000;
    }
    { DisplayCommand *p4 = (*arg0)++;
    p4->w0 = 0xED000000;
    p4->w1 = (((s32)((f32)arg1->width * 4.0f) & 0xFFF) << 12) | ((s32)((f32)arg1->height * 4.0f) & 0xFFF);
    }
    { DisplayCommand *p5 = (*arg0)++;
    p5->w1 = (u32)D_801CD490;
    p5->w0 = 0x06000000;
    }
    { DisplayCommand *p6 = (*arg0)++;
    p6->w1 = (u32)&D_2000000;
    p6->w0 = ((arg1->width - 1) & 0xFFF) | 0xFF100000;
    }
}




