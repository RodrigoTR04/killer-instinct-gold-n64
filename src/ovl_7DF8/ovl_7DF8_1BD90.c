#include "frontend.h"

/* Menu strings, including distinct copies used by the original pointer tables. */
const u8 D_80294F10[] = "SAVE TO CONTROLLER PAKS";
const u8 D_80294F28[] = "RELOAD";
const u8 D_80294F30[] = "RESET EVERYTHING TO FACTORY DEFAULTS";
const u8 D_80294F58[] = "CREATE SPACE ON PAK";
const u8 D_80294F6C[] = "MAIN OPTIONS";
const u8 D_80294F7C[] = "DIFFICULTY";
const u8 D_80294F88[] = "VERY EASY";
const u8 D_80294F94[] = "EXTRA HARD";
const u8 D_80294FA0[] = "MASTER";
const u8 D_80294FA8[] = "TRAINING DIFFICULTY";
const u8 D_80294FBC[] = "GAME SPEED";
const u8 D_80294FC8[] = "FAST";
const u8 D_80294FD0[] = "ULTRA";
const u8 D_80294FD8[] = "SLOW";
const u8 D_80294FE0[] = "CONTROLLER SETUP";
const u8 D_80294FF4[] = "BUTTON SETUP";
const u8 D_80295004[] = "DEFAULT SETUP";
const u8 D_80295014[] = "GAME PAK OPTIONS";
const u8 D_80295028[] = "GAME LOAD AND SAVE OPTIONS";
const u8 D_80295044[] = "STANDARD OPTIONS";
const u8 D_80295058[] = "MUSIC";
const u8 D_80295060[] = "RANDOM AFTER";
const u8 D_80295070[] = "1 WINS";
const u8 D_80295078[] = "TIME LIMIT";
const u8 D_80295084[] = "THROWING";
const u8 D_80295090[] = "BLOOD";
const u8 D_80295098[] = "LEVEL 1 OPTIONS";
const u8 D_802950A8[] = "THROW DAMAGE";
const u8 D_802950B8[] = "NORM";
const u8 D_802950C0[] = "NONE";
const u8 D_802950C8[] = "EASY BREAKERS";
const u8 D_802950D8[] = "INVISIBLE TAG";
const u8 D_802950E8[] = "AERIAL CAMERA";
const u8 D_802950F8[] = "LEVEL 2 OPTIONS";
const u8 D_80295108[] = "FULL SUPER BAR";
const u8 D_80295118[] = "FULL BREAKERS";
const u8 D_80295128[] = "POWERED FINISHERS";
const u8 D_8029513C[] = "LEVEL 3 OPTIONS";
const u8 D_8029514C[] = "MISSILES";
const u8 D_80295158[] = "FAST FIREBALLS";
const u8 D_80295168[] = "AUTODOUBLES";
const u8 D_80295174[] = "LEVEL 4 OPTIONS";
const u8 D_80295184[] = "EARLY ULTIMATES";
const u8 D_80295194[] = "KNOCKDOWNS";
const u8 D_802951A0[] = "QUICK OPENERS";
const u8 D_802951B0[] = "CHEAP JUGGLES";
const u8 D_802951C0[] = "LEVEL 5 OPTIONS";
const u8 D_802951D0[] = "BLOCKING";
const u8 D_802951DC[] = "QUICK PUNCH";
const u8 D_802951E8[] = "MEDIUM PUNCH";
const u8 D_802951F8[] = "FIERCE PUNCH";
const u8 D_80295208[] = "QUICK KICK";
const u8 D_80295214[] = "MEDIUM KICK";
const u8 D_80295220[] = "FIERCE KICK";
const u8 D_8029522C[] = "MAIN OPTIONS";
const u8 D_8029523C[] = "RIGHT C";
const u8 D_80295244[] = "LEFT C";
const u8 D_8029524C[] = "BOTTOM C";
const u8 D_80295258[] = "TOP C";
const u8 D_80295260[] = "R BUTTON";
const u8 D_8029526C[] = "L BUTTON";
const u8 D_80295278[] = "B";
const u8 D_8029527C[] = "A";
const u8 D_80295280[] = "OPTIONS";
const u8 D_80295288[] = "SAVE OPTIONS";
const u8 D_80295298[] = "BUTTON CONFIG";
const u8 D_802952A8[] = "TOURNAMENT";
const u8 D_802952B4[] = "DELETE FILES";
const u8 D_802952C4[] = "LUDICROUS";
const u8 D_802952D0[] = "SLOW";
const u8 D_802952D8[] = "SLOW";
const u8 D_802952E0[] = "BACK TO CHARACTER SELECT";
const u8 D_802952FC[] = "MAIN OPTIONS";
const u8 D_8029530C[] = "P1";
const u8 D_80295310[] = "P2";
const u8 D_80295314[] = "YES";
const u8 D_80295318[] = "NO";
const char D_8029531C[] = "WON 00, LOST 00";
const u8 D_8029532C[] = "PAD TO ENTER NAMES";
const u8 D_80295340[] = "LEFT C TO DELETE PLAYER";
const u8 D_80295358[] = "RIGHT C TO RESET STATS";
const u8 D_80295370[] = "START TO PLAY";
const u8 D_80295380[] = "Z TO EXIT";
const u8 D_8029538C[] = "PRESS START TO EXIT";
const u8 D_802953A0[] = "     FREE PAGES, KI GOLD REQUIRES 3";
const u8 D_802953C4[] = "PRESS A THEN B TO DELETE FILE";
const u8 D_802953E4[] = "PRESS START TO EXIT";
const u8 D_802953F8[] = "jGAME NOTE             PAGES";
const u8 D_80295418[] = "- NOT AVAILABLE";
const u8 D_80295428[] = "jEMPTY";





