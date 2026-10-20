#include "common.h"

extern void boot_dma(s32, s32, s32);
extern void boot_inflate(void *, void *, void *);
extern void func_8001C05C(u8 *);

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001CD50.s")

extern u8 D_8004EA9C[];
s32 osMapTLB(s32, s32, s32, s32, s32, s32);
s32 osUnmapTLB(s32);

void func_8001CF1C(void) {
    s32 i;

    for (i = 0; i < 31; i++) {
        osUnmapTLB(i);
    }
    osMapTLB(0, 0, 0, 0x3A4000, -1, -1);
    for (i = 0; i < 5; i++) {
        osMapTLB(i + 1, 0, (D_8004EA9C[0] << 16) + i * 0x2000 + 0x10000, 0x1DB000 + i * 0x2000, 0x1DC000 + i * 0x2000, -1);
    }
    if (D_8004EA9C[0] != D_8004EA9C[1]) {
        for (i = 0; i < 5; i++) {
            osMapTLB(i + 6, 0, (D_8004EA9C[1] << 16) + i * 0x2000 + 0x10000, 0x1E5000 + i * 0x2000, 0x1E6000 + i * 0x2000, -1);
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001D080.s")


typedef struct { u8 *start; u8 pad[28]; } T022DmaEntry;

extern T022DmaEntry D_80045E68[];
extern u8 D_8004EA9E[];
extern u8 D_8004CE90[][32], D_8004CEB0[], D_8004EA9F;
void func_8001D37C(u8 arg0, u8 arg1) {
    s32 index = arg0;
    boot_dma((s32)(((D_8004EA9E[0] == 9 ? 0 : D_8004EA9E[0]) << 5) + D_80045E68[index].start), (s32)D_8004CE90, 0x20);
    boot_dma((s32)(((D_8004EA9F == 9 ? 0 : D_8004EA9F) << 5) + D_80045E68[arg1].start), (s32)D_8004CEB0, 0x20);
}

void func_8001D42C(u8 arg0, u8 arg1, void *arg2) {
    s32 index = (u8)arg0;
    boot_dma((s32)(D_80045E68[index].start + (arg1 << 5)), (s32)arg2, 0x20);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001D47C.s")

typedef struct {
    s32 unk0; void *data; s16 halfWidth, halfHeight, width, height, width2, height2;
    u8 pad[4]; s16 flags; u8 pad2[2];
} T022Sprite;
extern T022Sprite D_8004CED0[];
void func_8001D768(s32 arg0, s32 *arg1) {
    T022Sprite *p = &D_8004CED0[arg0];
    p->data = arg1 + 2;
    p->flags = 7;
    p->width = arg1[0]; p->height = arg1[1];
    p->halfWidth = p->width / 2; p->halfHeight = p->height / 2;
    p->width2 = arg1[0]; p->height2 = arg1[1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001D7E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001DE5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001E0B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001E33C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001EC74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80020E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800216D4.s")

#ifndef T032_ROM_ENTRY_DEFINED
#define T032_ROM_ENTRY_DEFINED
typedef struct {
    u8 *start, *end, *palette;
    u32 flags;
    u8 *spriteStart, *spriteEnd;
    u8 tail[8];
} T032RomEntry;
#endif
extern T032RomEntry D_80045E50[];
extern u8 D_8011E670[];
void func_80021ADC(u8 player, u8 entry) {
    T032RomEntry *p = &D_80045E50[entry];
    u8 *start = p->spriteStart;
    u32 size = p->spriteEnd - start;
    if (size < 0x321U) {
        boot_dma((s32)start, 0x802D4000, size);
        boot_inflate((void *)0x802D4000, D_8011E670 + player * 0x320, (void *)0x803A2000);
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80021B6C.s")

extern s32 D_8004EA78;
extern u16 D_8004EAC8[][256][2];
s32 func_8002365C(u16 count,u16 start) {
    s32 i; u16 result=320;
    for (i=0;i<count;i++) result=D_8004EAC8[D_8004EA78][start+i][0] >= result ? result : D_8004EAC8[D_8004EA78][start+i][0];
    return result;
}


s32 func_80023790(u16 count,u16 start) {
    s32 i; u16 result=0;
    for (i=0;i<count;i++) result=D_8004EAC8[D_8004EA78][start+i][1] < result ? result : D_8004EAC8[D_8004EA78][start+i][1];
    return result;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800238C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80023EF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80024028.s")

extern void func_80020E98(u8,u8,void *);
extern s32 D_80045FE8;
extern u8 D_8004F394;
void func_80024144(s32 player,s32 kind) {
    s32 offset;
    func_80020E98((u8)player,12,0);
    if (kind==0xBA) offset=32; else offset=0;
    boot_dma(D_80045FE8 + offset,(s32)D_8004CE90[player],32);
    D_8004F394=1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800241BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800244F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800245B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80024714.s")

typedef struct T055MoveKind {
    u8 id;
    u8 kind;
} T055MoveKind;
extern u8 D_8004EA9A;
extern T055MoveKind D_80046010[][7];

void func_800249DC(s32 player, s32 id, u8 *kind) {
    s32 i;

    if (id == 199) {
        *kind = 5;
    } else {

        for (i = 0; i < 7; i++) {
            if (id == D_80046010[D_8004EA9C[player]][i].id) goto found;
        }
        i = 0;
found:
        *kind = D_80046010[D_8004EA9C[player]][i].kind;
        if (id == 176 && D_8004EA9C[player] == 9) *kind = 5;
    }
    switch (*kind) {
        case 0: D_8004EA78 = player + 2; break;
        case 1: D_8004EA78 = player + 18; break;
        case 2: D_8004EA78 = player + 20; break;
        case 3: D_8004EA78 = player + 22; break;
        case 4: D_8004EA78 = player + 24; break;
        case 5: D_8004EA78 = player + 26; break;
        default: D_8004EA78 = player + 2; break;
    }
    D_8004EA9A = *kind + 5;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_80024B0C.s")
