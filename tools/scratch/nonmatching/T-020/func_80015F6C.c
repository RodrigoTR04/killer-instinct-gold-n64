/* DRAFT T-020: Same size/control flow; v0/v1 and byte temporary register allocation differ. */
extern u8 D_80044E4C[], D_8004ACD0[];
extern s32 D_8004A264, D_8004ACF8, D_80066C40;
extern s16 D_8004A986;
extern void func_8002F8F8(s32, s16 *);
extern void func_8002F6F4(s32, s32, s32 *);
extern s32 func_800326F0(void);

void func_80015F6C(void) {
    s32 timer = D_8004ACF8;
    if (timer < 20 && timer % 10 < 5) {
        D_8004ACD0[1] = 255;
        D_8004ACD0[0] = 255;
        D_8004ACD0[2] = 255;
    } else {
        D_8004ACD0[0] = D_80044E4C[3];
        D_8004ACD0[1] = D_80044E4C[4];
        D_8004ACD0[2] = D_80044E4C[5];
    }
    if (D_8004A986 > 0) {
        D_8004A986--;
        if (D_8004A986 == 1) {
            func_8002F8F8(D_8004A264, &D_8004A986);
            func_8002F6F4(D_80066C40, 0x1A2, &D_8004A264);
            timer = D_8004ACF8;
        }
    }
    if (timer > 0) {
        D_8004ACF8 = timer - 1;
        return;
    }
    D_8004ACF8 = (func_800326F0() & 0x1FF) + 220;
    D_8004A986 = 70;
}
