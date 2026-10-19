/* DRAFT. Remaining diff: 522 differing instruction words; emitted 2112 / original 2080 bytes (positional comparison). */
/* Recovered event/voice byte fields and contiguous event buffers.
 * Private saved-register inputs are explicit parameters; ABI remains unresolved. */
extern u8 *__lookupSoundQuick();
extern u8 *__lookupVoice();
extern u8 *__mapVoice();
extern void __seqpReleaseVoice();
extern void __setInstChanState();
extern s32 __vsPan();
extern s32 __vsVol();
extern f32 alCents2Ratio();
extern void alEvtqPostEvent();
extern void alSynAllocVoice();
extern void alSynSetFXMix();
extern void alSynSetPan();
extern void alSynSetPitch();
extern void alSynSetVol();
extern void alSynStartVoiceParams();

void func_8003D9BC(u8 *arg0, u8 *player) {
    u8 frame[0x100];
    u8 *spB8;
    u8 *sp34;
    f32 temp_f0;
    f32 temp_f20;
    s16 *temp_v0_12;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_a2_5;
    s32 (*temp_v0_4)(s32 *, f32 *, u8, u8, s32, s32);
    s32 (*temp_v0_6)(s32 *, f32 *, u8, u8, s32, s32);
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_fp;
    s32 temp_fp_2;
    s32 temp_s4_2;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 temp_a2;
    u8 temp_a2_2;
    u8 temp_s2_2;
    u8 temp_s3;
    u8 temp_s4;
    u8 temp_s6;
    u8 temp_t6;
    u8 temp_v0_11;
    u8 *temp_a1;
    u8 *temp_s2;
    u8 *temp_s5;
    u8 *temp_v0;
    u8 *temp_v0_10;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_8;
    u8 *temp_v0_9;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 *var_s0_3;
    u8 *var_s0_4;
    u8 *var_s0_5;
    u8 *var_s0_6;

    temp_s6 = (*(u8 *)((u8 *)(arg0) + 0x8));
    temp_s3 = (*(u8 *)((u8 *)(arg0) + 0x9));
    temp_s4 = (*(u8 *)((u8 *)(arg0) + 0xA));
    temp_v1 = temp_s6 & 0xF0;
    temp_t6 = temp_s6 & 0xF;
    switch (temp_v1) {                              /* switch 1 */
    case 0x90:                                      /* switch 1 */
        if (temp_s4 != 0) {
            if ((*(s32 *)((u8 *)(player) + 0x2C)) == 1) {
                temp_v0 = __lookupSoundQuick(player, temp_s3 & 0xFF, temp_s4 & 0xFF, temp_t6 & 0xFF);
                if (temp_v0 != 0) {
                    temp_fp = temp_t6 * 0x10;
                    (*(s16 *)(frame + 0x9E)) = 0;
                    (*(s8 *)(frame + 0xA0)) = 0;
                    (*(s16 *)(frame + 0x9C)) = (s16) (*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp)) + 0x8));
                    temp_v0_2 = __mapVoice(player, temp_s3 & 0xFF, temp_s4 & 0xFF, temp_t6 & 0xFF);
                    if (temp_v0_2 != 0) {
                        temp_a1 = temp_v0_2 + 4;
                        sp34 = temp_a1;
                        alSynAllocVoice((*(s32 *)((u8 *)(player) + 0x14)), temp_a1, &(*(s16 *)(frame + 0x9C)));
                        (*(s32 *)((u8 *)(temp_v0_2) + 0x20)) = temp_v0;
                        (*(u8 *)((u8 *)(temp_v0_2) + 0x34)) = 0;
                        if ((s32) (*(u8 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp)) + 0xB)) >= 0x40) {
                            (*(u8 *)((u8 *)(temp_v0_2) + 0x35)) = 2;
                        } else {
                            (*(u8 *)((u8 *)(temp_v0_2) + 0x35)) = 0;
                        }
                        temp_v0_3 = (*(u8 * *)((u8 *)(temp_v0) + 0x4));
                        (*(f32 *)((u8 *)(temp_v0_2) + 0x28)) = alCents2Ratio((s16) (((temp_s3 - (*(s32 *)((u8 *)(temp_v0_3) + 0x4))) * 0x64) + (*(u8 *)((u8 *)(temp_v0_3) + 0x5))));
                        (*(u8 *)((u8 *)(temp_v0_2) + 0x30)) = (u8) (*(s32 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0xC));
                        (*(u8 *)((u8 *)(temp_v0_2) + 0x37)) = 0U;
                        (*(s32 *)((u8 *)(temp_v0_2) + 0x24)) = (s32) ((*(s32 *)((u8 *)(player) + 0x1C)) + (*(s32 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0x0)));
                        temp_s2 = *((*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp);
                        (*(f32 *)(frame + 0x8C)) = 127.0f;
                        temp_a2 = (*(s32 *)((u8 *)(temp_s2) + 0x4));
                        if (temp_a2 != 0) {
                            temp_v0_4 = (*(s32 (**)())((u8 *)(player) + 0x70));
                            if (temp_v0_4 != 0) {
                                temp_v0_5 = temp_v0_4(&(*(s32 *)(frame + 0x84)), &(*(f32 *)(frame + 0x8C)), temp_a2, (*(u8 *)((u8 *)(temp_s2) + 0x5)), (s32) (*(s16 *)((u8 *)(temp_s2) + 0x6)), (s32) (*(u8 *)((u8 *)(temp_s2) + 0x7)));
                                if (temp_v0_5 != 0) {
                                    (*(s16 *)(frame + 0xB4)) = 0x16;
                                    spB8 = temp_v0_2;
                                    alEvtqPostEvent(player + 0x48, &(*(s16 *)(frame + 0xB4)), temp_v0_5);
                                    (*(u8 *)((u8 *)(temp_v0_2) + 0x37)) = (u8) ((*(u8 *)((u8 *)(temp_v0_2) + 0x37)) | 1);
                                }
                            }
                        }
                        (*(f32 *)(frame + 0x8C)) = 1.0f;
                        temp_a2_2 = (*(s32 *)((u8 *)(temp_s2) + 0x8));
                        temp_s5 = player + 0x48;
                        if (temp_a2_2 != 0) {
                            temp_v0_6 = (*(s32 (**)())((u8 *)(player) + 0x70));
                            if (temp_v0_6 != 0) {
                                temp_v0_7 = temp_v0_6(&(*(s32 *)(frame + 0x84)), &(*(f32 *)(frame + 0x8C)), temp_a2_2, (*(u8 *)((u8 *)(temp_s2) + 0x9)), (s32) (*(s16 *)((u8 *)(temp_s2) + 0xA)), (s32) (*(u8 *)((u8 *)(temp_s2) + 0xB)));
                                if (temp_v0_7 != 0) {
                                    (*(s16 *)(frame + 0xB4)) = 0x17;
                                    spB8 = temp_v0_2;
                                    (*(u8 *)(frame + 0xC0)) = temp_t6;
                                    alEvtqPostEvent(temp_s5, &(*(s16 *)(frame + 0xB4)), temp_v0_7);
                                    (*(u8 *)((u8 *)(temp_v0_2) + 0x37)) = (u8) ((*(u8 *)((u8 *)(temp_v0_2) + 0x37)) | 2);
                                }
                            }
                        }
                        temp_v0_8 = (*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp;
                        temp_s2_2 = (*(s16 *)((u8 *)(temp_v0_8) + 0xA));
                        temp_f20 = (*(s32 *)((u8 *)(temp_v0_8) + 0xC)) * (*(f32 *)((u8 *)(temp_v0_2) + 0x28)) * (*(f32 *)((u8 *)(temp_v0_2) + 0x2C));
                        temp_s4_2 = __vsPan(temp_v0_2, player) & 0xFF;
                        alSynStartVoiceParams((*(s32 *)((u8 *)(player) + 0x14)), sp34, (*(s32 *)((u8 *)(temp_v0) + 0x8)), temp_f20, __vsVol(temp_v0_2, player), temp_s4_2, (s32) temp_s2_2, (*(s32 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0x0)));
                        (*(s16 *)(frame + 0xB4)) = 6;
                        spB8 = sp34;
                        (*(u8 *)(frame + 0xC0)) = (*(u8 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0xD));
                        (*(s32 *)(frame + 0xBC)) = (*(s32 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0x4));
                        alEvtqPostEvent(temp_s5, &(*(s16 *)(frame + 0xB4)), (*(s32 *)((u8 *)((*(u8 * *)((u8 *)(temp_v0) + 0x0))) + 0x0)));
                        return;
                    }
                }
            }
        } else {
        case 0x80:                                  /* switch 1 */
            temp_v0_9 = __lookupVoice(player, temp_s3 & 0xFF, temp_t6 & 0xFF);
            if (temp_v0_9 != 0) {
                if ((*(u8 *)((u8 *)(temp_v0_9) + 0x35)) == 2) {
                    (*(u8 *)((u8 *)(temp_v0_9) + 0x35)) = 4U;
                    return;
                }
                (*(u8 *)((u8 *)(temp_v0_9) + 0x35)) = 3U;
                __seqpReleaseVoice(player, temp_v0_9 + 4, (*(s32 *)((u8 *)((*(*(u8 ***)((u8 *)(temp_v0_9) + 0x20)))) + 0x8)));
                return;
            }
        default:                                    /* switch 1 */
            return;
        }
        break;
    case 0xA0:                                      /* switch 1 */
        temp_v0_10 = __lookupVoice(player, temp_s3 & 0xFF, temp_t6 & 0xFF);
        if (temp_v0_10 != 0) {
            (*(u8 *)((u8 *)(temp_v0_10) + 0x33)) = temp_s4;
            temp_a0 = (*(s32 *)((u8 *)(temp_v0_10) + 0x24)) - (*(s32 *)((u8 *)(player) + 0x1C));
            temp_a2_3 = __vsVol(temp_v0_10, player);
            if (temp_a0 >= 0) {
                var_v0 = temp_a0;
            } else {
                var_v0 = 0x3E8;
            }
            alSynSetVol((*(s32 *)((u8 *)(player) + 0x14)), temp_v0_10 + 4, temp_a2_3, var_v0);
            return;
        }
        break;
    case 0xD0:                                      /* switch 1 */
        var_s0 = (*(u8 * *)((u8 *)(player) + 0x64));
        if (var_s0 != 0) {
            do {
                if (temp_t6 == (*(u8 *)((u8 *)(var_s0) + 0x31))) {
                    (*(u8 *)((u8 *)(var_s0) + 0x33)) = temp_s3;
                    temp_a0_2 = (*(s32 *)((u8 *)(var_s0) + 0x24)) - (*(s32 *)((u8 *)(player) + 0x1C));
                    temp_a2_4 = __vsVol(var_s0, player);
                    if (temp_a0_2 >= 0) {
                        var_v0_2 = temp_a0_2;
                    } else {
                        var_v0_2 = 0x3E8;
                    }
                    alSynSetVol((*(s32 *)((u8 *)(player) + 0x14)), var_s0 + 4, temp_a2_4, var_v0_2);
                }
                var_s0 = (*(u8 * *)((u8 *)(var_s0) + 0x0));
            } while (var_s0 != 0);
            return;
        }
        break;
    case 0xB0:                                      /* switch 1 */
        switch ((s32) temp_s3) {                    /* switch 2; irregular */
        case 0xA:                                   /* switch 2 */
            (*(u8 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + (temp_t6 * 0x10))) + 0x7)) = temp_s4;
            var_s0_2 = (*(u8 * *)((u8 *)(player) + 0x64));
            if (var_s0_2 != 0) {
                do {
                    if (temp_t6 == (*(u8 *)((u8 *)(var_s0_2) + 0x31))) {
                        alSynSetPan((*(s32 *)((u8 *)(player) + 0x14)), var_s0_2 + 4, __vsPan(var_s0_2, player) & 0xFF);
                    }
                    var_s0_2 = (*(u8 * *)((u8 *)(var_s0_2) + 0x0));
                } while (var_s0_2 != 0);
                return;
            }
            break;
        case 0x7:                                   /* switch 2 */
            (*(u8 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + (temp_t6 * 0x10))) + 0x9)) = temp_s4;
            var_s0_3 = (*(u8 * *)((u8 *)(player) + 0x64));
            if (var_s0_3 != 0) {
                do {
                    if ((temp_t6 == (*(u8 *)((u8 *)(var_s0_3) + 0x31))) && ((*(u8 *)((u8 *)(var_s0_3) + 0x34)) != 3)) {
                        temp_a0_3 = (*(s32 *)((u8 *)(var_s0_3) + 0x24)) - (*(s32 *)((u8 *)(player) + 0x1C));
                        temp_a2_5 = __vsVol(var_s0_3, player);
                        if (temp_a0_3 >= 0) {
                            var_v0_3 = temp_a0_3;
                        } else {
                            var_v0_3 = 0x3E8;
                        }
                        alSynSetVol((*(s32 *)((u8 *)(player) + 0x14)), var_s0_3 + 4, temp_a2_5, var_v0_3);
                    }
                    var_s0_3 = (*(u8 * *)((u8 *)(var_s0_3) + 0x0));
                } while (var_s0_3 != 0);
                return;
            }
            break;
        case 0x10:                                  /* switch 2 */
            (*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + (temp_t6 * 0x10))) + 0x8)) = temp_s4;
            return;
        case 0x40:                                  /* switch 2 */
            (*(u8 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + (temp_t6 * 0x10))) + 0xB)) = temp_s4;
            var_s0_4 = (*(u8 * *)((u8 *)(player) + 0x64));
            if (var_s0_4 != 0) {
                do {
                    if (temp_t6 == (*(u8 *)((u8 *)(var_s0_4) + 0x31))) {
                        temp_v0_11 = (*(u8 *)((u8 *)(var_s0_4) + 0x35));
                        if (temp_v0_11 != 3) {
                            if ((s32) temp_s4 >= 0x40) {
                                if (temp_v0_11 == 0) {
                                    (*(u8 *)((u8 *)(var_s0_4) + 0x35)) = 2U;
                                }
                            } else if (temp_v0_11 == 2) {
                                (*(u8 *)((u8 *)(var_s0_4) + 0x35)) = 0U;
                            } else if (temp_v0_11 == 4) {
                                (*(u8 *)((u8 *)(var_s0_4) + 0x35)) = 3U;
                                __seqpReleaseVoice(player, var_s0_4 + 4, (*(s32 *)((u8 *)((*(*(u8 ***)((u8 *)(var_s0_4) + 0x20)))) + 0x8)));
                            }
                        }
                    }
                    var_s0_4 = (*(u8 * *)((u8 *)(var_s0_4) + 0x0));
                } while (var_s0_4 != 0);
                return;
            }
            break;
        case 0x5B:                                  /* switch 2 */
            (*(s16 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + (temp_t6 * 0x10))) + 0xA)) = temp_s4;
            var_s0_5 = (*(u8 * *)((u8 *)(player) + 0x64));
            if (var_s0_5 != 0) {
                do {
                    if (temp_t6 == (*(u8 *)((u8 *)(var_s0_5) + 0x31))) {
                        alSynSetFXMix((*(s32 *)((u8 *)(player) + 0x14)), var_s0_5 + 4, temp_s4 & 0xFF);
                    }
                    var_s0_5 = (*(u8 * *)((u8 *)(var_s0_5) + 0x0));
                } while (var_s0_5 != 0);
                return;
            }
            break;
        }
        break;
    case 0xC0:                                      /* switch 1 */
        temp_v0_12 = (*(u8 * *)((u8 *)(player) + 0x20));
        if ((s32) temp_s3 < *temp_v0_12) {
            __setInstChanState(player, (*(s32 *)((u8 *)((temp_v0_12 + (temp_s3 * 4))) + 0xC)), temp_t6);
            return;
        }
        break;
    case 0xE0:                                      /* switch 1 */
        temp_fp_2 = temp_t6 * 0x10;
        temp_f0 = alCents2Ratio((s16) ((s32) ((*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp_2)) + 0x4)) * (((temp_s4 << 7) + temp_s3) - 0x2000)) / 8192));
        (*(s32 *)((u8 *)(((*(u8 * *)((u8 *)(player) + 0x60)) + temp_fp_2)) + 0xC)) = temp_f0;
        var_s0_6 = (*(u8 * *)((u8 *)(player) + 0x64));
        if (var_s0_6 != 0) {
            do {
                if (temp_t6 == (*(u8 *)((u8 *)(var_s0_6) + 0x31))) {
                    alSynSetPitch((*(s32 *)((u8 *)(player) + 0x14)), var_s0_6 + 4, (*(f32 *)((u8 *)(var_s0_6) + 0x28)) * temp_f0 * (*(f32 *)((u8 *)(var_s0_6) + 0x2C)));
                }
                var_s0_6 = (*(u8 * *)((u8 *)(var_s0_6) + 0x0));
            } while (var_s0_6 != 0);
        }
        break;
    }
}
