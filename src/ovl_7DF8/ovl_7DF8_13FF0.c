#include "frontend.h"

const u8 D_80293710[] = "CAST OUT BY HER ";
const u8 D_80293724[] = "TRIBE AS GARGOS";
const u8 D_80293734[] = "RETURNS, MAYA MUST";
const u8 D_80293748[] = "VANQUISH HIM TO";
const u8 D_80293758[] = "REGAIN HER THRONE.";
const u8 D_8029376C[] = "GARGOS";


void func_801BFB10(void) {
    func_801CC784();
    func_801CC878();
    func_801BEFFC();
}

void func_801BFB40(u8 arg0) {
    D_802D37D0 = -1;
    D_802D37F0.x = D_80128300.x;
    D_802D37F0.y = D_80128300.y;
    D_802D37EA[0] = D_802D37EA[1] = 0;
    D_802D37D8.x = D_802D37D8.y = 40;
    D_802D37E0.x = D_802D37E0.y = 32;
    D_802D37F8 = 0;
    D_802D3820 = 2560;
    D_802D3824 = 2560;
    if (arg0) func_801ADAD4(42);
    D_802956F8 = D_802956FC = D_80295700 = 0;
}


void func_801BFC08(s32 arg0) {
    if (arg0 == 0) D_802D37F8 += 0x280;
    else D_802D37F8 = arg0 + 0xA0;
    if (D_802D37F8 != 0xA0) {
        if (++D_802D37D0 >= 14) {
            func_801ADC64(0);
            func_801AF5EC(0xFFFF);
            func_801AF5D4(16);
        }
    }
}


void func_801BFC8C(void) {
    if (D_802D37D0-- <= 0) D_802D37D0 = 13;
    D_802D37F8 = 160;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801BFCBC.s")

void func_801C0610(arg0)
s32 arg0; {
    FrontendGfxWords **list = (FrontendGfxWords **)arg0;

    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0xFB000000; p->w1 = 0x0F000410;
    }
    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0xFA000000; p->w1 = 0x3C010110;
    }
    guTranslate((void *)((D_802956F4 << 6) + D_802CA068), 60.0f, 5.0f, 270.0f);
    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0x01020040;
        p->w1 = (D_802956F4 << 6) + (s32)D_802C9F70.matrices;
    }
    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0x06000000; p->w1 = (u32)D_8029C4B0;
    }
    guTranslate((void *)(((D_802956F4 + 1) << 6) + (s32)D_802C9F70.matrices), -40.0f, -15.0f, 270.0f);
    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0x01020040;
        p->w1 = ((D_802956F4 + 1) << 6) + D_802CA068;
    }
    {
        FrontendGfxWords *p;
        p = (*list)++; p->w0 = 0x06000000; p->w1 = (u32)D_8029C8B0;
    }
    D_802956F4 += 2;
}




void func_801C0784(s32 arg0, u32 arg1) {
    if ((u32)D_802D37F8 < arg1) func_801BFC08(arg1);
    if (arg1 + 0x280 < (u32)D_802D37F8) D_802D37F8 = arg1 + 0x280;
    func_801C0610(arg0, arg1);
    func_801BF190(arg0, D_802CA068, D_802D37D0);
    D_801CD454 = 0;
}

#define COLOR_BYTE(v, shift) (((u32)(v) & 0xFF) << (shift))

extern u8 D_80282E88[];

