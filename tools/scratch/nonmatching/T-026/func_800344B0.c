/* DRAFT. Remaining diff: 23 differing instruction words; emitted 164 / original 164 bytes (positional comparison). */
extern void __osSiGetAccess(void), __osSiRelAccess(void);
extern s32 func_80034554(s32, s32), func_800347D0(void *), func_8003BA08(void *);
extern s8 D_8006F110;
s32 func_800344B0(s32 queue, s32 *pak, s32 channel) {
    s32 result;
    __osSiGetAccess();
    result = func_80034554(queue, channel);
    D_8006F110 = 0xFF;
    __osSiRelAccess();
    if (result != 0) return result;
    pak[1] = queue;
    pak[0] = 0;
    pak[2] = channel;
    result = func_8003BA08(pak);
    if (result != 0) return result;
    result = func_800347D0(pak);
    pak[0] |= 1;
    return result;
}
