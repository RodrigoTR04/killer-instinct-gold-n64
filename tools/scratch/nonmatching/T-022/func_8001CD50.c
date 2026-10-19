/* T-022 DRAFT: 104 instruction words differ; compiled 436 bytes, original 460 bytes */
typedef struct {
    s32 unk0; void *data; s16 halfWidth, halfHeight, width, height, width2, height2;
    u8 pad[4]; s16 flags; u8 pad2[2];
} T022Sprite;

extern T022Sprite D_8004CED0[];
extern void func_8001D768(s32 arg0, s32 *arg1);
s32 func_8001CF1C(s8 *, u8 *, s8 *, s32); /* extern */
s32 func_8001D080();                            /* extern */
s32 func_8001D37C(u8, u8);                      /* extern */
extern s32 D_80045C10;
extern u8 *D_80045EA8;
extern s16 D_8004D26E;
extern s8 D_8004D270;
extern s16 D_8004D272;
extern s32 D_8004EA78;
extern s32 D_8004EA88;
extern s32 D_8004EA8C;
extern s32 D_8004EA90;
extern s16 D_8004EA98;
extern s8 D_8004EAA4;
extern u8 *D_8004EAA8;
extern u8 *D_8004EAAC;
extern s8 D_8004EAB8;
extern s8 D_8004EAB9;
extern s8 D_8004EABA;
extern s8 D_8004EABB;
extern s8 D_8004EABC;
extern s8 D_8004EABD;
extern s8 D_8004EABE;
extern s8 D_8004EABF;
extern s8 D_8004EAC0;
extern s32 D_8004F2C8;
extern s16 D_8004F392;
extern s8 D_8004F394;
extern s8 D_8004F395;
extern u8 D_8004F396;
extern s8 D_8004F398;
extern u8 D_800614A0;
extern s32 D_800614C0;
extern s32 D_800614C4;
extern u8 D_8007D900;
extern u8 D_8008EA20;
extern u8 D_8009FB40;
extern u8 D_800B0C60;
extern u8 D_800B94F0;
extern u8 D_800C1D80;
extern u8 D_801265B0;

void func_8001CD50(void) {
    D_800614C4 = 0;
    D_8004EAB8 = 0;
    D_8004F2C8 = 0;
    D_8004D270 = 0;
    D_8004D26E = 0 & 0xFF;
    D_8004F398 = 0;
    D_8004F395 = 0;
    (*(s8 *)((u8 *)(&D_8004F396) + 1)) = 0;
    (*(s8 *)((u8 *)(&D_8004F396) + 0)) = 0;
    D_8004F394 = 0;
    D_8004EAA4 = 0;
    D_8004EA78 = 0;
    D_8004EA90 = 0;
    D_8004EA88 = 1;
    D_800614C0 = 1;
    D_8004D272 = 0;
    D_8004EA8C = 0x1000;
    D_8004EA98 = 0x42;
    D_8004EAB9 = 0;
    D_8004EABD = 0;
    D_8004EABA = 0;
    D_8004EABF = 0xFF;
    D_8004EABE = 0xFF;
    D_8004EABB = 0xFF;
    D_8004EAC0 = 0;
    D_8004EABC = 0;
    D_8004F392 = 0;
    func_8001CF1C(&D_8004F398, &D_8004F396, &D_8004F395, 1);
    func_8001D37C((*(u8 *)((u8 *)(D_8004EA9C) + 0)), (*(u8 *)((u8 *)(D_8004EA9C) + 1)));
    boot_dma(D_80045EA8, &D_800614A0, 0x20);
    D_8004CED0->unk0 = (s32) &D_8007D900;
    D_8004CED0->data = &D_800B0C60;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x1C)) = &D_8008EA20;
    (*(u8 **)((u8 *)(D_8004CED0) + 0x20)) = &D_800B94F0;
    D_8004EAA8 = &D_8009FB40;
    D_8004EAAC = &D_800C1D80;
    func_8001D080();
    func_8001D768(0xA, &D_80045C10);
    (*(u8 **)((u8 *)(D_8004CED0) + 0x1E0)) = &D_801265B0;
}
