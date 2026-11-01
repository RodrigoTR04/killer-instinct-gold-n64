#include "common.h"

extern void boot_dma(s32, s32, s32);
extern void boot_inflate(void *, void *, void *);
extern void func_8001C05C(u8 *);

typedef struct {
    u8 *unk0; void *data; s16 halfWidth, halfHeight, width, height, width2, height2;
    u8 pad[4]; s16 flags; u8 pad2[2];
} T022Sprite;
extern T022Sprite D_8004CED0[];

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

void func_8001D768(s32 arg0, s32 *arg1) {
    T022Sprite *p = &D_8004CED0[arg0];
    p->data = arg1 + 2;
    p->flags = 7;
    p->width = arg1[0]; p->height = arg1[1];
    p->halfWidth = p->width / 2; p->halfHeight = p->height / 2;
    p->width2 = arg1[0]; p->height2 = arg1[1];
}

typedef struct { s32 zero; void *data; } T032Bank;
extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001D7E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_8001DE5C.s")

extern u8 D_8004AC88;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern u8 D_8004EA9E[];
s32 func_8001EC74(u8 **, s32, s32, u32, u32, s32, s32, s32);
extern u8 D_80046100;
extern u8 D_8004A408;
typedef struct { u8 pad[12]; f32 x,y,z; u8 tail[24]; } T032Pos24B;
extern T032Pos24B D_8004A450[];
extern s16 D_8004CEE8;
extern s16 D_8004D26E;
extern s32 D_8004EA78;
extern u8 D_801D3430;
extern u16 D_801D876C;
extern u8 D_801D8770;
extern u8 D_801D87E0;
extern u8 D_801D87E1;
void func_8001E0B4(u8 **arg0)
{
    u8 fullScaleY;

    s32 size;
    u8 fade;
    int flipped;
    s32 playerNumber;
    s32 player;
    s32 flip;
    u32 scaleY;
    u32 scaleX;
    u8 palette;
    u8 *state;
    u8 *command;
    command = *arg0;
    *arg0 += 8;
    /* Keep the command pair together for IDO store scheduling. */
    *(s32 *)command = 0x06000000; *(u8 **)(command + 4) = &D_80046100;
    for (player = 0; player != 2; player++)
    {
        if ((D_801D876C == 0) || (player != *(&D_801D8770 + 1)))
        {
            if (*(u16 *)((u8 *)D_8004A450 + player * 0x30 + 0x22) != 0xBE)
            {
                state = &D_801D3430 + (player << 8);
                if (*(state - 0x17C) == 0)
                {
                    playerNumber = player + 1;
                    if (playerNumber != D_8004A408)
                    {
                        flipped = (s32)*((u8 *)D_8004A450 + player * 0x30 + 0x21) >= 0x80;
                        fullScaleY = D_8004AC88;
                        D_8004D26E = 0;

                        if (flipped)
                        {
                            flip = 1;
                        }
                        else
                        {
                            flip = 0;
                        }
                        scaleX = *(u16 *)(state + 0x58);
                        D_8004EA78 = player;
                        scaleY = *(u16 *)(state + 0x5A);
                        if (scaleX == 0)
                        {
                            scaleX = 0x1000;
                        }
                        if (scaleY == 0)
                        {
                            scaleY = 0x1000;
                        }
                        if (fullScaleY == 0)
                        {
                            scaleY = (s32)scaleY / 2;
                        }
                        if (playerNumber == D_801D87E0)
                        {
                            if (D_801D87E1 != 0)
                            {
                                D_8004D26E = 0x80 - (D_801D87E1 * 2);
                            }
                        }
                        else
                        {
                            D_8004D26E = 0x80;
                        }
                        fade = *(state - 0x170);
                        if (fade != 0)
                        {
                            if (((s32) fade) < 0x40)
                            {
                                D_8004D26E = 0x80 - (fade * 2);
                            }
                            else
                            {
                                D_8004D26E = 0;
                            }
                        }
                        if (*(s16 *)((u8 *)&D_8004CEE8 + D_8004EA78 * 0x1C) != 5)
                        {
                            if (D_8004EA9E[player] == 9)
                            {
                                palette = 1;
                            }
                            else
                            {
                                palette = (u8) D_8004AC89;
                            }
                            if (!(*(state + 0x95) & 0x10))
                            {
                                size = *(s32 *)(state + 0x70);
                                func_8001EC74(arg0, *(s32 *)(state + 0x68) / 16, *(s32 *)((u8 *)D_8004A450 + player * 0x30 + 0x1C), (u32)(size * scaleX) >> 12, (u32)(size * scaleY) >> 12, (s32) palette, flip, (u8)D_8004AC8A);
                            }
                        }
                    }
                }
            }
        }
    }

}

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

