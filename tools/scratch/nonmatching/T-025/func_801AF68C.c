/* DRAFT. Remaining diff: Callback dispatch and queue-compaction loop induction/unrolling, stack layout and temporary registers differ. */
typedef struct { u32 w0, w1; } T025GfxF68C;
typedef struct T025EffectF68C T025EffectF68C;
struct T025EffectF68C {
    s32 (*update)(T025GfxF68C **, T025EffectF68C *, void *, s32);
    void *list;
    s32 flags;
    s32 unused;
    s32 start;
    u8 rest[0x54];
};
typedef struct { s32 pad; s32 frame; u8 gap[0xF0]; u8 *matrices; } T025ContextF68C;
extern s32 D_802956F4;
extern T025EffectF68C *D_802A1990[];
extern T025EffectF68C *D_802A1A60[];
extern s32 D_802A1A80;
extern s32 D_802A2178;
void func_801AF68C(T025GfxF68C **arg0, T025ContextF68C *context) {
    T025EffectF68C **p;
    T025EffectF68C *effect;
    T025GfxF68C *g;
    s32 count, i, q, removed, remaining;
    T025EffectF68C **read;
    p = D_802A1990;
    do {
        effect = *p;
        if (effect->flags & D_802A2178) {
            count = 0;
            if (effect->start == -1) effect->start = context->frame;
            if ((*p)->update != 0) {
                count = (*p)->update(arg0, *p, context->matrices + (D_802956F4 << 6), context->frame - (*p)->start);
            }
            if (count != 0 && (*p)->list != 0) {
                g = (*arg0)++;
                g->w0 = 0x01020040;
                g->w1 = (u32)(context->matrices + (D_802956F4 << 6));
                for (i = 1; i < count; i++) {
                    g = (*arg0)++;
                    g->w0 = 0x01000040;
                    g->w1 = (u32)(context->matrices + ((D_802956F4 + i) << 6));
                }
                g = (*arg0)++;
                g->w0 = 0x06000000;
                g->w1 = (u32)(*p)->list;
            }
            D_802956F4 += count;
        }
        p++;
    } while (p != D_802A1990 + 52);
    remaining = D_802A1A80;
    q = 0;
    if (remaining > 0) {
        do {
            removed = 0;
            i = 0;
            read = D_802A1990;
            while (i + q < 52) {
                effect = *read++;
                if (effect == D_802A1A60[q]) {
                    q++;
                    i--;
                    removed++;
                } else if (removed != 0) {
                    D_802A1990[i] = effect;
                }
                i++;
            }
            if (removed != 0) {
                for (i = removed; i > 0; i--) {
                    D_802A1990[52 - i] = D_802A1A60[q - i];
                }
            }
            remaining -= removed;
            D_802A1A80 = remaining;
        } while (remaining > 0);
    }
    D_802A1A80 = 0;
}
