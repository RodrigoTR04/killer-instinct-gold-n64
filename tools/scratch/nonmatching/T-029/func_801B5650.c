/* T-111: 31 differing words, 1920 compiled bytes. DRAFT. Remaining diff: Carousel float lifetimes, matrix-call scheduling, frame and temporary registers differ. */
extern void func_801B5534(u8);
extern void func_801B446C(u8);
struct T029Gfx801B6528;
extern s32 func_801B6528(struct T029Gfx801B6528 **, void *, void *, s32);
extern void func_801AFA48(s32);
extern void func_8002F6F4(s32, s32, void *);
extern void guTranslate(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern u8 D_802C8D06, D_802C8CE0, D_802C8C28, D_802C8C2A;
extern u32 D_802C8D1C, D_802C9F74;
extern s32 D_802C8C10, D_80066C40;

typedef struct { s16 left, right; } CardHeights;
extern CardHeights D_802C8C30[];
extern f32 D_802C8C60[];
extern f64 D_80292AF8, D_80292B00;
extern u8 D_8004A25C[], D_801F35B0[], D_801F2E80[], D_801F2EB4[];
typedef struct T029LeftCard { u8 pad[12]; s32 index; } T029LeftCard;
s32 func_801B5650(u32 **arg0, T029LeftCard *arg1, u8 *arg2, s32 arg3) {
    f32 position, z, angle, height, rotation;
    s32 result;
    s32 index;
    s32 circumference;
    s32 state;
    CardHeights *record;
    u32 *command;
    state = D_802C8D06;
    result = 3;
    if (state == 7 && D_8004A407 != 0 && (D_802C8CE0 & 2) && D_802C8C28 == 0) {
        func_801B5534(0);
        D_8004A407 = 0;
    } else if (D_8004A407 == 1 && !(state & 8)) return func_801B6528((struct T029Gfx801B6528 **)arg0, arg1, arg2, 1);
    if (D_802C8D1C < D_802C9F74) func_801B446C(0);
    index = arg1->index;
    if (index >= D_802C8C2A || ((state = D_802C8D06) & 0x10)) return 0;
    position = index * 70 - D_802C8C10;
    rotation = D_802C8C2A * 70;
    if (rotation < position) position -= rotation;
    else if (position < 0.0f) position += rotation;
    circumference = D_802C8C2A * 24;
    angle = (f64)position * 0.34375;
    if (circumference - 90 < angle) angle -= circumference;
    else if (angle < -D_802C8C2A * 24 + 90) angle += circumference;
    if (angle > 90.0f || angle < -90.0f) return 0;
    record = &D_802C8C30[index];
    height = record->left;
    z = -10.0f;
    rotation = *(f32 *)((u8 *)D_802C8C60 + index * 8);
    if (position >= 0.0f && position < 70.0f) {
        f32 next;
        if (height < 100.0f) height += 5.0f;
        if ((state != 5) * 50 + 5 <= height || (D_802C8CE0 & 1)) D_802C8CB8[0] = index;
        func_801AFA48((s32)arg1);
        next = 8.0f;
        position = 0.0f;
        if (D_802C8CE0 & 1) {
            position -= rotation;
            z += rotation / next;
            if (position > -150.0f) { rotation += 3.0f; height += 5.0f; }
            else result = 0;
        }
        record = &D_802C8C30[arg1->index];
        state = D_802C8D06;
    } else if (!(D_802C8CE0 & 1)) {
        if (height >= 100.0f || D_80292AF8 < rotation) {
            rotation += 16.0f;
            if (D_80292B00 < rotation) rotation = 0.0f;
            else {
                guRotate(arg2 + 0xC0, rotation, 0.0f, 1.0f, 0.0f);
                result = 4;
                if (rotation > 90.0f && rotation < 106.0f) func_8002F6F4(D_80066C40, 0x194, D_8004A25C);
                else if (rotation > 270.0f && rotation < 286.0f) func_8002F6F4(D_80066C40, 0x195, D_8004A25C);
            }
            record = &D_802C8C30[arg1->index];
            state = D_802C8D06;
        } else rotation = 0.0f;
        position = 0.0f;
        if (height > 10.0f) height -= 10.0f;
        else height = 0.0f;
    } else if (height < 200.0f) {
        guRotate(arg2 + 0xC0, rotation, 1.0f, 0.0f, 0.0f);
        rotation += 5.0f;
        height += 6.0f;
        result = 4;
        position = 0.0f;
        z = (height * height - 100.0f * height) / 150.0f;
        record = &D_802C8C30[arg1->index];
        state = D_802C8D06;
    } else result = 0;
    record->left = (s32)height;
    index = arg1->index;
    D_802C8C60[index * 2] = rotation;
    if (state != 5) {
    guRotate(arg2 + 0x40, angle, 0.0f, 1.0f, 0.0f);
    guTranslate(arg2 + 0x80, 0.0f, z, 167.0f);
    guTranslate(arg2, position, 0.0f, height - 428.0f + 183.0f);

    command = *arg0; *arg0 = command + 2;
    command[0] = 0x03800010; command[1] = (u32)D_801F35B0;
    command = *arg0; *arg0 = command + 2;
    command[0] = 0x06000000; command[1] = (u32)D_801F2E80;
    command = *arg0; *arg0 = command + 2;
    command[0] = 0xFD100000; command[1] = *(u32 *)(D_801F2EB4 + arg1->index * 140);
    return result;
    }
    return 0;
}
