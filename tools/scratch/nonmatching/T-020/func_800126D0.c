/* DRAFT T-020: Loop-bound/base address materialization and register scheduling differ; initial draft also reused bound register for final global store. */
extern void *D_8004A258[];
extern s32 D_8004A280;
extern void func_8002F8F8(void *);

void func_800126D0(void) {
    void **ptr = D_8004A258;
    do {
        if (*ptr != 0) {
            func_8002F8F8(*ptr);
        }
        ptr++;
    } while (ptr != D_8004A258 + 10);
    D_8004A280 = 0;
}
