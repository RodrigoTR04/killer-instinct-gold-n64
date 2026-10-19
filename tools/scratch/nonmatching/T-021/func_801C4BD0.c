/* DRAFT. Remaining diff: Argument reload/register allocation and one call delay-slot schedule differ. */
extern void func_801C47E0();
extern u8 D_800F4070;
extern u8 D_802D3985;
extern u8 D_802D3986;
extern u8 D_802D399C;
extern s8 D_802D399D;
extern u8 D_802D399E;

void func_801C4BD0(u8 arg0) {
    if (arg0 == 0xC8) {
        func_801C47E0((D_802D3985 + 0x80) & 0xFF, D_802D3986, &D_800F4070, D_802D3985);
    } else {
        func_801C47E0(D_802D3985, D_802D3986, &D_800F4070, arg0);
    }
    D_802D399E = arg0;
    D_802D399C = 0;
    D_802D399D = 1;
}
