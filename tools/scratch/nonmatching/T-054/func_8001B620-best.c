extern void *D_8004A4C0[];
extern f32 D_8004A740[];
extern f32 D_8004A800[];
extern f32 D_8004A860[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
extern f32 D_8004A7A0;
extern f32 D_8004ACE0;
extern f32 D_8004ACE4;
extern s32 D_8004ACF0;
extern s32 D_8004ACF8;
/* DRAFT. Remaining diff: 87 linked instruction words; compiled 1016 bytes, original 1016 bytes. */

extern f32 D_8004ACE8;
s32 func_8002F6F4(s32, s32, s32 *);         /* extern */
s32 func_8002F8F8(s32);                         /* extern */
s32 func_800326F0(void);                         /* extern */
extern f32 D_800489B8;
extern f32 D_800489BC;
extern f32 D_800489C0;
extern f32 D_800489C4;
extern f32 D_800489C8;
extern f32 D_800489CC;
extern s32 D_8004A264;
extern s32 D_80066C40;
extern f32 D_800695CC;

void func_8001B620(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;
    u8 *sp18;
    s32 var_v0;

    sp18 = (u8 *)D_8004A4C0 + (arg0 * 0xC);
    sp24 = (*(s32 *)((u8 *)(sp18) + 8));
    sp20 = (*(s32 *)((u8 *)(((u8 *)D_8004A4C0 + (arg1 * 0xC))) + 8));
    if (D_8004ACF0 == 2) {
        D_8004ACF0 = func_800326F0() & 3;
    } else {
        D_8004ACF0 = 2;
    }
    if ((D_800489B8 < D_800695CC) && (D_8004ACF0 == 0)) {
        D_8004ACF0 = 2;
    }
    var_v0 = D_8004ACF0;
    if ((D_800695CC < D_800489BC) && (var_v0 == 1)) {
        D_8004ACF0 = 2;
        var_v0 = 2;
    }
    D_8004ACF8 = 0;
    switch (var_v0) {                               /* irregular */
    case 0:
        func_8002F8F8(D_8004A264);
        func_8002F6F4(D_80066C40, 0x1B3, &D_8004A264);
        D_8004A740[sp20] = -200.0f;
        D_8004A740[sp24] = -200.0f;
        (&D_8004A7A0)[sp20] = -2000.0f;
        (&D_8004A7A0)[sp24] = -2000.0f;
        D_8004A800[sp20] = D_800489C0;
        D_8004A800[sp24] = D_800489C0;
        D_8004A860[sp20] = 0.0f;
        D_8004A860[sp24] = 0.0f;
        D_8004A8C0[sp20] = 270.0f;
        D_8004A8C0[sp24] = 270.0f;
        D_8004A920[sp20] = 0.0f;
        D_8004A920[sp24] = 0.0f;
        (*(s16 *)((u8 *)(sp18) + 4)) = 1;
        break;
    case 1:
        func_8002F8F8(D_8004A264);
        func_8002F6F4(D_80066C40, 0x1B3, &D_8004A264);
        D_8004A740[sp20] = D_800489C4;
        D_8004A740[sp24] = D_800489C4;
        (&D_8004A7A0)[sp20] = -2000.0f;
        (&D_8004A7A0)[sp24] = -2000.0f;
        D_8004A800[sp20] = -1000.0f;
        D_8004A800[sp24] = -1000.0f;
        D_8004A860[sp20] = 0.0f;
        D_8004A860[sp24] = 0.0f;
        D_8004A8C0[sp20] = 0.0f;
        D_8004A8C0[sp24] = 0.0f;
        D_8004A920[sp20] = 0.0f;
        D_8004A920[sp24] = 0.0f;
        (*(s16 *)((u8 *)(sp18) + 4)) = 2;
        break;
    default:
    case 2:
        func_8002F8F8(D_8004A264);
        D_8004A740[sp20] = D_800489C8;
        D_8004A740[sp24] = D_800489C8;
        (&D_8004A7A0)[sp20] = -2000.0f;
        (&D_8004A7A0)[sp24] = -2000.0f;
        D_8004A800[sp20] = D_800489CC;
        D_8004A800[sp24] = D_800489CC;
        D_8004A860[sp20] = 0.0f;
        D_8004A860[sp24] = 0.0f;
        D_8004A8C0[sp20] = 0.0f;
        D_8004A8C0[sp24] = 0.0f;
        D_8004A920[sp20] = 0.0f;
        D_8004A920[sp24] = 0.0f;
        (*(s16 *)((u8 *)(sp18) + 4)) = 2;
        break;
    }
    D_8004ACE0 = 0.0f;
    D_8004ACE4 = 0.0f;
    D_8004ACE8 = 0.0f;
}
