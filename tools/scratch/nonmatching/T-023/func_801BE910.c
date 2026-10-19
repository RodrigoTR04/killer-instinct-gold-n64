/* DRAFT. Remaining diff: Score narrowing and loop unrolling/register allocation differ. */
typedef struct { s32 data; s16 score; u16 pad; } T023Entry910;
extern s32 guRandom(void);
extern s32 *D_80282DE8;
void func_801BE910(T023Entry910 *out, s32 count, s16 score, s32 step) {
    s32 index, i;
    s32 *p;
    index = guRandom() % 10;
    p = &D_80282DE8[index];
    for (i = 0; i < count; i++) {
        index++;
        if (index >= 11) { index = 0; p = D_80282DE8; }
        out->score = score;
        score -= step;
        out->data = *p++;
        out++;
    }
}
