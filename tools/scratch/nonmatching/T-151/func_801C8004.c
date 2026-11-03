extern void func_801C7F90();
extern u8 *D_802926F8[];
extern u8 *D_80292710[];

void func_801C8004(void) {
    s32 conflict = 0;
    s32 i;
    s32 map;
    s32 slot;
    u8 used;
    u8 *current = D_80292710[0];

    i = 0;
    for (;;) {
        u8 value = *current;

        if (value != 0 && value >= D_802926F8[0][i]) {
            conflict = 1;
        }
        i++;
        current++;
        if (i >= 34) {
            break;
        }
    }
    for (map = 0; map < 2; map++) {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            s32 button = D_80127C68[map].b[slot];

            if (button >= 8 || ((1 << button) & used)) {
                conflict = 2;
            }
            used |= 1 << button;
        }
    }
    if (conflict != 0) {
        func_801C7F90();
    }
}
