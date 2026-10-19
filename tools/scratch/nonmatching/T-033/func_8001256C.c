/* DRAFT. Remaining diff: 63 positional differing words; 356/356 bytes */
typedef struct { u32 command, value; } T033Gfx;
extern u8 D_80044A24;
extern u32 D_8004A428[];

void func_8001256C(T033Gfx **arg0, u8 red, u8 green, u8 blue) {
    s32 color;
    { T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xE7000000;
    }
    { T033Gfx *g = (*arg0)++;
    g->value = 0x300000;
    g->command = 0xBA001402;
    }
    { T033Gfx *g = (*arg0)++;
    g->command = 0xFCFFFFFF;
    g->value = 0xFFFE793C;
    }
    { T033Gfx *g = (*arg0)++;
    g->value = 0x0F0A4000;
    g->command = 0xB900031D;
    }
    { T033Gfx *g = (*arg0)++;
    g->command = 0xFF10013F;
    g->value = D_8004A428[D_80044A24];
    }
    { T033Gfx *g = (*arg0)++;
    g->command = 0xF7000000;
    color = ((red << 8) & 0xF800) | ((green << 3) & 0x7C0) | ((blue >> 2) & 0x3E) | 1;
    g->value = (color << 16) | color;
    }
    { T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xF64FC3BC;
    }
    { T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xE7000000;
    }
    { T033Gfx *g = (*arg0)++;
    g->value = 0;
    g->command = 0xBA001402;
    }
}
