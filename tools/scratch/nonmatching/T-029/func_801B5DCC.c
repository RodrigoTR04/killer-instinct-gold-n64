/* T-111: 155 differing words, 1884 compiled bytes. DRAFT. Remaining diff: Carousel float lifetimes, matrix-call scheduling, frame and temporary registers differ. */
extern void func_801B5534(u8);
extern void func_801B446C(u8);
extern s32 func_801B6528(u32 **, void *, void *, s32);
extern void func_801AFA48(s32);
extern void func_8002F6F4(s32, s32, void *);
extern void guTranslate(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern u8 D_802C8D06, D_802C8CE0, D_802C8C29, D_802C8C2A;
extern u32 D_802C8D1C, D_802C9F74;
extern s32 D_802C8C14, D_80066C40;
extern s8 D_802C8CB9;
extern s16 D_802C8C30[];
extern f32 D_802C8C64[];
extern f64 D_80292B08, D_80292B10;
extern u8 D_8004A260[], D_801F35C0[], D_801F2E80[], D_801F2EB4[];
typedef struct { s32 result; f32 height; f32 rotation; f32 angle; f32 z; } T138CarouselFrame;
typedef struct T029CarouselCard { u8 pad[12]; s32 index; } T029CarouselCard;
s32 func_801B5DCC(u32 **arg0, T029CarouselCard *arg1, u8 *arg2, s32 arg3) {
    f32 next;
    T138CarouselFrame values;
    s32 index;
    s32 circumference;
    s32 state;
    f32 position;
    s16 *record;
    u32 *command;
    state = D_802C8D06;
    values.result = 3;
    if (state == 7 && D_8004A407 != 0 && (D_802C8CE0 & 1) && D_802C8C29 == 0) {
        func_801B5534(1);
        D_8004A407 = 0;
    } else if (D_8004A407 == 2 && !(state & 8)) return func_801B6528(arg0, arg1, arg2, 0);
    if (D_802C8D1C < D_802C9F74) func_801B446C(1);
    index = arg1->index;
    if (index >= D_802C8C2A || ((state = D_802C8D06) & 0x20)) return 0;
    position = index * 70 - D_802C8C14;
    next = D_802C8C2A * 70;
    if (next < position) position -= next;
    else if (position < 0.0f) position += next;
    circumference = D_802C8C2A * 24;
    values.angle = (f64)position * 0.34375;
    if (circumference - 90 < values.angle) values.angle -= circumference;
    else if (values.angle < -D_802C8C2A * 24 + 90) values.angle += circumference;
    if (values.angle > 90.0f || values.angle < -90.0f) return 0;
    record = (s16 *)((u8 *)D_802C8C30 + index * 4);
    values.height = record[1];
    values.z = -10.0f;
    values.rotation = *(f32 *)((u8 *)D_802C8C64 + index * 8);
    if (position >= 0.0f && position < 70.0f) {
        if (values.height < 100.0f) values.height += 5.0f;
        if ((state != 5) * 50 + 5 <= values.height || (D_802C8CE0 & 2)) D_802C8CB9 = index;
        func_801AFA48((s32)arg1);
        next = 8.0f;
        position = 0.0f;
        if (D_802C8CE0 & 2) {
            position += values.rotation;
            values.z += values.rotation / next;
            if (position < 150.0f) { values.rotation += 3.0f; values.height += 5.0f; }
            else values.result = 0;
        }
        record = D_802C8C30 + arg1->index * 2;
        state = D_802C8D06;
    } else if (!(D_802C8CE0 & 2)) {
        if (values.height >= 100.0f || D_80292B08 < values.rotation) {
            next = values.rotation + 16.0f;
            if (D_80292B10 < next) values.rotation = 0.0f;
            else {
                guRotate(arg2 + 0xC0, next, 0.0f, 1.0f, 0.0f);
                values.rotation = next;
                values.result = 4;
                if (values.rotation > 90.0f && values.rotation < 106.0f) func_8002F6F4(D_80066C40, 0x194, D_8004A260);
                else if (values.rotation > 270.0f && values.rotation < 286.0f) func_8002F6F4(D_80066C40, 0x195, D_8004A260);
            }
            record = D_802C8C30 + arg1->index * 2;
            state = D_802C8D06;
        } else values.rotation = 0.0f;
        position = 0.0f;
        if (values.height > 10.0f) values.height -= 10.0f;
        else values.height = 0.0f;
    } else if (values.height < 200.0f) {
        guRotate(arg2 + 0xC0, values.rotation, 1.0f, 0.0f, 0.0f);
        values.height += 6.0f;
        values.rotation += 5.0f;
        values.result = 4;
        position = 0.0f;
        values.z = (values.height * values.height - 100.0f * values.height) / 150.0f;
        record = D_802C8C30 + arg1->index * 2;
        state = D_802C8D06;
    } else values.result = 0;
    record[1] = (s32)values.height;
    D_802C8C64[arg1->index * 2] = values.rotation;
    if (state == 5) return 0;
    guTranslate(arg2, position, 0.0f, values.height - 428.0f + 183.0f);
    guRotate(arg2 + 0x40, values.angle, 0.0f, 1.0f, 0.0f);
    guTranslate(arg2 + 0x80, 0.0f, values.z, 167.0f);
    command = *arg0; *arg0 = command + 2;
    command[1] = (u32)D_801F35C0; command[0] = 0x03800010;
    command = *arg0; *arg0 = command + 2;
    command[1] = (u32)D_801F2E80; command[0] = 0x06000000;
    command = *arg0; *arg0 = command + 2;
    command[0] = 0xFD10002B; command[1] = *(u32 *)(D_801F2EB4 + arg1->index * 140);
    return values.result;
}
