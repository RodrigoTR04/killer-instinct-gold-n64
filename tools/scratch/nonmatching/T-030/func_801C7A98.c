/* DRAFT. Remaining diff: Four-way unrolled threshold loop is close; final maximum/mode globals and registers differ. */
#include "common.h"

typedef struct { u8 first, second; } T030Modes7A98;
typedef struct { u8 pad[0x10]; void *text0, *text1; } T030Text7A98;
extern u8 D_80127D58[], D_80127D78[];
extern u8 D_8012834C;
typedef struct { u8 maximum; } T030Result7A98;
extern T030Result7A98 D_802923A0;
extern T030Modes7A98 D_80292674;
extern T030Text7A98 D_80292450;
extern u8 D_802952C4[], D_802952D0[], D_802952D8[];

void func_801C7A98(void) {
    u8 maximum = 0;
    s32 i;
    s32 level;
    u8 value;
    for (i = 0; i < 32; i++) {
        value = D_80127D58[i];
        level = value;
        if (level < 5) level = 0;
        else if (level < 55) level = 1;
        else if (level < 120) level = 2;
        else level = 3;
        if (maximum < level) maximum = level;
    }
    if (D_8012834C >= 2) level = (D_8012834C-1)&255;
    else if (D_8012834C == 1) level = 1;
    else level = 0;
    if (maximum < level) maximum = level;
    level = maximum & 255;
    D_802923A0.maximum = maximum;
    D_80292674.second = 5;
    if (level >= 4) D_80292674.second = 6;
    if (level == 5) {
        D_80292674.first = 5;
        D_80292450.text0 = D_802952C4;
        D_80292450.text1 = D_802952D0;
        return;
    }
    D_80292450.text0 = D_802952D8;
    D_80292674.first = 4;
}