void func_801C78B0(arg0, arg1)
u8 arg0;
u8 arg1;
{
    s32 i;

    if ((arg0 < 2) && (arg1 < 10)) {
        for (i = 0; i < 6; i++) {
            D_80127CA8[arg0][i] = D_802923AC[D_80127C68[arg1].b[i]];
        }
    }
}

/* Return the menu-key ordinal for a single button in the packed input. */
u8 func_801C7998(u64 buttons)
{
    u8 index = 0;

    switch (buttons & 0xFFFF) {
    case 0: break;
    case 0x8000: index++; /* fall through */
    case 0x4000: index++; /* fall through */
    case 0x20: index++; /* fall through */
    case 0x10: index++; /* fall through */
    case 8: index++; /* fall through */
    case 4: index++; /* fall through */
    case 2: index++; /* fall through */
    case 1: index++;
    }
    return index;
}

extern u8 D_80127D58[], D_80127D78[];
extern u8 D_8012834C;
typedef struct { u8 maximum; } T030Result7A98;
extern T030Result7A98 D_802923A0;

extern FrontendMenuText D_80292450;


void func_801C7A98(void) {
    u8 maximum = 0;
    s32 i;
    s32 level;
    u8 value;
    for (i = 0; i < 32; i++) {
        value = D_80127D58[i];
        level = value;
        if (level < 5) level = 0;
        else if (level < 55) level = 1;
        else if (level < 120) level = 2;
        else level = 3;
        if (maximum < level) maximum = level;
    }
    if (D_8012834C >= 2) level = (D_8012834C-1)&255;
    else if (D_8012834C == 1) level = 1;
    else level = 0;
    if (maximum < level) maximum = level;
    level = D_802923A0.maximum = maximum;
    D_80292674.second = 5;
    if (level >= 4) D_80292674.second = 6;
    if (level == 5) {
        D_80292674.first = 5;
        D_80292450.text0 = D_802952C4;
        D_80292450.text1 = D_802952D0;
        return;
    }
    D_80292450.text0 = D_802952D8;
    D_80292674.first = 4;
}



