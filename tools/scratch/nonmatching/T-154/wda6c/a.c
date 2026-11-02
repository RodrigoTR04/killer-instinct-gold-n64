typedef struct { u32 w0, w1; } T154Gfx;
typedef union { u64 align; u8 bytes[64]; } T154Mtx;
typedef struct { u32 image; f32 width; } T154Glyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern T154Glyph D_80282A70[];
extern f32 D_80282D20;
f32 sinf(f32);
s32 strlen(u8 *);

s32 func_801BDA6C(T154Gfx **dl, T154Mtx *matrices, u8 *text, f32 x, f32 y, f32 z,
                  u8 r, u8 g, u8 b, u8 a, f32 scale)
{
    T154Glyph *glyph;
    u8 *p;
    s32 pulse = 2000;
    s32 mode = 0;
    s32 count = 0;
    s32 len;
    s32 i;
    u32 color;
    s32 alpha;
    f64 advance;
    f64 width;

    len = strlen(text);
    if (len == 0) {
        return 0;
    }
    if (scale < 0.0f) {
        pulse = (s32)(-scale - 1.0f);
        scale = 1.0f;
    }
    if (scale != 1.0f) {
        guScale(matrices, scale, scale, 1.0f);
        count = 1;
    }
    {
        T154Gfx *cmd = (*dl)++;
        cmd->w1 = 0;
        cmd->w0 = 0xE7000000;
    }
    {
        T154Gfx *cmd = (*dl)++;
        cmd->w0 = 0xFA000000;
        alpha = a;
        color = (r << 24) | (g << 16) | (b << 8) | alpha;
        cmd->w1 = color;
    }
    {
        T154Gfx *cmd = (*dl)++;
        cmd->w1 = 0xFFFDF6FB;
        cmd->w0 = 0xFCFFFFFF;
    }
    {
        T154Gfx *cmd = (*dl)++;
        cmd->w0 = 0xB6000000;
        cmd->w1 = 0x22000;
    }
    if (a == 0xFF) {
        T154Gfx *cmd = (*dl)++;
        cmd->w0 = 0xB900031D;
        cmd->w1 = 0x0F0A4000;
    } else {
        T154Gfx *cmd = (*dl)++;
        cmd->w0 = 0xB900031D;
        cmd->w1 = 0x5041C8;
    }
    i = 0;
    if (len > 0) {
        p = text;
        do {
            s8 index = *p - 0x20;
            if (index < 59 && index >= 0 && (glyph = &D_80282A70[index])->image) {
                advance = scale;
                if (mode) width = 25.0;
                else width = glyph->width * 10.0f;
                x = x + advance * width;
                guTranslate(&matrices[count], x, y, z);
                {
                    T154Gfx *cmd = (*dl)++;
                    cmd->w0 = 0x01020040;
                    cmd->w1 = (u32)&matrices[count++];
                }
                if (scale != 1.0f) {
                    T154Gfx *cmd = (*dl)++;
                    cmd->w0 = 0x01000040;
                    cmd->w1 = (u32)matrices;
                }
                if (i == pulse) {
                    {
                        T154Gfx *cmd = (*dl)++;
                        cmd->w1 = 0;
                        cmd->w0 = 0xE7000000;
                    }
                    D_80282D20 = D_80282D20 + 0.4;
                    {
                        T154Gfx *cmd = (*dl)++;
                        cmd->w0 = 0xFA000000;
                        cmd->w1 = ((u32)(sinf(D_80282D20) * 63.0f + 192.0f) << 24) | alpha;
                    }
                }
                {
                    T154Gfx *cmd = (*dl)++;
                    cmd->w0 = 0x06000000;
                    cmd->w1 = glyph->image;
                }
                if (i == pulse) {
                    {
                        T154Gfx *cmd = (*dl)++;
                        cmd->w1 = 0;
                        cmd->w0 = 0xE7000000;
                    }
                    {
                        T154Gfx *cmd = (*dl)++;
                        cmd->w0 = 0xFA000000;
                        cmd->w1 = color;
                    }
                }
                if (mode) width = 25.0;
                else width = glyph->width * 10.0f;
                x = x + advance * width;
            } else if (index == 0x4A) {
                mode = 1;
            } else {
                advance = scale;
                if (mode) width = 50.0;
                else width = 30.0;
                x = x + advance * width;
            }
            i++;
            p++;
        } while (i != len);
    }
    return count;
}
