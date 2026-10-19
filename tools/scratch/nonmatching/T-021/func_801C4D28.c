/* DRAFT. Remaining diff: Six float register operands differ (f0/f2/f12 versus f4/f6/f8); same instruction sequence. */
typedef struct { f32 x, y, z; } T021Vec;
extern T021Vec D_80291E8C[], D_802D3990;
extern u8 D_802D3985;
void func_801C4D28(void) {
    T021Vec *p;
    f32 x, y, z;
    p = &D_80291E8C[D_802D3985];
    x = p->x;
    y = p->y;
    z = p->z;
    D_802D3990.x = x;
    D_802D3990.y = y;
    D_802D3990.z = z;
}
