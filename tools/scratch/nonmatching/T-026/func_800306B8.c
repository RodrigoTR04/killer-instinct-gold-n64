/* T-085 DRAFT: 513 -> 510 differing words in owning TU; 2096/2104 bytes. */ typedef struct
{ u32 w0, w1;
} T081Gfx; s32 func_80030EF0(u8); typedef
struct
{ u8 r,g,b,a;
} T081Color; extern T081Color D_800482A0[];
extern
s32 D_800482B8[]; typedef struct
{ u8 width, height, spacing, baseline;
} T081Glyph; extern T081Glyph D_80069E48[]; extern u8 D_80069F70[]; void func_800306B8(T081Gfx **arg0, s32 arg1,
s32 arg2, u8 *arg3, s32 arg4,
s32 arg5)
{ T081Gfx *command;
s32 sp40; s32 *temp_s4; s32 temp_a1;
s32 temp_a2; s32 temp_a2_2;
s32 temp_a2_3;
s32 temp_lo; s32 temp_lo_2; s32 temp_lo_3;
s32 temp_s3; s32 temp_t0; s32 temp_t0_2; s32
temp_t7; s32 temp_t7_2; s32 temp_t7_3; s32
temp_t9; s32 temp_t9_2; s32
temp_v0_10; s32 var_a3; s32 var_a3_2; s32 var_a3_3; s32 var_fp; s32 var_ra; s32 var_s1; s32 var_s1_2; s32 var_s3;
s32 var_s5; s32
var_s7; s32 var_t1; s32 var_t3; s32 var_t5; s32 var_v1; s32 var_v1_2;
s32 var_v1_3; s32
var_v1_4; u8 *var_s2;
u8 *var_s2_2; u8 temp_t3; u8
temp_t4;
u8 temp_v0_9; u8 var_a0; u8 var_a0_2; T081Glyph *temp_t2; T081Glyph *temp_t2_2; T081Color *temp_v1; var_s1 =
arg1; var_fp = -1; var_t3 = 0; if (arg1 == 0)
    {
var_s2 = arg3; if ((s32) *arg3 >= 0x14)
        { var_a0 = *var_s2; do
            { sp40 = var_t3; temp_t0 = func_80030EF0(var_a0) & 0xFF; if (temp_t0 == 0xFF)
                { var_t3 += 0x1FC; } else
                { temp_t2 = &D_80069E48[temp_t0]; var_t3 += (temp_t2->width + temp_t2->spacing + 1) * D_800482B8[arg5]; }
var_a0 = (*(u8 *)(var_s2 + 0x1)); var_s2 += 1; } while ((s32) var_a0 >= 0x14);
} var_s1 = 0xA0 - (var_t3 / 254); } command = *arg0;
*arg0 = command + 1; command->w1 = 0; command->w0 = 0xE7000000; command = *arg0;
*arg0 = command + 1; command->w1 = 0; command->w0 = 0xBA001701; command = *arg0;
*arg0 = command + 1; command->w1 = 0; command->w0 = 0xBA001301;
command = *arg0; *arg0 = command + 1; command->w1 = 0; command->w0 = 0xBA001001; command = *arg0;
*arg0 = command + 1; command->w0 = 0xB900031D;
command->w1 = 0x504240; command = *arg0;
*arg0 = command + 1; command->w0 = 0xF5900000;
command->w1 = 0x01080200; command = *arg0;
*arg0 = command + 1; command->w0 = 0xFA000100;
temp_v1 = &D_800482A0[arg4]; var_s1_2 = var_s1 * 0x7F;
command->w1 = (s32) ((temp_v1->b << 8) | (temp_v1->r << 0x18) | (temp_v1->g << 0x10) | 0xFF); command = *arg0;
*arg0 =
command + 1; command->w1 = 0; command->w0 = 0xFB000000; var_s3 = arg2 * 0x7F; var_s2_2 =
arg3; if ((s32) *arg3 >= 0x14)
    { var_a0_2 = *var_s2_2; do
        { temp_t0_2 = func_80030EF0(var_a0_2) & 0xFF; if (temp_t0_2 == 0xFF)
            { var_s1_2 += 0x1FC; }
else
            { temp_t2_2 = &D_80069E48[temp_t0_2];
temp_s4 = &D_800482B8[arg5];
temp_a2 = *temp_s4; temp_t3 = temp_t2_2->width; temp_v0_9 = (*(u8 *)(var_s2_2 + 0x0)); temp_t4 = temp_t2_2->height; var_t1 = 4; temp_s3 = var_s3 + (temp_t2_2->baseline *
temp_a2);
if ((temp_v0_9 == 0x86) || (temp_v0_9 == 0x85) || (temp_v0_9 == 0x87))
                {
var_s7 = (temp_t3 - 1) << 5; var_ra = (-0x1FC00 / temp_a2) & 0xFFFF; }
else
                { var_ra = 0x1FC00 / temp_a2; var_s7 = 0;
} if ((temp_v0_9 == 0x80) || (temp_v0_9 == 0x81) || (temp_v0_9 == 0x87))
                { var_s5 = (temp_t4 - 1) << 5; var_t5 = (-0x1FC00 / temp_a2) & 0xFFFF;
} else
                {
var_t5 = 0x1FC00 / temp_a2; var_s5 = 0; } if (temp_t0_2 == 0x47)
                { temp_v0_10 = var_fp ^ 1; var_fp = 1; var_t1 = 3; if (temp_v0_10 != 0)
                    { command = *arg0;
*arg0 = command + 1; command->w0 = 0xFC30FE61; command->w1 = 0x55FEF379;
} } else
                { temp_v0_10 = var_fp; var_fp = 0; if (temp_v0_10 != 0)
                    { command = *arg0;
*arg0 = command + 1; command->w0 = 0xFCFFFFFF; command->w1 = 0xFFFDF2F9;
} } command = *arg0; temp_t7 = (var_t1 & 7) << 0x15;
*arg0 = command + 1; command->w0 = (s32) (temp_t7 | 0xF5000000 | 0x80000 | ((((s32) (temp_t3 + 7) >> 3) & 0x1FF) << 9)); command->w1 = 0x03080200; command = *arg0; temp_t7_2 = (temp_t3 + 7) & 0xFFF8; *arg0 = command + 1; command->w0 = 0xF2000000; command->w1 = (s32) (((((temp_t7_2 - 1) * 4) & 0xFFF) << 0xC) | 0x03000000 | ((temp_t4 * 4) & 0xFFF)); command = *arg0;
*arg0 = command + 1; command->w1 = (s32) ((temp_t0_2 * 0x120) + D_80069F70); command->w0 = (s32) (temp_t7 | 0xFD000000 | 0x100000); command = *arg0; var_v1 = 0x7FF;
*arg0 = command + 1; var_a3 = 0; command->w0 = 0xF3000000; temp_a1 = ((s32) ((temp_t7_2 * (temp_t4 + 1)) + 1) >> 1) - 1; if (temp_a1 < 0x7FF)
                {
var_v1 = temp_a1;
} command->w1 = (s32) (((var_v1 & 0xFFF) << 0xC) | 0x01000000); command = *arg0; var_v1_2 = 0;
*arg0 = command + 1; temp_a2_2 = *temp_s4; temp_lo = (s32) (((temp_a2_2 * temp_t3) + var_s1_2) * 4) / 127; if (temp_lo > 0)
                { var_a3 = temp_lo;
} temp_lo_2 = (s32) (((temp_a2_2 * temp_t4) + temp_s3) * 4) / 127; if (temp_lo_2 > 0)
                { var_v1_2 = temp_lo_2; } temp_lo_3 = (s32) (var_s1_2 * 4) / 127; command->w0 = (s32) ((var_v1_2 & 0xFFF) | 0xE4000000 | ((var_a3 & 0xFFF) << 0xC)); var_v1_3 = 0; var_a3_2 = 0; if (temp_lo_3 > 0)
                { var_a3_2 = temp_lo_3; } temp_t9 = (temp_s3 / 127) * 4; if (temp_t9 > 0)
                { var_v1_3 = temp_t9; } command->w1 = (s32) ((var_v1_3 & 0xFFF) | 0x03000000 | ((var_a3_2 & 0xFFF) << 0xC)); command = *arg0;
*arg0 = command + 1; temp_t9_2 = (s32) (temp_lo_3 * var_ra) >> 7; command->w0 = 0xB3000000; if (temp_t9_2 < 0)
                {
var_a3_3 = temp_t9_2;
} else
                { var_a3_3 = 0;
} var_v1_4 = 0; temp_t7_3 = (s32) (temp_t9 *
var_t5) >> 7; if (temp_t7_3 < 0)
                { var_v1_4 = temp_t7_3;
} command->w1 = (s32) (((var_s5 - var_v1_4) & 0xFFFF) | ((var_s7 - var_a3_3) << 0x10)); command = *arg0; *arg0 = command + 1; command->w0 = 0xB2000000; command->w1 = (s32) ((var_ra << 0x10) | (var_t5 & 0xFFFF)); command = *arg0;
*arg0 = command + 1; command->w1 = 0; command->w0 = 0xE7000000; temp_a2_3 = *temp_s4; var_s3 = temp_s3 - (temp_t2_2->baseline * temp_a2_3); var_s1_2 = var_s1_2 + (temp_t2_2->spacing *
temp_a2_3) + ((temp_t3 + 1) * temp_a2_3);
} var_a0_2 = (*(u8 *)(var_s2_2 + 0x1)); var_s2_2 += 1;
} while ((s32) var_a0_2 >= 0x14);
} }
