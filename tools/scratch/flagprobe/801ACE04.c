typedef int s32; typedef unsigned char u8;
s32 func_801AF67C(int);                               /* extern */
int func_801AF68C(s32, s32);                          /* extern */
int func_801BBC84();                                  /* extern */
int func_801C3E40(s32);                               /* extern */
extern u8 D_801CD454;

void func_801ACE04(s32 arg0, s32 arg1) {
    if (D_801CD454 != 0) {
        func_801BBC84();
    }
    func_801AF68C(arg0, arg1);
    if (func_801AF67C(4) != 0) {
        func_801C3E40(arg0);
    }
}
