typedef struct { u32 w0, w1; } T157Gfx;
#define _SHIFTL(v, s, w) ((u32) (((u32) (v) & ((0x01 << (w)) - 1)) << (s)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define GCMD(pkt, a, b) { T157Gfx *_g = (T157Gfx *)(pkt); _g->w0 = (a); _g->w1 = (b); }
void func_801BC1B0(T157Gfx **dl, u32 tex, s32 fmt, u32 texW, u32 texH, s32 stepX, u32 cellW, u32 top, u32 left, u32 bottom, u32 right, f32 fx, f32 fy0, s32 scale, s32 flip) {
    f32 fy;
    u32 sCo;
    s32 lrt;
    f32 step;
    u32 pos;
    f32 dx;
    s32 ult;
    s32 lrs;
    s32 y1;
    s32 x1;
    s32 i;
    s32 mnY;
    f32 x0f;
    s32 xl;
    f32 accX;
    s32 cellH;
    s32 uls;
    s32 end;
    f32 yl;
    u32 mnX;
    s32 tOff;
    s32 cms;
    s32 x;
    f32 y1f;
    s32 tCo;
    u32 rows;
    s32 div;
    T157Gfx *g;

    g = *dl; dx = ((f32) stepX * (f32) scale) / 256;
    cms = 1;
    if (flip != 0) {
        tOff = 0x2010 - (stepX << 5);
        stepX = -stepX; step = -dx;
        fx = fx - ((f32) (-((scale << 4) >> 8)) - step);
    } else {
        step = dx; tOff = 0;
        cms = 2;
    }
    accX = 0.0f;
    i = 0; rows = bottom - top;
    if (rows != 0) {
        do {
            fy = fy0; x = left;
            if (x < right) {
                do {
                    div = 0x100000 / scale; x0f = accX + fx;
                    xl = (s32) x0f;
                    pos = i + top; end = i + stepX + top;
                    cellH = ((f32) cellW * (f32) scale) / 256; x1 = (s32) ((f32) xl + dx);
                    uls = 0; if (pos != 0) { uls = pos; }
                    y1f = cellH + fy; lrs = MIN(end, bottom - 1);
                    ult = 0; if (x - 1 > 0) { ult = x - 1; }
                    lrt = MIN(x + cellW, right - 1);
                    yl = fy; fy = y1f;
                    if (!(x1 < 0xA00)) { x1 = 0xA00; }
                    tCo = (s32) ((f32) ((f64) (f32) x - 0.5) * 32.0f);
                    y1 = (s32) y1f;
                    y1 = MIN(y1, 0x780);
                    switch (fmt) {
                    case 2:
                        GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), _SHIFTL(cms, 8, 2) | 0x07080070);
                        GCMD(g++, 0xE6000000, 0); GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); GCMD(g++, 0xE7000000, 0); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((((lrs - uls + 1) * 1) + 7) >> 3, 9, 9), _SHIFTL(cms, 8, 2) | 0x00080070); GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(0, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); break;
                    case 0:
                        GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);
                        GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((lrs - uls + 1) * 2) + 7) >> 3, 9, 9), 0x07080200); GCMD(g++, 0xE6000000, 0); GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); GCMD(g++, 0xE7000000, 0); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((lrs - uls + 1) * 2) + 7) >> 3, 9, 9), 0x00080200); GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(0, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); break;
                    default:
                        GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((lrs - uls + 1) * 2) + 7) >> 3, 9, 9), 0x07080200);
                        GCMD(g++, 0xE6000000, 0); GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); GCMD(g++, 0xE7000000, 0); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(0, 21, 3) | _SHIFTL(2, 19, 2) | _SHIFTL((((lrs - uls + 1) * 2) + 7) >> 3, 9, 9), 0x00080200); GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL(uls << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(0, 24, 3) | _SHIFTL(lrs << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12));
                        GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(4, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL((texW >> 1) - 1, 0, 12), tex + texW * texH * 2); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(4, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(((((lrs - uls + 1) >> 1) + 7) >> 3), 9, 9) | _SHIFTL(0x1C0, 0, 9), 0x07080200); GCMD(g++, 0xE6000000, 0); GCMD(g++, _SHIFTL(0xF4, 24, 8) | _SHIFTL((uls + 16) << 1, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(7, 24, 3) | _SHIFTL((lrs + 16) << 1, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); GCMD(g++, 0xE7000000, 0); GCMD(g++, _SHIFTL(0xF5, 24, 8) | _SHIFTL(4, 21, 3) | _SHIFTL(0, 19, 2) | _SHIFTL(((((lrs - uls + 1) >> 1) + 7) >> 3), 9, 9) | _SHIFTL(0x1C0, 0, 9), 0x01080200); GCMD(g++, _SHIFTL(0xF2, 24, 8) | _SHIFTL((uls + 16) << 2, 12, 12) | _SHIFTL(ult << 2, 0, 12), _SHIFTL(1, 24, 3) | _SHIFTL((lrs + 16) << 2, 12, 12) | _SHIFTL(lrt << 2, 0, 12)); break;
                    }
                    GCMD(g++, _SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX(x1, 0), 12, 12) | _SHIFTL(MAX(y1, 0), 0, 12),
                              _SHIFTL(0, 24, 3) | _SHIFTL(MAX(xl, 0), 12, 12) | _SHIFTL(MAX((s32) yl, 0), 0, 12)); mnX = MIN((xl * div) >> 7, 0); sCo = (((s32) (f32) (((f64) (f32) i - 0.5) + (f64) top) * 32 + tOff) & 0xFFFF); mnY = MIN((((s32) yl) * div) >> 7, 0); GCMD(g++, 0xB3000000, _SHIFTL(sCo - mnX, 16, 16) | _SHIFTL(tCo - mnY, 0, 16)); x += cellW; GCMD(g++, 0xB2000000, _SHIFTL(div, 16, 16) | _SHIFTL(div, 0, 16));
                } while (x < right);
            }
            i += stepX; accX += step;
        } while ((u32) i < rows);
    }
    *dl = g;
}
