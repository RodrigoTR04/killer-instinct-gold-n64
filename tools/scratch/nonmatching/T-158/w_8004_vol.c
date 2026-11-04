extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *volatile D_802926F8[];
extern FrontendSettings *D_80292710[];
void func_801C8004(void) {
    s32 conflict;
    s32 i;
    FrontendButtonMap *map;
    s32 slot;
    u8 used;
    s32 button;
    u8 value;
    conflict = 0;
    i = 0; for (;;) {
        value = D_80292710[0]->bytes[i];
        if (value != 0 && value >= D_802926F8[0][i]) {
            conflict = 1;
        }
        i++;
        if (i < 34) {
            continue;
        }
        break;
    }
    map = D_80127C68; do {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            button = map->b[slot];
            if (button >= 8 || ((1 << button) & used)) {
                conflict = 2;
            }
            used |= 1 << button;
        }
        map++;
    }
    while (map != (FrontendButtonMap *)&D_80127C74);
    if (conflict != 0) {
        func_801C7F90();
    }
}
