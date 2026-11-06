typedef struct { u8 kind, pad1[3]; s32 x, y, z;
u8 pad10[0x2A]; u8 hidden, pad3B[0x1D]; u16 strength; u8 pad5A[0x46];
u8 drawn, minimum; u16 override; u8 padA4[0x5C]; } T033EffectObject;
extern T033EffectObject D_801D3430[], D_801D5C30[];
extern u8 D_801D87AC;
extern void func_8002BB74(s32, s32, s32, f32 *, f32 *, f32 *);
extern void func_800297A4(f32, f32, f32, s32, s32, s32);

void func_8001272C(void) {
    s32 kindId, base, div, scale, scaled, wmul, adj;
    f32 z, y, x;
    T033EffectObject *obj;
    s32 product, quot, capped;
    s32 strength, delta, width, intensity; s32 fade; s32 kind;
    kindId = 21; base = 2731; div = 26; scale = 30;
    obj = D_801D3430; do {
        kind = obj->kind; if (kindId == kind && obj->hidden == 0 && obj->drawn == 0) {
            func_8002BB74(obj->x, obj->y, obj->z, &x, &y, &z);
            if (obj->override != 0) strength = obj->override - 4096;
            else strength = obj->strength - 4096;
            if (strength < 0) strength = 0; else if (strength > 4096) strength = 4096;
            if (obj->minimum != 0 && strength < 1280) strength = 1280;
            fade = D_801D87AC; if (fade >= 12) capped = 12; else capped = fade;
            delta = base - strength;
            if (delta > 0) { product = (base - strength) * capped; quot = product / div; strength = quot + strength; }
            wmul = strength * scale; width = wmul / 4096 + 18; if (width < kindId) width = kindId;
            scaled = strength * 6656; intensity = scaled / 4096 + 2560;
            adj = strength / 70; strength = adj + 80; if (strength < 100) strength = 100;
            func_800297A4(x, y, z, strength, width, intensity); obj->drawn = 1;
        } obj++;
    } while (obj != D_801D5C30);
}
