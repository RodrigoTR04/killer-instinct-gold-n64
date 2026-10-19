/* DRAFT. Remaining diff: main loop matches exactly. The trailing nibble unpack into D_80127D30[0..7] differs: target materialises arg0+1/+2/+3 into v1/a0/a1 and loads at 0(reg), interleaved with the epilogue; this version uses 1(s1)/2(s1)/3(s1). Tried pointer-increment and index loop variants. */
extern u8 D_80127D30;
typedef u8 T034Queue8[8];
#define T034_D_80127D30 (*(T034Queue8 *)&D_80127D30)
extern s32 func_801BF720(s32);
extern u32 D_80127D00[8];
extern u8 D_80127D20[8];
extern u8 D_80127D28[8];

void func_801C8C24(u8 *arg0) {
    s32 i;
    u16 c;
    u32 v;

    for (i = 0; i < 8; i++) {
        c = (arg0[0] << 8) + arg0[1];
        arg0 += 2;
        v = func_801BF720((c >> 10) & 0x1F) << 24;
        v |= func_801BF720((c >> 5) & 0x1F) << 16;
        v |= func_801BF720(c & 0x1F) << 8;
        if (v == 0x20202000) {
            v = 0;
        }
        D_80127D00[i] = v;
        D_80127D20[i] = *arg0++;
        D_80127D28[i] = *arg0++;
    }
    for (i = 0; i < 4; i++) {
        T034_D_80127D30[i * 2] = arg0[i] & 0xF;
        T034_D_80127D30[i * 2 + 1] = arg0[i] >> 4;
    }
}
