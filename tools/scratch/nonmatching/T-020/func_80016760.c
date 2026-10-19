/* DRAFT T-020: Loop unrolling is structurally correct; emits two extra lui instructions and shifts following code/data. */
extern u8 D_8004509C[], D_800450A4[], D_8004511C[], D_80045124[];
extern u8 D_8004A730[];
extern u8 D_8004A731, D_8004A732;
extern void func_8001C43C(s32, void *, void *, void *, void *);

void func_80016760(s32 arg0) {
    s32 i;
    func_8001C43C(7, D_8004509C, D_800450A4, D_8004511C, D_80045124);
    for (i = 0; i < 7; i++) {
        D_8004A730[i] = D_8004A730[i] - arg0;
    }
}