/* Places one textured quad at the given position with a packed fill colour. */
void func_801C0800(FrontendGfxWords **list, f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, u8 a) {
    FrontendGfxWords *p;

    guTranslate((void *)((D_802956F4 << 6) + D_802CA068), x, y, z);
    p = (*list)++;
    p->w0 = 0x01020040;
    p->w1 = D_802CA068 + (D_802956F4 << 6);
    p = (*list)++;
    p->w0 = 0xFA000000;
    p->w1 = COLOR_BYTE(r, 24) | COLOR_BYTE(g, 16) | COLOR_BYTE(b, 8) | COLOR_BYTE(a, 0);
    {
        FrontendGfxWords *command = (*list)++;
        command->w0 = 0x06000000; command->w1 = (u32)D_80282E88; /* both words on one line: match-only (scheduling) */
    }
    D_802956F4++;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C08F8.s")

extern u8 D_8004A407;
extern s8 D_80292CC4;
extern f32 D_80292CF0;
extern s32 D_802956F4, D_802CA068, D_802D3818[];
void func_801C11F0(s32 list, s32 unused, s32 side, s32 player) {
    f32 x;
    s8 digit[2];
    s32 shade;
    if (D_8004A407) player = 0;
    shade = (D_802D3818[player] % 100) * 255 / 100;
    if (shade >= 65 && shade < 192) shade = 63;
    if (shade >= 193) shade = 255 - shade;
    shade *= 4;
    x = side * 218;
    digit[1] = 0;
    digit[0] = D_802D3818[player] / 100 + '0';
    D_802956F4 += func_801BE540((FrontendGfxWords **)list, (void *)((D_802956F4 << 6) + D_802CA068), (u8 *)&D_80292CC4, x, 75.0f, -500.0f, 255, 255, 255, 255, 0.75f);
    D_802956F4 += func_801BE540((FrontendGfxWords **)list, (void *)((D_802956F4 << 6) + D_802CA068), (u8 *)digit, x, 0.0f, -500.0f, (u8)shade, (u8)shade, (u8)shade, 255, D_80292CF0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1434.s")

void func_801C1704(u8 player) {
    s32 i;


    D_80128308[player] = 0;
    D_8012830A[player] = 0;
    for (i = 0; i < 11; i++) {
        D_80128310[player][i] = 0;
        D_80128328[player][i] = 0;
    }
    D_80127C30[player] = 100;
}

extern u64 func_801BEA74(s32, s32, s32, u8 *, u8 *, s32, s32);
extern void func_801C1704(u8);
extern u8 D_8004EA9C[];
extern s32 D_80127C30[];
extern u64 D_802D3800[];

s32 func_801C17D0(u32 *stats, u8 player) {
s32 index = D_8004EA9C[player] ; u64 *out ; if (!player) {
if (D_80128328[player][index] < stats[3]) D_80128328[player][index] = stats[3] ; if (D_80128310[player][index] < stats[1]) D_80128310[player][index] = stats[1] ;  }
else {
if (D_80128328[player][index] < stats[4]) D_80128328[player][index] = stats[4] ; if (D_80128310[player][index] < stats[2]) D_80128310[player][index] = stats[2] ;  } out = &D_802D3800[player] ;
*out = func_801BEA74(D_8012830A[player], D_80128308[player], D_80127C30[player], D_80128310[player], D_80128328[player], ((s32 *)&D_80128300)[player], D_8004EA9C[player]) ;
func_801C1704(player) ; if (*out == 0) return 0 ;
return 1 ;
 }

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1C34.s")

void func_801C2110(f32 t, f32 *coef, f32 *position, f32 *velocity) {
    f32 two = 2.0f;
    f32 three = 3.0f;
    f32 t2;
    f32 t3;

    t2 = t * t;
    t3 = t2 * t;
    position[0] = coef[0] * t3 + coef[1] * t2 + coef[2] * t + coef[3];
    position[1] = coef[4] * t3 + coef[5] * t2 + coef[6] * t + coef[7];
    position[2] = coef[8] * t3 + coef[9] * t2 + coef[10] * t + coef[11];
    velocity[0] = three * coef[0] * t2 + two * coef[1] * t + coef[2];
    velocity[1] = three * coef[4] * t2 + two * coef[5] * t + coef[6];
    velocity[2] = three * coef[8] * t2 + two * coef[9] * t + coef[10];
}

extern void func_80012950(s32);
extern void func_80012A8C(u8);
extern void func_8001CD50(void);
extern void osViBlack(s32);
extern void (*D_800451EC[])(void);
extern u8 D_8004AC88;
extern s32 D_800698C4;
extern s32 D_8028326C[];
extern f32 D_80285240[][3][4];
extern f32 D_80285420[][4];
extern u8 D_80285570;
extern s32 D_80285574, D_80285578;
extern u8 D_80295718;
extern u8 D_802D3874;
extern f32 D_802D3878;
extern f32 D_802D3880[4];
extern s32 D_802D3890, D_802D3894;
extern f32 D_802D3898[3][4];
extern u8 D_802D38C8;

void func_801C224C(u8 arg0, s32 arg1) {
    s32 i, j;
    u8 selected;

    D_802D38C8 = arg0;
    osViBlack(1);
    func_80012950(1);
    selected = D_802D38C8;
    D_8004AC88 = selected;
    func_80012A8C(selected);
    D_800698C4 = 0;
    D_800451EC[D_802D38C8]();
    func_8001CD50();
    selected = D_802D38C8;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_802D3898[j][i] = D_80285240[selected][j][i];
        }
        D_802D3880[i] = D_80285420[selected][i];
    }
    D_80285574 = D_8028326C[selected];
    D_802D3890 = arg1;
    D_802D3874 = 0;
    D_802D3878 = 50.0f;
    D_80295718 = 2;
    D_80285578 = 0;
    D_80285570 = 0;
    D_802D3894 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C23C0.s")


extern void func_8002F6F4();
extern void func_801ADC64(s32);
extern u8 D_8004A26C[], D_8004A270[];
extern s32 D_80066C40;
extern u8 D_80127D38;
extern s8 D_8012834C, D_8029571A;
extern u8 D_80127D58[32];
extern u16 D_8028557C[5][7];
extern u64 D_802D3678[];
extern u8 D_802D3874, D_802D38CC[5];

void func_801C2ADC(s32 player, u64 buttons) {
    s32 i;
    s32 j;

    if ((buttons & 0x1000) && !(D_802D3678[player] & 0x1000) && D_802D3874 == 0) {
        D_802D3874 = 1;
        D_8029571A = 0;
    }
    if ((buttons & 0xFFFF) && !(D_802D3678[player] & 0xFFFF)) {
        for (i = 0; i < 5; i++) {
            if ((buttons & 0xFFFF) == D_8028557C[i][D_802D38CC[i]]) {
                D_802D38CC[i]++;
            } else {
                D_802D38CC[i] = 0;
            }
            if (D_8028557C[i][D_802D38CC[i]] == 0) {
                switch (i) {
                    case 0:
                        func_8002F6F4(D_80066C40, 0x8B, D_8004A26C);
                        D_80127D38 = 1;
                        break;
                    case 1:
                        func_801ADC64(4);
                        break;
                    case 2:
                        D_8012834C = 6;
                        func_8002F6F4(D_80066C40, 0x17D, D_8004A26C);
                        func_8002F6F4(D_80066C40, 0x17D, D_8004A270);
                        break;
                    case 3:
                        for (j = 0;
                             j < 32;
                             j++) D_80127D58[j] = 120;
                        func_8002F6F4(D_80066C40, 0x17A, D_8004A26C);
                        func_8002F6F4(D_80066C40, 0x17A, D_8004A26C);
                        break;
                    case 4:
                        break;
                }
                D_802D38CC[i] = 0;
            }
        }
    }
    D_802D3678[player] = buttons;
}




void func_801C2D34(FrontendGfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    FrontendGfx *temp_v0;
    FrontendGfx *temp_v0_2;
    FrontendGfx *temp_v0_3;
    FrontendGfx *temp_v0_4;
    FrontendGfx *temp_v0_5;
    FrontendGfx *temp_v0_6;
    FrontendGfx *temp_v0_7;
    temp_v0 = (*arg0)++;
    temp_v0->words.w0 = 0xBA001301; temp_v0->words.w1 = 0x80000;
    temp_v0_2 = (*arg0)++;
    temp_v0_2->words.w1 = 0;
    temp_v0_2->words.w0 = 0xBA000E02;
    temp_v0_3 = (*arg0)++;
    temp_v0_3->full = 0xB600000000060004ULL;
    guRotate(((D_802956F4 + 2) << 6) + D_802C9F70.matrices, (f32) (arg4 * 2), 0.0f, 1.0f, 0.0f);
    guRotate(((D_802956F4 + 1) << 6) + D_802C9F70.matrices, -8.0f, 1.0f, 0.0f, 0.0f);
    if (arg1 >= 0x77)
    {
        arg1 = -0x163;
    }
    else
    {
        arg1 = (arg1 * 3) - 0x2C6;
    }
    guTranslate((D_802956F4 << 6) + D_802C9F70.matrices, (f32) arg1, (f32) arg2, (f32) arg3);
    temp_v0_4 = (*arg0)++;
    temp_v0_4->words.w0 = 0x01020040;
    temp_v0_4->words.w1 = (u32) ((D_802956F4 << 6) + D_802C9F70.matrices);
    temp_v0_5 = (*arg0)++;
    temp_v0_5->words.w0 = 0x01000040;
    temp_v0_5->words.w1 = (u32) (((D_802956F4 + 1) << 6) + D_802C9F70.matrices);
    temp_v0_6 = (*arg0)++;
    temp_v0_6->words.w0 = 0x01000040;
    temp_v0_6->words.w1 = (u32) (((D_802956F4 + 2) << 6) + D_802C9F70.matrices);
    D_802956F4 += 3;
    temp_v0_7 = (*arg0)++;
    temp_v0_7->words.w0 = 0x06000000; temp_v0_7->words.w1 = (u32)&D_80285168;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C317C.s")


s32 func_801C3524(FrontendGfxWords **arg0, s32 arg1)
{
    FrontendGfxWords *command;
    if (arg1 >= 0x11)
    {
        arg1 = 0x10;
    }
    command = (*arg0)++;
    /* Keep each command pair on one line for IDO store scheduling. */
    command->w0 = 0xFA000000; command->w1 = (s32) ((arg1 * 0xF) & 0xFF);
    command = (*arg0)++;
    command->w0 = 0x06000000; command->w1 = (s32) (&D_802855C8);
    return arg1 == 0x10;
}

void func_801C3580(s32 arg0, s32 arg1)
{
  func_801C35D8(arg0, &D_80290DF8, 0x17, arg1);
}

void func_801C35AC(s32 arg0, s32 arg1)
{
  func_801C35D8(arg0, &D_80290F0C, 0xB, arg1);
}



void func_801C35D8(FrontendGfxWords **arg0, FrontendCloud *arg1, s32 arg2, s32 arg3)
{
    FrontendGfxWords *dl;
    s32 i, offset;
    s32 visible;
    FrontendCloud *cloud;
    s16 start;
    s32 end;
    dl = (*arg0)++;
    dl->w0 = 0x06000000; dl->w1 = (u32)D_80290F90;
    D_802D38E0 = D_800F4070;
    i = 0;
    if (arg2 > 0)
    {
        offset = 0; cloud = arg1; do
        {
            start = cloud->angle;
            end = cloud->width + start;
            if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1;
            else visible = 0;
            if (visible || cloud->alpha > 0)
            {
                if (visible)
                {
                    cloud->alpha += 1;
                    if (cloud->alpha >= 17) cloud->alpha = 16;
                }
                else
                {
                    cloud->alpha -= 2;
                    if (cloud->alpha <= 0) cloud->alpha = 0;
                }
                func_801C3758(arg0, (FrontendCloud *)((u32)offset + (u8 *)arg1), cloud->alpha);
            }
            else cloud->alpha = 0;
            i++;
            offset += 12;
            if (D_80290D88 >= 60) D_80290D88 = 0;
            cloud++;
        }
        while (i != arg2);
    }
}


#include "frontend.h"

extern s32 D_80290D88;
extern s16 D_80290D8C[][6];
#define T105Vertices ((FrontendVertex *)D_802D38E0)

void func_801C3758(arg0,arg1,arg2)
FrontendGfxWords **arg0; FrontendCloud *arg1; s8 arg2;
{
    u8 frame;
    FrontendGfxWords *dl;
    frame = arg1->animation + 12;
    if (frame >= 64) frame = 0;
    arg1->animation = frame;
    T105Vertices[D_80290D88].x = arg1->x - arg2;
    T105Vertices[D_80290D88+1].x = arg1->x + arg2;
    T105Vertices[D_80290D88+2].x = arg1->x;
    T105Vertices[D_80290D88].y = arg1->y - arg2;
    T105Vertices[D_80290D88+1].y = arg1->y - arg2;
    T105Vertices[D_80290D88+2].y = arg1->y + arg2;
    T105Vertices[D_80290D88].z = arg1->z;
    T105Vertices[D_80290D88+1].z = arg1->z;
    T105Vertices[D_80290D88+2].z = arg1->z;
    T105Vertices[D_80290D88].s = D_80290D8C[frame >> 3][0];
    T105Vertices[D_80290D88].t = D_80290D8C[frame >> 3][1];
    T105Vertices[D_80290D88+1].s = D_80290D8C[frame >> 3][2];
    T105Vertices[D_80290D88+1].t = D_80290D8C[frame >> 3][3];
    T105Vertices[D_80290D88+2].s = D_80290D8C[frame >> 3][4];
    T105Vertices[D_80290D88+2].t = D_80290D8C[frame >> 3][5];
    dl = (*arg0)++;
    dl->w0 = 0x04200030;
    dl->w1 = (u32)(D_802D38E0 + (D_80290D88 << 4));
    dl = (*arg0)++;
    dl->w0 = 0xBF000000; dl->w1 = 0xA14;
    D_80290D88 += 3;
}
