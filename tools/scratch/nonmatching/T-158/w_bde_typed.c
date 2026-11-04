extern u8 D_8004AA28;
void func_8001BF1C(u8 **, s32, s32, f32);
extern u8 D_8004A4C8;
typedef struct { f32 z; f32 y; u8 pad[0x28]; } Item8001;
extern struct { u8 pad[0xF0]; Item8001 items[40]; } D_801D7E00;
void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {
    s32 i; f32 depth; u8 *temp_v1;
    if (D_8004AA28 != 1) {
        temp_v1 = *arg0;
        *arg0 += 8;
        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;
        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
        for (i = 0; i < 40; i++) {
            depth = D_801D7E00.items[i].z * 1500.0f - 590.0f;
            if (depth > arg2) { break; }
            func_8001BF1C(arg0, arg1, i, depth);
        }
        for (i = 39; i >= 0; i--) {
            depth = D_801D7E00.items[i].z * 1500.0f - 590.0f;
            if (depth <= arg2) { break; }
            func_8001BF1C(arg0, arg1, i, depth);
        }
    }
}
