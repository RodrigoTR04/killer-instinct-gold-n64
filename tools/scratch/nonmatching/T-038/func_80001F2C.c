/* DRAFT. Remaining diff: Scheduler state-machine control flow and register allocation; see REPORT.md. */
void func_800022C0();
void func_80002420();
s32 osRecvMesg(s32 *, u8 **, s32);
s32 osSendMesg(s32, s16 *, s32);
void osSpTaskLoad(u8 *);
void osSpTaskStartGo(u8 *);
void osSpTaskYield();
s32 osSpTaskYielded(u8 *);
void osViSwapBuffer(s32);
extern u8 *D_80006678;
extern u8 *D_8000667C;
extern s32 D_8000CF68;
extern s32 D_8000CF80;
extern s32 D_8000D180;
extern u8 D_8000D18C;
extern s32 D_8000D190;
extern u8 D_8000D194;
extern u8 D_8000D195;
extern u8 D_8000D196;
extern u8 D_8000D197;
extern u8 D_8000D198;

void func_80001F2C(s32 arg0) {
    u8 sp74;
    u8 *sp70;
    s16 sp50[16];
    s32 *var_s1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_s0;
    u8 temp_v1;

    D_8000D194 = 0;
    D_8000D195 = 0;
    D_8000D196 = 0;
    D_8000D198 = 1;
    sp70 = &sp74;
    D_8000D197 = 0;
    sp50[0] = 1;
loop_1:
    osRecvMesg(&D_8000CF80, &sp70, 1);
    temp_v1 = *sp70;
    if (temp_v1 == 0) {
        if (D_8000D194 == 0) {
            if (osRecvMesg(&D_8000CF68, &D_8000667C, 0) == 0) {
                if (D_8000D197 != 0) {
                    osSpTaskYield();
                    D_8000D195 = 3;
                } else {
                    osSpTaskLoad(D_8000667C + 0x18);
                    osSpTaskStartGo(D_8000667C + 0x18);
                    D_8000D194 = 1;
                    if (D_8000D198 == 1) {
                        func_80002420();
                    }
                }
            } else if ((D_8000D195 == 0) || (D_8000D196 == 2)) {
                func_80002420();
            } else {
                func_800022C0();
            }
        }
        var_s1 = &D_8000D180;
        var_s0 = 0;
        if ((s32) D_8000D18C > 0) {
            do {
                osSendMesg(*var_s1, sp50, 0);
                var_s0 += 1;
                var_s1 += 1;
            } while (var_s0 < (s32) D_8000D18C);
        }
        goto loop_1;
    }
    switch (temp_v1) {                              /* irregular */
    case 1:
        break;
    case 2:
        if (D_8000D195 == 3) {
            if (osSpTaskYielded(D_80006678 + 0x18) == 1) {
                osSpTaskLoad(D_8000667C + 0x18);
                osSpTaskStartGo(D_8000667C + 0x18);
                D_8000D194 = 1;
                D_8000D195 = 4;
            } else {
                D_8000D195 = 1;
                osSpTaskLoad(D_8000667C + 0x18);
                osSpTaskStartGo(D_8000667C + 0x18);
                D_8000D194 = 1;
                D_8000D197 = 0;
            }
        } else if (D_8000D194 != 0) {
            osSendMesg(*(s32 *)((u8 *)(D_8000667C) + (0x58)), *(s16 **)((u8 *)(D_8000667C) + (0x5C)), 1);
            D_8000D194 = 0;
            if (D_8000D196 == 0) {
                func_800022C0();
            }
        } else {
            D_8000D197 = 0;
            if (D_8000D198 == 1) {
                temp_a0 = *(s32 *)((u8 *)(D_80006678) + (0x10));
                D_8000D190 = temp_a0;
                osViSwapBuffer(temp_a0);
                D_8000D195 = 0;
                osSendMesg(*(s32 *)((u8 *)(D_80006678) + (0x58)), *(s16 **)((u8 *)(D_80006678) + (0x5C)), 1);
            }
        }
        goto loop_1;
    }
    if (D_8000D196 == 1) {
        D_8000D196 = 0;
        if (D_8000D194 == 0) {
            func_800022C0();
        }
        goto loop_1;
    }
    D_8000D198 = 1;
    if (D_8000D197 != 0) {
        goto loop_1;
    }
    temp_a0_2 = *(s32 *)((u8 *)(D_80006678) + (0x10));
    D_8000D190 = temp_a0_2;
    osViSwapBuffer(temp_a0_2);
    D_8000D195 = 0;
    osSendMesg(*(s32 *)((u8 *)(D_80006678) + (0x58)), *(s16 **)((u8 *)(D_80006678) + (0x5C)), 1);
    goto loop_1;
}
