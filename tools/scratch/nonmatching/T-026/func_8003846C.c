/* DRAFT. Remaining diff: 387 differing instruction words; emitted 1300 / original 1556 bytes (positional comparison). */
/* Recovered event/voice byte fields and contiguous event buffers.
 * Private saved-register inputs are explicit parameters; ABI remains unresolved. */
extern void __CSPPostNextSeqEvent();
extern void __initFromBank();
extern void __seqpReleaseVoice();
extern void __seqpStopOsc();
extern void __unmapVoice();
extern s32 __voiceNeedsNoteKill();
extern s32 __vsDelta();
extern s16 __vsVol();
extern void alCSeqNextEvent();
extern void alEvtqFlushType();
extern s32 alEvtqNextEvent();
extern void alEvtqPostEvent();
extern void alSynFreeVoice();
extern void alSynSetPitch();
extern void alSynSetVol();
extern void alSynStopVoice();
extern void func_80037A30();
extern void func_80037A6C();
extern void func_80037C3C();
extern f32 D_80049324;

void func_8003846C(u8 *arg0) {
    u8 frame[0x100];
    u8 *sp90;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s1;
    u8 *temp_s1_2;
    u8 *temp_s1_3;
    u8 *temp_s1_4;
    u8 *var_s1;
    u8 *var_s1_2;
    s16 temp_s0_3;
    s16 temp_s0_5;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s5;
    u16 temp_t7;
    u8 temp_s0_4;

    (*(s32 *)(frame + 0x50)) = arg0 + 0x38;
    var_s5 = arg0 + 0x48;
    do {
        temp_t7 = (*(u16 *)((u8 *)(arg0) + 0x38));
        switch (temp_t7) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            temp_a0 = (*(u8 * *)((u8 *)(arg0) + 0x18));
            if (temp_a0 != 0) {
                alCSeqNextEvent(temp_a0, &(*(s16 *)(frame + 0x58)));
                switch ((*(s16 *)(frame + 0x58))) {                     /* switch 2 */
                case 1:                             /* switch 2 */
                    (*(s32 *)(frame + 0x4C)) = var_s5;
                    func_80037C3C();
                    __CSPPostNextSeqEvent(arg0);
                    break;
                case 3:                             /* switch 2 */
                    (*(s32 *)(frame + 0x4C)) = var_s5;
                    func_80037A6C();
                    __CSPPostNextSeqEvent(arg0);
                    break;
                case 4:                             /* switch 2 */
                    (*(s32 *)((u8 *)(arg0) + 0x2C)) = 2;
                    (*(s16 *)(frame + 0x58)) = 0x10;
                    alEvtqPostEvent(var_s5, &(*(s16 *)(frame + 0x58)), 0x7FFFFFFF);
                    break;
                case 18:                            /* switch 2 */
                case 19:                            /* switch 2 */
                case 20:                            /* switch 2 */
                    __CSPPostNextSeqEvent(arg0);
                    break;
                }
            }
            break;
        case 9:                                     /* switch 1 */
            (*(s16 *)(frame + 0x8C)) = 9;
            alEvtqPostEvent(var_s5, &(*(s16 *)(frame + 0x8C)), (*(s32 *)((u8 *)(arg0) + 0x5C)));
            break;
        case 5:                                     /* switch 1 */
            temp_s0 = (*(u8 * *)((u8 *)(arg0) + 0x3C));
            alSynStopVoice((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s0);
            alSynFreeVoice((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s0);
            temp_s1 = (*(u8 * *)((u8 *)(temp_s0) + 0x10));
            if ((*(u8 *)((u8 *)(temp_s1) + 0x37)) != 0) {
                __seqpStopOsc(arg0, temp_s1);
            }
            __unmapVoice(arg0, temp_s0);
            break;
        case 6:                                     /* switch 1 */
            temp_s0_2 = (*(u8 * *)((u8 *)(arg0) + 0x3C));
            temp_s1_2 = (*(u8 * *)((u8 *)(temp_s0_2) + 0x10));
            if ((*(u8 *)((u8 *)(temp_s1_2) + 0x34)) == 0) {
                (*(u8 *)((u8 *)(temp_s1_2) + 0x34)) = 1U;
            }
            temp_s3 = (*(s32 *)((u8 *)(arg0) + 0x40));
            (*(s32 *)((u8 *)(temp_s1_2) + 0x24)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x1C)) + temp_s3);
            (*(u8 *)((u8 *)(temp_s1_2) + 0x30)) = (u8) (*(s32 *)((u8 *)(arg0) + 0x44));
            alSynSetVol((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s0_2, __vsVol(temp_s1_2, arg0), temp_s3);
            break;
        case 22:                                    /* switch 1 */
            temp_s4 = (*(s32 *)((u8 *)(arg0) + 0x40));
            temp_s1_3 = (*(u8 * *)((u8 *)(arg0) + 0x3C));
            temp_s3_2 = (*(s32 (**)())((u8 *)(arg0) + 0x74))(temp_s4, &(*(f32 *)(frame + 0x78)));
            temp_s0_3 = __vsVol(temp_s1_3, arg0);
            alSynSetVol((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s1_3 + 4, temp_s0_3, __vsDelta(temp_s1_3, (*(s32 *)((u8 *)(arg0) + 0x1C))));
            (*(s16 *)(frame + 0x8C)) = 0x16;
            sp90 = temp_s1_3;
            (*(s32 *)(frame + 0x94)) = temp_s4;
            alEvtqPostEvent(var_s5, &(*(s16 *)(frame + 0x8C)), temp_s3_2);
            break;
        case 23:                                    /* switch 1 */
            temp_s4_2 = (*(s32 *)((u8 *)(arg0) + 0x40));
            temp_s1_4 = (*(u8 * *)((u8 *)(arg0) + 0x3C));
            temp_s0_4 = (*(s32 *)((u8 *)(arg0) + 0x44));
            temp_v0_2 = (*(s32 (**)())((u8 *)(arg0) + 0x74))(temp_s4_2, &(*(f32 *)(frame + 0x78)));
            alSynSetPitch((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s1_4 + 4, (*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(arg0) + 0x60)) + (temp_s0_4 * 0x10))) + 0xC)) * ((*(s32 *)((u8 *)(temp_s1_4) + 0x28)) * (*(s32 *)((u8 *)(temp_s1_4) + 0x2C))));
            (*(s16 *)(frame + 0x8C)) = 0x17;
            sp90 = temp_s1_4;
            (*(s32 *)(frame + 0x94)) = temp_s4_2;
            (*(u8 *)(frame + 0x98)) = temp_s0_4;
            alEvtqPostEvent(var_s5, &(*(s16 *)(frame + 0x8C)), temp_v0_2);
            break;
        case 2:                                     /* switch 1 */
        case 21:                                    /* switch 1 */
            (*(s32 *)(frame + 0x4C)) = var_s5;
            func_80037C3C();
            break;
        case 7:                                     /* switch 1 */
            (*(s32 *)(frame + 0x4C)) = var_s5;
            func_80037A6C();
            break;
        case 10:                                    /* switch 1 */
            var_s1 = (*(u8 * *)((u8 *)(arg0) + 0x64));
            (*(s32 *)((u8 *)(arg0) + 0x32)) = (s16) (*(u8 * *)((u8 *)(arg0) + 0x3C));
            if (var_s1 != 0) {
                do {
                    temp_s0_5 = __vsVol(var_s1, arg0);
                    alSynSetVol((*(s32 *)((u8 *)(arg0) + 0x14)), var_s1 + 4, temp_s0_5, __vsDelta(var_s1, (*(s32 *)((u8 *)(arg0) + 0x1C))));
                    var_s1 = *var_s1;
                } while (var_s1 != 0);
            }
            break;
        case 15:                                    /* switch 1 */
            if ((*(s32 *)((u8 *)(arg0) + 0x2C)) != 1) {
                (*(s32 *)((u8 *)(arg0) + 0x2C)) = 1;
                __CSPPostNextSeqEvent(arg0);
            }
            break;
        case 16:                                    /* switch 1 */
            if ((*(s32 *)((u8 *)(arg0) + 0x2C)) == 2) {
                if ((*(u8 * *)((u8 *)(arg0) + 0x64)) != 0) {
                    do {
                        temp_s0_6 = (*(u8 * *)((u8 *)(arg0) + 0x64)) + 4;
                        alSynStopVoice((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s0_6);
                        alSynFreeVoice((*(s32 *)((u8 *)(arg0) + 0x14)), temp_s0_6);
                        if ((*(u8 *)((u8 *)((*(u8 * *)((u8 *)(arg0) + 0x64))) + 0x37)) != 0) {
                            __seqpStopOsc(arg0, (*(u8 * *)((u8 *)(arg0) + 0x64)));
                        }
                        __unmapVoice(arg0, temp_s0_6);
                    } while ((*(u8 * *)((u8 *)(arg0) + 0x64)) != 0);
                }
                (*(s32 *)((u8 *)(arg0) + 0x2C)) = 0;
            }
            break;
        case 17:                                    /* switch 1 */
            if ((*(s32 *)((u8 *)(arg0) + 0x2C)) == 1) {
                alEvtqFlushType(var_s5, 0);
                alEvtqFlushType(var_s5, 0x15);
                alEvtqFlushType(var_s5, 2);
                var_s1_2 = (*(u8 * *)((u8 *)(arg0) + 0x64));
                if (var_s1_2 != 0) {
                    do {
                        temp_s0_7 = var_s1_2 + 4;
                        if (__voiceNeedsNoteKill(arg0, temp_s0_7, 0xC350) != 0) {
                            __seqpReleaseVoice(arg0, temp_s0_7, 0xC350);
                        }
                        var_s1_2 = *var_s1_2;
                    } while (var_s1_2 != 0);
                }
                (*(s32 *)((u8 *)(arg0) + 0x2C)) = 2;
                (*(s16 *)(frame + 0x8C)) = 0x10;
                alEvtqPostEvent(var_s5, &(*(s16 *)(frame + 0x8C)), 0x7FFFFFFF);
            }
            break;
        case 12:                                    /* switch 1 */
            (*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(arg0) + 0x60)) + ((u8) (*(u8 * *)((u8 *)(arg0) + 0x3C)) * 0x10))) + 0x8)) = (u8) (*(s32 *)((u8 *)(arg0) + 0x3D));
            break;
        case 13:                                    /* switch 1 */
            (*(u8 * *)((u8 *)(arg0) + 0x18)) = (u8 *) (*(u8 * *)((u8 *)(arg0) + 0x3C));
            func_80037A30(D_80049324, arg0);
            temp_a1 = (*(u8 * *)((u8 *)(arg0) + 0x20));
            if (temp_a1 != 0) {
                __initFromBank(arg0, temp_a1);
            }
            break;
        case 14:                                    /* switch 1 */
            temp_a1_2 = (*(u8 * *)((u8 *)(arg0) + 0x3C));
            (*(u8 * *)((u8 *)(arg0) + 0x20)) = temp_a1_2;
            __initFromBank(arg0, temp_a1_2);
            break;
        }
        temp_v0 = alEvtqNextEvent(var_s5, (*(s32 *)(frame + 0x50)));
        (*(s32 *)((u8 *)(arg0) + 0x28)) = temp_v0;
    } while (temp_v0 == 0);
    (*(s32 *)((u8 *)(arg0) + 0x1C)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x1C)) + temp_v0);
}
