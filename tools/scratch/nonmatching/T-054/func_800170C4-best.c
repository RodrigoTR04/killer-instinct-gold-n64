
/* DRAFT. Remaining diff: 266 positional differing words; 1084/692 bytes */
typedef struct { u8 kind, pad1[0x53]; s16 speed; u8 pad56[0xAA]; } T033170C4Object;
typedef union { s32 words[4]; u8 bytes[16]; } T033170C4Vertex;
typedef struct { void *display; s16 flags, pad; s32 transform; } T033170C4StagePart;
typedef struct { f32 pitch, yaw, roll, speed, scale; } T033170C4StageRotation;
extern u8 D_80045030;
extern T033170C4Vertex *D_80045060;
extern T033170C4Vertex *D_80045064;
extern T033170C4Vertex *D_80045068;
extern void *D_8004A4C0[];
extern f32 D_8004A740[];
extern u8 D_8004AC8D;
extern T033170C4Vertex D_8004AD28;
extern T033170C4Vertex D_8004ADE8;
extern T033170C4Vertex D_8004ADF8;
extern T033170C4Vertex D_8004AE08;
extern T033170C4Vertex D_8004AE18;
extern T033170C4Vertex D_8004AE28;
extern T033170C4Vertex D_8004AE38;
extern T033170C4Vertex D_8004AEB8;
extern u8 D_801939F0;
extern s32 D_801C4234;
extern s32 D_801C4334;
extern T033170C4Object D_801D3430;
extern T033170C4Object D_801D5C30;
extern u8 D_801D7DF7;
extern void func_8001C370(f32,f32,void *,s32,s32,void *);

extern f32 D_8004A920[];
void func_800170C4(void) {
    T033170C4Vertex *var_a0;
    T033170C4Vertex *var_a1;
    T033170C4Vertex *var_a2;
    T033170C4Object *var_v0_2;
    T033170C4Vertex *var_v1;
    s32 temp_t4;
    T033170C4Vertex **var_v0;
    T033170C4Vertex *temp_t6;
    T033170C4Vertex *temp_t6_2;
    T033170C4Vertex *temp_t7;
    T033170C4Vertex *temp_t9;

    if (D_801D7DF7 == 1) {
        D_8004AC8D = 1;
    }
    if (D_8004AC8D == 1) {
        D_8004AC8D = 2;
        ((T033170C4StagePart *)D_8004A4C0)[6].display = 0;
        ((T033170C4StagePart *)D_8004A4C0)[0].display = &D_801939F0;
        D_801C4234 = 0x1F0A5;
        D_801C4334 = 0x210D7;
        D_80045060[0].words[0] = (s32) D_8004ADE8.words[0];
        D_80045060[0].words[1] = (s32) D_8004ADE8.words[1];
        D_80045060[0].words[2] = (s32) D_8004ADE8.words[2];
        D_80045060[0].words[3] = (s32) D_8004ADE8.words[3];
        D_80045064[0].words[0] = (s32) D_8004ADF8.words[0];
        var_a2 = &D_8004AE28;
        var_a1 = &D_8004AE18;
        D_80045064[0].words[1] = (s32) D_8004ADF8.words[1];
        var_a0 = &D_8004AE08;
        var_v1 = &D_8004AE38;
        D_80045064[0].words[2] = (s32) D_8004ADF8.words[2];
        var_v0 = &D_80045068;
        D_80045064[0].words[3] = (s32) D_8004ADF8.words[3];
        do {
            temp_t6 = *var_v0;
            var_v1 += 4;
            var_v0 += 4;
            temp_t6[0].words[0] = (s32) var_a0[0].words[0];
            temp_t4 = var_a0[0].words[1];
            var_a0 += 4;
            var_a1 += 4;
            temp_t6[0].words[1] = temp_t4;
            var_a2 += 4;
            temp_t6[0].words[2] = (s32) var_a0[-4].words[2];
            temp_t6[0].words[3] = (s32) var_a0[-4].words[3];
            temp_t7 = var_v0[-3];
            temp_t7[0].words[0] = (s32) var_a1[-4].words[0];
            temp_t7[0].words[1] = (s32) var_a1[-4].words[1];
            temp_t7[0].words[2] = (s32) var_a1[-4].words[2];
            temp_t7[0].words[3] = (s32) var_a1[-4].words[3];
            temp_t9 = var_v0[-2];
            temp_t9[0].words[0] = (s32) var_a2[-4].words[0];
            temp_t9[0].words[1] = (s32) var_a2[-4].words[1];
            temp_t9[0].words[2] = (s32) var_a2[-4].words[2];
            temp_t9[0].words[3] = (s32) var_a2[-4].words[3];
            temp_t6_2 = var_v0[-1];
            temp_t6_2[0].words[0] = (s32) var_v1[-4].words[0];
            temp_t6_2[0].words[1] = (s32) var_v1[-4].words[1];
            temp_t6_2[0].words[2] = (s32) var_v1[-4].words[2];
            temp_t6_2[0].words[3] = (s32) var_v1[-4].words[3];
        } while (var_v1 != &D_8004AEB8);
    }
    var_v0_2 = &D_801D3430;
    do {
        if (var_v0_2->kind == 0x3C) {
            D_8004A920[0] -= (f32) var_v0_2->speed / 200.0f;
            if (D_8004A920[0] > 20.0f) {
                D_8004A920[0] = 20.0f;
            } else if (D_8004A920[0] < -20.0f) {
                D_8004A920[0] = -20.0f;
            }
            var_v0_2->speed = (s16) (s32) ((f32) var_v0_2->speed + ((D_8004A920[0] * 256.0f) / 200.0f));
        }
        var_v0_2++;
    } while ((u8 *)var_v0_2 != (u8 *)&D_801D5C30);
    func_8001C370(20.0f, -20.0f, &D_80045030, 0xC, 0x3F, &D_8004AD28);
}
