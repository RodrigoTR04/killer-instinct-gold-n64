extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern FrontendSettings *D_80292710[];
void func_801C8004(void) {
    s32 conflict;
    s32 i;
    s32 j;
    u8 used;
    s32 button;
    conflict = 0;
    for (i = 0; i < 34; i++) {
        if (D_80292710[0]->bytes[i] != 0 && D_80292710[0]->bytes[i] >= D_802926F8[0][i]) {
            conflict = 1;
        }
    }
    for (i = 0; i < 2; i++) {
        used = 0;
        for (j = 0; j < 6; j++) {
            button = D_80127C68[i].b[j];
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
