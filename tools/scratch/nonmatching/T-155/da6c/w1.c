#define COLOR_BYTE(v, shift) (((u32)(v) & 0xFF) << (shift))
extern f32 D_80282D20;
f32 sinf(f32);
s32 strlen(u8 *);

s32 func_801BDA6C(TextGfx **dl, TextMtx *matrices, u8 *text, f32 x, f32 y, f32 z,
                  u8 r, u8 g, u8 b, u8 a, f32 scale)
{
    TextGfx *cmd;
    s32 len;
    s32 pulse = 2000;
    u8 *p;
    GlyphRecord *glyph;
    s32 mode = 0;
    s32 count = 0;
    s32 i;
    f32 phase;
    f32 *glowPhase = &D_80282D20;
    u32 color;
    s32 alpha;
    f64 advance;
    f64 width;
    f64 width2;

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
        cmd = (*dl)++;
        cmd->w1 = 0;
        cmd->w0 = 0xE7000000;
    }
    {
        cmd = (*dl)++;
        cmd->w0 = 0xFA000000;
        alpha = a & 0xFF;
        color = COLOR_BYTE(r, 24) | COLOR_BYTE(g, 16) | COLOR_BYTE(b, 8) | alpha;
        cmd->w1 = color;
    }
    {
        cmd = (*dl)++;
        cmd->w0 = 0xFCFFFFFF; cmd->w1 = 0xFFFDF6FB;
    }
    {
        cmd = (*dl)++;
        cmd->w0 = 0xB6000000; cmd->w1 = 0x22000;
    }
    if (a == 0xFF) {
        cmd = (*dl)++;
        cmd->w0 = 0xB900031D; cmd->w1 = 0x0F0A4000;
    } else {
        cmd = (*dl)++;
        cmd->w0 = 0xB900031D; cmd->w1 = 0x5041C8;
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
                    cmd = (*dl)++;
                    cmd->w0 = 0x01020040;
                    cmd->w1 = (u32)&matrices[count++];
                }
                if (scale != 1.0f) {
                    cmd = (*dl)++;
                    cmd->w0 = 0x01000040;
                    cmd->w1 = (u32)matrices;
                }
                if (i == pulse) {
                    phase = *glowPhase;
                    {
                        cmd = (*dl)++;
                        cmd->w1 = 0;
                        cmd->w0 = 0xE7000000;
                    }
                    phase += 0.4;
                    *glowPhase = phase;
                    {
                        u32 glow = sinf(phase) * 63.0f + 192.0f;
                        TextGfx *cmd = (*dl)++;
                        cmd->w0 = 0xFA000000;
                        cmd->w1 = (glow << 24) | alpha;
                    }
                }
                {
                    cmd = (*dl)++;
                    cmd->w0 = 0x06000000;
                    cmd->w1 = glyph->image;
                }
                if (i == pulse) {
                    {
                        cmd = (*dl)++;
                        cmd->w1 = 0;
                        cmd->w0 = 0xE7000000;
                    }
                    {
                        cmd = (*dl)++;
                        cmd->w0 = 0xFA000000;
                        cmd->w1 = color;
                    }
                }
                if (mode) width2 = 25.0;
                else width2 = glyph->width * 10.0f;
                x = x + advance * width2;
            } else if (index == 0x4A) {
                mode = 1;
            } else {
                advance = scale;
                if (mode) width2 = 50.0;
                else width2 = 30.0;
                x = x + advance * width2;
            }
            i++;
            p++;
        } while (i != len);
    }
    return count;
}
