/* DRAFT. Remaining diff: 68 positional differing words; 328/324 bytes */
typedef struct {
    u8 kind;
    u8 pad1[11];
    s32 x;
    u8 pad10[0x44];
    u8 active, pad55, index;
    u8 pad57[0x2D];
    s16 speed;
    u8 pad86[0x7A];
} T033RotatingObject;
typedef struct { f32 pitch, yaw; u8 pad[12]; } T033Rotation;
extern u8 D_8004A9D8;
extern T033RotatingObject D_801D3430[], D_801D5C30[];

void func_80015450(s32 arg0) {
    T033RotatingObject *obj;
    obj = D_801D3430;
    do {
        if (obj->kind == 0x3B) {
            ((T033Rotation *)&D_8004A9D8)[obj->index].yaw = ((T033Rotation *)&D_8004A9D8)[obj->index].yaw + obj->speed / 50.0;
            while (((T033Rotation *)&D_8004A9D8)[obj->index].yaw >= 360.0f) {
                ((T033Rotation *)&D_8004A9D8)[obj->index].yaw -= 360.0f;
            }
            if (obj->active != 0 && ((T033Rotation *)&D_8004A9D8)[obj->index].pitch < 90.0f) ((T033Rotation *)&D_8004A9D8)[obj->index].pitch += 2.0f;
            if (obj->active != 0) {
                if (arg0 < obj->x) obj->x -= 128;
                else if (obj->x < arg0) obj->x = arg0;
            }
        }
        obj++;
    } while (obj != D_801D5C30);
}