void func_801C7CD0(u8 arg0)
{
    if (D_802D3E15)
    {
        arg0 = 5;
    }
    func_801C7A98();
    D_802D39F8 = 0.0f;
    if (D_802D3A06)
    {
        arg0 = 3;
        D_802925AC = D_802952E0;
    }
    else
    {
        D_802925AC = D_802952FC;
    }
    D_802D39FC = 0;
    D_802956F8 = D_802956FC = D_80295700 = 0;
    D_802CA064 = 480;
    D_801CD454 = 0;
    D_802D3A00 = arg0;
    if (D_802D3A00 == 5)
    {
        if (D_802D3E15 == 0)
        {
            D_802D3E15 = 1;
        }
        D_802D3678[0] = 0x1000;
        D_802D3678[1] = 0x1000;
        D_802923F5 = 0;
        func_801CD038((s32) D_800F4070, D_802D3E15 - 1);
        D_802926AC = D_800F4070;
    }
    else if (D_802D3A00 != 4 && D_802D3A06 == 0)
    {
        func_801ADAD4(40);
    }
    D_802D3A01 = 0;
    D_802D3A02 = 65;
    D_802D3A07 = 0;
}

void func_801C7E4C(u8 arg0) {
    FrontendButtonMap *p;

    p = &D_80127C68[arg0];
    p->b[0] = 6;
    p->b[1] = 1;
    p->b[2] = 3;
    p->b[3] = 7;
    p->b[4] = 2;
    p->b[5] = 0;
}

void func_801C7E98(u8 arg0, u8 arg1) {
    s32 i;

    for (i = 0; i < 6; i++) {
        D_80127C68[arg1].b[i] = D_80127C68[arg0].b[i];
    }
}


void func_801C7F10(void) {
    func_801C78B0(0, 0);
    func_801C78B0(1, 1);
}


void func_801C7F40(void) {
    func_801C78B0(0, (D_80127D30[0] + 1) & 0xFF);
    func_801C78B0(1, (D_80127D31 + 1) & 0xFF);
}

extern u8 D_80127CC1, D_80127CC2[];

