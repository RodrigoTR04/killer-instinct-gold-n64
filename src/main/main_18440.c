#include "common.h"

extern void guOrtho(void *, f32, f32, f32, f32, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern u8 D_80061D20[], D_80061CE0[];
void func_80027DA0(void) {
    guOrtho(D_80061D20, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f, 10.0f, 1.0f);
    guRotate(D_80061CE0, 0, 0.0f, 0.0f, 1.0f);
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80027E1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_800281C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80028230.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80028600.s")

extern u8 D_80061CD4,D_80061CD5;
extern s16 D_80061CD6;
extern u32 func_800326F0(void);
void func_80028708(void) {
    if (D_80061CD4!=255) {
        if (D_80061CD6>0) {
            D_80061CD6--;
            return;
        }
        D_80061CD5^=1;
        D_80061CD6=func_800326F0()&0x1FF;
        if (D_80061CD5==1) D_80061CD6=(D_80061CD6*255)/(256-D_80061CD4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_800287D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80028A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_8002970C.s")

typedef struct { u8 pad[0x12C]; s16 timer; u8 tail[0x12]; } T024ResetEffect;
extern T024ResetEffect D_80061D60[];
void func_80029770(void) {
    s32 i;
    for (i=0;i<4;i++) D_80061D60[i].timer=-1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_800297A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80029AB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80029BE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_8002A004.s")
