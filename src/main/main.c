#include "common.h"

extern u8 D_8004A230[], D_80127C30[], D_80128350[], D_8006F1C0[];
extern void *D_8004A294;
extern u8 D_8004A298[], D_8004A2D0[], D_8004EA9C[], D_8004EA9E[];
extern s32 D_8004A414, D_80127D80;
extern void bzero(void *, s32);
extern void func_8000FA50(void), boot_init_scheduler(void), boot_init_dma_events(void);
extern void func_8002A4F0(void), func_80027DA0(void), func_8002B500(void), func_8000FA80(void);
extern void osViBlack(s32);
extern void boot_subscribe_retrace(void *, void *);
extern void func_8002FAC0(s32, s32);
extern void func_8002A900(s32);

void func_8000F960(void) {
    bzero(D_8004A230, D_80127C30 - D_8004A230);
    bzero(D_80128350, 0x4A380);
    D_8004A294 = D_8006F1C0;
    func_8000FA50();
    boot_init_scheduler();
    osViBlack(1);
    boot_subscribe_retrace(D_8004A2D0, D_8004A298);
    boot_init_dma_events();
    func_8002A4F0();
    func_8002FAC0(0, 0x4E20);
    func_80027DA0();
    D_8004EA9C[0] = 0;
    D_8004EA9C[1] = 0;
    D_8004A414 = 0;
    D_8004EA9E[0] = 0;
    D_8004EA9E[1] = 0;
    D_80127D80 = 0;
    func_8002B500();
    for (;;) {
        func_8000FA80();
        func_8002A900(0x11);
    }
}

extern u8 D_8004A298[], D_8004A2B0[];
extern void osCreateMesgQueue(void *, void *, s32);

void func_8000FA50(void) {
    osCreateMesgQueue(D_8004A298, D_8004A2B0, 8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8000FA80.s")

typedef struct { u16 buttons; s8 x, y; } T020Controller;

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001178C.s")

extern u16 D_80127CA8[][6];

s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
    s32 result;
    s8 x, y;
    u32 buttons;
    u16 *map;
    map = D_80127CA8[arg1];
    result = 0;
    if ((buttons = arg0->buttons) & map[3]) result = 8;
    if (map[0] & buttons) result |= 1;
    if (map[1] & buttons) result |= 2;
    if (map[4] & buttons) result |= 0x10;
    if (map[2] & buttons) result |= 4;
    if (map[5] & buttons) result |= 0x20;
    if (buttons & 0x800) result |= 0x40;
    if (buttons & 0x400) result |= 0x80;
    if (buttons & 0x200) result |= 0x100;
    if (buttons & 0x100) result |= 0x200;
    x = arg0->x;
    if (x >= 41) result |= 0x200;
    if (x < -40) result |= 0x100;
    y = arg0->y;
    if (y >= 41) result |= 0x40;
    if (y < -40) result |= 0x80;
    return result;
}


typedef struct { u8 *start; u8 *end; } T020Range12100;
extern T020Range12100 D_80007208[];
extern void func_80012338(void *, void *, s32);
extern void boot_dma_chunked(void *, void *, s32);

void func_80012100(u8 arg0, u8 arg1) {
    boot_dma_chunked(D_80007208[arg0].start, (void *)0x802D4000, D_80007208[arg0].end - D_80007208[arg0].start);
    func_80012338((void *)0x802D4000, (void *)0x801DB000, D_80007208[arg0].end - D_80007208[arg0].start);
    boot_dma_chunked(D_80007208[arg1].start, (void *)0x802D4000, D_80007208[arg1].end - D_80007208[arg1].start);
    func_80012338((void *)0x802D4000, (void *)0x801E5000, D_80007208[arg1].end - D_80007208[arg1].start);
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800121C8.s")

void func_800122F8(s16 *arg0) {
    s32 i;
    for (i = 0; i < 0x12BFF; i++) {
        arg0[i] = 0;
    }
}

extern void boot_inflate(void *, void *, void *);

void func_80012338(void *arg0, void *arg1, s32 arg2) {
    boot_inflate(arg0, arg1, (void *)0x803A2000);
}

extern void func_80012390(void);
extern void func_80020E98(s32, s32, s32);

void func_80012360(void) {
    func_80012390();
    func_80020E98(1, 13, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012390.s")

typedef struct { u32 command, value; } T033Gfx;
extern u8 D_80044A24;
extern u32 D_8004A428[];

void func_8001256C(T033Gfx **arg0, u8 red, u8 green, u8 blue)
{
  s32 color;

  /* Keep paired command stores together: their line layout affects IDO scheduling. */
  {
    T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xE7000000;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->value = 0x300000;
    g->command = 0xBA001402;
  }
 {
    T033Gfx *g = (*arg0)++;
    g->command = 0xFCFFFFFF; g->value = 0xFFFE793C;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->command = 0xB900031D; g->value = 0x0F0A4000;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->command = 0xFF10013F;
    g->value = D_8004A428[D_80044A24];
  }
  {
    T033Gfx *g = (*arg0)++;
    g->command = 0xF7000000;
    color = ((red << 8) & 0xF800) | ((green << 3) & 0x7C0) | ((blue >> 2) & 0x3E) | 1;
    g->value = color;
    g->value = (g->value << 16) | color;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xF64FC3BC;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xE7000000;
  }
  {
    T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xBA001402;
  }
}

extern void *D_8004A258[];
extern s32 D_8004A280;
extern void func_8002F8F8(void *);

void func_800126D0(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_8004A258[i] != 0) {
            func_8002F8F8(D_8004A258[i]);
        }
    }
    D_8004A280 = 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001272C.s")