void func_801C7F90(void) {
    u8 *second = &D_80127CC1;
    s32 i;
    s32 zero = 0;

    D_80127CC0.bytes[0] = zero;
    *second = zero; for (i = 0; i < 32; i++) {
        D_80127CC2[i] = 0;
    } *second = 2;
    func_801C7E4C(0);
    func_801C7E4C(1);
    func_801C7F10();
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C8004.s")

extern f32 sinf(f32);
extern u32 D_80127D00[];
extern u8 *D_802925CC[];
extern u8 ***D_80292698[];
extern f32 D_802926B0[];
extern s32 D_802956F4;
extern u8 D_802D39FE[2];
extern u8 D_802D3A00;
extern u8 D_802D3A06;

void func_801C80F0(FrontendGfxWords **gfxp, FrontendRenderContext *arg1) {
    f32 y;
    f32 x;
    s32 pulse;
    s32 r;
    u8 *name2;
    u8 ***names;
    s32 gb;
    f32 scale;
    s32 i;
    u8 *name1;
    u8 p2;
    u8 p1;
    y = D_802926B0[D_802D3A00];
    p2 = 0;
    p1 = 1;
    x = -450.0f;
    pulse = sinf(arg1->frame * 0.0174532925199432955 * 5.0) * 63.0f + 192.0f;
    names = D_80292698[D_802D3A00];
    if (D_802D3A06) {
        p2 = D_80127D30[0] + 1;
        p1 = D_80127D30[1] + 1;
        name1 = (u8 *)&D_80127D00[D_80127D30[0] - 1];
        name2 = (u8 *)&D_80127D00[D_80127D30[1] - 1];
    } else {
        name1 = D_8029530C;
        name2 = D_80295310;
    }
    scale = 0.62f;
    D_802956F4 += func_801BDA6C(gfxp, arg1->matrices + (D_802956F4 << 6), name1, 75.0f, 230.0f,
                                -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, scale);
    D_802956F4 += func_801BDA6C(gfxp, arg1->matrices + (D_802956F4 << 6), name2, 315.0f, 230.0f,
                                -800.0f, 0xFF, 0xFF, 0xFF, 0xFF, scale);
    for (i = 0; i < 7; i++) {
        if (i == 6 - (D_802D3A00 == 0)) {
            y = -300.0f;
            if (D_802D3A06) {
                x = -320.0f;
            } else {
                x = -200.0f;
            }
        }
        if (i == 6) {
            if (i == D_802D39FE[0] || i == D_802D39FE[1]) {
                r = pulse;
                gb = 0;
            } else {
                gb = 100;
                r = 100;
            }
        } else {
            r = 0xFF;
            gb = 0xFF;
        }
        if (i == 3) {
            y -= 50.0f;
        }
        D_802956F4 += func_801BDA6C(gfxp, arg1->matrices + (D_802956F4 << 6), *names[i], x, y,
                                    -800.0f, r, (u8)gb, (u8)gb, 0xFF, 0.65f);
        if (i != 6) {
            if (i == D_802D39FE[0]) {
                r = pulse;
                gb = 0;
            } else {
                r = 100;
                gb = 100;
            }
            D_802956F4 +=
                func_801BDA6C(gfxp, arg1->matrices + (D_802956F4 << 6),
                              D_802925CC[D_80127C68[p2].b[i]], 40.0f, y, -800.0f, (u8)gb, r, (u8)gb, 0xFF, 0.5f);
            if (i == D_802D39FE[1]) {
                r = pulse ^ 0x3F;
                gb = 0;
            } else {
                r = 100;
                gb = 100;
            }
            D_802956F4 +=
                func_801BDA6C(gfxp, arg1->matrices + (D_802956F4 << 6),
                              D_802925CC[D_80127C68[p1].b[i]], 260.0f, y, -800.0f, r, (u8)gb, (u8)gb, 0xFF, 0.5f);
        }
        y -= 50.0f;
    }
}

extern u32 D_80127D00[8];
extern u8 D_80127D20[8];
extern u8 D_80127D28[8];

void func_801C85C0(void) {
    s32 i;

    for (i = 0;
         i < 8;
         ++i) {
        D_80127D20[i] = 0;
        D_80127D28[i] = 0;
        D_80127D00[i] = 0;
        D_80127D30[i] = 0;
        func_801C7E98(0, (u8)(i + 2));
    }
}

void func_801C8668(u8 arg0) {
    s32 i;
    for (i = 0; i < 16; i++) {
        D_80127D58[i + arg0 * 16] = 0;
    }
}


s32 func_801C86A8(u8 *arg0) {
    s32 i;
    s32 j;
    u32 v;
    u8 b;
    u8 *start = arg0;

    for (i = 0; i < 10; i++) {
        v = 0;
        for (j = 0; j < 6; j++) {
            v |= D_80127C68[i].b[j] << (j * 3);
        }
        *arg0++ = v & 0xFF;
        v >>= 8;
        *arg0++ = v & 0xFF;
        v >>= 8;
        *arg0++ = v & 0xFF;
    }
    for (i = 0; i < 34; i++) {
        if (i & 1) {
            b |= D_80127CC0.bytes[i] << 4;
            *arg0++ = b;
        } else {
            b = D_80127CC0.bytes[i];
        }
    }
    if (i & 1) {
        *arg0++ = b;
    }
    return arg0 - start;
}



s32 func_801C8868(u8 *arg0) {
    s32 i;
    s32 j;
    u32 v;
    u8 *start = arg0;

    for (i = 0; i < 10; i++) {
        v = arg0[0] + (arg0[1] << 8) + (arg0[2] << 16);
        arg0 += 3;
        for (j = 0; j < 6; j++) {
            D_80127C68[i].b[j] = (v >> (j * 3)) & 7;
        }
    }
    for (i = 0; i < 34; i++) {
        if (i & 1) {
            D_80127CC0.bytes[i] = (*arg0++ >> 4) & 0xF;
        } else {
            D_80127CC0.bytes[i] = *arg0 & 0xF;
        }
    }
    if (i & 1) {
        arg0++;
    }
    return arg0 - start;
}


void func_801C8A38(u8 *arg0, s32 arg1) {
    s32 j;
    u32 v;

    arg0 += arg1 * 3;
    v = arg0[0] + (arg0[1] << 8) + (arg0[2] << 16);
    for (j = 0; j < 6; j++) {
        D_80127C68[arg1].b[j] = (v >> (j * 3)) & 7;
    }
}

extern s32 func_801BF914(s32);
extern u32 D_80127D00[8];
extern u8 D_80127D20[8];
extern u8 D_80127D28[8];

void func_801C8AE0(u8 *arg0)
{
  s32 i;
  u16 c;
  for (i = 0; i < 8; i++)
  {
    c = func_801BF914((D_80127D00[i] >> 24) & 0xFF) << 10;
    c |= func_801BF914((D_80127D00[i] >> 16) & 0xFF) << 5;
    c |= func_801BF914((D_80127D00[i] >> 8) & 0xFF);
    *(arg0++) = c >> 8;
    *(arg0++) = c & 0xFFu;
    *(arg0++) = D_80127D20[i];
    *(arg0++) = D_80127D28[i];
  }

  *(arg0++) = D_80127D30[0] | (D_80127D30[1] << 4);
  *(arg0++) = D_80127D30[2] | (D_80127D30[3] << 4);
  *(arg0++) = D_80127D30[4] | (D_80127D30[5] << 4);
  *(arg0++) = D_80127D30[6] | (D_80127D30[7] << 4);
}

extern s32 func_801BF720(u32);
extern u32 D_80127D00[8];

void func_801C8C24(u8 *data)
{
    s32 i;
    u16 packedName;
    u16 byteIndex;
    u32 name;
    for (i = 0; i < 8; i++)
    {
        packedName = (data[0] << 8) + data[1];
        data += 2;
        name = func_801BF720((packedName >> 10) & 0x1F) << 24;
        name |= func_801BF720((packedName >> 5) & 0x1F) << 16;
        name |= func_801BF720(packedName & 0x1F) << 8;
        if (name == 0x20202000)
        {
            name = 0;
        }
        D_80127D00[i] = name;
        D_80127D20[i] = *data++;
        D_80127D28[i] = *data++;
    }

    for (i = 0; i < 4; i++)
    {
        byteIndex = i;
        D_80127D30[i * 2] = data[byteIndex] & 0xF;
        D_80127D30[(byteIndex * 2) + 1] = data[byteIndex] >> 4;
    }
}


void func_801C8DBC(u8 *arg0) {
    u64 bits;
    u8 i;
    u8 level;

    bits = 0;
    for (i = 0; i < 10; i++) {
        if (D_80127D58[i] > D_80127D58[i + 16]) {
            level = D_80127D58[i];
        } else {
            level = D_80127D58[i + 16];
        }
        if (level >= 120) {
            level = 3;
        } else if (level >= 55) {
            level = 2;
        } else if (level >= 5) {
            level = 1;
        } else {
            level = 0;
        }
        bits |= level << (i * 2);
    }
    bits |= bits << 20;
    arg0[0] = bits;
    arg0[1] = bits >> 8;
    arg0[2] = bits >> 16;
    arg0[3] = bits >> 24;
    arg0[4] = bits >> 32;
}


void func_801C8F28(u8 *arg0)
{
    u8 i;
    u8 v;
    /* Keep the first row value in a signed halfword for IDO register allocation. */
    s16 intensity;
    u64 bits;
    bits = (u64)arg0[0] + ((u64)arg0[1] << 8) + ((u64)arg0[2] << 16) + ((u64)arg0[3] << 24) + ((u64)arg0[4] << 32);
    for (i = 0; i < 20; i++)
    {
        switch ((s32)(bits >> (i * 2)) & 3)
        {
            default:
                v = 0;
                break;

            case 3:
                v = 120;
                break;

            case 2:
                v = 55;
                break;

            case 1:
                v = 5;
                break;

        }

        if (i < 10)
        {
            intensity = v;
            D_80127D58[i] = intensity;
        }
        else
        {
            D_80127D58[i + 6] = v;
        }
    }

}

extern u8 ***D_80292698[];
extern FrontendGfxWords D_80292748[];
extern s32 D_802956F4;

extern u8 D_802D3A00;
extern u8 D_802D3A08;
extern f32 D_802D3A10[2];

void func_801C90D4(FrontendGfxWords **gfxp, FrontendRenderContext *arg1)
    {
    s32 i;
    FrontendGfxWords *g;
    f32 target;
    g = (*gfxp)++; g->w0 = 0x06000000; g->w1 = (u32)D_80292748;
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), *D_80292698[D_802D3A00][D_802D39FC], 0.0f, 80.0f, -2700.0f, 0xC0, 0xC0, 0xC0, 0xFF, 1.0f);
    for (i = 0;
    i < 2;
    i++) { target = (i == D_802D3A08) * 0.5 + 0.5;
    if (D_802D3A10[i] < target - 0.03) {
            D_802D3A10[i] += 0.1;
    } else if (D_802D3A10[i] > target + 0.03) {
            D_802D3A10[i] -= 0.1;
    }
    }
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), D_80295314, -60.0f, -30.0f, -600.0f, (u32)(D_802D3A10[1] * 255.0f), (u8)(255.0f - D_802D3A10[1] * 255.0f), (u8)(255.0f - D_802D3A10[1] * 255.0f), 0xFF, D_802D3A10[1]);
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), D_80295318, 60.0f, -25.0f, -600.0f, (u32)(D_802D3A10[0] * 255.0f), (u8)(255.0f - D_802D3A10[0] * 255.0f), (u8)(255.0f - D_802D3A10[0] * 255.0f), 0xFF, D_802D3A10[0]);
    }


