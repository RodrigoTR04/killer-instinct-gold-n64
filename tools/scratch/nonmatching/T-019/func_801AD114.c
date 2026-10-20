/* T-087: nonmatching; verified aligned callback and player-initializer prototypes. */
s32 func_8002FA3C(u8 *);                              void func_801ADC64(s32);                               void func_801ADE48(u8, u8, u8, u8);                        void func_801B3DB0(u8, s32);                         void func_801B4300();                               u8 func_801BFCBC(s32, u64, u8);                              extern u8 D_8004A404;
extern u8 D_8004A407;
extern u8 D_80127D50;
extern s32 D_80295710;
extern u8 D_80295719;
extern u8 D_80295720;

void func_801AD114(s32 arg0, u64 buttons) {
    s32 temp_a0;
    s32 temp_t5;
    s32 temp_v1;
    u8 temp_v0;
    u8 temp_v1_2;

    temp_v0 = func_801BFCBC(arg0, buttons, D_80295719);
    temp_v1 = temp_v0 & 0xFF;
    D_80295719 = temp_v0;
    if (temp_v1 == 4) {
        func_8002FA3C(&D_80295719);
        if (D_80127D50 == 1 || D_80127D50 == 2 || D_8004A404 == 2) {
            D_8004A407 = 0;
            func_801ADC64(0);
            return;
        } else {
            temp_v1_2 = D_80295720;
            if ((arg0 == (2 - temp_v1_2)) && !((arg0 + 1) & D_8004A407)) {
                temp_a0 = temp_v1_2 - 1;
                if (D_8004A407 == 0) {
                    func_801B3DB0(temp_a0 & 0xFF, 1);
                    D_80295710 = 5;
                } else {
                    func_801B4300(temp_a0);
                }
                func_801ADC64(D_80295710);
                D_80295719 = 0;
                return;
            }
            temp_t5 = (temp_v1_2 - 1) & 0xFF;
            if (D_8004A407 != 0) {
                func_801B3DB0(temp_t5, 2);
                D_80295719 = 0;
                return;
            }
            func_801B4300(temp_t5);
            func_801ADC64(0);
            D_80295719 = 0;
            return;
        }
    }
    if ((temp_v1 == 5) || (temp_v1 == 6)) {
        func_8002FA3C(&D_80295719);
        if ((D_80127D50 == 1) || (D_80127D50 == 2)) {
            D_8004A407 &= 0xFB;
            func_801ADE48(0, 0, 1, 2);
            D_80295710 = 0xA;
        } else {
            D_80295710 = 5;
            if (D_8004A407 == 0) {
                if (D_80295720 != 0) {
                    func_801B3DB0((D_80295720 - 1) & 0xFF, 3);
                } else {
                    func_801B3DB0((D_80295719 - 5) & 0xFF, 3);
                    D_8004A407 = 7 - D_80295719;
                }
            } else {
                func_801B3DB0((2 - D_80295720) & 0xFF, 4);
            }
        }
        func_801ADC64(D_80295710);
    }
}
