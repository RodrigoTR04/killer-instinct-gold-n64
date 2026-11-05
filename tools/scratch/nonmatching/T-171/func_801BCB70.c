/* T-162: else-arm for uls. Full TU 258 -> 221 words, 1668/1676 bytes. */
typedef struct { u32 w0, w1; } T157Gfx;
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define GCMD(pkt, a, b) { T157Gfx *_g = (T157Gfx *)(pkt); _g->w0 = (a); _g->w1 = (b); }
void func_801BCB70(T157Gfx **dl, u32 tex, s32 arg2, s32 texW, s32 arg4, s32 stepX, u32 cellW, u32 top, u32 left, u32 bottom, u32 right, f32 fx, f32 fy0, s32 scale, u8 alpha, u16 *mask) {
    f32 accX;
    s32 ult;
    s32 i;
    s32 yl;
    f32 cellH;
    s32 lrs;
    f32 y1f;
    s32 rows;
    s32 end;
    f32 y1c;
    s32 col;
    f32 fy;
    s32 lrt;
    f32 x1c;
    s32 xl;
    f32 x1f;
    f32 dx;
    f32 absDx;
    u32 pos;
    s32 div;
    u16 bit;
    u32 flag;
    f32 x0f;
    s32 uls;
    T157Gfx *g;
    s32 x;
    u16 run;

    g = *dl;
    dx = ((f32) stepX * (f32) scale) / 1024;
    cellH = ((f32) cellW * (f32) scale) / 1024;
    bit = 1;
    GCMD(g++, 0xFA000000, _SHIFTL(alpha, 24, 8) | _SHIFTL(alpha, 16, 8) | _SHIFTL(alpha, 8, 8) | _SHIFTL(255, 0, 8));
    if (dx < 0.0f) {
        absDx = -dx;
        flag = 0x200;
        stepX = -stepX;
    } else {
        absDx = dx;
        flag = 0;
    }
    i = 0;
    accX = 0.0f; rows = bottom - top;
    if (rows != 0) {
        do {
            x = left; fy = fy0;
            col = 0;
            if (x < right) {
                do {
                    run = 1;
                    if (mask[col] & bit) {
                        div = 0x100000 / scale; x0f = accX + fx;
                        end = i + stepX + top; 
                        x1f = x0f + absDx;
                        pos = top + i;
                        
                        
                        while ((mask[col + run] & bit) && run < 5) {
                            run++;
                        }
                        if (pos != 0) { uls = pos; } else { uls = 0; }
                        lrs = (end < (bottom - 1)) ? end : (bottom - 1);
                        ult = MAX(x - 1, 0);
                        lrt = (x + cellW * run < (right - 1)) ? x + cellW * run : (right - 1);
                        y1f = cellH * (f32) run + fy; x1c = x1f;
                        if (!(x1f < 640.0f)) {
                            x1c = 640.0f;
                        }
                        y1c = y1f;
                        if (!(y1f < 480.0f)) {
                            y1c = 480.0f;
                        }
                        xl = (s32) (x0f * 4.0f); GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);
                        GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), 0x07080140); GCMD(g++, 0xE6000000, 0); GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); GCMD(g++, 0xE7000000, 0); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), 0x00080140); GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(0, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12));
                        yl = (s32) (fy * 4.0f); GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX((s32) (x1c * 4.0f), 0), 12, 12) | _SHIFTL(MAX((s32) (y1c * 4.0f), 0), 0, 12),
                                  _SHIFTL(0, 24, 3) | _SHIFTL(MAX(xl, 0), 12, 12) | _SHIFTL(MAX(yl, 0), 0, 12)); GCMD(g++, 0xB3000000, _SHIFTL((((s32) ((f32) (((f64) (f32) i - 0.5) + (f64) top) * 32.0f) + flag) & 0xFFFF) - MIN((xl * div) >> 7, 0), 16, 16) | _SHIFTL((s32) ((f32) ((f64) (f32) x - 0.5) * 32.0f) - MIN((yl * div) >> 7, 0), 0, 16));
                        GCMD(g++, 0xB2000000, _SHIFTL(div, 16, 16) | _SHIFTL(div, 0, 16));
                    }
                    x += cellW * run; fy += cellH * (f32) run;
                    col += run;
                } while (x < right);
            }
            accX += dx; bit <<= 1;
            i += stepX;
        } while ((u32) i < bottom - top);
    }
    *dl = g;
}