char *func_801C9584(u8 arg0, u8 arg1) {
    char *ret = D_802D3A20.line1;

    memcpy(&D_802D3A20, D_8029531C, sizeof(FrontendStatsText));
    D_802D3A20.line1[4] = D_80127D20[arg0] / 10 + '0';
    D_802D3A20.line1[5] = D_80127D20[arg0] % 10 + '0';
    D_802D3A20.line2[5] = D_80127D28[arg0] / 10 + '0';
    D_802D3A20.line2[6] = D_80127D28[arg0] % 10 + '0';
    switch (arg1) {
    case 2:
        D_802D3A20.line1[6] = ',';
        return D_802D3A20.line1;
    }
    D_802D3A20.line1[6] = 0;
    if (arg1 == 0) {
        return D_802D3A20.line2;
    }
    return D_802D3A20.line1;
}


void func_801C9698(s32 arg0, FrontendRenderContext *arg1) {
    s32 r;
    u8 i;
    u8 label[3];
    s32 temporary;
    f32 y;
    s32 b;
    s32 g;
    y = 225.0f;
    label[0] = '1';
    label[1] = ':';
    label[2] = 0;
    for (i = 0; i < 8; i++) {
        temporary = 1;
        if (i == D_802D39FC) {
            r = 0xFF;
            g = 0xE6;
            b = 0x82;
            temporary = -1 - D_802D3A01;
        } else {
            if (D_80127D00[i] == 0) {
                g = 0x3C;
                b = 0x3C;
                r = 0x3C;
            } else {
                r = g = b = 0x87;
            }
        }
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), label, -550.0f, y, -1200.0f, r, g, b, 0xFF, 0.8f);
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), (u8 *)&D_80127D00[i], -400.0f, y, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, temporary);
        temporary = (s32)func_801C9584(i, 2);
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), (char *)temporary, 0.0f, y, -1200.0f, r, g, b, 0xFF, 0.8f);
        label[0]++;
        y -= 70.0f;
    }
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_8029532C, -450.0f, -320.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295340, -450.0f, -380.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295358, -450.0f, -440.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295370, 150.0f, -360.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295380, 150.0f, -420.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801C9B14.s")

