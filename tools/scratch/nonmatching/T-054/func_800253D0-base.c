
/* DRAFT. Remaining diff: 214 positional words differ; 1044/1068 bytes */
typedef struct { u32 w0,w1; } T032Gfx253;
typedef struct { u8 pad[0x56]; u16 health; u8 pad58[0x37]; u8 flash; u8 tail[0x70]; } T032HudActor253;
typedef struct { s16 halfW; u8 tail[26]; } T032Half253;
extern T032HudActor253 D_801D3430[];
extern T032Half253 D_8004CED8[];
extern s32 D_8004EA78,D_801D8760;
extern s32 *D_80047D38[];
extern u8 D_80047D60[],D_801D5D50[];
extern u8 D_8004A40C,D_8004D26C,D_801D87FE,D_801D3235,D_801D3335;
extern void func_8001D768(s32,s32 *),func_800257FC(u8,u16,u8,u8);
extern void func_8001EC74(T032Gfx253 **,s32,s32,s32,s32,s32,s32,s32);
extern void func_80025FC4(T032Gfx253 **,s32,s32,u8,u8),func_80026738(T032Gfx253 **),func_800269AC(T032Gfx253 **);
void func_800253D0(T032Gfx253 **arg0) {
    T032Gfx253 *temp_v0;
    T032Gfx253 *temp_v0_10;
    T032Gfx253 *temp_v0_2;
    T032Gfx253 *temp_v0_3;
    T032Gfx253 *temp_v0_4;
    T032Gfx253 *temp_v0_5;
    T032Gfx253 *temp_v0_6;
    T032Gfx253 *temp_v0_7;
    T032Gfx253 *temp_v0_8;
    T032Gfx253 *temp_v0_9;

    if ((D_8004A40C == 0) && (D_801D87FE == 0)) {
        D_8004D26C += 1;
    }
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    temp_v0->w0 = 0x06000000;
    temp_v0->w1 = (u32)&D_80047D60;
    D_8004EA78 = 4;
    func_800257FC((u8)D_8004EA78, D_801D3430[0].health, 0, D_801D3430[0].flash);
    func_8001EC74(arg0, 0x4F000, 0x16000, 0x1000, 0x1000, 0, 0, 0);
    D_8004EA78 = 5;
    func_800257FC((u8)D_8004EA78, D_801D3430[1].health, 1, D_801D3430[1].flash);
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 1;
    temp_v0_2->w1 = 0;
    temp_v0_2->w0 = 0xE7000000;
    func_8001EC74(arg0, 0xF1000, 0x16000, 0x1000, 0x1000, 0, 0, 0);
    if ((D_801D5D50[2] != 0) || ((s32) D_801D5D50[1] >= 6) || ((D_801D5D50[0] & 8) != 8)) {
        temp_v0_3 = *arg0;
        *arg0 = temp_v0_3 + 1;
        temp_v0_3->w1 = 0;
        temp_v0_3->w0 = 0xE7000000;
        temp_v0_4 = *arg0;
        *arg0 = temp_v0_4 + 1;
        temp_v0_4->w1 = (u32)-1;
        temp_v0_4->w0 = 0xFA000100;
        temp_v0_5 = *arg0;
        *arg0 = temp_v0_5 + 1;
        temp_v0_5->w1 = (u32)0xFF80;
        temp_v0_5->w0 = 0xFB000000;
        D_8004EA78 = 6;
        func_8001D768(6, D_80047D38[D_801D5D50[2]]);
        func_8001EC74(arg0, 0x9A000, 0x19000, 0x1000, 0x1000, 7, 0, 0);
        D_8004EA78 = 7;
        func_8001D768(7, D_80047D38[D_801D5D50[1]]);
        temp_v0_6 = *arg0;
        *arg0 = temp_v0_6 + 1;
        temp_v0_6->w1 = 0;
        temp_v0_6->w0 = 0xE7000000;
        func_8001EC74(arg0, 0xAA000, 0x19000, 0x1000, 0x1000, 7, 0, 0);
    }
    temp_v0_7 = *arg0;
    *arg0 = temp_v0_7 + 1;
    temp_v0_7->w1 = 0;
    temp_v0_7->w0 = 0xE7000000;
    temp_v0_8 = *arg0;
    *arg0 = temp_v0_8 + 1;
    temp_v0_8->w0 = 0xFA000100;
    temp_v0_8->w1 = (u32)0xFFFF00FF;
    temp_v0_9 = *arg0;
    *arg0 = temp_v0_9 + 1;
    temp_v0_9->w0 = 0xFB000000;
    temp_v0_9->w1 = (u32)0xA00000FF;
    D_8004EA78 = 8;
    func_8001EC74(arg0, (D_8004CED8[8].halfW * -0x1000) + 0x8F000, 0x23000, 0x1000, 0x1000, 7, 0, 0);
    temp_v0_10 = *arg0;
    *arg0 = temp_v0_10 + 1;
    temp_v0_10->w0 = 0xE7000000;
    temp_v0_10->w1 = 0;
    D_8004EA78 = 9;
    func_8001EC74(arg0, (D_8004CED8[9].halfW << 0xC) + 0xB1000, 0x23000, 0x1000, 0x1000, 7, 0, 0);
    func_80025FC4(arg0, 0x14, 0x1C, 0, (s32) D_801D3235);
    func_80025FC4(arg0, 0xF2, 0x1C, 1, (s32) D_801D3335);
    func_80026738(arg0);
    func_800269AC(arg0);
    if (D_8004A40C == 0) {
        D_801D8760 = 0;
    }
}
