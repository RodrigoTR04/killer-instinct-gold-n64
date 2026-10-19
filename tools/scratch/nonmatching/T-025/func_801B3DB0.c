/* DRAFT. Remaining diff: Typed initialization loops have different induction/unrolling, saved registers and scheduling. */
extern s8 D_8004A407;
extern s32 D_8004A4B0;
extern u8 D_8004EA9C[];
extern u8 D_8004EA9D[];
extern u8 D_8004EA9E;
extern u8 D_8004EA9F;
extern u8 D_80127CCA;
extern u8 D_80127CFE[];
extern u8 D_80127D38;
extern u8 D_8012830A[];
extern u8 D_80128340[];
extern u8 D_8012834B;
extern s8 D_801CD454;
extern s8 D_801F3D64;
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern s32 D_8029571C;
extern s32 D_802C8C08[];
extern s32 D_802C8C10[];
extern s32 D_802C8C18[];
extern f32 D_802C8C20[];
extern u8 D_802C8C28[];
extern u8 D_802C8C2A;
extern s16 D_802C8C30[];
extern f32 D_802C8C60[];
extern u8 D_802C8CB8[];
extern u8 D_802C8CC8[];
extern s32 D_802C8CD4;
extern s32 D_802C8CD8;
extern s32 D_802C8CDC;
extern s8 D_802C8CE0;
extern s16 D_802C8CE2;
extern s16 D_802C8CE4[];
extern s16 D_802C8CE6[];
extern u8 D_802C8CEA[];
extern u8 D_802C8D06;
extern u8 D_802C8D07;
extern u8 D_802C8D0A[];
extern s8 D_802C8D0C;
extern s8 D_802C8D0D;
extern s8 D_802C8D0E;
extern s8 D_802C8D0F;
extern s16 D_802C8D12;
extern s32 D_802C8D14;
extern s32 D_802C8D18;
extern s32 D_802C8D1C;
extern s8 D_802C9F69;
extern s32 D_802C9F74;
extern s32 D_802CA064;

extern void func_801AF5EC(s32);
extern void func_801ADC64(s32);
extern void func_801B446C(u8, s32);
extern void func_801B465C();
extern void func_801B5534(u8, s32);
extern s32 func_801BBC84(void);
void func_801B3DB0(u8 player, s32 mode) {
    u8 kind = mode;
    u8 selection = kind;
    s16 initial = 0;
    f32 position = 0.0f;
    s32 i;
    if (D_8004A4B0 == 2) D_8004A4B0 = 0;
    if (kind == 2) {
        initial = 200;
        D_8012834B++;
        position = 150.0f;
    }
    if (kind == 1) {
        position = 150.0f;
        selection = 2;
        initial = 200;
        kind = 2;
    }
    if (kind == 6 || kind == 7 || kind == 0x40) D_802C8C2A = 10;
    else D_802C8C2A = D_80127D38 + 10;
    if (kind == 0x40) { selection = 8; kind = 8; }
    if (D_8004EA9C[0] >= D_802C8C2A) D_8004EA9C[0] = 0;
    if (D_8004EA9C[1] >= D_802C8C2A) D_8004EA9C[1] = 0;
    D_802C8D06 = selection;
    if (kind == 8) {
        D_802C8D06 = selection | 0x30;
        D_802C8D1C = D_802C9F74 + 0xA00;
    } else D_802C8D1C = D_802C9F74 + 0x500;
    for (i = 0; i < 2; i++) {
        D_802C8C20[i] = 0.0f;
        D_802C8C08[i] = 10;
        D_802C8C28[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        D_802C8C30[i * 2 + player] = initial;
        D_802C8C60[i * 2 + player] = position;
        D_802C8C30[i * 2 + 1 - player] = 0;
        D_802C8C60[i * 2 + 1 - player] = 0.0f;
    }
    func_801AF5EC(0xFFFF);
    func_801AF5D4(0x60);
    func_801ADC64(5);
    D_8029571C = 1;
    selection = D_802C8D06;
    if (selection == 2) {
        D_802C8CE0 = 0;
        func_801B446C(player, 2);
        D_802C8D1C = D_802C9F74 + 0xA00;
    } else D_802C8CE0 = 0;
    D_802C8D12 = kind == 5 ? -80 : 0;
    if (selection == 3 || kind == 5) D_8004A407 = 0;
    else {
        D_8004A407 = 2 - player;
        D_802C8CE2 = D_8012834B * -70 + 1190;
        D_8004EA9D[-player] = D_80128340[D_8012834B];
    }
    if (D_80127CCA != 0 && kind != 2 && D_8012830A[player] >= D_80127CCA) func_801B5534(player, 2);
    if (D_8012830A[player] != 0) D_802C8D07 = player;
    else D_802C8D07 = 255;
    D_802C8CD4 = 0;
    D_802C8CD8 = 0;
    D_802C8CDC = 0;
    D_802C9F69 = 1;
    D_801CD454 = 1;
    D_801F3D64 = -1;
    for (i = 0; i != 50; i++) func_801BBC84();
    D_801F3D64 = 13;
    D_80295700 = 0;
    D_802956FC = 0;
    D_802956F8 = 0;
    D_802C8CE6[-player] = 300;
    D_802C8CE4[player] = 0;
    D_80127CFE[0] = 5;
    D_80127CFE[1] = 5;
    D_802C8D0C = 2;
    D_802C8D0D = 0;
    D_802C8D0E = 0;
    D_802C8C10[0] = D_8004EA9C[0] * 70;
    D_802C8CB8[0] = D_8004EA9C[0];
    D_802C8C18[0] = D_8004EA9C[0];
    D_802C8CC8[0] = D_8004EA9E;
    D_802C8C10[1] = D_8004EA9D[0] * 70;
    D_802C8CB8[1] = D_8004EA9D[0];
    D_802C8C18[1] = D_8004EA9D[0];
    D_802C8CC8[1] = D_8004EA9F;
    func_801B465C(0, 0);
    func_801B465C(1, 0);
    D_802C8D0A[0] = 0;
    D_802C8D0A[1] = 0;
    D_802C8CEA[0] = 0;
    D_802C8CEA[1] = 0;
    D_802C8D14 = 0;
    D_802C8D18 = 0;
    D_802C8D0F = 0;
    D_802CA064 = 479;
}
