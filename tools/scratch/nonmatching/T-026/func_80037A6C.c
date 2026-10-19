/* DRAFT. Remaining diff: 125 positional words; 500/464 bytes. Original player input in s7; explicit C argument changes ABI and allocation. */
/* Original receives player in s7; use an explicit parameter for that state. */
typedef struct T026TempoEvent { struct T026TempoEvent *next, *prev; s32 delta; s16 type; } T026TempoEvent;
extern void alUnlink(void *), alLink(void *, void *);
extern s32 osSetIntMask(s32);
extern void func_80037A30(f32, void *);
void func_80037A6C(u8 *player, u8 *event) {
    T026TempoEvent *pending = 0;
    T026TempoEvent *node;
    T026TempoEvent *next;
    s32 elapsed = 0;
    s32 oldTempo;
    if (event[8] != 0xFF || event[9] != 0x51) return;
    oldTempo = *(s32 *)(player+0x24);
    func_80037A30((f32)((event[11]<<16)|(event[12]<<8)|event[13]), player);
    node = *(T026TempoEvent **)(player+0x50);
    while (node != 0) {
        next = node->next;
        elapsed += node->delta;
        if (node->type == 0x15) {
            alUnlink(node);
            if (pending != 0) alLink(node, pending);
            else { node->next = 0; node->prev = 0; pending = node; }
            if (next != 0) { elapsed -= node->delta; next->delta += node->delta; }
            node->delta = elapsed;
        }
        node = next;
    }
    node = pending;
    while (node != 0) {
        T026TempoEvent *head = (T026TempoEvent *)(player+0x50);
        s32 mask;
        next = node->next;
        node->delta = *(s32 *)(player+0x24) * (node->delta / oldTempo);
        mask = osSetIntMask(1);
        while (head != 0) {
            T026TempoEvent *following = head->next;
            if (following == 0) { alLink(node, head); break; }
            if (node->delta < following->delta) { following->delta -= node->delta; alLink(node, head); break; }
            node->delta -= following->delta;
            head = head->next;
        }
        osSetIntMask(mask);
        node = next;
    }
}
