/* T-085 DRAFT: 1183 -> 1182 differing words in owning TU; 4792/4708 bytes. */ typedef struct { u32
w0,w1; }
T032Gfx26B; typedef struct { u16 *pixels; u8 *alpha; s16
halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite26B; typedef
struct { u8 kind,param; u8
pad[2];
s32 x,y,z; u8
tail[8]; s32 unused18; } T032Effect26B; extern T032Sprite26B D_8004CED0[]; extern T032Effect26B D_801D5D58[],D_801D7338[]; extern u8 D_80047E50[],D_8004EA9C[],D_8004AC88,D_8004F394,D_801D87E0,D_801D87E1; extern s8 D_8004EA9A;
extern
u32 D_801D34A0; extern s32 D_8004EA78; extern u16 D_801D87E8; extern void func_8001D7E4(s32,s32,s32,s32,s32),func_8002BB74(s32,s32,s32,f32 *,f32 *,s32 *),func_8002DCC8(f32,f32,s32,u32 *),func_8002DDD4(f32,f32,s32,s32,s32 *,s32 *); extern u32 osVirtualToPhysical(void *); void
func_80026B38(T032Gfx26B **arg0, u8 arg1) { s32 sp1DC; f32 sp1D4; f32 sp1D0; s32 sp1CC;
s32
sp1C8; s32 sp1C4; s32
sp1BC;
s32 sp1B8; s32 sp1AC; s32 sp1A8; s32
sp1A0; s32 sp19C; s32 sp194;
s32 sp190; s32 sp188; s32 sp184; u32 sp180; s32 sp178; s32 sp174; s32 sp50; T032Effect26B *var_s1; s16 temp_a0_2;
s16 temp_a0_4; s16 temp_a0_6; s16 temp_s5; s16 temp_t1; s16 temp_t1_2; s16 temp_t1_3; s16 temp_t1_4; s32 temp_a2; s32 temp_a2_2;
s32 temp_a2_3;
s32 temp_a2_4; s32 temp_t6; s32 temp_t7; s32 temp_t7_2;
s32 temp_t7_3; s32 temp_t8; s32 temp_t9; s32 temp_t9_2; s32 temp_t9_3; s32 temp_v0_5; s32 temp_v0_6; s32 temp_v0_7; s32 temp_v0_8; s32 temp_v1_58; s32 var_a1; s32 var_a1_2; s32 var_a1_3;
s32 var_a1_4;
s32 var_a1_7; s32
var_a2_2; s32
var_s3; s32 var_t1; s32 var_t2; s32 var_t3; s32 var_t4; s32 var_t6; s32
var_v0; s32 var_v0_2; u32 temp_lo; u32 temp_t6_2; u32 temp_t6_3; u32 var_a1_6; u32
var_a2; u8 temp_a2_5; u8 temp_v0_9; u8 temp_v1_6; u8
var_a1_5; T032Gfx26B *temp_a0; T032Gfx26B *temp_a0_3; T032Gfx26B *temp_a0_5; T032Gfx26B *temp_a0_7; T032Gfx26B *temp_s2;
T032Gfx26B *temp_s2_2; T032Gfx26B *temp_s2_3; T032Gfx26B *temp_s2_4; T032Gfx26B *temp_t0; T032Sprite26B *temp_v0; T032Sprite26B *temp_v0_10;
T032Sprite26B *temp_v0_2; T032Sprite26B *temp_v0_3; T032Sprite26B *temp_v0_4; T032Gfx26B *temp_v1; T032Gfx26B *temp_v1_10;
T032Gfx26B *temp_v1_11; T032Gfx26B *temp_v1_12; T032Gfx26B *temp_v1_13; T032Gfx26B *temp_v1_14; T032Gfx26B *temp_v1_15; T032Gfx26B *temp_v1_16;
T032Gfx26B *temp_v1_17; T032Gfx26B *temp_v1_18; T032Gfx26B *temp_v1_19; T032Gfx26B *temp_v1_20; T032Gfx26B *temp_v1_21; T032Gfx26B *temp_v1_22; T032Gfx26B *temp_v1_23;
T032Gfx26B *temp_v1_24; T032Gfx26B *temp_v1_25; T032Gfx26B *temp_v1_26; T032Gfx26B *temp_v1_27; T032Gfx26B *temp_v1_28; T032Gfx26B *temp_v1_29; T032Gfx26B *temp_v1_2; T032Gfx26B *temp_v1_30; T032Gfx26B *temp_v1_31; T032Gfx26B *temp_v1_32; T032Gfx26B *temp_v1_33; T032Gfx26B *temp_v1_34; T032Gfx26B *temp_v1_35; T032Gfx26B *temp_v1_36; T032Gfx26B *temp_v1_37; T032Gfx26B *temp_v1_38; T032Gfx26B *temp_v1_39; T032Gfx26B *temp_v1_3; T032Gfx26B *temp_v1_40; T032Gfx26B *temp_v1_41; T032Gfx26B *temp_v1_42; T032Gfx26B *temp_v1_43; T032Gfx26B *temp_v1_44; T032Gfx26B *temp_v1_45; T032Gfx26B *temp_v1_46; T032Gfx26B *temp_v1_47; T032Gfx26B *temp_v1_48; T032Gfx26B *temp_v1_49; T032Gfx26B *temp_v1_4;
T032Gfx26B *temp_v1_50;
T032Gfx26B *temp_v1_51; T032Gfx26B *temp_v1_52; T032Gfx26B *temp_v1_53; T032Gfx26B *temp_v1_54; T032Gfx26B *temp_v1_55; T032Gfx26B *temp_v1_56; T032Gfx26B *temp_v1_57; T032Gfx26B *temp_v1_59; T032Gfx26B *temp_v1_5; T032Gfx26B *temp_v1_60; T032Gfx26B *temp_v1_61;
T032Gfx26B *temp_v1_62; T032Gfx26B *temp_v1_7; T032Gfx26B *temp_v1_8; T032Gfx26B *temp_v1_9; D_8004EA78 = 0xA; temp_v1 = *arg0;
*arg0 = temp_v1 + 1; temp_v1->w0 = 0x06000000; temp_v1->w1 = (u32)D_80047E50;
var_s3 = 0; temp_v0 = &D_8004CED0[D_8004EA78]; temp_t1 = temp_v0->w2; temp_s5 = temp_v0->h; sp1AC = temp_v0->w - 2; temp_v1_2 = *arg0; *arg0 = temp_v1_2 + 1; temp_v1_2->w0 = 0xF5700000; temp_v1_2->w1 = (u32)0x80200; temp_v1_3 = *arg0; *arg0 = temp_v1_3 + 1; temp_v1_3->w0 = (s32) (((((s32) (temp_t1 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000); temp_v1_3->w1 = (u32)0x01080200; temp_v1_4 = *arg0; temp_t9 = (temp_t1 + 7) & 0xFFF8; *arg0 = temp_v1_4 + 1; temp_v1_4->w1 = (u32) (((((temp_t9 - 1) * 4) & 0xFFF) << 0xC) | 0x01000000 | (((temp_s5 - 1) * 4) & 0xFFF)); temp_v1_4->w0 = 0xF2000000; temp_v1_5 = *arg0;
*arg0 = temp_v1_5 + 1; temp_v1_5->w1 = 0; temp_v1_5->w0 = 0xE6000000; temp_s2 = *arg0; *arg0 = temp_s2 + 1;
temp_s2->w0 = 0xFD900000; temp_s2->w1 = osVirtualToPhysical((&D_8004CED0[D_8004EA78])->alpha); temp_a0 = *arg0;
*arg0 = temp_a0 + 1; var_a1 = 0x7FF; temp_a0->w0 = 0xF3000000; temp_a2 = ((s32) ((temp_t9 * temp_s5) + 1) >> 1) - 1; if (temp_a2 < 0x7FF) { var_a1 = temp_a2;
} sp1A8 = (s32) temp_s5; temp_a0->w1 = (s32) ((var_a1 & 0xFFF) << 0xC); temp_v1_6 = D_8004EA9C[0]; if (temp_v1_6 == 2) { var_v0 = 0; } else { var_v0 = 2; if (D_8004EA9C[1] == 2) { var_v0 = 1; }
}
if ((var_v0 != 2) && (D_8004F394 == 0)) { D_8004EA9A = 0xB; func_8001D7E4(0x1C, 0x96, D_800614C0,
var_v0 & 0xFF, 0); temp_v0_2 = &D_8004CED0[D_8004EA78]; temp_t1_2 = temp_v0_2->h;
temp_a0_2 = temp_v0_2->w2; sp1A0 = temp_v0_2->w - 2; temp_v1_7 = *arg0;
*arg0 = temp_v1_7 + 1; temp_v1_7->w1 = 0x02080200; temp_v1_7->w0 = 0xF5100018; temp_v1_8 = *arg0; *arg0 = temp_v1_8 + 1; temp_v1_8->w0 = (s32) (((((s32) ((temp_a0_2 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000 | 0x18);
temp_v1_8->w1 = 0x03080200; temp_v1_9 = *arg0; temp_t6 = (temp_a0_2 + 7) & 0xFFF8;
*arg0 = temp_v1_9 + 1;
temp_v1_9->w1 = (s32) (((((temp_t6 - 1) * 4) & 0xFFF) << 0xC) | 0x03000000 | (((temp_t1_2 - 1) * 4) & 0xFFF));
temp_v1_9->w0 = 0xF2000000; temp_v1_10 = *arg0;
*arg0 = temp_v1_10 + 1; sp19C = (s32) temp_t1_2; temp_v1_10->w1 = 0;
temp_v1_10->w0 = 0xE6000000; temp_v1_11 = *arg0;
*arg0 = temp_v1_11 + 1; temp_v1_11->w1 = 0; temp_v1_11->w0 = 0xE7000000; temp_s2_2 = *arg0; *arg0 = temp_s2_2 + 1;
temp_s2_2->w0 = 0xFD100000; temp_s2_2->w1 = osVirtualToPhysical(D_8004CED0[D_8004EA78].pixels); temp_a0_3 = *arg0; var_a1_2 = 0x7FF;
*arg0 = temp_a0_3 + 1; temp_a0_3->w0 = 0xF3000000; temp_a2_2 = (temp_t6 * sp19C) - 1; if (temp_a2_2 < 0x7FF) { var_a1_2 = temp_a2_2;
} temp_a0_3->w1 = (s32) (((var_a1_2 & 0xFFF) << 0xC) | 0x02000000);
} if (temp_v1_6 == 7) { var_v0_2 = 0; } else { var_v0_2 = 2; if (D_8004EA9C[1] == 7) { var_v0_2 = 1;
}
} if ((var_v0_2 != 2) && (D_8004F394 == 0)) { D_8004EA9A = 6;
func_8001D7E4(var_v0_2 + 0x16, 0xA6, (s32) D_800614C0 % 9, var_v0_2 & 0xFF, 0);
temp_v0_3 = &D_8004CED0[D_8004EA78]; temp_t1_3 = temp_v0_3->h; temp_a0_4 = temp_v0_3->w2; sp194 = temp_v0_3->w - 2; temp_v1_12 = *arg0;
*arg0 = temp_v1_12 + 1; temp_v1_12->w1 = 0x04080200; temp_v1_12->w0 = 0xF5900054; temp_v1_13 = *arg0;
*arg0 = temp_v1_13 + 1; temp_v1_13->w0 = (s32) (((((s32) (temp_a0_4 + 7) >> 3) & 0x1FF) << 9) | 0xF5880000 | 0x54); temp_v1_13->w1 = 0x05080200; temp_v1_14 = *arg0; temp_t9_2 = (temp_a0_4 + 7) & 0xFFF8; *arg0 =
temp_v1_14 + 1; temp_v1_14->w1 = (s32) (((((temp_t9_2 - 1) * 4) & 0xFFF) << 0xC) | 0x05000000 | (((temp_t1_3 - 1) * 4) & 0xFFF)); temp_v1_14->w0 = 0xF2000000; temp_v1_15 = *arg0;
*arg0 = temp_v1_15 + 1; sp190 = (s32) temp_t1_3; temp_v1_15->w1 = 0; temp_v1_15->w0 = 0xE6000000; temp_v1_16 = *arg0;
*arg0 = temp_v1_16 + 1;
temp_v1_16->w1 = 0; temp_v1_16->w0 = 0xE7000000; temp_s2_3 = *arg0;
*arg0 = temp_s2_3 + 1; temp_s2_3->w0 = 0xFD900000; temp_s2_3->w1 = osVirtualToPhysical(D_8004CED0[D_8004EA78].alpha); temp_a0_5 = *arg0; var_a1_3 = 0x7FF;
*arg0 = temp_a0_5 + 1; temp_a0_5->w0 = 0xF3000000; temp_a2_3 = ((s32) ((temp_t9_2 *
sp190) + 1) >> 1) - 1; if (temp_a2_3 < 0x7FF) { var_a1_3 = temp_a2_3;
} temp_a0_5->w1 = (s32) (((var_a1_3 & 0xFFF) << 0xC) | 0x04000000);
} if (D_8004AC88 == 7) { D_8004EA9A = 0; func_8001D7E4(0x20, 0xC8, (s32) D_800614C8, 2, 0); temp_v0_4 = &D_8004CED0[D_8004EA78];
temp_t1_4 =
temp_v0_4->h;
temp_a0_6 = temp_v0_4->w2; sp188 = temp_v0_4->w - 2;
temp_v1_17 = *arg0;
*arg0 =
temp_v1_17 + 1; temp_v1_17->w1 = 0x06080200; temp_v1_17->w0 = 0xF59000EA; temp_v1_18 = *arg0;
*arg0 = temp_v1_18 + 1; temp_v1_18->w0 = (s32) (((((s32) (temp_a0_6 + 7) >> 3) & 0x1FF) << 9) | 0xF5880000 | 0xEA); temp_v1_18->w1 = 0x07080200; temp_v1_19 = *arg0; temp_t7 = (temp_a0_6 + 7) & 0xFFF8;
*arg0 = temp_v1_19 + 1;
temp_v1_19->w1 = (s32) (((((temp_t7 - 1) * 4) & 0xFFF) << 0xC) | 0x07000000 | (((temp_t1_4 - 1) * 4) & 0xFFF)); temp_v1_19->w0 = 0xF2000000; temp_v1_20 = *arg0;
*arg0 = temp_v1_20 + 1; sp184 = (s32) temp_t1_4; temp_v1_20->w1 = 0; temp_v1_20->w0 = 0xE6000000; temp_v1_21 = *arg0;
*arg0 = temp_v1_21 + 1; temp_v1_21->w1 = 0; temp_v1_21->w0 = 0xE7000000;
temp_s2_4 = *arg0;
*arg0 = temp_s2_4 + 1; temp_s2_4->w0 = 0xFD900000; temp_s2_4->w1 = osVirtualToPhysical(D_8004CED0[D_8004EA78].alpha); temp_a0_7 = *arg0; var_a1_4 = 0x7FF;
*arg0 = temp_a0_7 + 1; temp_a0_7->w0 = 0xF3000000; temp_a2_4 = ((s32) ((temp_t7 * sp184) + 1) >> 1) - 1; if (temp_a2_4 < 0x7FF) { var_a1_4 =
temp_a2_4; } temp_a0_7->w1 = (s32) (((var_a1_4 & 0xFFF) << 0xC) | 0x06000000);
}
var_t3 = -1; var_s1 = D_801D5D58; do { sp174 = 0; if ((var_s1->kind != 0) && (((sp178 = var_t3, sp50 = (s32) arg1, func_8002BB74(var_s1->x, var_s1->y, var_s1->z, &sp1D4, &sp1D0, &sp1CC), func_8002DCC8(sp1D4, sp1D0, sp1CC, &sp180),
var_t3 = sp178, (sp50 == 0)) && (sp180 >= (u32) D_801D34A0)) || ((sp50 == 1) && (sp180 < (u32)
D_801D34A0)))) { temp_a2_5 = var_s1->kind; var_a1_5 = temp_a2_5;
switch (temp_a2_5) {
/* switch 1; irregular */ case 3:                                 /*
switch 1 */ var_t3 = -1; break; case 7:                                 /* switch 1 */ var_t3 = -1; break; case 8:                                 /* switch 1 */ if (var_t3 != 3) { temp_v1_22 = *arg0; var_t3 = 3; *arg0 = temp_v1_22 + 1; temp_v1_22->w1 = 0;
temp_v1_22->w0 = 0xE7000000; temp_v1_23 = *arg0;
*arg0 = temp_v1_23 + 1; temp_v1_23->w1 = -0x3F01; temp_v1_23->w0 = 0xFA000100; temp_v1_24 = *arg0;
*arg0 = temp_v1_24 + 1; temp_v1_24->w1 = 0xFFFF00FF; temp_v1_24->w0 = 0xFB000000; } break; case 16:                                /*
switch 1 */ var_t3 = -1; break;
default:                                /*
switch 1 */ var_a1_5 = (u8) ((s32) var_s1->unused18 / 10); if (var_t3 !=
var_a1_5) { temp_v1_25 = *arg0;
*arg0 = temp_v1_25 + 1; temp_v1_25->w1 = 0; temp_v1_25->w0 = 0xE7000000; temp_lo = (u8) var_s1->unused18 / 10U; switch (temp_lo) { /*
switch 2 */ case 0:                         /* switch 2 */ temp_v1_26 = *arg0;
*arg0 = temp_v1_26 + 1; temp_v1_26->w1 = 0xC0FFC0FF; temp_v1_26->w0 = 0xFA000100; temp_v1_27 = *arg0;
*arg0 = temp_v1_27 + 1; temp_v1_27->w1 = 0xFF00FF; temp_v1_27->w0 = 0xFB000000; var_a1_5 = (u8) ((s32) var_s1->unused18 / 10); break; case 1:                         /* switch 2 */ temp_v1_28 = *arg0;
*arg0 =
temp_v1_28 + 1; temp_v1_28->w1 = 0xFFC0C0FF;
temp_v1_28->w0 = 0xFA000100; temp_v1_29 = *arg0; *arg0 = temp_v1_29 + 1; temp_v1_29->w1 = 0xFF0000FF; temp_v1_29->w0 = 0xFB000000;
var_a1_5 = (u8) ((s32) var_s1->unused18 / 10);
break; case 2:                         /*
switch 2 */ temp_v1_30 = *arg0; *arg0 =
temp_v1_30 + 1; temp_v1_30->w1 = 0xC0C0FFFF; temp_v1_30->w0 = 0xFA000100; temp_v1_31 = *arg0;
*arg0 = temp_v1_31 + 1; temp_v1_31->w1 = 0xFFFF;
temp_v1_31->w0 = 0xFB000000; var_a1_5 = (u8) ((s32) var_s1->unused18 / 10); break; case 3:                         /* switch 2 */ temp_v1_32 = *arg0; *arg0 = temp_v1_32 + 1; temp_v1_32->w1 = -0x3F01; temp_v1_32->w0 = 0xFA000100; temp_v1_33 = *arg0;
*arg0 = temp_v1_33 + 1; temp_v1_33->w1 = 0xFFFF00FF; temp_v1_33->w0 = 0xFB000000;
var_a1_5 = (u8) ((s32)
var_s1->unused18 / 10); break; default:                        /* switch 2 */ temp_v1_34 = *arg0;
*arg0 = temp_v1_34 + 1; temp_v1_34->w1 = -1; temp_v1_34->w0 = 0xFA000100;
temp_v1_35 = *arg0; *arg0 = temp_v1_35 + 1; temp_v1_35->w1 = 0xFFFFFF; temp_v1_35->w0 = 0xFB000000;
var_a1_5 = (u8) ((s32) var_s1->unused18 / 10); break; }
} var_t3 = (s32) var_a1_5; if ((s32) var_a1_5 >= 4) {
var_t3 = 4; } break;
} switch (var_s1->kind) {
/* switch 3 */ case 3:                                 /* switch 3 */ temp_v0_5 = var_s3 ^ 3; var_s3 = 3; var_t4 = 3;
var_t1 = sp1A0; var_t2 = sp19C; if (temp_v0_5 != 0) { temp_v1_36 = *arg0;
*arg0 =
temp_v1_36 + 1; temp_v1_36->w1 = 0; temp_v1_36->w0 = 0xE7000000; temp_v1_37 = *arg0; *arg0 = temp_v1_37 + 1; temp_v1_37->w1 = 0xFFFCF279; temp_v1_37->w0 = 0xFCFFFFFF; temp_v1_38 = *arg0;
*arg0 = temp_v1_38 + 1; temp_v1_38->w1 = 0x0F0A4000; temp_v1_38->w0 = 0xB900031D; temp_v1_39 = *arg0;
*arg0 = temp_v1_39 + 1; temp_v1_39->w1 = 1; temp_v1_39->w0 = 0xB9000002; temp_v1_40 = *arg0;
*arg0 = temp_v1_40 + 1; temp_v1_40->w1 = 1; temp_v1_40->w0 = 0xF9000000;
}
D_8004EA78 = 0x1C; if (((s32) D_801D87E1 >= 0x31) && ((var_s1->param + 1) == D_801D87E0)) { sp174 = 1;
} break; case 16:                                /* switch 3 */ temp_v0_6 = var_s3 ^ 0x10; var_s3 = 0x10; var_t4 = 5; var_t1 = sp194; var_t2 = sp190; if (temp_v0_6 != 0) { temp_v1_41 = *arg0; *arg0 = temp_v1_41 + 1; temp_v1_41->w1 = 0;
temp_v1_41->w0 = 0xE7000000; temp_v1_42 = *arg0; *arg0 =
temp_v1_42 + 1; temp_v1_42->w1 = 0x5566DB6D; temp_v1_42->w0 = 0xFC313262; temp_v1_43 = *arg0; *arg0 = temp_v1_43 + 1;
temp_v1_43->w1 = 0x404040FF; temp_v1_43->w0 = 0xFA000100;
temp_v1_44 = *arg0;
*arg0 = temp_v1_44 + 1; temp_v1_44->w1 = 0; temp_v1_44->w0 = 0xFB000000; temp_v1_45 = *arg0;
*arg0 = temp_v1_45 + 1; temp_v1_45->w1 = 0x0F0A4000;
temp_v1_45->w0 = 0xB900031D; temp_v1_46 = *arg0;
*arg0 = temp_v1_46 + 1; temp_v1_46->w1 = 1; temp_v1_46->w0 = 0xB9000002; temp_v1_47 = *arg0; *arg0 = temp_v1_47 + 1;
temp_v1_47->w1 = 1; temp_v1_47->w0 = 0xF9000000; } D_8004EA78 = 0x16; break; case 7:                                 /* switch 3 */ temp_v0_7 = var_s3 ^ 7; var_s3 = 7; var_t1 = sp188; var_t2 = sp184; var_t4 = 7; if (temp_v0_7 != 0) { temp_v1_48 = *arg0; *arg0 = temp_v1_48 + 1; temp_v1_48->w1 = 0;
temp_v1_48->w0 = 0xE7000000; temp_v1_49 = *arg0;
*arg0 =
temp_v1_49 + 1; temp_v1_49->w1 = 0x5566DB6D; temp_v1_49->w0 = 0xFC313262; temp_v1_50 = *arg0;
*arg0 = temp_v1_50 + 1; temp_v1_50->w1 = 0xFFFF00FF;
temp_v1_50->w0 = 0xFA000100; temp_v1_51 = *arg0;
*arg0 = temp_v1_51 + 1; temp_v1_51->w1 = 0xFF000000; temp_v1_51->w0 = 0xFB000000;
temp_v1_52 = *arg0;
*arg0 = temp_v1_52 + 1;
temp_v1_52->w1 = 0x504240; temp_v1_52->w0 = 0xB900031D; temp_v1_53 = *arg0;
*arg0 = temp_v1_53 + 1; temp_v1_53->w1 = 0; temp_v1_53->w0 = 0xB9000002;
} var_t6 = 0x20; block_66: D_8004EA78 = var_t6; break; default:                                /* switch 3 */ case 1:                                 /* switch 3 */ case 2:                                 /* switch 3 */
case 4:                                 /* switch 3 */ case 5:                                 /* switch 3 */ case 6:                                 /* switch 3 */ case 8:                                 /* switch 3 */ case 9:                                 /* switch 3 */ case 10:                                /*
switch 3 */ case 11:                                /* switch 3 */ case 12:                                /* switch 3 */ case 13:                                /* switch 3 */ case 14:                                /* switch 3 */
case 15:                                /* switch 3 */ temp_v0_8 =
var_s3 ^ 1; var_s3 = 1; var_t4 = 1; var_t1 = sp1AC; var_t2 = sp1A8; if (temp_v0_8 != 0) { temp_v1_54 = *arg0;
*arg0 = temp_v1_54 + 1; temp_v1_54->w1 = 0; temp_v1_54->w0 = 0xE7000000; temp_v1_55 = *arg0;
*arg0 =
temp_v1_55 + 1; temp_v1_55->w1 = 0x55FEF379;
temp_v1_55->w0 = 0xFC30FE61; temp_v1_56 = *arg0;
*arg0 = temp_v1_56 + 1; temp_v1_56->w1 = 0x504240;
temp_v1_56->w0 = 0xB900031D; temp_v1_57 = *arg0;
*arg0 = temp_v1_57 + 1; temp_v1_57->w1 = 0; temp_v1_57->w0 = 0xB9000002; }
var_t6 = 0xA; sp180 = (u32) (sp180 * 3) >> 2; goto block_66;
}
if ((D_8004F394 != 1) || ((var_s1->kind != 3) && (var_s1->kind != 0x10))) {
if ((var_s1->kind == 1) || (var_s1->kind == 8)) { temp_v0_9 = var_s1->param; if ((s32) temp_v0_9 < 8) { sp180 = (u32) (temp_v0_9 * sp180) >> 3;
}
} if ((D_801D87E8 != 0) && (var_s1->kind != 3)) { sp180 *= 2;
} sp1C8 =
var_t1; sp1C4 =
var_t2; sp178 = var_t3; sp1DC = var_t4; func_8002DDD4(sp1D4, sp1D0, (s32) var_a1_5, sp1CC, &sp1BC, &sp1B8);
temp_v0_10 = &D_8004CED0[D_8004EA78]; var_t3 =
sp178;
temp_v1_58 = (sp1BC >> 4) - (temp_v0_10->halfW * sp180); temp_t7_2 = (sp1B8 >> 4) - (temp_v0_10->h * sp180); sp1B8 = temp_t7_2; sp1B8 = (temp_v0_10->halfH * sp180) + temp_t7_2; if (sp180 < 0x2BCU) { sp180 = 0x2BC;
} if (sp174 == 0) { if (temp_v1_58 > 0) { if (sp1B8 > 0) {
if ((temp_v1_58 < 0x140000) && (sp1B8 < 0xF0000) && (sp180 >= 0x19AU)) { temp_t0 = *arg0;
*arg0 =
temp_t0 + 1; var_a2 = 0; var_a1_6 = 0; temp_t6_2 = (u32) (sp1BC + ((sp1C8 + 2) * sp180)) >> 0xA; if (temp_t6_2 != 0) { var_a2 = temp_t6_2; } temp_t6_3 = (u32) (sp1B8 + (sp1C4 * sp180)) >> 0xA; if (temp_t6_3 != 0) { var_a1_6 = temp_t6_3;
} temp_t0->w0 = (s32) ((var_a1_6 & 0xFFF) | 0xE4000000 | ((var_a2 & 0xFFF) << 0xC)); var_a2_2 = 0; temp_t7_3 = sp1BC >> 0xA; if (temp_t7_3 > 0) { var_a2_2 = temp_t7_3; } temp_t9_3 = sp1B8 >> 0xA; if (temp_t9_3 > 0) { var_a1_7 = temp_t9_3; } else {
var_a1_7 = 0;
} temp_t0->w1 = (s32) ((var_a1_7 & 0xFFF) | ((sp1DC & 7) << 0x18) | ((var_a2_2 & 0xFFF) << 0xC)); temp_v1_59 = *arg0;
*arg0 = temp_v1_59 + 1; temp_v1_59->w0 = 0xB3000000; temp_v1_59->w1 = (s32) ((((s32) (32.0f - ((((f32) sp1B8 / 4096.0f) - (f32) (sp1B8 >> 0xC)) * 32.0f)) - 0) & 0xFFFF) | (0 * -0x10000)); temp_v1_60 = *arg0;
*arg0 = temp_v1_60 + 1; temp_v1_60->w0 = 0xB2000000; temp_t8 = (0x400000U / sp180) & 0xFFFF & 0xFFFF; temp_v1_60->w1 = (s32) ((temp_t8 << 0x10) | temp_t8);
} }
} }
}
} var_s1++; } while (var_s1 != D_801D7338); temp_v1_61 = *arg0;
*arg0 = temp_v1_61 + 1; temp_v1_61->w1 = 0;
temp_v1_61->w0 = 0xE7000000; temp_v1_62 = *arg0;
*arg0 = temp_v1_62 + 1;
temp_v1_62->w1 = 0; temp_v1_62->w0 = 0xB9000002;
}
