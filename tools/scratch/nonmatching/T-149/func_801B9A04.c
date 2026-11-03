/* T-132 DRAFT: 406 differing words; see T-132/REPORT.md. */
extern s32 guRandom(void);
extern void guTranslate(void *, f32, f32, f32);
extern void func_8002F6F4(s32, s32, void *);
extern void func_801ADE48(u8, u8, u8, u8);
typedef struct T029Vertex { s16 x, y, z; u16 flag; s16 s, t; u8 r, g, b, a; } T029Vertex;
extern T029Vertex D_802A96E0[], D_802A9E40[];
extern f32 D_801F3640;
extern f64 D_80292B48;
extern s16 D_802C8D12, D_801F35AC;
extern s32 D_802C9F64, D_8004A4B0, D_80066C40;
extern s32 D_801F3D6C, D_801F3D70;
extern u8 D_8004A26C[], D_801F35A4[], D_801F3648[];
extern u8 D_8004AC88, D_8004AC8B, D_80127D50, D_802C8D06;
extern u8 D_802C8CB7[], D_802C8CC8[], D_802C8D0A[], D_80127CE7[];
extern s8 D_801CD454;
s32 func_801B9A04(u32 **arg0, s32 arg1, void *arg2, s32 arg3) {
    f32 radius;
    f32 scale;
    f32 factor;
    s16 size;
    s32 i;
    s32 count;
    s32 timer;
    s32 mode;
    s32 random;
    T029Vertex *dst;
    T029Vertex *src;
    u32 *command;
    dst = D_802A96E0;
    src = D_802A9E40;
    count = 117;
    radius = func_801B1A14(D_801F3640, 5.0f, 200.0f);
    D_802C8D12 += 16;
    for (i = 0; i < count + 1; i++, src++, dst++) {
        if (src->z >= 6) {
            scale = radius / 3.0f;
            factor = scale / 10.0f;
            size = (s32)(factor * 75.0f + 256.0f);
            dst->x = (src->x * size) >> 8;
            dst->a = 0;
            dst->z = (s32)((f64)scale * D_80292B48);
            dst->y = ((src->y * size) >> 8) + (s32)(factor * D_801F3640);
        } else dst->a = D_801F35AC;
    }
    timer = D_802C9F64;
    if (timer >= 21 && D_801F35AC == 0) D_802C9F64 = timer - 20;
    else {
        if (D_801F35AC < 235) {
            D_801F35AC += 20;
            D_801F3640 += 1.0f;
        } else {
            D_801F35AC = 255;
            if (D_801F3640 > 9.0f) D_801F3640 -= 1.0f;
            else if (D_801F3640 < 9.0f) D_801F3640 += 1.0f;
            else if (D_801F3640 == 9.0f) {
                func_8002F6F4(D_80066C40, 0x179, D_8004A26C);
                if (D_8004A407 != 0 && D_80127D50 == 0) D_8004AC88 = D_802C8CB7[D_8004A407];
                else {
                    if (D_802C8D0A[0] != 0) {
                        D_8004AC88 = D_802C8D0A[0] - 1;
                        mode = D_8004A4B0;
                        if (mode == 1) { D_8004A4B0 = 0; mode = 0; }
                    } else if (D_80127D50 == 4) {
                        D_8004AC88 = D_801F35A4[guRandom() % 7];
                        mode = D_8004A4B0;
                    } else {
                        D_8004AC88 = guRandom() % 11;
                        mode = D_8004A4B0;
                    }
                    D_8004AC8B = D_802C8D0A[1];
                    if (mode != 2 && D_802C8D0A[0] == 3 && D_802C8D0A[1] == 3) D_8004A4B0 = 1;
                }
                if (D_802C8D06 & 8) {
                    random = guRandom() % 5;
                    D_802C8CC8[0] = random;
                    D_802C8CC8[1] = random + 1;
                    if (D_8004A407 != 0) D_80127CE7[D_8004A407 * 11] = 10;
                }
                func_801ADE48(D_802C8CB8[0], D_802C8CB8[1], D_802C8CC8[0], D_802C8CC8[1]);
                timer = D_802C9F64;
            }
        }
        if (timer < 470) D_802C9F64 = timer + 10;
        else D_801CD454 = 0;
    }
    D_801F3D6C = 0;
    D_801F3D70 = 639;
    { struct { s16 x, y, z; } position;
      position.x = 2; position.y = 50; position.z = 0;
      guTranslate(arg2, position.x, position.y, position.z); }
    command = *arg0; *arg0 = command + 2;
    command[1] = (u32)D_801F3648; command[0] = 0x06000000;
    return 1;
}
