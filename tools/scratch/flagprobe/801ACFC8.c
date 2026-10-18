typedef int s32; typedef unsigned char u8;
int func_801ACB1C(int *, int *, int *);                     /* extern */
extern int D_801ACEC0;
extern int D_801ACF84;
extern int D_801AD568;
extern int D_801C71FC;
extern u8 D_802D39BA;

void func_801ACFC8(void) {
    if (D_802D39BA & 1) {
        func_801ACB1C(&D_801ACEC0, &D_801ACF84, &D_801C71FC);
        return;
    }
    func_801ACB1C(&D_801AD568, &D_801ACF84, &D_801C71FC);
}
