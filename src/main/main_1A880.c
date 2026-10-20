#include "common.h"

extern s32 D_800669A8, D_800669AC, D_800669B0;
extern s32 func_8003278C(void);
void func_8002A1E0(void) {
    s32 i;
    D_800669A8 = 0;
    for (i = 1;
    i <= 16;
    i++) {
        D_800669A8 = (D_800669A8 << 1) + func_8003278C();
    }
    D_800669AC = 0;
    D_800669B0 = 0xFFFF;
}

extern s32 D_80065C80[], D_80066188[], D_800665A0[];
extern u8 D_80066080[];
void func_8002A254(void) {
    s32 i, bit;

    for (i = 0; i < 256; i++) {
        D_80065C80[i] = i + 1;
        D_80066080[i + 1] = i;
    }
    for (i = 0; i < 258; i++) {
        D_800665A0[i] = 1;
        for (bit = 0; bit < 8; bit++) {
            if ((1 << bit) & i) break;
        }
        D_80066188[i] = 1 << bit;
    }
    D_80066188[0] = 257;
    D_800665A0[0] = 0;
}


extern void func_8002A254(void),func_8002A1E0(void),func_80032750(void *);

extern s8 func_800327E8(void *,void *,void *,void *);



void func_8002A300(void *data,s8 *out,s32 count) { s32 i;
 s32 value=0,delta,runLength;
 func_8002A254();
 func_80032750(data);
 func_8002A1E0();
 for(i=0;
i<count;
i++) { delta=func_800327E8(D_80066188,D_800665A0,D_80066080,D_80065C80);
 if(delta==0) { runLength=func_800327E8(D_80066188,D_800665A0,D_80066080,D_80065C80);
 i+=runLength;
 if(runLength>=0) do { runLength--;
 *out++=value;
 } while(runLength>=0);
 } else { value-=delta;
 *out++=value;
 } } }

extern void func_8002A254(void),func_8002A1E0(void),func_80032750(void *);
extern s8 func_800327E8(void *,void *,void *,void *);
extern s32 D_80066188[], D_800665A0[], D_80065C80[];
extern u8 D_80066080[];
void func_8002A40C(u8 *src, s8 *out) {
    s32 size = (src[4] << 24) + (src[5] << 16) + (src[6] << 8) + src[7];
    s32 i;

    src += 8;
    func_8002A254();
    func_80032750(src);
    func_8002A1E0();
    for (i = 0; i < size; i++) {
        *out++ = func_800327E8(D_80066188, D_800665A0, D_80066080, D_80065C80);
    }
}

