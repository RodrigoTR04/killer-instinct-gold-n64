/* T-095 DRAFT: remaining differences recorded in T-095/REPORT.md. */
typedef struct { u32 w0, w1; } T032Gfx269AC;
extern void func_8001EC74(T032Gfx269AC **, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_8004EA78, D_801D8760, D_801D8764, D_801D8768;
extern u8 D_801D5D50[];
void func_800269AC(T032Gfx269AC **dl)
{
    T032Gfx269AC *environment;
    T032Gfx269AC *p;
    if (D_801D8760)
    {
        if ((D_801D5D50[2] == 0) && (D_801D5D50[1] == 0))
        {
            D_8004EA78 = 30;
        }
        else
        {
            D_8004EA78 = 29;
        }
        p = (*dl)++;
        p->w1 = 0;
        p->w0 = 0xE7000000;
        p = (*dl)++;
        p->w1 = 255;
        p->w0 = 0xFA000100;
        environment = (*dl)++;
        p = environment;
        p->w1 = 0;
        p->w0 = 0xFB000000;
        func_8001EC74(dl, D_801D8760 * 16, D_801D8764 * 16, D_801D8768, D_801D8768, 8, 0, 0);
    }
}
