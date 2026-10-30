/* T-138 DRAFT: 14 differing words, 208/208 B. Not matching. */
extern void osViBlack(s32);

extern s32 D_80000300, D_801CD4B8, D_801CD4BC;
typedef struct VideoMode { u8 data[0x50];
    } VideoMode;
extern VideoMode D_800066D0[];
extern void osViSetMode(), osViSetSpecialFeatures(u32);
void func_801ADA04(RenderState *arg0)
{
  s32 mode = arg0->mode;
  s32 needs_adjustment;
  s32 next;
  s32 pending;
  s32 *pendingp = &D_801CD4BC;
  needs_adjustment = mode < 14;
  if (needs_adjustment != 0)
  {
    next = mode + 14;
    if (D_80000300 != 1)
    {
      arg0->mode = next;
      mode = next;
    }
  }
  if (D_801CD4B8 != mode)
  {
    pending = *pendingp;
    if (pending == (-1))
    {
      D_801CD4BC = mode;
      return;
    }
    D_801CD4BC = pending;
    osViSetMode(&D_800066D0[pending]);
    osViBlack(1);
    osViSetSpecialFeatures(0xAA);
    osViBlack(1);
    D_801CD4B8 = arg0->mode;
    D_801CD4BC = -1;
  }
}
