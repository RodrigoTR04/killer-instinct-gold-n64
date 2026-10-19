/* DRAFT. Remaining diff: 41 differing instruction words; emitted 176 / original 188 bytes (positional comparison). */
typedef struct { s16 buttons; s8 stick; u8 error; } T026Controller;
typedef struct { u8 bytes[8]; } T026ControllerReply;
extern u8 D_8006F080[];
extern u8 D_8006F111;
void func_800343F4(s8 *mask, T026Controller *out) {
    T026ControllerReply reply;
    T026ControllerReply *input = (T026ControllerReply *)D_8006F080;
    s8 present = 0;
    s32 i = 0;
    if (D_8006F111 > 0) {
        do {
            reply = *input++;
            out->error = (reply.bytes[2] & 0xC0) >> 4;
            if (!out->error) {
                out->buttons = (reply.bytes[5] << 8) | reply.bytes[4];
                present = (present | (1 << i)) & 0xFF;
                out->stick = reply.bytes[6];
            }
            i++;
            out++;
        } while (i < D_8006F111);
    }
    *mask = present;
}
