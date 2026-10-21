/* T-117: exact 984-byte code candidate; remains asm for constant-pool ownership. */
typedef struct { void *display; s16 flags, pad; s32 transform; } T117B134Part;
extern void *D_8004A4C0[];
extern f32 D_8004A7A0, D_8004A800[], D_8004A8C0[];
extern f32 D_8004ACE0, D_8004ACE4;
extern void func_8001B50C(s32);
extern void func_8001BA18(f32);
extern s32 func_8002FA5C();
extern s32 D_8004A264;
extern s16 D_8004AA2A;

void func_8001B134(s32 arg0, s32 arg1) {
    s32 first;
    s32 second;
    first = ((T117B134Part *)D_8004A4C0)[arg0].transform;
    second = ((T117B134Part *)D_8004A4C0)[arg1].transform;
    if (D_8004A800[first] > 6000.0f) {
        func_8001B620(arg0, arg1);
        return;
    }
    if ((&D_8004A7A0)[first] < 1000.0f) {
        func_8002FA5C(D_8004A264, 8, (s32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3000.0f));
        D_8004AA2A = (u32)((((&D_8004A7A0)[first] + 2000.0f) * 32767.0f) / 3000.0f);
        (&D_8004A7A0)[first] += 30.0f;
        (&D_8004A7A0)[second] += 30.0f;
    } else {
        if (D_8004A8C0[first] < 90.0f) {
            func_8001BA18(0.3f);
        } else {
            func_8001BA18(0.0f);
        }
        if (D_8004A800[first] > 2000.0f) {
            func_8002FA5C(D_8004A264, 8, (s32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f));
            D_8004AA2A = (u32)(((6000.0f - (&D_8004A7A0)[first]) * 32767.0f) / 4000.0f);
        }
        D_8004A8C0[first] += D_8004ACE4;
        D_8004A8C0[second] += D_8004ACE4;
        if (D_8004ACE0 < 50.0f) {
            D_8004ACE0 += 1.0f;
        }
        func_8001B50C(first);
        func_8001B50C(second);
    }
}
