/* DRAFT T-020: Same control flow and size; button mask allocated in a3 rather than a2, with operand/register differences. */
typedef struct { u16 buttons; s8 x, y; } T020Controller;
extern u16 D_80127CA8[][6];

s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
    s32 result;
    s8 x, y;
    u32 buttons;
    u16 *map;
    map = D_80127CA8[arg1];
    result = 0;
    if (map[3] & (buttons = arg0->buttons)) result = 8;
    if (map[0] & buttons) result |= 1;
    if (map[1] & buttons) result |= 2;
    if (map[4] & buttons) result |= 0x10;
    if (map[2] & buttons) result |= 4;
    if (map[5] & buttons) result |= 0x20;
    if (buttons & 0x800) result |= 0x40;
    if (buttons & 0x400) result |= 0x80;
    if (buttons & 0x200) result |= 0x100;
    if (buttons & 0x100) result |= 0x200;
    x = arg0->x;
    if (x >= 41) result |= 0x200;
    if (x < -40) result |= 0x100;
    y = arg0->y;
    if (y >= 41) result |= 0x40;
    if (y < -40) result |= 0x80;
    return result;
}
