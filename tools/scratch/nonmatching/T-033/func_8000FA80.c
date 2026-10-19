/* DRAFT. Remaining diff: 2028 positional differing words; 8148/7436 bytes */
/* Task, camera, and snapshot layouts are reconstructed; packed HUD/replay views and callback ABIs remain provisional. */
typedef struct { u32 command, value; } T033FrameCommand;
typedef struct { u8 pad[0xC]; s32 flags; void *framebuffer; u8 pad14[4]; u32 type, taskFlags; void *boot; u32 bootSize; void *ucode; u32 ucodeSize; void *ucodeData; u32 ucodeDataSize; void *stack; u32 stackSize; void *output; u32 outputSize; T033FrameCommand *list; u32 listSize; void *yield; u32 yieldSize; void *queue; void *message; } T033FrameTask;
typedef struct { f32 x,y,z,pitch,yaw; } T033InitialCamera;
typedef struct { f32 x,y,z,pitch,yaw,unused14,unused18,timer,unused20,distance; } T033Camera;
typedef struct { s32 x,y,z; u8 padC[0x14]; u8 a,b; u16 state; s32 facing; s16 end28,end2A; s32 end2C; } T033FrameSnapshot;
typedef struct { u8 kind,pad1[3]; s32 x,y,z; u8 pad10[4]; u8 a,pad15[15]; u8 b,pad25[15]; u16 state; u8 pad36[0x1E]; u16 speed; u8 pad56[0x42]; s32 facing; u8 pad9C[4]; u8 dirty; u8 padA1[0x5F]; } T033FramePlayer;
extern T033FrameCommand *D_8004A420;
extern T033FrameCommand *D_8004A418[2];
extern void *D_8004A428[2];
extern T033FrameTask *D_8004A318;
extern T033FrameSnapshot D_8004A450[2];
extern T033FrameSnapshot D_8004A480;
extern T033InitialCamera D_80044AC8[];
extern T033Camera D_80044BCC[];
extern T033FramePlayer D_801D3430[];
extern u8 D_8004EA9C[2], D_8004EA9E[2];
extern u8 D_8004EAA0[2], D_8004EAA2[2];
extern u8 D_8004AC92[3];

extern u8 D_8004A298[], D_8004A2D8[];
extern f32 D_800695BC, D_800695D0;
extern void (*D_800451EC[])(void);
extern void *D_8004A294;
extern void (*D_8004AA30)(void *,void *,f32,f32,f32,f32,f32);
extern void (*D_8004AA34)(void *);
extern void (*D_8004AA38)(void);
extern void func_8000FA80(void);
extern void func_8002A900(s32);
extern void boot_inflate(void *, void *, void *);
extern void osViBlack(s32);
extern f32 sinf(f32), cosf(f32);

extern void boot_dma_chunked();
extern void func_8001178C();
extern void func_80012100();
extern void func_800121C8();
extern void func_800122F8();
extern void func_80012360();
extern void func_80012390();
extern void func_8001256C();
extern void func_80012950();
extern void func_80012A8C();
extern void func_80012B7C();
extern void func_800131A4();
extern void func_8001A9E8();
extern void func_8001AA20();
extern void func_8001AA90();
extern void func_8001C5A0();
extern void func_8001CD50();
extern void func_8001D080();
extern void func_8001D37C();
extern void func_8001D42C();
extern void func_8001D7E4();
extern void func_8001E0B4();
extern void func_80020E98();
extern void func_80021ADC();
extern void func_80021B6C();
extern void func_80024CE0();
extern void func_80025354();
extern void func_800253D0();
extern void func_80026738();
extern void func_80026AA0();
extern void func_80026B38();
extern void func_80028230();
extern void func_80028708();
extern void func_800287D4();
extern void func_80029770();
extern void func_80029AB0();
extern void func_80029BE0();
extern void func_8002A888();
extern void func_8002B57C();
extern void func_8002B6EC();
extern void func_8002B710();
extern void func_8002B7E0();
extern void func_8002B8B0();
extern void func_8002B9B4();
extern void func_8002BAF0();
extern void func_8002BBD0();
extern void func_8002DCC8();
extern void func_8002DDD4();
extern void func_8002F6F4();
extern void func_8002F8F8();
extern void func_800306B8();
extern void func_801AD900();
extern void osInvalDCache();
extern void osInvalICache();
extern s32 osRecvMesg();
extern void osSendMesg();
extern void osViSetMode();
extern void osViSetSpecialFeatures();
extern void osViSwapBuffer();
extern void osWritebackDCacheAll();
extern u8 D_800066D0;
extern u8 D_800071F0;
extern u8 D_8000C3C8;
extern u8 D_8000CF50;
extern u8 D_80042710;
extern u8 D_800427E0;
extern u8 D_80044A10;
extern u8 D_80044A18;
extern u8 D_80044A1C;
extern u8 D_80044A20;
extern u8 D_80044A24;
extern u8 D_80044A28;
extern f32 D_80044C2C;
extern u8 D_80044DD4;
extern f64 D_80048760;
extern f64 D_80048768;
extern f64 D_80048770;
extern f64 D_80048778;
extern u8 D_800496D0;
extern u8 D_80049770;
extern u8 D_8004A258;
extern s32 D_8004A264;
extern u32 D_8004A280;
extern u8 D_8004A320;
extern u8 D_8004A400;
extern u8 D_8004A401;
extern s8 D_8004A402;
extern u8 D_8004A403;
extern s8 D_8004A404;
extern u8 D_8004A407;
extern s8 D_8004A408;
extern s8 D_8004A409;
extern u8 D_8004A40C;
extern u8 D_8004A40D;
extern s8 D_8004A40F;
extern s16 D_8004A410;
extern s32 D_8004A42C;
extern u8 D_8004A430;
extern s32 D_8004A4B0;
extern u8 D_8004A4B4;
extern s8 D_8004A4B5;
extern u8 D_8004AC88;
extern u8 D_8004AC8B;
extern s8 D_8004ACDC;
extern u8 D_8004CED0;
extern u8 D_8004D26C;
extern s16 D_8004D272;
extern s8 D_8004EA9A;
extern u8 D_8004EAA4;
extern s32 D_8004EAA8;
extern s32 D_8004EAAC;
extern s32 D_8004EAB0;
extern s32 D_8004EAB4;
extern s8 D_8004EAB8;
extern u8 D_8004EAC8;
extern u8 D_8004EEC8;
extern u8 *D_8004F2C8;
extern u8 *D_8004F2CC;
extern u16 D_80061490;
extern u8 D_80061494;
extern s8 D_80061CDC;
extern s32 D_80066C40;
extern u8 D_80068530;
extern f32 D_800695B8;
extern f32 D_800695C0;
extern f32 D_800695C4;
extern f32 D_800695C8;
extern f32 D_800695CC;
extern f32 D_800695D4;
extern f32 D_800695D8;
extern f32 D_800695DC;
extern f32 D_800695E0;
extern f32 D_800695F8;
extern f32 D_800695FC;
extern f32 D_800698C0;
extern s32 D_800698C4;
extern s32 D_800698C8;
extern s8 D_80069930;
extern s32 D_80069940;
extern u8 D_80069948;
extern u8 D_80127C40;
extern u8 D_80127C50;
extern u8 D_80127CE8;
extern u8 D_80127CFE;
extern u8 D_8012834B;
extern u8 D_801C3FC0;
extern u8 D_801D3230;
extern s16 D_801D73C8;
extern u8 D_801D7DF8;
extern u8 D_801D7DF9;
extern u16 D_801D876C;
extern u8 D_801D8771;
extern u8 D_801D87FE;
extern u8 D_803B5000;
extern u8 D_803DA800;

