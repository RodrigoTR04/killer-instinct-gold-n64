extern void func_801B695C(FrontendSprite *, s32);
extern s32 func_801B6A68(FrontendGfxWords **, FrontendSprite *, s32);
extern void func_801BCB70(FrontendGfxWords **, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, void *);
extern FrontendSprite D_801F2EA8[];
extern FrontendSpriteLayout D_802854D0[];
extern u8 D_802D38C8;

void func_801C2F5C(FrontendGfxWords **arg0, s32 arg1, s32 arg2)
{
    u8 byteVal;
    s32 savedScale;
    s32 spriteSheet;
    s32 stepX;
    FrontendSprite *sprite;
    FrontendGfxWords *cmd;

    byteVal = 0xFF;
    sprite = &D_801F2EA8[D_802D38C8];
    if (sprite->texture != 0)
    {
        savedScale = sprite->scale;
        sprite->scale = (D_802854D0[D_802D38C8].scale * sprite->scale) >> 8;
        arg1 += D_802854D0[D_802D38C8].x;
        func_801B695C(sprite, 0);
        spriteSheet = func_801B6A68(arg0, sprite, 0);
        if (D_802854D0[D_802D38C8].flip != 0)
        {
            stepX = -0x10;
        }
        else
        {
            stepX = 0x10;
        }
        func_801BCB70(arg0, sprite->texture, spriteSheet, 0xC0, 0x110, stepX, 0x10, 0, 0, 0xBF, 0x10F, (f32) arg1, (f32) (D_802854D0[D_802D38C8].y + sprite->y), (s32) sprite->scale, byteVal, sprite->clip);
        if (sprite->draw != 0)
        {
            cmd = *arg0;
            *arg0 = cmd + 1;
            cmd->w1 = 0;
            cmd->w0 = 0xE7000000;
            cmd = *arg0;
            *arg0 = cmd + 1;
            cmd->w0 = 0xB9000002; cmd->w1 = 1;
            cmd = *arg0;
            *arg0 = cmd + 1;
            cmd->w0 = 0xBA001701; cmd->w1 = 0x800000;
            byteVal = D_802854D0[D_802D38C8].flip;
            if (byteVal != 0)
            {
                arg1 = 0x26C - arg1;
            }
            sprite->draw(arg0, arg1, D_802854D0[D_802D38C8].y, arg2, sprite, (s32) byteVal);
        }
        sprite->scale = (u16) savedScale;
    }
}
