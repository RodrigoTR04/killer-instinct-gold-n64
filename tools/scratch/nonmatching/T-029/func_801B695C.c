/* DRAFT (T-044). Remaining diff: 4 relocation-masked instruction words; see T-044/REPORT.md. */
extern void *memcpy(void *, const void *, u32);
extern u8 D_802C8CC8[];
extern u8 D_802C8D08[];
extern u8 D_802C8808[][512];
typedef struct T029Asset { u8 pad[8]; u8 *frames; } T029Asset;
void func_801B695C(T029Asset *arg0, s32 arg1) {
    s32 offset;

    u8 *bank;

    u8 *frame;

    if (arg0 != 0 && arg0->frames != 0) {
        offset = D_802C8CC8[arg1];
        bank = &D_802C8D08[arg1];

        frame = (offset * 3 << 5) + arg0->frames;
        *bank ^= 0x40;
        if (offset < 8) {
            offset = arg1 << 9;
            memcpy((u8 *)D_802C8808 + *bank * 2 + offset, arg0->frames, 0x60);
        } else {
            offset = arg1 << 9;
            memcpy((u8 *)D_802C8808 + *bank * 2 + offset, frame, 0x60);
        }
        memcpy((u8 *)D_802C8808 + *bank * 2 + offset + 0x100, frame, 0x60);
    }
}