void func_8000FA80(void) {
    u8 sp124[12];
    T033FrameCommand *sp104[2];
    s16 *spFC;
    u8 spF2;
    u8 *sp74;
    u32 sp58;
    u8 *temp_t9_2;
    u8 *var_a2;
    u8 *var_s0_3;
    u8 *var_s0_4;
    T033FrameCommand **var_t0_2;
    s32 var_a1_2;
    s32 var_a2_3;
    s32 var_a3_3;
    T033Camera *temp_s0;
    T033Camera *temp_s0_2;
    T033Camera *temp_s0_3;
    T033FrameCommand **var_a3_2;
    T033FrameCommand **var_a3_4;
    T033FrameCommand *temp_t6;
    T033FrameCommand *temp_t6_3;
    T033FrameCommand *temp_t6_4;
    T033FrameCommand *temp_v0_12;
    T033FrameCommand *temp_v0_13;
    T033FrameCommand *temp_v0_14;
    T033FrameCommand *temp_v0_15;
    T033FrameCommand *temp_v0_16;
    T033FrameCommand *temp_v0_17;
    T033FrameCommand *temp_v0_19;
    T033FrameCommand *temp_v0_20;
    T033FrameCommand *temp_v0_21;
    T033FrameCommand *temp_v0_22;
    T033FrameCommand *temp_v0_23;
    T033FrameCommand *temp_v0_24;
    T033FrameCommand *temp_v0_25;
    T033FrameCommand *temp_v0_26;
    T033FrameCommand *temp_v0_27;
    T033FrameCommand *temp_v0_28;
    T033FrameCommand *temp_v0_29;
    T033FrameCommand *temp_v0_2;
    T033FrameCommand *temp_v0_3;
    T033FrameCommand *temp_v0_6;
    T033FrameCommand *temp_v0_7;
    T033FrameCommand *temp_v0_8;
    T033FramePlayer *temp_s1;
    T033FramePlayer *var_a1;
    T033FramePlayer *var_s1;
    T033FramePlayer *var_s1_3;
    T033FrameSnapshot *temp_s0_5;
    T033FrameSnapshot *var_s0;
    T033FrameSnapshot *var_s0_2;
    T033InitialCamera *temp_v0;
    s16 *var_s0_5;
    s16 temp_t9_4;
    s16 temp_v1;
    s16 var_a0_3;
    s16 var_a0_4;
    s16 var_a2_4;
    s16 var_v1_5;
    s16 var_v1_8;
    s16 var_v1_9;
    s32 *temp_s0_4;
    s32 temp_a0;
    s32 temp_f6;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_t9_3;
    s32 temp_v0_11;
    s32 temp_v0_18;
    s32 temp_v0_4;
    s32 var_a1_3;
    s32 var_a3;
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s5_4;
    s32 var_s5_5;
    s32 var_s5_6;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1_4;
    s8 var_t0_4;
    u16 *var_v1_2;
    u16 temp_t9;
    u16 temp_v0_5;
    u32 *var_s1_2;
    u32 temp_t8_2;
    u32 temp_v0_9;
    u32 var_s5_3;
    u32 var_v0_3;
    u32 var_v1_3;
    u8 *temp_s2;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 *var_a0_5;
    u8 *var_a0_6;
    u8 *var_s4;
    u8 *var_t0;
    u8 *var_v0;
    u8 *var_v1_6;
    u8 *var_v1_7;
    u8 temp_a2;
    u8 temp_t8;
    u8 temp_t9_5;
    u8 var_t0_3;
    u8 **var_a2_2;
    u8 **var_a2_5;
    u8 *temp_v0_10;
    u8 *var_v0_10;
    u8 *var_v0_6;
    u8 *var_v0_7;
    u8 *var_v0_8;
    u8 *var_v0_9;
    u8 *var_v1;

    (*(s32 *)(sp124 + 0)) = (s32) (*(s32 *)(&D_80044A28 + 0));
    (*(s32 *)(sp124 + 4)) = (s32) (*(s32 *)(&D_80044A28 + 4));
    (*(s32 *)(sp124 + 8)) = (s32) (*(s32 *)(&D_80044A28 + 8));
    spFC = 0;
    spF2 = 0;
    osViBlack(1);
    func_8002B57C();
    D_80069930 = 1;
    func_800121C8();
    D_80069930 = 0xA;
    if (((D_80127C40 == 1) || (D_80127C40 == 0x11)) && (D_8004A407 != 3)) {
        D_8004EA9C[0] = (*(u8 *)(&D_80127CE8 + 0));
        D_8004EA9C[1] = (*(u8 *)(&D_80127CE8 + 11));
    }
    if (D_8012834B == 0xA) {
        D_8004AC8B = 0;
        D_8004A4B0 = 0;
    }
    if (D_8004AC8B != 0) {
        D_8004AC8B = sp124[D_8004AC8B - 1];
    }
    if (D_8004A4B0 == 1) {
        D_8004AC8B = 0;
    }
    if (D_8004A407 == 3) {
        D_8004A410 = 0x4B0;
        D_8004A403 = 0;
    }
    D_8004A428[0] = &D_803B5000;
    D_8004A428[1] = &D_803DA800;
    D_8004A280 = 0;
    D_8004A400 = 1;
    osInvalICache(func_801AD900, &D_801C3FC0 - (u8 *)func_801AD900, 1);
    osInvalDCache(&D_801C3FC0, &D_801D3230 - &D_801C3FC0);
    boot_dma_chunked((*(u32 *)(&D_800071F0 + 16)), 0x802D4000, (*(u32 *)(&D_800071F0 + 20)) - (*(u32 *)(&D_800071F0 + 16)));
    boot_inflate((u8 *)0x802D4000, func_801AD900, (u8 *)0x803A2000);
    func_8002B6EC();
    func_8002B710();
    func_8002B6EC();
    if (D_8004A4B0 == 1) {
        D_8004AC88 = 0xB;
    } else if ((D_8004A4B0 == 2) && (D_8004A407 != 3)) {
        D_8004AC88 = 0xC;
    }
    func_80012950(0);
    if (D_8004AC88 == 0xC) {
        if (D_8004A407 == 1) {
            D_8004EA9C[0] = D_8004EA9C[1];
            D_8004EA9E[0] = D_8004EA9E[1];
        } else {
            D_8004EA9C[1] = D_8004EA9C[0];
        }
    }
    func_8001CD50();
    func_80012100(D_8004EA9C[0], D_8004EA9C[1]);
    if (D_8004AC88 == 0xC) {
        func_8001D42C(D_8004EA9C[0], 7, 0x803A3FE0);
        func_8001D42C(D_8004EA9C[0], ((s32) (D_8004EA9E[0] + 2) % 7) & 0xFF, 0x803A3FC0);
        D_8004EA9E[1] = 0;
        D_8004EA9C[1] = 0xD;
        func_8001D37C(D_8004EA9C[0], 0xD & 0xFF);
        D_8004EA9C[1] = D_8004EA9C[0];
    }
    func_8002B7E0();
    if (D_8004AC88 == 0xC) {
        func_8002B8B0(0U);
    } else {
        func_8002B8B0(D_80127C50);
    }
    D_8004A401 = 1;
    D_8004A404 = 0;
    D_8004A402 = 0;
    D_8004A408 = 0;
    D_8004A40C = 0;
    D_80069940 = 0;
    D_8004A40D = 0;
    func_80029770();
    func_80012A8C(D_8004AC88);
    D_800451EC[D_8004AC88]();
    if (D_8004AC88 == 0xC) {
        D_8004AC92[0] = 0;
        D_8004AC92[1] = 0x40;
        D_8004AC92[2] = 0x40;
    }
    temp_v0 = &D_80044AC8[D_8004AC88];
    D_800695CC = temp_v0->x;
    D_800695D0 = temp_v0->y;
    D_800695D4 = temp_v0->z;
    D_800695D8 = temp_v0->pitch;
    D_800695DC = temp_v0->yaw;
    D_800695E0 = 0.0f;
    func_801AD900(D_8012834B, D_8004A4B4, D_8004AC88);
    var_a1 = D_801D3430;
    var_v0 = D_8004EA9E;
    var_s5 = 0;
    var_a0 = (u8 *)9;
    do {
        if (*var_v0 == 9) {
            ((u8 *)&D_801D3430[var_s5])[-0x160] = 1;
        }
        var_s5 += 1;
        var_v0 += 1;
    } while (var_s5 < 2);
    var_s0 = D_8004A450;
    if (D_8004A407 != 3) {
        var_t0 = &D_80127CFE;
        var_a2 = &D_8004A430;
        var_s5_2 = 0;
        var_a3 = 0;
        do {
            var_a1 = (T033FramePlayer *) *var_t0;
            ((u8 *)var_a2)[0] = 0;
            var_v0_2 = 0;
            ((u8 *)var_a2)[1] = (s8) var_a1;
            if ((s32) var_a1 > 0) {
                var_a0 = (var_s5_2 * 0xB) + &D_80127CE8;
                var_v1 = var_a3 + &D_8004A430;
                do {
                    temp_t8 = *var_a0;
                    var_v0_2 += 1;
                    var_v1 += 1;
                    var_a0 += 1;
                    ((u8 *)var_v1)[1] = temp_t8;
                } while (var_v0_2 < (s32) var_a1);
            }
            var_s5_2 += 1;
            var_a3 += 0x10;
            var_a2 += 0x10;
            var_t0 += 1;
        } while (var_s5_2 != 2);
    }
    D_8004A4B5 = 0;
    D_8004A418[1] = (T033FrameCommand *)((u8 *)D_8004A294 + 0x73A0);
    var_a2_2 = D_8004A428;
    var_a3_2 = D_8004A418;
    sp74 = &D_800496D0;
    var_t0_2 = sp104;
    D_8004A418[0] = (T033FrameCommand *) D_8004A294;
    do {
        temp_t6 = *var_a3_2;
        var_s0++;
        var_a3_2++;
        D_8004A420 = temp_t6;
        D_8004A420 = temp_t6 + 8;
        temp_t6->value = 0;
        temp_t6->command = 0xBC000006;
        temp_v0_2 = D_8004A420;
        var_a2_2++;
        var_t0_2++;
        D_8004A420 = temp_v0_2 + 8;
        temp_v0_2->value = (u32) &D_800496D0;
        temp_v0_2->command = 0x06000000;
        temp_v0_3 = D_8004A420;
        D_8004A420 = temp_v0_3 + 8;
        temp_v0_3->command = 0xFF10013F;
        temp_v0_3->value = ((u32 *)var_a2_2)[-1] + 0x80000000;
        (*(s16 *)((u8 *)var_s0 + -8)) = 0;
        (*(s16 *)((u8 *)var_s0 + -6)) = 0;
        (*(s16 *)((u8 *)var_s0 + -4)) = 0;
        var_t0_2[-1] = (T033FrameCommand *) D_8004A420;
    } while ((u8 *)var_s0 != (u8 *)&D_8004A4B0);
    (*(s16 *)(D_8004A2D8 + 0)) = 2;
    (*(s16 *)(D_8004A2D8 + 32)) = 2;
    D_8004A420 = sp104[D_80044A24];
    func_80024CE0(var_a0, (u8) var_a1, var_a2_2, var_a3_2);
    func_80021ADC(0, D_8004EA9C[0]);
    func_80021ADC(1, D_8004EA9C[1]);
    func_80020E98(2, 0xBU, 0);
    if (D_8004AC88 != 0xC) {
        func_80012390();
        func_80020E98(1, D_8004EA9C[1], 0);
    } else {
        func_80012360();
    }
    func_80020E98(0, D_8004EA9C[0], 0);
    func_80025354();
    D_8004F2C8 = &D_8004EAC8;
    D_8004F2CC = 0;
    D_8004EA9A = 0;
    func_8001D7E4(0, 0U, 1U, 0, 0);
    D_8004F2C8 = &D_8004EEC8;
    if (D_8004AC88 != 0xC) {
        func_8001D7E4(1, 0U, 1U, 1, 0);
    } else {
        func_8001D7E4(1, 0U, 1U, 0, 0);
    }
    D_8004F2C8 = 0;
    D_8004EAA0[1] = 1;
    D_8004EAA0[0] = 1;
    D_8004EAA2[1] = 0;
    D_8004EAA2[0] = 0;
    D_8004EA9A = 4;
    func_8001D7E4(0x11, 0x48U, 0x13U, 2, 0);
    if (osRecvMesg(D_8004A298, &spFC, 0) == 0) {
        do {

        } while (osRecvMesg(D_8004A298, &spFC, 0) == 0);
    }
    func_800122F8(D_8004A42C);
    osViBlack(1);
    osViSetMode(&D_800066D0);
    osViSwapBuffer(D_8004A42C);
    osViSetSpecialFeatures(2);
    D_80044A24 = 0;
    do {
loop_49:
        osRecvMesg(D_8004A298, &spFC, 1);
        temp_v1 = *spFC;
        if (temp_v1 != 1) {
            if (temp_v1 == 2) {
                D_8004A414 -= 1;
                if ((D_801D87FE != 0) && ((s32) D_8004A40D < 4)) {
                    D_8004A40D += 1;
                }
            }
            goto loop_49;
        }
        temp_v0_4 = D_8004A414;
        if (temp_v0_4 >= 2) {
            if (D_8004A40C == 0) {
                func_8001178C(&D_8004A264);
                if (D_801D87FE == 0) {
                    func_8002BBD0(D_8004A450, &D_8004A480);
                    D_8004D26C += 1;
                    var_v1_2 = &D_80061490;
                    var_s1 = D_801D3430;
                    do {
                        temp_v0_5 = *var_v1_2;
                        temp_t9 = var_s1->speed;
                        var_v1_2++;
                        var_s1++;
                        var_v1_2[-1] = (s16) (temp_v0_5 + ((s32) (temp_t9 - temp_v0_5) / 8));
                    } while ((u8 *)var_v1_2 != &D_80061494);
                    func_8001A9E8(D_800695DC, &D_80061494);
                    func_80026AA0();
                    if (D_8004D272 < 0x167) {
                        D_8004D272 += 1;
                    } else {
                        D_8004D272 = 0;
                    }
                    func_80028708();
                    func_800287D4();
                    func_80029AB0();
                }
            } else if ((D_8004A40C == 1) || (D_8004A40C == 3)) {
                if (D_8004A40F > 0) {
                    D_8004A40F -= 4;
                }
            } else if (D_8004A40F < 0x3C) {
                D_8004A40F += 4;
            }
            goto loop_49;
        }
        if (D_8004A401 != 0) {
            sp58 = &D_800427E0 - &D_80042710;
            var_s5_3 = 0;
            D_8004A420 = sp104[D_80044A24];
            if (D_8004A401 == 2) {
                var_v1_3 = D_8004A280;
                if (var_v1_3 == 0xA) {
                    D_8004A280 = 9;
                    var_v1_3 = 9;
                }
                temp_a2 = D_8004AC88;
                D_8004A230[var_v1_3] = 0x110F;
                D_8004A280 = var_v1_3 + 1;
                D_8004A401 = 3;
                temp_s0 = &D_80044BCC[temp_a2];
                temp_f6 = (s32) temp_s0->timer;
                D_800698C4 = temp_f6;
                D_800698C8 = temp_f6;
                D_800695B8 = D_800695CC;
                D_800695BC = D_800695D0;
                D_800695C0 = D_800695D4;
                D_800695C4 = D_800695D8;
                D_800695C8 = D_800695DC;
                D_800695F8 = temp_s0->y;
                D_800695FC = 0.0f;
                D_800698C0 = 0.0f;
                if ((*(&D_80044DD4 + temp_a2) & 8) == 8) {
                    temp_s0_2 = &D_80044BCC[D_8004AC88];
                    temp_s0_2->x = D_800695CC - (temp_s0_2->distance * sinf((f32) (((f64) D_800695DC * D_80048760) / D_80048768)));
                    temp_s0_3 = &D_80044BCC[D_8004AC88];
                    temp_s0_3->z = (temp_s0_3->distance * cosf((f32) (((f64) D_800695DC * D_80048770) / D_80048778))) + D_800695D4;
                }
                if (temp_a2 == 2) {
                    if (D_800695DC < 180.0f) {
                        D_80044C2C = 90.0f;
                    } else {
                        D_80044C2C = -90.0f;
                    }
                }
                D_8004ACDC = 0;
            }
            func_8001178C();
            if ((D_8004A403 != 0) && (D_801D87FE != 0) && (D_8004A40D == 4) && (D_8004AC88 != 1) && (D_8004AC88 != 8) && (D_8004AC88 != 5)) {
                temp_v0_6 = D_8004A420;
                D_8004A420 = temp_v0_6 + 8;
                temp_v0_6->value = 0;
                temp_v0_6->command = 0xE7000000;
                temp_v0_7 = D_8004A420;
                D_8004A420 = temp_v0_7 + 8;
                temp_v0_7->value = 0x4403C0;
                temp_v0_7->command = 0xED0C0000;
                temp_v0_8 = D_8004A420;
                D_8004A420 = temp_v0_8 + 8;
                temp_v0_8->value = 0;
                temp_v0_8->command = 0xE7000000;
            }
            if (D_8004A280 != 0) {
                var_s1_2 = D_8004A230;
                do {
                    var_v0_3 = *var_s1_2;
                    if (var_v0_3 == 0x742) {
                        spF2 = 0;
                        func_8002A900(0x2B);
                        func_8002A888();
                        D_8004AC8B = 0;
                    } else if ((var_v0_3 == 0x747) || (var_v0_3 == 0xF17) || (var_v0_3 == 0x16E7)) {
                        spF2 = 0;
                        func_8002A900(0x2E);
                        func_8002A888();
                        D_8004AC8B = 0;
                    } else {
                        temp_t8_2 = var_v0_3 - 0x7D0;
                        if (var_v0_3 < 0x7D0U) {
                            var_v1_4 = 0;
                        } else {
                            var_v1_4 = 2;
                            if (var_v0_3 < 0xFA0U) {
                                var_v1_4 = 1;
                            }
                        }
                        if (var_v0_3 >= 0x1770U) {
                            *var_s1_2 = temp_t8_2;
                            var_v0_3 = temp_t8_2;
                        }
                        temp_s0_4 = (var_v1_4 * 4) + &D_8004A258;
                        temp_a0 = *temp_s0_4;
                        *var_s1_2 = var_v0_3 - (var_v1_4 * 0x7D0);
                        if (temp_a0 != 0) {
                            func_8002F8F8(temp_a0);
                        }
                        temp_v0_9 = *var_s1_2;
                        if ((temp_v0_9 != 0) && (temp_v0_9 < 0x1AEU)) {
                            func_8002F6F4(D_80066C40, (s16) temp_v0_9, temp_s0_4);
                        }
                    }
                    var_s5_3 += 1;
                    var_s1_2 += 4;
                } while (var_s5_3 < (u32) D_8004A280);
                var_s5_3 = 0;
            }
            D_8004A280 = 0;
            if (D_8004AC88 == 0xC) {
                D_8004AC8B = 0x29;
            }
            if ((D_8004A400 != 0) && (D_8004AC8B != spF2)) {
                func_8002A900((s32) D_8004AC8B);
                func_8002A888();
                spF2 = D_8004AC8B;
            }
            func_8001C5A0();
            func_80028708();
            func_8002BAF0(D_8004A450);
            func_8002BAF0(&D_8004A480);
            if ((D_8004A40C == 0) && (D_801D87FE == 0)) {
                func_8002BBD0(D_8004A450, &D_8004A480);
            }
            func_8002B9B4();
            D_8004A409 = 0;
            do {
                if ((D_801D876C == 0) || (var_s5_3 != D_801D8771) || (D_8004AC88 == 0xB)) {
                    temp_s0_5 = &D_8004A450[var_s5_3];
                    temp_s1 = &D_801D3430[var_s5_3];
                    temp_s2 = &temp_s1->pad56[0x12];
                    func_8002DDD4((*(f32 *)((u8 *)temp_s0_5 + 0xC)), (*(f32 *)((u8 *)temp_s0_5 + 0x18)), (*(s32 *)((u8 *)temp_s0_5 + 0x14)), temp_s2, &temp_s0_5->padC[0x10]);
                    func_8002DDD4((*(f32 *)((u8 *)temp_s0_5 + 0xC)), (*(f32 *)((u8 *)temp_s0_5 + 0x10)), (*(s32 *)((u8 *)temp_s0_5 + 0x14)), temp_s2, &temp_s1->pad56[0x16]);
                    (*(s32 *)((u8 *)temp_s0_5 + 0x1C)) = (s32) ((s32) (*(s32 *)((u8 *)temp_s0_5 + 0x1C)) / 16);
                    func_8002DCC8((*(f32 *)((u8 *)temp_s0_5 + 0xC)), (*(f32 *)((u8 *)temp_s0_5 + 0x10)), (*(s32 *)((u8 *)temp_s0_5 + 0x14)), &temp_s1->pad56[0x1A]);
                }
                var_s5_3 += 1;
            } while ((s32) var_s5_3 < 2);
            if ((D_8004A40C == 0) && (D_801D87FE == 0)) {
                D_8004AA38();
                func_8001AA20();
                func_80026AA0();
                func_80029AB0();
            }
            if ((s32) D_801D7DF8 >= 0x20) {
                var_a3_3 = 0;
                var_a2_3 = 0;
                var_a1_2 = 0;
                if ((D_801D7DF9 == 1) || (D_801D7DF9 == 4)) {
                    var_a3_3 = 0xFF;
                    var_a2_3 = 0xFF;
                    goto block_121;
                }
                if (D_801D7DF9 == 2) {
                    var_a3_3 = 0xFF;
                } else {
block_121:
                    var_a1_2 = 0xFF;
                }
                func_8001256C(&D_8004A420, var_a1_2, var_a2_3, var_a3_3);
            } else {
                func_80012B7C(&D_8004A420, D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0);
            }
            func_8001D080();
            var_s4 = D_8004EA9C;
            var_s0_2 = D_8004A450;
            var_s1_3 = D_801D3430;
            var_s5_4 = 0;
            do {
                D_8004AA34(var_s0_2);
                var_t0_3 = var_s1_3->pad56[0x3E];
                if ((var_t0_3 == 0x90) || (var_t0_3 == 0x60)) {
                    var_t0_3 = 0;
                }
                var_v0_4 = var_s5_4;
                if (var_s1_3->kind != (*var_s4 + 1)) {
                    var_v0_4 = var_s5_4 ^ 1;
                }
                if ((s8) var_s1_3->pad56[0x36] < 0) {
                    D_8004EAB8 = 1;
                }
                temp_t9_2 = (var_s5_4 << 0xA) + &D_8004EAC8;
                if (var_s5_4 == D_8004EAA4) {
                    D_8004F2C8 = temp_t9_2;
                    D_8004F2CC = temp_t9_2;
                    D_8004EA9A = 0;
                    if (D_8004AC88 == 0xC) {
                        func_8001D7E4(var_s5_4, var_s0_2->state, var_s0_2->a, 0, (s32) var_t0_3);
                    } else {
                        func_8001D7E4(var_s5_4, var_s0_2->state, var_s0_2->a, var_v0_4 & 0xFF, (s32) var_t0_3);
                    }
                    D_8004EAA2[var_s5_4] = (u8) var_s0_2->state;
                    D_8004EAA0[var_s5_4] = var_s0_2->a;
                } else if (var_s5_4 == D_8004EAA4) {
                    temp_v0_10 = (var_s5_4 * 0x1C) + &D_8004CED0;
                    temp_t7 = (*(s32 *)((u8 *)temp_v0_10 + 0));
                    temp_t8_3 = (*(s32 *)((u8 *)temp_v0_10 + 4));
                    temp_t6_2 = D_8004EAA8;
                    temp_t9_3 = D_8004EAAC;
                    D_8004EAB0 = temp_t7;
                    D_8004EAA8 = temp_t7;
                    D_8004EAB4 = temp_t8_3;
                    D_8004EAAC = temp_t8_3;
                    (*(s32 *)((u8 *)temp_v0_10 + 0)) = temp_t6_2;
                    (*(s32 *)((u8 *)temp_v0_10 + 4)) = temp_t9_3;
                }
                D_8004F2C8 = 0;
                D_8004F2CC = 0;
                var_s5_4 += 1;
                D_8004EAB8 = 0;
                var_s1_3++;
                var_s0_2++;
                var_s4 += 1;
            } while (var_s5_4 < 2);
            D_8004EAA4 ^= 1;
            func_800287D4();
            if ((s32) D_801D7DF8 < 0x20) {
                func_8001E0B4(&D_8004A420);
                func_80026B38(&D_8004A420, 1);
                D_80061CDC = 0;
                func_80021B6C(&D_8004A420);
                func_80026B38(&D_8004A420, 0);
                func_80029BE0(&D_8004A420);
                func_800131A4(&D_8004A420, D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0);
                if (D_8004AC88 != 2) {
                    if ((D_8004AC88 != 4) && (D_8004AC88 != 6)) {
                        if (D_8004AC88 == 9) {
                            goto block_145;
                        }
                    } else {
                        func_80028230(&D_8004A420);
                    }
                } else {
block_145:
                    func_80028230(&D_8004A420);
                }
            }
            if (D_8004AC88 == 0xC) {
                var_s0_3 = &D_80069948;
                var_s5_5 = 0;
                if (D_80069940 > 0) {
                    do {
                        temp_v0_11 = (*(s32 *)((u8 *)var_s0_3 + 12));
                        func_800306B8(&D_8004A420, (*(s32 *)((u8 *)var_s0_3 + 0)), (*(s32 *)((u8 *)var_s0_3 + 4)), (*(s32 *)((u8 *)var_s0_3 + 8)), temp_v0_11 >> 4, temp_v0_11 & 0xF);
                        var_s5_5 += 1;
                        var_s0_3 += 0x10;
                    } while (var_s5_5 < D_80069940);
                }
            }
            func_800253D0(&D_8004A420);
            if (D_8004A403 != 0) {
                temp_v0_12 = D_8004A420;
                D_8004A420 = temp_v0_12 + 8;
                temp_v0_12->value = 0;
                temp_v0_12->command = 0xE7000000;
                temp_v0_13 = D_8004A420;
                D_8004A420 = temp_v0_13 + 8;
                temp_v0_13->command = 0xFCFFFFFF;
                temp_v0_13->value = 0xFFFDF6FB;
                temp_v0_14 = D_8004A420;
                D_8004A420 = temp_v0_14 + 8;
                temp_v0_14->value = 0x504240;
                temp_v0_14->command = 0xB900031D;
                temp_v0_15 = D_8004A420;
                D_8004A420 = temp_v0_15 + 8;
                temp_v0_15->value = 0xA0;
                temp_v0_15->command = 0xFA000000;
                if (D_801D87FE == 0) {
                    temp_v0_16 = D_8004A420;
                    D_8004A420 = temp_v0_16 + 8;
                    temp_v0_16->value = 0x320;
                    temp_v0_16->command = 0xF64FC398;
                } else {
                    temp_v0_17 = D_8004A420;
                    D_8004A420 = temp_v0_17 + 8;
                    temp_v0_17->value = 0xC8000;
                    temp_v0_17->command = 0xF64383BC;
                }
            }
            if (D_8004AC88 != 0xC) {
                var_s0_4 = &D_80069948;
                var_s5_6 = 0;
                if (D_80069940 > 0) {
                    do {
                        temp_v0_18 = (*(s32 *)((u8 *)var_s0_4 + 12));
                        func_800306B8(&D_8004A420, (*(s32 *)((u8 *)var_s0_4 + 0)), (*(s32 *)((u8 *)var_s0_4 + 4)), (*(s32 *)((u8 *)var_s0_4 + 8)), temp_v0_18 >> 4, temp_v0_18 & 0xF);
                        var_s5_6 += 1;
                        var_s0_4 += 0x10;
                    } while (var_s5_6 < D_80069940);
                }
            }
            if (D_8004A40C != 0) {
                temp_v0_19 = D_8004A420;
                D_8004A420 = temp_v0_19 + 8;
                temp_v0_19->value = 0;
                temp_v0_19->command = 0xE7000000;
                temp_v0_20 = D_8004A420;
                D_8004A420 = temp_v0_20 + 8;
                temp_v0_20->command = 0xFCFFFFFF;
                temp_v0_20->value = 0xFFFDF6FB;
                temp_v0_21 = D_8004A420;
                D_8004A420 = temp_v0_21 + 8;
                temp_v0_21->value = 0x504240;
                temp_v0_21->command = 0xB900031D;
                temp_v0_22 = D_8004A420;
                D_8004A420 = temp_v0_22 + 8;
                temp_v0_22->value = 0xA0;
                temp_v0_22->command = 0xFA000000;
                temp_v0_23 = D_8004A420;
                D_8004A420 = temp_v0_23 + 8;
                temp_v0_23->value = 0x1B8140;
                temp_v0_23->command = 0xF6344204;
                if ((D_8004A40C == 1) || (D_8004A40C == 3)) {
                    var_t0_4 = D_8004A40F;
                    if (var_t0_4 > 0) {
                        D_8004A40F = var_t0_4 - 4;
                        goto block_164;
                    }
                } else {
                    var_t0_4 = D_8004A40F;
                    if (var_t0_4 < 0x3C) {
                        D_8004A40F = var_t0_4 + 4;
block_164:
                        var_t0_4 = D_8004A40F;
                    }
                }
                var_v0_5 = 0;
                if (D_801D73C8 != 0) {
                    var_s0_5 = &D_801D73C8;
                    do {
                        temp_t9_4 = (*(s16 *)((u8 *)var_s0_5 + 8));
                        var_v0_5 += 1;
                        var_s0_5 += 8;
                    } while (temp_t9_4 != 0);
                }
                if (var_v0_5 >= 0x10) {
                    var_v0_5 = 0xF;
                }
                temp_t7_2 = var_v0_5 * 8;
                if ((s32) D_8004A40C < 3) {
                    var_a0_2 = &D_80044A10;
                    var_v0_6 = temp_t7_2 + &D_801D73C8;
                    var_v1_5 = 0x4180;
                    do {
                        (*(s16 *)((u8 *)var_v0_6 + 0)) = (s16) *var_a0_2;
                        if (D_8004A40C == 1) {

                        }
                        (*(s16 *)((u8 *)var_v0_6 + 2)) = (s16) ((s32) ((var_t0_4 * -0x1000) + 0x78000) / 130);
                        (*(s16 *)((u8 *)var_v0_6 + 4)) = var_v1_5;
                        var_v1_5 += 0x700;
                        var_v0_6 += 8;
                        var_a0_2 += 1;
                        (*(s16 *)((u8 *)var_v0_6 + -2)) = 0x5A00;
                    } while (var_v1_5 < 0x6480);
                    var_a1_3 = (s32) ((var_t0_4 << 0xC) + 0x3C000) / 130;
                    var_v1_6 = &D_80044A18;
                    var_v0_7 = temp_t7_2 + &D_801D73C8;
                    var_a0_3 = 0x4500;
                    var_a2_4 = 0x4C00;
                    do {
                        (*(s16 *)((u8 *)var_v0_7 + 40)) = (s16) ((u8 *)var_v1_6)[0];
                        if (D_8004A40C == 2) {

                        }
                        (*(s16 *)((u8 *)var_v0_7 + 42)) = (s16) var_a1_3;
                        (*(s16 *)((u8 *)var_v0_7 + 44)) = var_a0_3;
                        (*(s16 *)((u8 *)var_v0_7 + 46)) = 0x7300;
                        (*(s16 *)((u8 *)var_v0_7 + 48)) = (s16) ((u8 *)var_v1_6)[1];
                        if (D_8004A40C == 2) {

                        }
                        (*(s16 *)((u8 *)var_v0_7 + 50)) = (s16) var_a1_3;
                        (*(s16 *)((u8 *)var_v0_7 + 52)) = var_a2_4;
                        var_a2_4 += 0xE00;
                        (*(s16 *)((u8 *)var_v0_7 + 54)) = 0x7300;
                        var_v0_7 += 0x10;
                        var_v1_6 += 2;
                        var_a0_3 += 0xE00;
                    } while (var_a2_4 != 0x6800);
                    (*(s16 *)((u8 *)var_v0_7 + 40)) = 0;
                } else {
                    var_v1_7 = &D_80044A18;
                    var_v0_8 = temp_t7_2 + &D_801D73C8;
                    var_a0_4 = 0x4500;
                    var_a2_4 = 0x5A00;
                    do {
                        (*(s16 *)((u8 *)var_v0_8 + 4)) = var_a0_4;
                        temp_t9_5 = *var_v1_7;
                        var_a0_4 += 0x700;
                        var_v0_8 += 8;
                        var_v1_7 += 1;
                        (*(s16 *)((u8 *)var_v0_8 + -6)) = 0x1000;
                        (*(s16 *)((u8 *)var_v0_8 + -2)) = 0x5A00;
                        (*(s16 *)((u8 *)var_v0_8 + -8)) = (s16) temp_t9_5;
                    } while (var_a0_4 < 0x6100);
                    var_a0_5 = &D_80044A1C;
                    var_v0_9 = temp_t7_2 + &D_801D73C8;
                    var_v1_8 = 0x3C00;
                    do {
                        (*(s16 *)((u8 *)var_v0_9 + 32)) = (s16) *var_a0_5;
                        if (D_8004A40C == 3) {

                        }
                        (*(s16 *)((u8 *)var_v0_9 + 34)) = (s16) ((s32) ((var_t0_4 * -0x1000) + 0x78000) / 160);
                        (*(s16 *)((u8 *)var_v0_9 + 36)) = var_v1_8;
                        var_v1_8 += 0x700;
                        var_v0_9 += 8;
                        var_a0_5 += 1;
                        (*(s16 *)((u8 *)var_v0_9 + 30)) = 0x7400;
                    } while (var_v1_8 < 0x4A00);
                    var_a1_3 = (s32) ((var_t0_4 << 0xC) + 0x3C000) / 160;
                    var_a0_6 = &D_80044A20;
                    var_v0_10 = temp_t7_2 + &D_801D73C8;
                    var_v1_9 = 0x5500;
                    do {
                        (*(s16 *)((u8 *)var_v0_10 + 48)) = (s16) *var_a0_6;
                        if (D_8004A40C == 4) {

                        }
                        (*(s16 *)((u8 *)var_v0_10 + 50)) = (s16) var_a1_3;
                        (*(s16 *)((u8 *)var_v0_10 + 52)) = var_v1_9;
                        var_v1_9 += 0x700;
                        var_v0_10 += 8;
                        var_a0_6 += 1;
                        (*(s16 *)((u8 *)var_v0_10 + 46)) = 0x7300;
                    } while (var_v1_9 != 0x6A00);
                    (*(s16 *)((u8 *)var_v0_10 + 48)) = 0;
                }
                temp_v0_24 = D_8004A420;
                D_8004A420 = temp_v0_24 + 8;
                temp_v0_24->value = 0;
                temp_v0_24->command = 0xE7000000;
                func_80026738(&D_8004A420, var_a1_3, var_a2_4, D_8004A40C);
                *(temp_t7_2 + &D_801D73C8) = 0;
            }
            temp_v0_25 = D_8004A420;
            D_8004A420 = temp_v0_25 + 8;
            temp_v0_25->value = 0;
            temp_v0_25->command = 0xE9000000;
            temp_v0_26 = D_8004A420;
            D_8004A420 = temp_v0_26 + 8;
            temp_v0_26->value = 0;
            temp_v0_26->command = 0xB8000000;
            D_8004A318 = (D_80044A24 * 0x60) + &D_8004A320;
            if ((D_8004A40C == 0) && (D_801D87FE == 0)) {
                func_8001AA90(D_800695DC);
            }
            D_8004AA30(D_8004A318, &D_8004A318->pad[4], D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC);
            osWritebackDCacheAll();
            D_8004A318->list = D_8004A418[D_80044A24];
            D_8004A318->listSize = (D_8004A420 - D_8004A418[D_80044A24]) * 8;
            temp_t8_4 = (D_8004A420 - D_8004A418[D_80044A24]);
            if ((temp_t8_4 < 0) || (var_a3_4 = D_8004A418, ((temp_t8_4 < 0xE75) == 0))) {
                var_a2_5 = D_8004A428;
                var_a3_4 = D_8004A418;
                do {
                    temp_t6_3 = *var_a3_4;
                    var_a2_5++;
                    var_a3_4++;
                    D_8004A420 = temp_t6_3;
                    D_8004A420 = temp_t6_3 + 8;
                    temp_t6_3->value = 0;
                    temp_t6_3->command = 0xBC000006;
                    temp_v0_27 = D_8004A420;
                    D_8004A420 = temp_v0_27 + 8;
                    temp_v0_27->value = (u32) sp74;
                    temp_v0_27->command = 0x06000000;
                    temp_v0_28 = D_8004A420;
                    D_8004A420 = temp_v0_28 + 8;
                    temp_v0_28->command = 0xFF10013F;
                    temp_v0_28->value = ((u32 *)var_a2_5)[-1] + 0x80000000;
                } while ((u8 *)var_a2_5 != &D_8004A430);
                temp_t6_4 = sp104[D_80044A24];
                D_8004A420 = temp_t6_4;
                D_8004A420 = temp_t6_4 + 8;
                temp_t6_4->value = 0;
                temp_t6_4->command = 0xE9000000;
                temp_v0_29 = D_8004A420;
                D_8004A420 = temp_v0_29 + 8;
                temp_v0_29->value = 0;
                temp_v0_29->command = 0xB8000000;
            }
            D_8004A318->type = 1;
            D_8004A318->taskFlags = 2;
            D_8004A318->boot = &D_80042710;
            D_8004A318->bootSize = sp58;
            D_8004A318->ucode = &D_800427E0;
            D_8004A318->ucodeData = &D_80049770;
            D_8004A318->ucodeDataSize = 0x800;
            D_8004A318->stack = &D_80068530;
            D_8004A318->stackSize = 0x400;
            D_8004A318->output = 0;
            D_8004A318->outputSize = 0;
            D_8004A318->yield = &D_8000C3C8;
            D_8004A318->yieldSize = 0x900;
            D_8004A318->flags = 0x63;
            D_8004A318->queue = D_8004A298;
            D_8004A318->message = (D_80044A24 << 5) + D_8004A2D8;
            D_8004A318->framebuffer = D_8004A428[D_80044A24];
            if (D_8004A401 != 0) {
                osSendMesg(&D_8000CF50, D_8004A318, 1);
                D_80044A24 ^= 1;
                D_8004A414 += 1;
            }
            if ((D_8004A40C == 0) && (D_801D87FE == 0)) {
                if (D_8004D272 < 0x167) {
                    D_8004D272 += 1;
                } else {
                    D_8004D272 = 0;
                }
            }
            goto loop_49;
        }
        if (D_8004A264 != 0) {
            func_8002F8F8(D_8004A264);
        }
    } while (temp_v0_4 != 0);
    func_8002B710();
}