void func_801CA784(s32 arg0) {
    s32 i;

    for (i = 0; i < 7 && D_80127D30[i]; i++) {
        if (arg0 == D_80127D30[i]) {
            return;
        }
    }
    if (i < 8) {
        D_80127D30[i] = arg0;
    }
}

/* Queue alias retained for the following functions. */
typedef u8 T034Queue8[8];
#define T034_D_80127D30 (*(T034Queue8 *)&D_80127D30)

void func_801CA7E4(s32 arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < 8 && arg0 != T034_D_80127D30[i]; i++) {
    }
    if (arg0 == T034_D_80127D30[i]) {
        for (j = i + 1; j < 8; j++) {
            T034_D_80127D30[j - 1] = T034_D_80127D30[j];
        }
        T034_D_80127D30[j - 1] = 0;
        for (i = 0; i < 8; i++) {
            if (arg0 < T034_D_80127D30[i]) {
                T034_D_80127D30[i]--;
            }
        }
    }
}



void func_801CA91C(s32 arg0) {
    s32 i;
    u8 v;

    if (arg0 == 1) {
        v = T034_D_80127D30[0];
        T034_D_80127D30[0] = T034_D_80127D30[1];
    } else {
        v = T034_D_80127D30[1];
    }
    for (i = 1; i < 8 && T034_D_80127D30[i] != 0; i++) {
        T034_D_80127D30[i] = T034_D_80127D30[i + 1];
    }
    T034_D_80127D30[i - 1] = v;
    if (++D_80127D20[T034_D_80127D30[0] - 1] >= 100) {
        D_80127D20[T034_D_80127D30[0] - 1] = 99;
    }
    if (++D_80127D28[v - 1] >= 100) {
        D_80127D28[v - 1] = 99;
    }
    if (arg0 == 1) {
        u8 t = T034_D_80127D30[0];

        T034_D_80127D30[0] = T034_D_80127D30[1];
        T034_D_80127D30[1] = t;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1BD90/func_801CAA00.s")

extern void func_801BED0C(u32, u64);
extern s32 D_80127CFC[];
extern u64 D_802D3800, D_802D3808;

void func_801CB998(u8 arg0)
{
    if (arg0 & 1) {
        func_801BED0C(D_80127CFC[D_80127D30[0]], D_802D3800);
    }
    if (arg0 & 2) {
        func_801BED0C(D_80127CFC[D_80127D31], D_802D3808);
    }
}


void func_801CBA2C(void) {
    s32 i;

    func_801C7A98();
    for (i = 0; i < 5; i++) {
        if (D_80292728[i] != 0) {
            D_80127C40[i] = D_80127CC0.bytes[D_80292728[i] - 1];
        }
    }
    if (D_80292674.first == 4) {
        D_80127C40[2] = D_80127CC0.bytes[0];
    } else if (D_80127CC0.bytes[0] >= 3) {
        D_80127C40[2] = 7 - D_80127CC0.bytes[0];
    }
    for (i = 0; i < 10; i++) {
        if (D_80292730[i] != 0) {
            D_80127C48[i] = D_80127CC0.bytes[D_80292730[i] - 1];
        }
    }
    for (i = 0; i < 11; i++) {
        if (D_8029273C[i]) {
            D_80127C58[i] = D_80127CC0.bytes[D_8029273C[i] - 1];
        }
    }
}

