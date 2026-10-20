/* T-087: nonmatching; 150 differing words, 1344 compiled bytes. See T-087/REPORT.md. */
#include "common.h"

typedef struct { u32 w0,w1; } T030Cmd4240;
typedef struct { u32 id,ticks; u8 pad8[0xF0]; u8 *matrices; } T030Render4240;
extern void func_8002B9B4(void);
extern void func_8002DCC8(f32,f32,f32,u32 *);
extern void func_8002DDD4(f32,f32,f32,s32 *,s32 *);
extern void func_8002F6F4();
extern void func_8002FA3C(void);
extern void func_8002FA5C(s32,s32,s32);
extern void func_801ADC64(s32);
extern s32 func_801BDF94(T030Cmd4240 **, void *, void *, f32,f32,f32,s32,f32,f32);
extern void func_801C49A8(T030Cmd4240 **,s32,s32,s32,u32,s32,s32);
extern void guTranslate(void *,f32,f32,f32);
extern u8 D_8004A25C[], D_8004A260[];
extern s32 D_80066C40;
extern u8 D_802918C0[],D_802937F8[],D_80293800[],D_802AA5A0[];
extern f32 D_8029381C,D_80293820,D_80293824,D_80293828;
extern s32 D_802956F4,D_80295714;

extern void *D_802D3950;
extern u8 D_802D3960;

extern s32 D_802D395C;

void func_801C4240(T030Cmd4240 **arg0, T030Render4240 *arg1) {
    f32 sp8C;
    f32 sp84;
    u32 sp80;
    s32 sp78;
    s32 sp74;
    f32 sp50;
    f32 sp48;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f2;
    s32 temp_t4_2;
    s32 temp_t5;
    s32 var_a2;
    u32 temp_t4;


    var_a2 = D_802D395C;
    if (var_a2 == 0) {
        var_a2 = arg1->ticks;
    }
    temp_f20 = (((f32) ((arg1->ticks - var_a2) * (u8)D_802D3958) / 120.0f) * -2000.0f) + D_8029381C;
    D_802D395C = var_a2;
    sp8C = temp_f20;
    sp84 = temp_f20;
    if ((D_802D3956 != 0) && ((temp_f20 < 1000.0f) || (D_802D3958 == 0))) {
        func_8002F6F4(D_80066C40, (s16) D_802D3956, &D_8004A260);
        func_8002F6F4(D_80066C40, (s16) D_802D3956, &D_8004A25C);
        D_802D3956 = 0;
    }
    if (temp_f20 < 1000.0f) {
        if ((s32) D_802D3960 < 0x28) {
            D_802D3960 += 8;
        }
        if (temp_f20 < 0.0f) {
            if (temp_f20 < D_80293820) {
                func_8002FA5C(*(s32 *)D_8004A278, 8, (s32) ((temp_f20 + D_80293824) * 100.0f));
            }
            if (temp_f20 < D_80293828) {
                func_8002FA3C();
                func_801ADC64(D_80295714);
            }
            sp84 = 0.0f;
        }
        sp8C = 1000.0f;
    }
    func_8002B9B4();
    temp_f0 = -sp8C;
    temp_f2 = temp_f0 - 346.0f;
    sp50 = temp_f0;
    sp48 = temp_f2;
    func_8002DCC8(0.0f, -350.0f, temp_f2, &sp80);
    guTranslate(arg1->matrices + (D_802956F4 << 6), 0.0f, -350.0f, sp50);
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w1 = (u32)&D_802918C0;
    temp_v0->w0 = 0x06000000;
    }
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w0 = 0x01020040;
    temp_v0->w1 = (u32) (arg1->matrices + (D_802956F4 << 6));
    }
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w0 = 0xFB000000;
    temp_v0->w1 = (u32) ((D_802D3960 << 0x18) | (D_802D3960 << 0x10) | (D_802D3960 << 8) | 0xFF);
    }
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w1 = (u32)&D_802AA5A0;
    temp_v0->w0 = 0x06000000;
    }
    D_802956F4 += 1;
    func_8002DDD4(-13.0f, -350.0f, sp48, &sp78, &sp74);
    temp_t4 = (u32) ((0x38 - ((u8)D_802C8724 * 8)) * sp80) >> 5;
    sp80 = temp_t4;
    func_801C49A8(arg0, 0, 0x12C000, sp74 >> 3, temp_t4, 4, (s32) D_802D3960);
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w1 = 0;
    temp_v0->w0 = 0xE7000000;
    }
    { T030Cmd4240 *temp_v0 = (*arg0)++;
    temp_v0->w1 = (u32)0x80000;
    temp_v0->w0 = 0xBA001301;
    temp_f0_2 = (f32) (s32) (360.0f - temp_f20);
    sp50 = temp_f0_2;
    temp_t5 = D_802956F4 + func_801BDF94(arg0, arg1->matrices + (D_802956F4 << 6), D_802D3950, -240.0f - sp84, 30.0f, -300.0f, 1, 1.0f, temp_f0_2);
    }
    D_802956F4 = temp_t5;
    temp_t4_2 = D_802956F4 + func_801BDF94(arg0, arg1->matrices + (temp_t5 << 6), &D_802937F8, -230.0f + sp84, -40.0f, -300.0f, 1, 1.0f, sp50);
    D_802956F4 = temp_t4_2;
    if (D_802D3954 != 0) {
        D_802956F4 += func_801BDF94(arg0, arg1->matrices + (temp_t4_2 << 6), &D_80293800, -230.0f, 200.0f + sp84, -300.0f, 0, 1.0f, sp50);
    }
}
