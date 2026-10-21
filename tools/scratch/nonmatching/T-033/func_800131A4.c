/* T-122 nonmatching: 41 differing words; 712 compiled bytes. See T-122/REPORT.md. */
/* T-054 DRAFT: 169 relocation-masked positional words differ; 676 emitted bytes. See T-054/REPORT.md. */

typedef struct { u32 command, value; } T033RenderCommand;
extern u8 D_80044A24, D_8004ABC0;

extern u16 D_8004ACFC;
extern s32 (*D_8004AEAC)(s32, s32, s32, s32);
extern void func_8001346C(T033RenderCommand **, u8, f32);
extern void func_8001BB64(T033RenderCommand **);

void func_800131A4(T033RenderCommand **arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) { extern u8 D_4AC40; T033RenderCommand *command; T033RenderCommand *g; s16 part; s16 i;
    f32 callbackX; g = (*arg0)++; g->command = 0x01020040;
    g->value = (((u32) (&D_8004ABC0)) + (D_80044A24 << 6)) + 0x80000000; g = (*arg0)++; g->command = 0x01030040; g->value = (u32)&D_4AC40; g = (*arg0)++; g->command = 0xE7000000; g->value = 0; func_8001BB64(arg0); g = (*arg0)++; g->command = 0xBA001701; g->value = 0; g = (*arg0)++;
    g->command = 0xBA001301; g->value = 0x80000; g = (*arg0)++; g->command = 0xB9000002; g->value = 0;
    g = (*arg0)++; g->command = 0xF9000000; g->value = 1; g = (*arg0)++;
    g->command = 0xB4000000;
    g->value = D_8004ACFC; g = (*arg0)++; g->command = 0xBC000404; g->value = 3;
    g = (*arg0)++; g->command = 0xBC000C04; g->value = 3; g = (*arg0)++; g->command = 0xBC001404; g->value = 0xFFFD; command = (*arg0)++; callbackX = arg1; g = command; g->command = 0xBC001C04; g->value = 0xFFFD; part = ((s16 (*)(s32, s32, s32, s32, s32)) D_8004AEAC)((s32) callbackX, (s32) arg2, (s32) arg3, (s32) arg4, (s32) arg5); i = 0; if (D_8004A738[part] > 0) { do
    { func_8001346C(arg0, ((u8 *)D_8004A688)[((i << 3) - i) + part], arg1); g = (*arg0)++; g->command = 0xE7000000; g->value = 0;
    g = (*arg0)++; i++; g->command = 0xB9000002; g->value = 0;
    } while (i < D_8004A738[part]); } }
