/* DRAFT. Remaining diff: Frame is 0x30 instead of 0x28; bank/frame-pointer temporaries and scheduling differ. */
extern void *memcpy(void *, const void *, u32);
extern u8 D_802C8CC8[];
extern u8 D_802C8D08[];
extern u8 D_802C8808[];
typedef struct T029Asset { u8 pad[8]; u8 *frames; } T029Asset;
void func_801B695C(T029Asset *arg0, s32 arg1) {
    u8 *frame;
    s32 offset;
    u8 *bank;
    u8 index;
    u8 toggle;
    if (arg0 != 0 && arg0->frames != 0) {
        index = D_802C8CC8[arg1];
        bank = &D_802C8D08[arg1];
        toggle = *bank ^ 0x40;
        frame = arg0->frames + index * 0x60;
        *bank = toggle;
        if (index < 8) {
            offset = arg1 << 9;
            memcpy(D_802C8808 + (u8)toggle * 2 + offset, arg0->frames, 0x60);
        } else {
            offset = arg1 << 9;
            memcpy(D_802C8808 + *bank * 2 + offset, frame, 0x60);
        }
        memcpy(D_802C8808 + *bank * 2 + offset + 0x100, frame, 0x60);
    }
}
