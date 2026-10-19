/* DRAFT. Remaining diff: 71 differing instruction words; emitted 404 / original 416 bytes (positional comparison). */
extern s32 func_8003BC0C(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_80034630(u8 *pak, s32 company, s32 game, u8 *name, u8 *extension, s32 *file) {
    u8 entry[32];
    s32 index;
    s32 result;
    if (func_8003BC0C(pak) == 2) return 2;
    for (index = 0; index < *(s32 *)(pak + 0x50); index++) {
        s32 different = 0;
        result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), (*(s32 *)(pak + 0x5C) + index) & 0xFFFF, entry);
        if (result != 0) return result;
        if ((company & 0xFFFF) == *(u16 *)(entry + 4) && *(s32 *)entry == game) {
            s32 i;
            if (name != 0) for (i = 0; i < 16; i++) if (entry[16+i] != name[i]) { different = 1; break; }
            if (extension != 0 && different == 0) for (i = 0; i < 4; i++) if (entry[12+i] != extension[i]) { different = 1; break; }
            if (different == 0) { *file = index; return result; }
        }
    }
    *file = -1;
    return 5;
}
