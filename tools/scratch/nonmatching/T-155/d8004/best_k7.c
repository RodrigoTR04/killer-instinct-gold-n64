extern void func_801C7F90(void);
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];

void func_801C8004(void) {
    s32 step = 1;
    u8 *q;
    u8 mask;
    s32 bad = 0;
    FrontendButtonMap *map;
    u8 *cur;
    u8 button;
    s32 i;
    u8 value;
    s32 j;
    cur = D_80292710[0];
    i = 0;
    for (;;) {
        value = *cur;
        if (value != 0 && value >= D_802926F8[0][i]) {
            bad = 1;
        }
        i += step;
        cur += step;
        if (i >= 34) {
            break;
        }
    }
    map = D_80127C68;
    do {
        mask = 0;
        j = 0;
        q = map->b;
        do {
            button = *q;
            j++;
            q++;
            if (button >= 8 || (mask & (1 << button))) {
                bad = 2;
            }
            mask |= 1 << button;
        } while (j != 6);
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
    if (bad) {
        func_801C7F90();
    }
}
