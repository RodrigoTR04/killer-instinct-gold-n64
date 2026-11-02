/* T-151 rewrite of func_801C5E74 (full-TU draft). */
typedef struct { s32 id, ticks; u8 pad8[0xF0]; u8 *matrices; } T030Render5E74;
typedef struct { u32 start, end; } T030Asset5E74;
typedef struct { u8 pad[12]; u8 *texture; u8 tail[0x7C]; } T030Sprite5E74;
extern void boot_dma(s32, s32, s32);
extern s32 boot_inflate(void *, void *, void *);
extern void func_8002AAEC(s32);
extern void func_801ADB20(void);
extern void func_801BC1B0(T021Gfx **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 func_801BDF94(T021Gfx **, void *, void *, f32, f32, f32, s32, f32, f32);
extern void func_801C0610(T021Gfx **);
extern void func_801C2D34(T021Gfx **, s32, s32, s32, s32);
extern void func_801C4D6C(void);
extern u8 D_8004A422[], D_8004A430[], D_8007D900[], D_8007DC00[], D_800CA610[], D_800CC610[];
extern T030Sprite5E74 D_801F2EA8[];
extern T030Asset5E74 D_80291FE8[];
extern u8 D_80292050[];
const u8 D_80294864[] = "PLAYER ONE";
const u8 D_80294870[] = "PLAYER TWO";
const u8 D_8029487C[] = "WINNING TEAM";
extern s16 D_802920E0[];
extern s32 D_802956F4;
extern u8 D_80295720;
extern u8 *D_802CA068, *D_802D3980;
extern u8 D_802D3985, D_802D39BA;
extern s32 D_802D39B0;
extern u16 D_802D39B8;

#define PUT(g, w0v, w1v) { g = *arg0; *arg0 = g + 1; g->w0 = (w0v); g->w1 = (w1v); }
#define PUTR(g, w0v, w1v) { g = *arg0; *arg0 = g + 1; g->w1 = (w1v); g->w0 = (w0v); }

u8 func_801C5E74(T021Gfx **arg0, T030Render5E74 *arg1, s32 arg2) {
    u8 *dc;
    u8 **bufp;
    s32 flags;
    s32 second;
    s32 alpha = 255;
    u8 *rgb;
    u16 *palette;
    s32 i;
    s32 start;
    T021Gfx *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7;
    s32 count, solid;
    u8 *name;
    T021Gfx *q0, *q1, *q2;
    T021Gfx *r0, *r1, *r2, *r3, *r4, *r5, *r6, *r7;
    s32 j;
    s16 v;
    s32 y;
    u8 *texture;
    u32 labels;

    if ((D_802D3985 == 5 || D_802D3985 == 1) && D_802D39B8 < 0x7918) {
        func_8002AAEC(0x7FFF - D_802D39B8);
        D_802D39B8 += 0x300;
    }
    if (D_80291FE8[D_802D3985].start == 0) {
        D_802D39BA &= 0xFD;
        func_801C4D6C();
    }
    bufp = &D_802D3980;
    if (*bufp == 0 && (D_802D39BA & 2)) {
        start = D_80291FE8[D_802D3985].start;
        *bufp = D_800CA610;
        boot_dma(start, (s32)D_800CC610, D_80291FE8[D_802D3985].end - start);
        func_801ADB20();
        boot_inflate(*bufp + 0x2000, D_8007D900, *bufp);
        {
            rgb = D_8007D900;
            palette = (u16 *)D_8007D900;
            for (i = 0; i < 256; i++) {
                palette[i] = ((rgb[i * 3] << 8) & 0xF800) | ((rgb[i * 3 + 1] * 8) & 0x7C0) | ((rgb[i * 3 + 2] >> 2) & 0x3E) | 1;
            }
        }
    }
    flags = D_802D39BA;
    second = flags & 2;
    if (flags & 6) {
        if (second) {
            alpha = (500 - arg2) << 2;
        } else {
            alpha = (700 - arg2) << 2;
        }
        if (alpha < 255) {
            if (alpha < 0) {
                alpha = 0;
            }
        } else {
            alpha = 254;
        }
    }
    if (arg2 < 64) {
        alpha = arg2 * 4;
    }
    dc = D_8007DC00;
    if (second) {
        func_801C51F8(arg0);
        PUT(p0, 0xFD100000, (u32)D_8007D900);
        PUTR(p1, 0xE8000000, 0);
        PUTR(p2, 0xF5000100, 0x07000000);
        PUTR(p3, 0xE6000000, 0);
        PUTR(p4, 0xF0000000, 0x073FC000);
        PUTR(p5, 0xE7000000, 0);
        PUTR(p6, 0x06000000, (u32)D_80292050);
        if (alpha < 255) {
            PUT(p7, 0xFB000000, ((alpha & 0xFF) << 24) | ((alpha & 0xFF) << 16) | ((alpha & 0xFF) << 8) | 0xFF);
        }
        func_801BC1B0(arg0, dc, 2, 0x100, 0x96, 0x20, 0x1E, 0, 0, 0xFF, 0x95, 0.0f, 0.0f, 0xA00, 0);
        flags = D_802D39BA;
    }
    if (flags & 0xC) {
        func_801C0610(arg0);
        flags = D_802D39BA;
    }
    if (flags & 6) {
        func_801C5064((s32)arg0, (T030Render5064 *)arg1, (u8)alpha, (flags & 2) == 0);
        flags = D_802D39BA;
    }
    if ((flags & 8) && D_80295720 != 0) {
        labels = (u32)D_80292050;
        name = D_80294864;
        solid = D_8004A430[D_80295720 * 16 - 16];
        count = D_8004A430[D_80295720 * 16 - 15];
        if (D_80295720 == 2) {
            name = D_80294870;
        }
        PUTR(q0, 0xBA001301, 0x80000);
        func_801C2D34(arg0, 1000, -250, -600, arg1->ticks);
        D_802956F4 += func_801BDF94(arg0, (D_802956F4 << 6) + D_802CA068, name, -320.0f, 210.0f, -500.0f, 0, 1.0f, 0.0f);
        D_802956F4 += func_801BDF94(arg0, (D_802956F4 << 6) + D_802CA068, D_8029487C, -360.0f, 150.0f, -500.0f, 0, 1.0f, 0.0f);
        PUT(q1, 0x06000000, labels);
        PUTR(q2, 0xBA000E02, 0);
        if (count > 0) {
            for (j = 0; j < count; j++) {
                texture = D_801F2EA8[D_8004A422[j + D_80295720 * 16]].texture;
                PUTR(r0, 0xE7000000, 0);
                if (j < solid) {
                    PUTR(r1, 0xFC11FE23, -0x805);
                } else {
                    PUTR(r1, 0xFCFFFFFF, 0xFFFCF279);
                }
                v = D_802920E0[count * 11 - 11 + j];
                y = -0x32;
                if (v >= 0x1F5) {
                    v -= 0x3E8;
                    y = 0x32;
                }
                if (v >= 0x1F5) {
                    v -= 0x3E8;
                    y = 0x96;
                }
                PUTR(r2, 0xFD100000, (u32)texture);
                PUTR(r3, 0xF5100000, 0x07080200);
                PUTR(r4, 0xE6000000, 0);
                PUTR(r5, 0xF3000000, 0x0778F0BB);
                PUTR(r6, 0xE7000000, 0);
                PUT(r7, 0xF5101600, 0x80200);
                PUT(r6, 0xF2000000, 0xAC0AC);
                PUT(r7, (((v + 0x182) * 4 & 0xFFF) << 12) | 0xE4000000 | ((y + 0x132) * 4 & 0xFFF),
                    (((v + 0x140) * 4 & 0xFFF) << 12) | ((y + 0xF0) * 4 & 0xFFF));
                PUTR(r2, 0xB3000000, 0x560);
                PUT(r3, 0xB2000000, 0x02AAFD56);
            }
        }
    }
    flags = D_802D39BA;
    if (flags & 2) {
        if (arg2 >= 0x1F5) {
            D_802D39BA = flags & 0xFC;
            D_802D39B0 = arg1->ticks;
            func_801C4D6C();
            flags = D_802D39BA;
        }
    } else if (flags & 4) {
        if (arg2 >= 0x2BD) {
            D_802D39BA = 0;
            flags = 0;
        }
    } else if (flags & 8) {
        if (arg2 >= 0x2BD) {
            D_802D39BA = 0;
            flags = 0;
        }
    }
    return flags == 0;
}
