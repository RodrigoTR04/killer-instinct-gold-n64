extern unsigned char D_8004EA9C[], D_8004EA9E[];
extern void func_801ADC64(int);
void func_801ADE48(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    D_8004EA9C[0] = a;
    D_8004EA9C[1] = b;
    D_8004EA9E[0] = c;
    D_8004EA9E[1] = d;
    func_801ADC64(10);
}
