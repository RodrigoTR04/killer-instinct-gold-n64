/* DRAFT. Remaining diff: Body matches; missing four-byte boundary alignment after the return shifts following code. */
extern s32 D_802A1A60[];
extern s32 D_802A1A80;
void func_801AFA48(s32 arg0) {
    if (D_802A1A80 < 7) {
        D_802A1A60[D_802A1A80] = arg0;
        D_802A1A80++;
    }
}