extern void boot_dma(s32, s32, s32);
extern void func_800245B4(s32, void *, s32);
extern u8 D_8B70[], D_119F0[], D_48FD0[], D_2ECB0[];
void func_800244F0(s32 player)
{
  /* Naming the ROM address retains the original IDO stack layout. */
  s32 romStart;
  u8 *base;
  u32 size;
  if (player == 0)
  {
    base = (u8 *) 0x8020B480;
  }
  else
  {
    base = (u8 *) 0x802D7A40;
  }
  func_800245B4(player, base + 0x493E0, 0x2F760);
  base = (u8 *) ((((u32) ((base + ((u32) D_48FD0)) - ((u32) D_2ECB0))) + 15) & (~15));
  size = ((s32) D_119F0) - ((s32) D_8B70);
  romStart = (s32) D_8B70;
  boot_dma(romStart, (s32) base, size);
  func_800245B4(player, base, size);
  D_8004D278.banks[player].data = base;
  D_8004D278.banks[player].zero = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_D3F0/func_800245B4.s")

extern u8 D_8004AC88;
typedef struct { u8 pad0[3144]; u8 *slotC48; u8 *slotC4C; u8 padC50[16]; u8 *slotC60; u8 *slotC64; u8 padC68[16]; u8 *slotC78; u8 *slotC7C; u8 padC80[16]; u8 *slotC90; u8 *slotC94; u8 padC98[928]; u8 *slot1038; u8 *slot103C; u8 pad1040[352]; u8 *slot11A0; u8 *slot11A4; } T032Resource714;
extern u8 D_1EB6D0[],D_1F3200[],D_2C2280[],D_2CF0A0[],D_469660[],D_470390[],D_53CC40[],D_543D10[],D_8004EA9C[],D_8004F396[];
extern u8 D_8004F395;
extern void boot_dma(s32,s32,s32),boot_dma_chunked(void *,void *,s32),func_800245B4(s32,void *,s32),func_80030220(void *,void *,s32);
void func_80024714(s32 arg0) {
    s32 temp_v0;
    T032Resource714 *temp_v0_2;
    T032Resource714 *temp_v0_3;
    u8 *var_s0;
    T032Resource714 *var_v0;

    if (arg0 == 0) {
        var_s0 = (void *)0x802A9F90;
    } else {
        var_s0 = (void *)0x80376550;
    }
    if (D_8004AC88 == 0xC) {
        var_s0 = (void *)0x80320000;
    }
    temp_v0 = D_8004EA9C[arg0];
    switch (temp_v0) {                              /* irregular */
    case 1:
        boot_dma((s32)(D_1EB6D0), (s32)( var_s0),  (s32)D_1F3200 - (s32)D_1EB6D0);
        temp_v0_2 = (T032Resource714 *)((u8 *)&D_8004D278 + arg0 * 8);
        temp_v0_2->slotC60 = var_s0;
        temp_v0_2->slotC64 = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        temp_v0_2->slotC78 = var_s0;
        temp_v0_2->slotC7C = 0;
        break;
    case 2:
        boot_dma((s32)(D_2C2280), (s32)( var_s0),  (s32)D_2CF0A0 - (s32)D_2C2280);
        temp_v0_3 = (T032Resource714 *)((u8 *)&D_8004D278 + arg0 * 8);
        temp_v0_3->slotC60 = var_s0;
        temp_v0_3->slotC64 = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        temp_v0_3->slotC90 = var_s0;
        temp_v0_3->slotC94 = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        temp_v0_3->slot1038 = var_s0;
        temp_v0_3->slot103C = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        temp_v0_3->slot11A0 = var_s0;
        temp_v0_3->slot11A4 = 0;
        break;
    case 4:
        boot_dma((s32)(D_469660), (s32)( var_s0),  (s32)D_470390 - (s32)D_469660);
        var_v0 = (T032Resource714 *)((u8 *)&D_8004D278 + arg0 * 8);
        var_v0->slotC78 = var_s0;
        var_v0->slotC7C = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        var_v0->slotC90 = var_s0;
        var_v0->slotC94 = 0;
        break;
    case 5:
        boot_dma((s32)(D_53CC40), (s32)( var_s0),  (s32)D_543D10 - (s32)D_53CC40);
        var_v0 = (T032Resource714 *)((u8 *)&D_8004D278 + arg0 * 8);
        var_v0->slotC48 = var_s0;
        var_v0->slotC4C = 0;
        var_s0 = (u8 *)((u32)var_s0 + var_s0[4] + ((u32)var_s0[5] << 8) + ((u32)var_s0[6] << 16) + ((u32)var_s0[7] << 24));
        var_v0->slotC90 = var_s0;
        var_v0->slotC94 = 0;
        break;
    }
    D_8004F396[arg0] = 1;
}

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

typedef struct { u32 w0,w1; } T032Gfx24B;
extern u8 D_471440[],D_472FB0[],D_80046130[];
extern u8 D_80044A24;
extern f32 D_8004AC84,D_800695DC,D_800695E0;
extern void guTranslate(void *,f32,f32,f32),guRotateRPY(void *,f32,f32,f32),guScale(void *,f32,f32,f32);
typedef union { u64 align; u8 bytes[64]; } T102Matrix;
void func_80024B0C(T032Gfx24B **dl,s32 player) {
    T032Pos24B *pos = &D_8004A450[player ^ 1];
    T102Matrix *base = (void *)(D_472FB0 - D_471440 + 0x8023D400);

    f32 scale;
    /* Matrices are 64 bytes; keep byte offsets explicit for IDO scheduling. */
    guTranslate(((u8 *)base + ((D_80044A24 * 3) << 6)),pos->x,pos->y,pos->z);
    guRotateRPY(((u8 *)base + ((D_80044A24 * 3 + 1) << 6)),0.0f,-D_800695DC,D_800695E0);
    scale = 230.0f / D_8004AC84;
    guScale(((u8 *)base + ((D_80044A24 * 3 + 2) << 6)),scale,scale,scale);
    { T032Gfx24B *p = (*dl)++; p->w0 = 0x01040040; p->w1 = (u32)(((u8 *)base + ((D_80044A24 * 3) << 6))); }
    { T032Gfx24B *p = (*dl)++; p->w0 = 0x01000040; p->w1 = (u32)(((u8 *)base + ((D_80044A24 * 3 + 1) << 6))); }
    { T032Gfx24B *p = (*dl)++; p->w0 = 0x01000040; p->w1 = (u32)(((u8 *)base + ((D_80044A24 * 3 + 2) << 6))); }
    { T032Gfx24B *p = (*dl)++; p->w0 = 0x06000000; p->w1 = (u32)D_80046130; }
}
