/* DRAFT. Remaining diff: Input/state reconstruction compiles; loop induction, control flow, frame and registers differ. */
extern void func_801BB7B4(u8);
extern s32 func_801AF67C(s32);
extern void func_801AF5EC(s32);
extern void func_801ADC64(s32);
extern void func_801C7CD0(s32);
extern void func_801B5534(u8);
extern void func_801B4590(u8);
extern void func_801B446C(u8);
extern void func_801B465C(s32, s32);
extern void func_8002F6F4(s32, s32, void *);
extern s32 D_80066C40;
extern u8 D_8004A26C[], D_801F353C[];
extern u16 D_80127CA8[];
extern u8 D_80127CFE[], D_80127CFF[];
extern u8 D_802C8800, D_802C8C28[], D_802C8C29[], D_802C8C2A, D_802C8CC8[];
extern s16 D_802C8C30[], D_802C8CE2;
extern f32 D_802C8C60[], D_802C8C20[];
extern s32 D_802C8C08[], D_802C8C10[], D_802C8C18[];
extern s32 D_802C8CD4, D_802C8CDC, D_802C8D1C;
extern u8 D_802C8CE0, D_802C8D06, D_802C8D0A[], D_802C8D0C, D_802C8D0F;
extern s8 D_802C8CE8, D_802C8D0D, D_802D3A06;
typedef struct T029Input { s32 buttonsHi, buttonsLo; } T029Input;
extern T029Input D_802D3678[];
typedef struct T029Clock { s32 pad; s32 ticks; } T029Clock;
void func_801B47A4(u8 player, s32 hi, s32 lo, T029Clock *clock) {
    s32 bit;
    s32 other;
    s32 i;
    s32 modeBit;
    s32 step;
    s32 position;
    s32 selected;
    s32 circumference;
    u8 *selection;
    u8 phase;
    T029Input *previous;
    func_801BB7B4(player);
    if (!func_801AF67C(0x60)) return;
    bit = 1 << player;
    previous = &D_802D3678[player];
    if (D_802C8CE0 & bit) {
        selection = &D_802C8D0A[player != D_802C8D0C];
        if (D_8004A407 == 0 && *selection == 0) {
            for (i = 0; i < 6; i++) {
                if (D_80127CA8[player * 6 + i] & lo) {
                    D_802C8CDC = D_802C8CD4 + 2;
                    if (lo & 0x800) *selection = (D_801F353C[i] >> 4) + 1;
                    else if ((lo & 0x400) && i != 5) *selection = (D_801F353C[i] & 15) + 1;
                }
            }
        } else if (D_802C8D0F) {
            selection = &D_80127CFF[-player];
            if ((lo & 0x200) && !(previous->buttonsLo & 0x200) && *selection >= 3) {
                D_802C8CDC = D_802C8CD4 + 2; --*selection;
            }
            if ((lo & 0x100) && !(previous->buttonsLo & 0x100) && *selection < 11) {
                D_802C8CDC = D_802C8CD4 + 2; ++*selection;
            }
        }
        if ((lo & 0xD00F) && !(previous->buttonsLo & 0xD00F)) {
            if (D_802C8D0F) D_802C8D0F = 0;
            else D_802C8CE8 = 1;
        }
        previous->buttonsHi = hi; previous->buttonsLo = lo;
        return;
    }
    if (func_801AF67C(0x80)) return;
    if (D_8004A407 & bit) {
        previous->buttonsHi = hi; previous->buttonsLo = lo;
        if (!(lo & 0x1000)) return;
        if (D_802C8D06 == 6) return;
        D_8004A407 ^= bit;
        D_802C8CDC = D_802C8CD4 + 1;
        D_802C8CE2 = 0;
        if (D_802C8D06 & 8) {
            D_802C8D06 |= 0x10 << player;
            D_802C8D0F = 0;
            D_802C8D1C = clock->ticks + 0xA00;
        } else {
            other = 1 - player;
            if (D_802C8CE0 & (1 << other)) {
                for (i = 0; i < 11; i++) {
                    D_802C8C30[i * 2 + other] = 0;
                    D_802C8C60[i * 2 + other] = 0.0f;
                }
                D_802C8C29[-player] = 0;
                D_802C8CE0 = 0;
            }
            D_802C8D0D = 0;
            D_802C8D1C = clock->ticks + 0x500;
        }
        func_8002F6F4(D_80066C40, 8, D_8004A26C);
    }
    if (((lo & 0x2000) && D_802C8CE0 != 3 && (D_802C8D06 == 6 || D_802C8D06 == 7 || (D_802C8D06 & 8) || D_8012834B == 0)) || (D_802C8D06 == 5 && (lo & 0x6000))) {
        func_801AF5EC(0xFFFF);
        if (D_802C8D06 == 5) {
            if (lo & 0x4000) { D_802D3A06 = 1; func_801ADC64(2); }
            else { func_801C7CD0(4); func_801ADC64(9); }
        } else func_801ADC64(0);
        previous->buttonsHi = hi; previous->buttonsLo = lo;
        return;
    }
    modeBit = 0x10 << player;
    if (!(D_802C8D06 & modeBit)) {
        if ((lo & 0x300) != (previous->buttonsLo & 0x300)) {
            D_802C8C20[player] = 0.0f;
            if (hi == 0 && lo == 0) D_802C8C08[player] = 10;
        }
        phase = D_802C8C28[player];
        if (phase == 0) {
            if ((lo & 0x100) && !(lo & 0x200)) {
                if (D_802C8C20[player] > 0.0f) D_802C8C20[player] -= 1.0f;
                else { D_802C8C18[player]++; D_802C8C20[player] = D_802C8C08[player] - 1; D_802C8C08[player] = 7; }
            }
            if ((lo & 0x200) && !(lo & 0x100)) {
                if (D_802C8C20[player] < 0.0f) D_802C8C20[player] += 1.0f;
                else { D_802C8C18[player]--; D_802C8C20[player] = 1 - D_802C8C08[player]; D_802C8C08[player] = 7; }
            }
            selected = D_802C8C18[player];
            position = D_802C8C10[player];
            step = (D_802C8C08[player] / 2 + 70) / D_802C8C08[player];
            if (position < selected * 70 - step) position += step;
            if (selected * 70 < position) position -= step;
            D_802C8C10[player] = position;
            circumference = D_802C8C2A * 70;
        } else {
            step = (D_802C8C08[player] / 2 + 70) / D_802C8C08[player];
            position = D_802C8C10[player] + step;
            circumference = D_802C8C2A * 70;
            if (position >= circumference) position -= circumference;
            D_802C8C10[player] = position;
            selected = D_802C8C18[player];
            if (selected * 70 < position && position < selected * 70 + 70) D_802C8C28[player] = phase | 4;
            else D_802C8C28[player] = phase & ~4;
            switch (D_802C8C28[player]) {
                case 5: D_802C8C28[player]++; break;
                case 2: D_802C8C28[player]++;
                case 3: D_802C8C08[player] = 12 - (D_802C8C2A + selected - position / 70) % D_802C8C2A; break;
                case 7:
                    func_801B446C(player);
                    D_802C8C28[player] = 0;
                    position = D_802C8C10[player] - (D_802C8C08[player] / 2 + 70) / D_802C8C08[player];
                    D_802C8C10[player] = position;
                    circumference = D_802C8C2A * 70;
                    selected = D_802C8C18[player];
                    break;
            }
        }
        if (selected < 0) { position += circumference; D_802C8C18[player] = selected + D_802C8C2A; }
        else if (selected >= D_802C8C2A) { position -= circumference; D_802C8C18[player] = selected - D_802C8C2A; }
        if (position >= circumference) position = circumference;
        else if (position < -69) position = -69;
        D_802C8C10[player] = position;
    } else {
        selection = &D_80127CFE[player];
        if ((lo & 0x200) && !(previous->buttonsLo & 0x200) && *selection >= 3) { D_802C8CDC = D_802C8CD4 + 2; --*selection; }
        if ((lo & 0x100) && !(previous->buttonsLo & 0x100) && *selection < 11) { D_802C8CDC = D_802C8CD4 + 2; ++*selection; }
    }
    if (D_802C8800 < 40) D_802C8800++;
    else if (D_802C8C28[player] == 0) {
        if ((lo & 0xD00F) && !(previous->buttonsLo & 0xD00F)) {
            if (D_802C8D06 & modeBit) D_802C8D06 ^= modeBit;
            else if (!(D_802C8CE0 & bit)) {
                if ((lo & 0x1800) == 0x1800) func_801B5534(player);
                else if ((lo & 0x1400) == 0x1400) func_801B4590(player);
                else func_801B446C(player);
            }
        } else if (!(lo & 0x800) && (previous->buttonsLo & 0x800)) {
            D_802C8CC8[player]++;
            if (D_802C8CC8[player] >= func_801B4324(player) + 7) D_802C8CC8[player] = 0;
            func_801B465C(player, 1);
        } else if (!(lo & 0x400) && (previous->buttonsLo & 0x400)) {
            i = D_802C8CC8[player];
            D_802C8CC8[player] = i - 1;
            if (i <= 0) D_802C8CC8[player] = func_801B4324(player) + 6;
            func_801B465C(player, -1);
        }
    }
    previous->buttonsHi = hi; previous->buttonsLo = lo;
}
