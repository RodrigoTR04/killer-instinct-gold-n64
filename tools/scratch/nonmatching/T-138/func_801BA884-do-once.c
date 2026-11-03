/* T-138 claimed match (500 B, byte-identical) REJECTED by the lead: the trailing `do { ... if (frame < 0xC) break; D_801F39EC = clear; } while (0);`
   is a layout-only construct (equivalent to a plain `if`). Plain if, early return, frame=0 select and literal-0 forms all differ. Needs a different honest structure. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA884;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F39EC;
extern u8 D_801F39F0[];
extern u8 D_801F39F4[];

void func_801BA884(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA884 *arg4, s32 arg5)
{
    s32 firstY;
    s32 frame;
    s32 x1;
    s32 secondY;
    int clear;
    s32 x0;
    x0 = (arg1 * 4) + (((s32) (((arg5 * 0x15) + 0x1CC) * arg4->scale)) >> 0xA);
    firstY = ((arg2 * 4) + (((s32) (arg4->scale * 0x70)) >> 0xA)) + (arg4->yOffset * 4);
    secondY = ((arg2 * 4) + (((s32) (arg4->scale * 0x70)) >> 0xA)) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + (((s32) (arg4->scale * 0x12C)) >> 0xA);
    if (arg5 != 0)
    {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *((s32 *) (D_801F39F0 + (D_801F39EC * 8))), 2, 0x20, 0x40, 0x20, 0x40, 0, 0, 0x1F, 0x3F, (f32) x0, (f32) firstY, ((s32) (arg4->scale * 4)) / 3, arg5);
    clear = 0;
    do {
        func_801BC1B0(arg0, *((s32 *) (D_801F39F4 + (D_801F39EC * 8))), 2, 0x34, 0x1C, 0x34, 0x1C, clear, clear, 0x33, 0x1B, (f32) x1, (f32) secondY, (s32) arg4->scale, arg5);
        frame = D_801F39EC + 1;
        D_801F39EC = frame;
        if (frame < 0xC) break;
        D_801F39EC = clear;
    } while (0);
}

