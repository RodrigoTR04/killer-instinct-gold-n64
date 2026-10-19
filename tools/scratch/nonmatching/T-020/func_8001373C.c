/* DRAFT T-020: Adds a 0x18-byte stack frame and float spill; float register allocation and field-load scheduling differ. */
typedef struct {
    u8 pad0[0xC];
    f32 x, y, z;
    u8 pad18[0x10];
    s16 vx, vy, vz;
} T020ForceTarget;
extern f32 D_800487F4, D_800487F8;

void func_8001373C(T020ForceTarget *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    f32 dy;
    f32 dz;
    f32 dx;
    f32 distance;
    dx = arg0->x - arg1;
    dy = arg0->y - arg2;
    dz = arg0->z - arg3;
    distance = dx * dx + dy * dy + dz * dz;
    if (distance < D_800487F4) distance = D_800487F8;
    arg0->vx = arg0->vx + (s32)((f32)(arg4 * 30000) / distance);
    arg0->vy = arg0->vy + (s32)((f32)(arg5 * 30000) / distance);
    arg0->vz = arg0->vz + (s32)((f32)(arg6 * 30000) / distance);
}
