/* T-076: nonmatching, 281 differing words including size penalty; 1264 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
#include "common.h"

typedef struct { u32 id,ticks; u8 pad8[0xF0]; u8 *matrices; } T030Render7310;
extern void func_8002A8C4(void);
extern void func_8002A9DC(s32);
extern void func_8002AA98(u32);
extern void func_8002AAEC(u32);
extern void func_8002AB40(void), func_8002AB64(void);
extern void func_801ADAD4(s32);
extern s32 func_801BE540(s32,void *,u8 *,f32,f32,f32,u8,u8,u8,u8,f32);
extern s32 func_801BE660(s32,void *,u8 *,f32,f32,f32,f32);
extern void func_801C0610(s32);
extern void func_801C2D34(s32,s32,s32,s32,s32);
extern u8 *D_802921E0[];
extern u8 D_80292378[];
extern u16 D_80292384[];
extern f32 D_80294EF0, D_80294EF4, D_80294EF8, D_80294EFC, D_80294F00;
extern s32 D_802956F4;
extern u32 D_802D39C0, D_802D39C4;
extern s32 D_802D39C8;
extern s8 D_802D39CC, D_802D39CD;
extern u8 D_802D39CE;
extern f32 D_802D39D0;

void func_801C7310(s32 arg0, T030Render7310 *arg1) {
    f32 var_f0;
    f32 var_f16;
    f32 var_f20;
    f32 var_f22;
    s32 i = 0;
    s32 var_a0;
    u32 temp_t3;
    u32 temp_t9;
    u32 var_v0;
    u8 **var_s1;
    u8 *var_a2;
    u8 *var_v1;
    u8 temp_v0;
    u8 var_a0_2;

    if (D_802D39D0 == 0.0f) {
        D_802D39D0 = (f32)arg1->ticks;
    }
    var_f16 = (f32)arg1->ticks;
    var_f20 = (f32) (((f64) (var_f16 - D_802D39D0) * 1.5) - 400.0);
    func_801C0610(arg0);
    func_801C2D34(arg0, 0x3E8, -0xFA, -0x258, arg1->ticks);
    var_s1 = &D_802921E0[i];
    if (*var_s1 && D_80294EF0 < var_f20) {
        do {
            D_802D39D5 = 1;
            var_a2 = *var_s1;
            var_a0 = 0;
            if (*var_a2 != 'c') {
                var_f22 = 85.0f;
                if (*var_a2 == 'g') { var_a0 = 1; var_f0 = 1.0f; }
                else if (*var_a2 == 'h') { var_a0 = 1; var_f0 = D_80294EF8; }
                else if (*var_a2 == 't') { var_f0 = D_80294EF4; var_a2++; }
                else { var_f0 = 1.0f; }
            } else {
                var_f22 = 75.0f;
                var_f0 = 0.75f;
                var_a2++;
                var_f20 -= 30.0f;
            }
            if (var_f20 < D_80294EFC) {
                if (var_a0) {
                    D_802956F4 += func_801BE660(arg0, arg1->matrices + (D_802956F4 << 6), var_a2, 0.0f, var_f20, -1200.0f, var_f0);
                } else {
                    D_802956F4 += func_801BE540(arg0, arg1->matrices + (D_802956F4 << 6), var_a2, 0.0f, var_f20, -1200.0f, 255, 255, 255, 255, var_f0);
                }
                D_802D39D5 = 0;
            }
            var_s1++;
            var_f20 -= var_f22;
        } while (*var_s1 && D_80294F00 < var_f20);
    }
    if (D_802D39C8-- == 0) {
        D_802D39CC += 1;
        D_802D39CE = 2;
        var_a0_2 = D_80292378[D_802D39CC];
        if (var_a0_2 == 0) {
            D_802D39CC = 0;
            var_a0_2 = D_80292378[D_802D39CC];
        }
        if (D_802D39CC & 1) {
            func_8002A9DC(var_a0_2);
            func_8002A8C4();
        } else {
            func_801ADAD4(var_a0_2);
        }
        D_802D39C0 = 0;
        D_802D39C4 = 0x7FFF;
        D_802D39C8 = (s32) D_80292384[D_802D39CC];
    }
    var_v0 = D_802D39C0;
    if ((var_v0 < 0x7DDDU) || (D_802D39D5 != 0)) {
        if (D_802D39D5 != 0) {
            temp_t9 = var_v0 - 0x444;
            if (var_v0 >= 0x444U) {
                D_802D39C0 = temp_t9;
                var_v0 = temp_t9;
            }
            if ((u32) D_802D39C4 >= 0x444U) {
                D_802D39C4 -= 0x444;
            } else if (var_v0 < 0x445U) {
                D_802D39D5 = 2;
            }
        } else {
            if (D_802D39CD != 0) {
                var_v0 = 0x7DDD;
                D_802D39C0 = 0x7DDD;
                D_802D39C4 = 0x222;
                D_802D39CD = 0;
            }
            temp_t3 = var_v0 + 0x222;
            D_802D39C0 = temp_t3;
            D_802D39C4 -= 0x222;
            var_v0 = temp_t3;
        }
        if (D_802D39CC & 1) {
            func_8002AAEC(var_v0);
            func_8002AA98(D_802D39C4);
            return;
        }
        func_8002AA98(var_v0);
        func_8002AAEC(D_802D39C4);
        return;
    }
    D_802D39C0 = 0x7FFF;
    D_802D39C4 = 0;
    if (D_802D39CE == 2) {
        if (D_802D39CC & 1) {
            func_8002AB40();
        } else {
            func_8002AB64();
        }
        D_802D39CE = 1;
    }
}
