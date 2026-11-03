/* T-143 DRAFT: 101 relocation-masked differing words; 636/636 bytes. */
extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8;
extern u8 D_8004AC92[], D_8004AC8E[];
void func_8001BB64(T033RenderCommand **list) {
    s16 colors[3];
    u8 brightness; s16 r,g,b;
    u8 amount,mode;
    u8 *src;
    s16 *dst;
    T033RenderCommand *cmd;
    if (D_8004AA28 == 0) {
        if (D_801D7DFC > 0) brightness = (D_801D7DFC * 4 - 1);
        else brightness = 0;
        amount = (&D_801D7DF8)[0]; mode = (&D_801D7DF8)[1];
    } else { brightness = 0; amount = 0; mode = 0; }
    src = D_8004AC92; dst = colors;
    do {
        *dst = *src++ + brightness;
        if (*dst >= 128) *dst = 127;
        dst++;
    } while (src != D_8004AC92 + 3);
    cmd = (*list)++;
    cmd->command = 0xFB000000;
    cmd->value = ((colors[2] & 255) << 8) | (colors[0] << 24) | ((colors[1] & 255) << 16);
    switch (mode) {
    case 2:
        b = D_8004AC8E[2] + amount * 4;
        if (b >= 128) b = 127;
        cmd = (*list)++;
        cmd->command = 0xFA000100;
        cmd->value = (D_8004AC8E[1] << 16) | (D_8004AC8E[0] << 24) | ((b & 255) << 8) | 255;
        break;
    case 1: case 4:
        r = D_8004AC8E[0] + amount * 4;
        if (r >= 128) r = 127;
        g = D_8004AC8E[1] + amount * 4;
        if (g >= 128) g = 127;
        b = D_8004AC8E[2] + amount * 4;
        if (b >= 128) b = 127;
        cmd = (*list)++;
        cmd->command = 0xFA000100;
        cmd->value = (r << 24) | ((g & 255) << 16) | ((b & 255) << 8) | 255;
        break;
    default:
        r = D_8004AC8E[0] + amount * 4;
        if (r >= 128) r = 127;
        cmd = (*list)++;
        cmd->command = 0xFA000100;
        cmd->value = (D_8004AC8E[2] << 8) | (r << 24) | (D_8004AC8E[1] << 16) | 255;
        break;
    }
}
