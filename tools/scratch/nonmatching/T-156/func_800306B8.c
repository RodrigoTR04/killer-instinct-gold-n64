void func_800306B8(RenderGfx **gfx, s32 x, s32 y, u8 *text, s32 colorIndex, s32 size) {
    RenderGfx *cmd;
    RenderGlyph *glyph;
    RenderColor *color;
    s32 *scale;
    s32 i, width, mode, format;
    s32 index;
    s32 w, h;
    s32 skewS, skewT, dsdx, dtdy;
    s32 s0, t0, left, top, right, bottom;

    width = 0;
    i = 0;
    mode = -1;
    if (x == 0) {
        for (i = 0; text[i] >= 0x14; i++) {
            index = func_80030EF0(text[i]) & 0xFF;
            if (index == 0xFF) {
                width += 0x1FC;
            } else {
                glyph = &D_80069E48[index];
                width += (glyph->width + glyph->spacing + 1) * D_800482B8[size];
            }
        }
        x = 0xA0 - width / 254;
        i = 0;
    }
    cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xE7000000;
    cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xBA001701;
    cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xBA001301;
    cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xBA001001;
    cmd = *gfx; *gfx = cmd + 1; cmd->w0 = 0xB900031D; cmd->w1 = 0x504240;
    cmd = *gfx; *gfx = cmd + 1; cmd->w0 = 0xF5900000; cmd->w1 = 0x01080200;
    cmd = *gfx; *gfx = cmd + 1; cmd->w0 = 0xFA000100;
    color = &D_800482A0[colorIndex];
    x = x * 127;
    cmd->w1 = (color->b << 8) | (color->r << 24) | (color->g << 16) | 0xFF;
    cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xFB000000;
    y = y * 127;
    for (i = 0; text[i] >= 0x14; i++) {
        index = func_80030EF0(text[i]) & 0xFF;
        if (index == 0xFF) {
            x += 0x1FC;
        } else {
            glyph = &D_80069E48[index];
            scale = &D_800482B8[size];
            w = glyph->width;
            h = glyph->height;
            format = 4;
            y += (s8)glyph->baseline * *scale;
            if (text[i] == 0x86 || text[i] == 0x85 || text[i] == 0x87) {
                skewS = (w - 1) << 5;
                dsdx = (-0x1FC00 / *scale) & 0xFFFF;
            } else {
                dsdx = 0x1FC00 / *scale;
                skewS = 0;
            }
            if (text[i] == 0x80 || text[i] == 0x81 || text[i] == 0x87) {
                skewT = (h - 1) << 5;
                dtdy = (-0x1FC00 / *scale) & 0xFFFF;
            } else {
                dtdy = 0x1FC00 / *scale;
                skewT = 0;
            }
            if (index == 0x47) {
                if (mode != 1) {
                    cmd = *gfx; *gfx = cmd + 1; cmd->w0 = 0xFC30FE61; cmd->w1 = 0x55FEF379;
                }
                mode = 1;
                format = 3;
            } else {
                if (mode != 0) {
                    cmd = *gfx; *gfx = cmd + 1; cmd->w0 = 0xFCFFFFFF; cmd->w1 = 0xFFFDF2F9;
                }
                mode = 0;
            }
            cmd = *gfx; *gfx = cmd + 1;
            cmd->w0 = ((format & 7) << 21) | 0xF5000000 | 0x80000 | ((((w + 7) >> 3) & 0x1FF) << 9);
            cmd->w1 = 0x03080200;
            cmd = *gfx; *gfx = cmd + 1;
            cmd->w0 = 0xF2000000;
            cmd->w1 = ((((((w + 7) & 0xFFF8) - 1) * 4) & 0xFFF) << 12) | 0x03000000 | ((h * 4) & 0xFFF);
            cmd = *gfx; *gfx = cmd + 1;
            cmd->w1 = index * 0x120 + (s32)D_80069F70;
            cmd->w0 = ((format & 7) << 21) | 0xFD000000 | 0x100000;
            cmd = *gfx; *gfx = cmd + 1;
            cmd->w0 = 0xF3000000;
            s0 = ((((w + 7) & 0xFFF8) * (h + 1) + 1) >> 1) - 1;
            if (s0 >= 0x7FF) s0 = 0x7FF;
            cmd->w1 = ((s0 & 0xFFF) << 12) | 0x01000000;
            cmd = *gfx; *gfx = cmd + 1;
            left = 0;
            t0 = 0;
            right = (((*scale * w) + x) * 4) / 127;
            if (right > 0) left = right;
            bottom = (((*scale * h) + y) * 4) / 127;
            if (bottom > 0) t0 = bottom;
            top = (x * 4) / 127;
            cmd->w0 = (t0 & 0xFFF) | 0xE4000000 | ((left & 0xFFF) << 12);
            s0 = 0;
            right = 0;
            if (top > 0) right = top;
            bottom = (y / 127) * 4;
            if (bottom > 0) s0 = bottom;
            cmd->w1 = (s0 & 0xFFF) | 0x03000000 | ((right & 0xFFF) << 12);
            cmd = *gfx; *gfx = cmd + 1;
            left = (top * dsdx) >> 7;
            cmd->w0 = 0xB3000000;
            if (left >= 0) left = 0;
            t0 = 0;
            right = (bottom * dtdy) >> 7;
            if (right < 0) t0 = right;
            cmd->w1 = ((skewT - t0) & 0xFFFF) | ((skewS - left) << 16);
            cmd = *gfx; *gfx = cmd + 1;
            cmd->w0 = 0xB2000000;
            cmd->w1 = (dsdx << 16) | (dtdy & 0xFFFF);
            cmd = *gfx; *gfx = cmd + 1; cmd->w1 = 0; cmd->w0 = 0xE7000000;
            y -= (s8)glyph->baseline * *scale;
            x += (s8)glyph->spacing * *scale + (w + 1) * *scale;
        }
    }
}
