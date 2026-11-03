#include "common.h"

typedef struct { u32 w0, w1; } FwCmd;
typedef struct { u32 id, ticks; u8 pad8[0xF0]; u8 *matrices; } FwRender;

extern void func_8002B9B4(void);
extern void func_8002DCC8(f32, f32, f32, u32 *);
extern void func_8002DDD4(f32, f32, f32, s32 *, s32 *);
extern void func_8002F6F4(s32, s32, void *);
extern void func_8002FA3C(void);
extern void func_8002FA5C(s32, s32, s32);
extern void func_801ADC64(s32);
extern s32 func_801BDF94(FwCmd **, void *, void *, f32, f32, f32, s32, f32, f32);
extern void func_801C49A8(FwCmd **, s32, s32, s32, u32, u8, u8);
extern void guTranslate(void *, f32, f32, f32);

extern u8 D_8004A25C[], D_8004A260[];
extern s32 D_80066C40;
extern u8 D_802918C0[], D_802AA5A0[];
extern u8 D_802937F8[], D_80293800[];
extern f32 D_8029381C, D_80293820, D_80293824, D_80293828;
extern s32 D_802956F4, D_80295714;
extern u16 D_802D3956;
extern u8 D_802D3954, D_802D3958, D_802D3960;
extern void *D_802D3950;
extern s32 D_802D395C;
extern u8 D_802C8724;

/* Victory screen banner: elapsed time drives the scroll and the fade. */
void func_801C4240(FwCmd **pkt, FwRender *render) {
    f32 elapsed;
    f32 fade;
    f32 scroll;
    u32 scaled;
    s32 started;
    s32 used;
    s32 tmpX, tmpY;
    f32 angle;
    FwCmd *cmd;

    started = D_802D395C;
    if (started == 0) {
        started = render->ticks;
    }
    elapsed = (((f32) (render->ticks - started) * D_802D3958) / 120.0f) * -2000.0f + D_8029381C;
    D_802D395C = started;
    fade = elapsed;
    scroll = elapsed;
    if (D_802D3956 != 0 && (elapsed < 1000.0f || D_802D3958 == 0)) {
        func_8002F6F4(D_80066C40, D_802D3956, D_8004A260);
        func_8002F6F4(D_80066C40, D_802D3956, D_8004A25C);
        D_802D3956 = 0;
    }
    if (elapsed < 1000.0f) {
        if (D_802D3960 < 0x28) {
            D_802D3960 += 8;
        }
        if (elapsed < 0.0f) {
            if (elapsed < D_80293820) {
                func_8002FA5C(*(s32 *) D_8004A278, 8, (s32) ((elapsed + D_80293824) * 100.0f));
            }
            if (elapsed < D_80293828) {
                func_8002FA3C();
                func_801ADC64(D_80295714);
            }
            scroll = 0.0f;
        }
        fade = 1000.0f;
    }
    func_8002B9B4();
    angle = -fade - 346.0f;
    func_8002DCC8(0.0f, -350.0f, angle, &scaled);
    guTranslate(render->matrices + (D_802956F4 << 6), 0.0f, -350.0f, -fade);
    cmd = (*pkt)++;
    cmd->w1 = (u32) D_802918C0;
    cmd->w0 = 0x06000000;
    cmd = (*pkt)++;
    cmd->w0 = 0x01020040;
    cmd->w1 = (u32) (render->matrices + (D_802956F4 << 6));
    cmd = (*pkt)++;
    cmd->w0 = 0xFB000000;
    cmd->w1 = (D_802D3960 << 24) | (D_802D3960 << 16) | (D_802D3960 << 8) | 0xFF;
    cmd = (*pkt)++;
    cmd->w1 = (u32) D_802AA5A0;
    cmd->w0 = 0x06000000;
    D_802956F4 += 1;
    func_8002DDD4(-13.0f, -350.0f, angle, &tmpX, &tmpY);
    scaled = ((0x38 - D_802C8724 * 8) * scaled) >> 5;
    func_801C49A8(pkt, 0, 0x12C000, tmpY >> 3, scaled, 4, D_802D3960);
    cmd = (*pkt)++;
    cmd->w1 = 0;
    cmd->w0 = 0xE7000000;
    cmd = (*pkt)++;
    cmd->w1 = 0x80000;
    cmd->w0 = 0xBA001301;
    used = func_801BDF94(pkt, render->matrices + (D_802956F4 << 6), D_802D3950, -240.0f - scroll, 30.0f, -300.0f, 1, 1.0f, 360.0f - elapsed);
    D_802956F4 += used;
    used = func_801BDF94(pkt, render->matrices + (D_802956F4 << 6), D_802937F8, -230.0f + scroll, -40.0f, -300.0f, 1, 1.0f, 360.0f - elapsed);
    D_802956F4 += used;
    if (D_802D3954 != 0) {
        used = func_801BDF94(pkt, render->matrices + (D_802956F4 << 6), D_80293800, -230.0f, 200.0f + scroll, -300.0f, 0, 1.0f, 360.0f - elapsed);
        D_802956F4 += used;
    }
}
