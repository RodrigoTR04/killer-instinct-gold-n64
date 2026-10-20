/* T-085 DRAFT: 1875 -> 1843 differing words in owning TU; 7692/7668 bytes. */
typedef struct {
s32 x,y,z;
float worldX,worldY,worldZ;
}
T024CameraObject;
typedef struct {
float x,y,z,pitch,yaw,velocity,acceleration,pad,limit,pad24;
} T024CameraPreset;
typedef struct {
float x,y,z,pitch,yaw;
}
T024CameraKeyframe;
typedef struct {
u8 pad[0x29];
u8 first,second;
}
T024CameraFade;
typedef struct {
u8 pad[0x10];
s32 first;
u8 middle[0xFC]; s32 second;
}
T024CameraTracking;
extern T024CameraPreset D_80044BCC[];
extern T024CameraKeyframe D_80044AC8[];
extern float D_80044BD8[]; extern u8 D_80044DD4[]; extern T024CameraFade D_801C4198;
extern T024CameraTracking D_801D3430;
void func_8002BBD0(T024CameraObject *,T024CameraObject *);
void func_8002D9C4(void *,s32,s32,s32);
void func_8002DBDC(float,float *);
void func_8002DC48(float *);
double func_8002E150(double);
float sqrtf(float);
float sinf(float);
float cosf(float);
extern f32 D_80048D74;
extern f32 D_80048D78;
extern f32 D_80048D7C;
extern f32 D_80048D80;
extern f32 D_80048D84;
extern f32 D_80048D88;
extern f32 D_80048D8C;
extern f32 D_80048D90;
extern f32 D_80048D94;
extern f32 D_80048D98;
extern f64 D_80048DA0;
extern f32 D_80048DA8; extern f32 D_80048DAC; extern f32 D_80048DB0;
extern f32 D_80048DB4;
extern f32 D_80048DB8;
extern f64 D_80048DC0;
extern f64 D_80048DC8;
extern f64 D_80048DD0;
extern f64 D_80048DD8;
extern f64 D_80048DE0;
extern f64 D_80048DE8;
extern f64 D_80048DF0;
extern f64 D_80048DF8;
extern f64 D_80048E00;
extern f64 D_80048E08;
extern f64 D_80048E10;
extern f64 D_80048E18;
extern f32 D_80048E20;
extern f32 D_80048E24;
extern f32 D_80048E28;
extern f32 D_80048E60;
extern f32 D_80048E64;
extern f32 D_80048E68;
extern f32 D_80048E6C;
extern f32 D_80048E70;
extern f32 D_80048E74; extern f32 D_80048E78;
extern f32 D_80048E7C;
extern f32 D_80048E80;
extern f64 D_80048E88;
extern f64 D_80048E90;
extern f64 D_80048E98; extern f64 D_80048EA0;
extern f32 D_80048EA8;
extern f32 D_80048EAC;
extern f32 D_80048EB0;
extern f64 D_80048EB8;
extern f64 D_80048EC0;
extern f64 D_80048EC8; extern f64 D_80048ED0;
extern f32 D_80048ED8;
extern u8 D_8004A401; extern f32 D_8004AC80;
extern f32 D_8004AC84;
extern u8 D_8004AC88;
extern f32 D_800695B8;
extern f32 D_800695BC;
extern f32 D_800695C0;
extern f32 D_800695C4;
extern f32 D_800695C8;
extern f32 D_800695CC;
extern f32 D_800695D0;
extern f32 D_800695D4;
extern f32 D_800695D8; extern f32 D_800695DC;
extern f32 D_800695E4;
extern f32 D_800695E8; extern f32 D_800695EC;
extern f32 D_800695F4;
extern f32 D_800695F8;
extern f32 D_800695FC; extern f32 D_800698C0;
extern s32 D_800698C4;
extern s32 D_800698C8; extern s32 D_801D5D34;
extern s32 D_801D5D38;
extern s32 D_801D5D3C;
extern s32 D_801D5D40;
extern s8 D_801D73C7;
extern u8 D_801D7DF7;
extern s8 D_801D8777;
extern u8 D_801D87DC;
extern u8 D_801D87EC;
extern f32 D_801D87F0;
extern f32 D_801D87F4;
extern u8 D_801D8804;
void func_8002BBD0(T024CameraObject *subject, T024CameraObject *opponent) {
f32 spC4;
f32 spC0;
f32 spBC;
f32 spB8;
f32 spB0;
f32 spAC;
f32 spA4;
f32 spA0; f32 sp9C;
f32 sp90;
f64 sp80;
f64 sp78;
u8 followMatch;
f32 sp48;
f32 sp40;
f32 sp38;
f32 sp30;
f32 sp24;
f32 sp20;
f32 sp1C;
T024CameraPreset *temp_a0; T024CameraPreset *temp_a0_2;
f32 temp_f0;
f32 temp_f0_2; f32 temp_f0_3;
f32 temp_f0_4;
f32 temp_f0_5;
f32 temp_f10;
f32 temp_f12;
f32 temp_f12_2;
f32 temp_f12_3;
f32 temp_f12_4;
f32 temp_f14; f32 temp_f14_2;
f32 temp_f16;
f32 temp_f2; f32 temp_f2_10;
f32 temp_f2_11;
f32 temp_f2_12;
f32 temp_f2_13;
f32 temp_f2_2;
f32 temp_f2_3;
f32 temp_f2_4;
f32 temp_f2_5;
f32 temp_f2_6;
f32 temp_f2_7;
f32 temp_f2_8;
f32 temp_f2_9;
f32 temp_f6;
f32 temp_f6_2;
f32 var_f0;
f32 var_f0_10;
f32 var_f0_11;
f32 var_f0_12;
f32 var_f0_13;
f32 var_f0_2; f32 var_f0_3;
f32 var_f0_4;
f32 var_f0_6;
f32 var_f0_7;
f32 var_f0_8;
f32 var_f0_9; f32 var_f10;
f32 var_f10_2;
f32 var_f12;
f32 var_f14;
f32 var_f14_3;
f32 var_f16;
f32 var_f16_2;
f32 var_f16_3;
f32 var_f16_4;
f32 var_f18;
f32 var_f2;
f32 var_f6;
f32 var_f8;
f32 var_f8_2;
f32 var_f8_3; f64 var_f0_5;
f64 var_f14_2;
f64 var_f14_4;
f64 var_f18_2;
f64 var_f18_3;
f64 var_f18_4;
s32 temp_a0_3;
s32 temp_a1;
s32 temp_a1_2;
s32 temp_f8;
s32 temp_t6;
s32 temp_t7;
s32 var_a1;
s32 var_a2;
s32 var_v0;
s32 var_v0_2; u32 temp_t8;
u8 temp_t2;
u8 temp_t5;
u8 temp_v0;
if ((D_8004AC88 == 0) || (D_8004AC88 == 4) || (D_8004AC88 == 5) || (D_8004AC88 == 7) || (D_8004AC88 == 8) || (D_8004AC88 == 9) || (D_8004AC88 == 0xA)) { followMatch = 1;
}
else {
followMatch = 0;
}
if (D_8004AC88 == 7) {
var_f14 = D_80048D74; var_f16 = D_80048D78;
var_f0 = D_80048D7C;
}
else if (D_8004AC88 == 8) {
var_f14 = 1.5f;
var_f16 = D_80048D80;
var_f0 = D_80048D84;
}
else {
var_f0 = D_80048D88;
var_f14 = 1.5f;
var_f16 = var_f0;
}
switch ((u32)D_8004A401) {
/* switch 1;
irregular */
    case 3:                                         /* switch 1 */
        D_801D8777 = 0x64;
D_800695CC = D_800695B8;
D_800695BC = D_800695D0;
D_800695D4 = D_800695C0;
D_800695C4 = D_800695D8;
D_800695DC = D_800695C8;
if (D_8004AC88 == 1) {
var_f14 = 1.5f;
var_f16 = var_f0;
*(D_80044BD8 + (D_8004AC88 * 0x28)) = 80.0f; }
spA4 = var_f14;
spA0 = var_f16;
func_8002D9C4(&D_80044BCC[D_8004AC88], D_800698C4, D_800698C8, 1);
temp_v0 = D_80044DD4[D_8004AC88];
if ((temp_v0 & 2) == 2) {
D_800695CC = D_800695B8;
}
temp_a1 = temp_v0 & 4;
if (temp_a1 == 4) {
D_800695DC = D_800695C8; } temp_a0 = &D_80044BCC[D_8004AC88];
temp_f2 = temp_a0->acceleration; temp_f6 = D_800695BC + D_800695F8;
D_800695F8 += temp_a0->velocity;
D_800695D0 = temp_f6;
if (D_800695F8 < temp_f2) {
D_800695F8 = temp_f2;
}
if ((D_8004AC88 == 8) && (D_800695D0 < D_80048D8C)) {
D_800695D0 = D_80048D90 + D_800695D0 + D_80048D94;
}
D_800695D8 = D_800695C4;
if (D_8004AC88 != 6) {
D_800695D8 = (temp_a0->pitch - D_800695D8) / 10.0f;
if (var_f14 < D_800695D8) {
D_800695D8 = var_f14;
} temp_f2_2 = D_800698C0 + var_f16;
if (temp_f2_2 < D_800695D8) {
D_800695D8 = temp_f2_2;
D_800698C0 = D_800695D8;
}
D_800695D8 += D_800695C4;
}
temp_t7 = D_800698C4 - 1;
D_800698C4 = temp_t7;
if (temp_t7 == 0) {
D_8004A401 = 4;
temp_f8 = (s32) temp_a0->limit;
D_800698C4 = temp_f8;
D_800698C8 = temp_f8; D_800695F4 = 0.0f;
D_800695C4 = D_800695D8;
if (temp_a1 == 4) {
D_800695C8 = D_800695DC;
return;
}
if (D_8004AC88 != 8) {
D_800695C8 = temp_a0->yaw;
return;
}
}
else {
case 0:                                     /* switch 1 */
            return;
}
break;
case 4:                                         /* switch 1 */
        if (D_801D8804 == 0) {
if (D_8004AC88 == 1) {
var_f14 = D_80048D98;
var_f16 = var_f0;
*(D_80044BD8 + (D_8004AC88 * 0x28)) = 45.0f;
}
temp_a0_2 = &D_80044BCC[D_8004AC88];
if (D_8004AC88 == 6) {
D_801C4198.first = 0xFF;
D_801C4198.second = 0xFF;
}
if (D_800698C4 >= 0x33) {
D_801D8777 = 0x64;
}
if (D_80044DD4[D_8004AC88] & 1) {
if (D_800695FC < 6.0f) {
D_800695FC = (f32) ((f64) D_800695FC + D_80048DA0);
}
D_800695DC = D_800695C8 + D_800695F4;
D_800695F4 += D_800695FC;
} temp_f2_3 = temp_a0_2->acceleration;
temp_f6_2 = D_800695D0 + D_800695F8;
D_800695F8 += temp_a0_2->velocity;
D_800695D0 = temp_f6_2; if (D_800695F8 < temp_f2_3) {
D_800695F8 = temp_f2_3; }
if ((D_8004AC88 == 6) && (D_800695D0 < -2000.0f)) {
D_800695D0 = -2000.0f;
}
if ((D_8004AC88 == 1) && (D_800695D0 < D_80048DA8)) {
D_800695D0 = D_80048DA8;
}
if ((D_8004AC88 == 8) && (D_800695D0 < D_80048DAC)) {
D_800695D0 = D_80048DB0 + D_800695D0 + D_80048DB4;
}
D_800695C4 = D_800695D8;
D_800695D8 = (temp_a0_2->pitch - D_800695D8) / 10.0f;
if (var_f14 < D_800695D8) {
D_800695D8 = var_f14;
}
else { temp_f2_4 = -var_f14;
if (D_800695D8 < temp_f2_4) {
D_800695D8 = temp_f2_4;
}
}
temp_f2_5 = D_800698C0 + var_f16;
if (temp_f2_5 < D_800695D8) {
D_800695D8 = temp_f2_5;
D_800698C0 = D_800695D8;
}
temp_t6 = D_800698C4 - 1;
D_800698C4 = temp_t6;
D_800695D8 += D_800695C4;
if (temp_t6 == 0) {
D_8004A401 = 0;
return;
}
}
break;
case 1:                                         /* switch 1 */
        temp_f2_6 = subject->worldX;
temp_f12 = opponent->worldX;
spC4 = (f32) ((f64) (temp_f2_6 + temp_f12) * 0.5);
temp_f16 = opponent->worldZ;
temp_f14 = subject->worldZ; var_f18 = (f32) ((f64) (temp_f14 + temp_f16) * 0.5);
switch (D_800695B4) {
/* switch 2;
irregular */
        default:                                    /* switch 2 */
            var_f2 = D_8004AC84;
break;
case 2:                                     /* switch 2 */
            sp30 = D_8004AC84;
spC4 = temp_f2_6 + ((f32) (D_801D5D3C * 0x32) / D_8004AC84);
var_f0_2 = subject->worldY;
var_f18 = temp_f14 + ((f32) (D_801D5D40 * 0x32) / D_8004AC84);
if (D_8004AC88 != 0) {
var_f0_2 -= 5120.0f / D_8004AC84; }
spC0 = var_f0_2;
var_f2 = sp30;
break;
case 3:                                     /* switch 2 */
            sp30 = D_8004AC84;
spC4 = temp_f12 - ((f32) (D_801D5D3C * 0x32) / D_8004AC84);
var_f0_3 = opponent->worldY;
var_f18 = temp_f16 - ((f32) (D_801D5D40 * 0x32) / D_8004AC84);
if (D_8004AC88 != 0) {
var_f0_3 -= 5120.0f / D_8004AC84; }
spC0 = var_f0_3;
var_f2 = sp30;
break;
case 0:                                     /* switch 2 */
        case 1:                                     /* switch 2 */
            temp_f2_7 = opponent->worldY;
temp_f0 = subject->worldY;
if (temp_f2_7 < temp_f0) {
spC0 = temp_f2_7;
} else {
spC0 = temp_f0;
}
var_f2 = D_8004AC84;
sp30 = var_f2;
break;
}
if ((D_801D87DC != 0) && ((spC0 = D_8004AC80, (D_800695B4 == 2)) || (D_800695B4 == 3)) && (D_8004AC88 != 0)) {
spC0 -= 5120.0f / var_f2;
}
if (D_801D87EC == 0) { temp_t8 = D_801D5D34 * 2;
if ((u32) D_800695B0 < temp_t8) {
var_f10 = (f32) temp_t8;
if (D_801D5D34 & 0x40000000) {
var_f10 += 4294967296.0f;
}
sp9C = var_f10;
}
else {
var_f6 = (f32) D_800695B0;
if ((s32) D_800695B0 < 0) {
var_f6 += 4294967296.0f; }
sp9C = var_f6;
}
var_a1 = -D_801D3430.first;
if (D_801D3430.first >= 0) {
var_a1 = D_801D3430.first; }
temp_a0_3 = subject->z - opponent->z;
if (temp_a0_3 >= 0) {
var_a2 = temp_a0_3;
}
else {
var_a2 = -temp_a0_3;
}
var_v0 = -D_801D3430.second; if (D_801D3430.second >= 0) {
var_v0 = D_801D3430.second;
}
if (((f32) (((var_v0 * 2) + var_a2 + (var_a1 * 2)) * 3) < sp9C) || (D_801D87DC != 0) || (D_8004AC88 == 0xC) || ((D_8004AC88 == 7) && (D_801D7DF7 == 0))) {
var_f10_2 = (f32) temp_t8;
if (D_801D5D34 & 0x40000000) { var_f10_2 += 4294967296.0f; }
sp9C = var_f10_2 / var_f2;
}
else {
var_v0_2 = -temp_a0_3;
if (temp_a0_3 >= 0) {
var_v0_2 = temp_a0_3;
}
sp9C = (f32) (var_v0_2 * 4) / var_f2;
}
var_f16_2 = sp9C; var_f0_4 = (f32) D_800695B0 / var_f2;
} else {
var_f0_4 = (f32) D_800695B0 / var_f2; sp9C = var_f0_4;
var_f16_2 = sp9C;
}
if (var_f16_2 < var_f0_4) {
goto block_123;
}
var_f0_4 = D_80048DB8 / var_f2;
if (var_f0_4 < var_f16_2) {
block_123:
            var_f16_2 = var_f0_4;
}
spBC = var_f18;
if (D_8004AC88 == 2) {
var_f14_2 = (f64) (spC4 - D_800695CC);
var_f0_5 = (f64) (spBC - D_800695D4); }
else {
var_f14_2 = (f64) D_801D87F4;
var_f0_5 = (f64) D_801D87F0; }
sp78 = var_f14_2;
sp9C = var_f16_2;
var_f18_2 = (f64) sqrtf((f32) ((var_f0_5 * var_f0_5) + (var_f14_2 * var_f14_2)));
if (var_f18_2 == 0.0) {
var_f18_2 = D_80048DC0;
}
if (followMatch != 0) {
followMatch = 0;
if (D_801D87F0 >= 0.0f) {
D_801D5D38 = 0;
}
else {
D_801D5D38 = 1;
}
}
if ((D_801D5D38 != 0) && (D_8004AC88 != 2)) {
sp80 = var_f18_2;
var_f18_3 = var_f18_2;
D_800695DC = (f32) (-(func_8002E150(var_f14_2 / var_f18_2) * D_80048DC8) / D_80048DD0);
if (D_801D87F0 > 0.0f) {
D_800695DC = 180.0f - D_800695DC;
}
}
else {
sp80 = var_f18_2;
var_f18_3 = var_f18_2; temp_f10 = (f32) ((func_8002E150(var_f14_2 / var_f18_2) * D_80048DD8) / D_80048DE0);
D_800695DC = temp_f10;
if ((D_801D87F0 < 0.0f) && (D_8004AC88 != 2) && (followMatch == 0)) {
D_800695DC = 180.0f - temp_f10;
}
}
temp_f2_8 = D_800695DC;
if (temp_f2_8 < 0.0f) {
do {
D_800695DC = temp_f2_8 + 360.0f;
}
while (D_800695DC < 0.0f);
} if (D_800698C4 == 0) {
sp80 = var_f18_3;
func_8002DBDC(D_800695C8, &D_800695DC);
if (D_800695DC < D_800695C8) {
temp_f12_2 = D_800695C8 - D_800695DC;
if (temp_f12_2 > 45.0f) {
D_800695C8 = D_800695DC + 45.0f; }
else if ((f64) temp_f12_2 > 0.5) {
D_800695C8 = (f32) ((f64) D_800695C8 - 0.5);
}
else {
goto block_156;
} }
else if (D_800695C8 < D_800695DC) {
temp_f12_3 = D_800695C8 - D_800695DC;
if (temp_f12_3 < -45.0f) { D_800695C8 = D_800695DC - 45.0f;
}
else if ((f64) temp_f12_3 < -0.5) {
D_800695C8 = (f32) ((f64) D_800695C8 + 0.5); }
else {
block_156:
                    D_800695C8 = D_800695DC;
}
} sp80 = var_f18_3;
func_8002DC48(&D_800695C8);
func_8002DC48(&D_800695DC);
}
else {
D_800695C8 = temp_f2_8;
}
if ((D_801D87F0 < 0.0f) && (followMatch == 0)) {
var_f14_3 = (f32) ((((f64) (temp_f2_8 - D_800695C8) * D_80048DE8) / D_80048DF0) + D_80048DF8); }
else { var_f14_3 = (f32) (D_80048E10 - (((f64) (temp_f2_8 - D_800695C8) * D_80048E00) / D_80048E08));
} spB8 = var_f14_3;
temp_f12_4 = (f32) (((f64) var_f14_3 - D_80048E18) + (f64) (f32) func_8002E150((f64) D_801D87F4 / var_f18_3));
spB0 = temp_f12_4;
temp_f14_2 = sinf(temp_f12_4) * sp9C; spAC = temp_f14_2;
temp_f2_9 = cosf(temp_f12_4) * sp9C;
var_f12 = temp_f2_9;
if ((D_801D87F0 < 0.0f) && (followMatch == 0)) {
var_f12 = -temp_f2_9;
}
if (D_800695C8 < 0.0f) { do {
D_800695C8 += 360.0f;
}
while (D_800695C8 < 0.0f);
}
temp_t5 = D_8004AC88;
temp_t2 = temp_t5;
if ((temp_t5 == 0xB) && (D_800695B4 == 1)) {
sp30 = D_8004AC84;
var_f8 = (D_80048E20 / D_8004AC84) + spC0;
goto block_174; }
if (D_800695B4 != 1) {
sp30 = D_8004AC84;
D_800695D0 = (D_80048E24 / D_8004AC84) + spC0 + ((sp9C - ((f32) D_800695B0 / D_8004AC84)) / 3.0f);
}
else {
sp30 = D_8004AC84;
var_f8 = (D_80048E28 / D_8004AC84) + spC0 + ((sp9C - ((f32) D_800695B0 / D_8004AC84)) / 3.0f);
block_174:
            D_800695D0 = var_f8;
}
if (D_801D5D38 != 0) {
var_f8_2 = spBC - var_f12;
D_800695CC = spC4 + temp_f14_2;
}
else {
var_f8_2 = spBC + var_f12;
D_800695CC = spC4 - temp_f14_2;
}
D_800695D4 = var_f8_2;
switch (temp_t2) {
/* switch 3 */
        case 0:                                     /* switch 3 */
            if (D_80048E60 < D_800695D4) {
D_800695D4 = D_80048E60;
}
break;
case 1:                                     /* switch 3 */
            if (D_800695CC < D_80048E64) {
var_f0_6 = 350.0f;
if (D_800695D0 < 350.0f) {
goto block_188;
} }
else if (D_800695CC > 270.0f) {
var_f0_6 = 300.0f;
if (D_800695D0 < 300.0f) { block_188:
                    D_800695D0 = var_f0_6;
}
}
break;
case 2:                                     /* switch 3 */
            if (D_800695CC > 79.0f) {
D_800695CC = 79.0f;
}
else if (D_800695CC < D_80048E68) {
D_800695CC = D_80048E68; }
if (D_80048E6C < D_800695D4) {
D_800695D4 = D_80048E6C;
}
if (D_800695D0 > 1000.0f) {
D_800695D0 = 1000.0f;
}
D_800695D0 += (f32) (D_801D73C7 * 0x14);
break;
case 3:                                     /* switch 3 */
            if (D_800695B4 == 1) {
if (D_800695D0 < D_80048E70) {
D_800695D0 = D_80048E70;
}
}
else {
if (D_80048E74 <= D_800695CC) {
var_f0_7 = D_800695CC - D_80048E74;
}
else {
var_f0_7 = -(D_800695CC - D_80048E74);
}
D_800695D0 += var_f0_7 / 3.0f;
}
break;
case 4:                                     /* switch 3 */
            if (D_800695B4 == 1) {
if ((D_800695CC > 50.0f) && (D_800695DC < 180.0f)) {
D_800695CC = 50.0f;
}
else {
temp_f0_2 = ((360.0f - D_800695DC) * 3.0f) + 50.0f;
if ((temp_f0_2 < D_800695CC) && (D_800695DC > 180.0f)) {
D_800695CC = temp_f0_2;
}
}
}
break;
case 6:                                     /* switch 3 */
            if ((D_800695D4 < -200.0f) && (D_800695D0 < 360.0f)) { D_800695D0 = 360.0f;
} if ((D_800695CC > 580.0f) && (D_800695D0 < 270.0f)) {
D_800695D0 = 270.0f;
} break;
case 7:                                     /* switch 3 */
            if (D_800695B4 == 1) { if (D_800695CC < -300.0f) {
D_800695CC = -300.0f;
}
if ((D_801D7DF7 == 0) && (D_800695CC > 700.0f)) {
D_800695CC = 700.0f;
}
D_800695C8 = 0.0f;
}
break; case 8:                                     /* switch 3 */
            if (D_80048E78 < D_800695D4) {
temp_f0_3 = (D_80048E7C + D_800695D4) - D_80048E78;
if (D_800695D0 < temp_f0_3) {
D_800695D0 = temp_f0_3;
}
}
if (D_80048E80 < D_800695D4) { D_800695D4 = D_80048E80; }
if (D_800695D0 > 2000.0f) {
D_800695D0 = 2000.0f;
}
break;
case 12:                                    /* switch 3 */
            D_800695CC = 110.0f;
D_800695D0 = 146.0f; if (D_800695D4 < 700.0f) {
D_800695D4 = 700.0f;
}
D_800695C8 = 0.0f;
D_800695DC = D_800695C8;
break; case 11:                                    /* switch 3 */
            D_800695D0 += (f32) (D_801D73C7 * 7);
break;
default:                                    /* switch 3 */
            break;
}
var_f16_3 = 1.0f;
D_800695E4 = D_800695CC;
D_800695E8 = D_800695D0;
temp_a1_2 = D_800698C4;
D_800695EC = D_800695D4;
if (temp_a1_2 == 0) { if (D_800695CC <= D_800695B8) {
sp48 = D_800695B8;
sp24 = D_800695B8 - D_800695CC;
var_f16_4 = sp24; }
else {
temp_f2_10 = D_800695B8 - D_800695CC;
sp48 = D_800695B8; var_f16_4 = -temp_f2_10; sp24 = temp_f2_10;
}
sp38 = D_800695BC;
if (D_800695D0 <= D_800695BC) {
var_f0_8 = sp38 - D_800695D0; sp20 = var_f0_8;
}
else {
temp_f2_11 = sp38 - D_800695D0;
var_f0_8 = -temp_f2_11;
sp20 = temp_f2_11;
}
if (var_f16_4 < var_f0_8) {
if (D_800695D0 <= sp38) {
var_f0_9 = sp20;
}
else {
var_f0_9 = -sp20;
}
var_f16_4 = var_f0_9;
}
sp40 = D_800695C0;
if (D_800695D4 <= D_800695C0) {
var_f0_10 = sp40 - D_800695D4;
sp1C = var_f0_10;
}
else {
temp_f2_12 = sp40 - D_800695D4;
var_f0_10 = -temp_f2_12;
sp1C = temp_f2_12;
}
if (var_f16_4 < var_f0_10) {
if (D_800695D4 <= sp40) {
var_f0_11 = sp1C; }
else {
var_f0_11 = -sp1C;
}
var_f16_4 = var_f0_11;
}
temp_f0_4 = var_f16_4 / 12.0f;
if (temp_f0_4 < sp24) { var_f16_3 = sp24 / temp_f0_4;
}
else if (sp24 < -temp_f0_4) {
var_f16_3 = (D_800695CC - sp48) / temp_f0_4;
}
else {
var_f16_3 = 1.0f;
}
if (temp_f0_4 < sp20) {
var_f0_12 = sp20 / temp_f0_4;
}
else if (sp20 < -temp_f0_4) {
var_f0_12 = (D_800695D0 - sp38) / temp_f0_4;
}
else {
var_f0_12 = 1.0f;
}
if (var_f16_3 < var_f0_12) {
var_f16_3 = var_f0_12; }
if (temp_f0_4 < sp1C) { var_f0_13 = sp1C / temp_f0_4;
}
else if (sp1C < -temp_f0_4) { var_f0_13 = (D_800695D4 - sp40) / temp_f0_4; }
else {
var_f0_13 = 1.0f;
}
if (var_f16_3 < var_f0_13) {
var_f16_3 = var_f0_13;
}
D_800695CC = sp48 - (sp24 / var_f16_3);
D_800695D0 = sp38 - (sp20 / var_f16_3);
D_800695D4 = sp40 - (sp1C / var_f16_3);
}
if (temp_t2 == 0xB) {
D_800695D8 = 5.0f;
}
else {
temp_f0_5 = (f32) D_800695B0;
if (temp_t2 == 0) {
if (D_800695B4 != 1) {
var_f8_3 = (D_800695D0 - spC0) - ((17920.0f + (((sp9C * sp30) - temp_f0_5) / 4.0f)) / sp30);
goto block_294;
}
var_f14_4 = (f64) ((D_800695D0 - spC0) - ((33280.0f + (((sp9C * sp30) - temp_f0_5) / 4.0f)) / sp30));
}
else if (D_800695B4 != 1) {
var_f14_4 = (f64) ((D_800695E8 - spC0) - ((23040.0f + (((sp9C * sp30) - temp_f0_5) / 4.0f)) / sp30));
}
else { var_f8_3 = (D_800695E8 - spC0) - ((38400.0f + (((sp9C * sp30) - temp_f0_5) / 4.0f)) / sp30);
block_294:
                var_f14_4 = (f64) var_f8_3;
}
sp78 = var_f14_4;
sp90 = var_f16_3;
var_f18_4 = (f64) sqrtf((f32) ((var_f14_4 * var_f14_4) + (f64) (sp9C * sp9C))); if (var_f18_4 < D_80048E88) {
var_f18_4 = D_80048E90;
}
sp90 = var_f16_3;
D_800695D8 = (f32) ((func_8002E150(var_f14_4 / var_f18_4) * D_80048E98) / D_80048EA0);
D_800695D8 = ((D_800695D8 - D_800695C4) / var_f16_3) + D_800695C4;
}
if (temp_a1_2 == 0) {
D_800695DC = D_800695C8;
if ((temp_t2 == 0xB) || (temp_t2 == 2)) {
D_800695D8 = 5.0f;
}
D_800695C4 = D_800695D8;
temp_f2_13 = (f32) D_801D73C7 / 8.0f; D_800695D8 += temp_f2_13;
if (temp_t2 == 0xC) {
D_800695D8 = temp_f2_13 + 3.0f;
}
D_800695B8 = D_800695CC;
D_800695BC = D_800695D0;
D_800695C0 = D_800695D4;
return;
}
if (temp_t2 == 2) {
D_800695CC = D_80048EA8;
D_800695D0 = D_80048EAC;
D_800695D8 = 5.0f;
D_800695DC = 0.0f;
D_800695D4 = D_80048EB0;
}
if (temp_t2 == 0xC) {
if (temp_a1_2 >= 0x1E) {
D_800695DC = (f32) ((s32) ((temp_a1_2 * -0x168) + 0xA8C0) / 90);
D_800695CC = 230.0f - (sinf((f32) (((f64) D_800695DC * D_80048EB8) / D_80048EC0)) * (f32) (((s32) ((D_800698C4 * -0x3E8) + 0x1D4C0) / 90) + 0xC8));
D_800695D4 = (cosf((f32) (((f64) D_800695DC * D_80048EC8) / D_80048ED0)) * (f32) (((s32) ((D_800698C4 * -0x3E8) + 0x1D4C0) / 90) + 0xC8)) + 228.0f;
}
else {
D_800695CC = 230.0f;
D_800695D4 = D_80048ED8;
func_8002D9C4(&D_80044AC8[temp_t5], temp_a1_2, 0x1E, 1);
} D_800695D0 = 146.0f;
D_800695D8 = 3.0f;
D_800695B8 = D_800695CC;
D_800695BC = D_800695D0;
D_800695C0 = D_800695D4;
D_800695C4 = D_800695D8;
D_800695C8 = D_800695DC;
}
else {
D_800695B8 = D_800695CC;
D_800695BC = D_800695D0;
D_800695C0 = D_800695D4;
D_800695C4 = D_800695D8;
D_800695C8 = D_800695DC;
func_8002D9C4(&D_80044AC8[temp_t5], temp_a1_2, 0x50, 0);
} D_800698C4 -= 1;
break;
}
}
