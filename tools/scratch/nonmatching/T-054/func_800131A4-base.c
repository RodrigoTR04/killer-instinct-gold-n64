
/* DRAFT. Remaining diff: 181 positional differing words; 732/712 bytes */
typedef struct { u32 command, value; } T033RenderCommand;
extern u8 D_80044A24, D_8004ABC0;
extern s8 D_8004A738, D_8004A688;
extern u16 D_8004ACFC;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern void func_8001346C(T033RenderCommand **, u8, f32);
extern void func_8001BB64(T033RenderCommand **);

void func_800131A4(T033RenderCommand **arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    T033RenderCommand *g;
    s16 part, i;
    g = (*arg0)++;
    g->command = 0x01020040;
    g->value = (u32)&D_8004ABC0 + (D_80044A24 << 6) + 0x80000000;
    g = (*arg0)++;
    g->value = 0x4AC40;
    g->command = 0x01030040;
    g = (*arg0)++;
    g->value = 0;
    g->command = 0xE7000000;
    func_8001BB64(arg0);
    g = (*arg0)++;
    g->value = 0;
    g->command = 0xBA001701;
    g = (*arg0)++;
    g->value = 0x80000;
    g->command = 0xBA001301;
    g = (*arg0)++;
    g->value = 0;
    g->command = 0xB9000002;
    g = (*arg0)++;
    g->value = 1;
    g->command = 0xF9000000;
    g = (*arg0)++;
    g->command = 0xB4000000;
    g->value = D_8004ACFC;
    g = (*arg0)++;
    g->value = 3;
    g->command = 0xBC000404;
    g = (*arg0)++;
    g->value = 3;
    g->command = 0xBC000C04;
    g = (*arg0)++;
    g->value = 0xFFFD;
    g->command = 0xBC001404;
    g = (*arg0)++;
    g->value = 0xFFFD;
    g->command = 0xBC001C04;
    part = ((s32 (*)(s32,s32,s32,s32,s32))D_8004AEAC)((s32)arg1,(s32)arg2,(s32)arg3,(s32)arg4,(s32)arg5);
    i = 0;
    if ((&D_8004A738)[part] > 0) {
        do {
            func_8001346C(arg0, (&D_8004A688)[i * 7 + part], arg1);
            g = (*arg0)++;
            g->value = 0;
            g->command = 0xE7000000;
            g = (*arg0)++;
            i++;
            g->value = 0;
            g->command = 0xB9000002;
        } while (i < (&D_8004A738)[part]);
    }
}
