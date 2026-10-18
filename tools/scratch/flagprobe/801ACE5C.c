typedef int s32; typedef unsigned char u8;
int func_801ACB1C(int *, int *, int *);                     /* extern */
s32 func_801AF67C(int);                               /* extern */
extern int D_801ACE04;
extern int D_801AD568;
extern int D_801B47A4;
extern int D_801BD3FC;

void func_801ACE5C(void) {
    if (func_801AF67C(0x20) != 0) {
        func_801ACB1C(&D_801AD568, &D_801ACE04, &D_801B47A4);
        return;
    }
    func_801ACB1C(&D_801AD568, &D_801ACE04, &D_801BD3FC);
}
