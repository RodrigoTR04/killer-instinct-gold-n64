/* DRAFT. Remaining diff: 46 differing instruction words; emitted 176 / original 188 bytes (positional comparison). */
extern void func_800300DC(u8 *, s32, s32);
extern void func_8002A40C(s32, s32, s32);
s32 func_80030020(u8 *sources, u8 *targets, u8 *lengths, s32 count) {
    s32 i = 0;
    s32 n = count & 0xFFFF;
    if (n > 0) {
        do {
            u16 item = *(u16 *)lengths;
            s32 source = *(s32 *)sources;
            s32 target = *(s32 *)targets;
            s32 kind = item >> 13;
            s32 length = item & 0x1FFF;
            if (kind == 0) func_800300DC((void *)source, target, length);
            else if (kind == 1) func_8002A40C(source, target, length);
            i++;
            sources += 16;
            targets += 16;
            lengths += 4;
        } while (i != n);
    }
}
