/* DRAFT. Remaining diff: Body matches all 348 bytes; missing 4-byte trailing alignment gap shifts following code. */
s32 func_80030EF0(u8 code) {
    s32 character;

    character = code & 0xFF;
    if (character == 0x20) {
        return 0xFF;
    }
    if ((character >= 0x41) && (character < 0x5B)) {
        return character - 0x41;
    }
    if ((character >= 0x61) && (character < 0x7B)) {
        return character - 0x47;
    }
    if (character == 0x2E) {
        return 0x34;
    }
    if ((character >= 0x30) && (character < 0x3A)) {
        return character + 5;
    }
    if (character == 0x2D) {
        return 0x3F;
    }
    if (((character & 1) == 1) && (character >= 0x81) && (character < 0x88)) {
        return 0x40;
    }
    if ((character == 0x82) || (character == 0x86)) {
        return 0x41;
    }
    if ((character == 0x84) || (character == 0x80)) {
        return 0x42;
    }
    if (character == 0x2B) {
        return 0x43;
    }
    if (character == 0x27) {
        return 0x44;
    }
    if (character == 0x2C) {
        return 0x45;
    }
    if (character == 0x2F) {
        return 0x46;
    }
    if (character == 0x89) {
        return 0x47;
    }
    return 0x34;
}
