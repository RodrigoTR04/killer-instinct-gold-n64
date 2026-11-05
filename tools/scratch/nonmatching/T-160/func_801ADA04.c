/* T-160 DRAFT: 5 positional words, 208/208 B. Not matching. */
extern void osViBlack(s32);

extern s32 D_80000300, D_801CD4B8, D_801CD4BC;
typedef struct VideoMode { u8 data[0x50];
    } VideoMode;
extern VideoMode D_800066D0[];
extern void osViSetMode(), osViSetSpecialFeatures(u32);
void func_801ADA04(RenderState *arg0)
{
  s32 pending; s32 *pendingp = &D_801CD4BC;
  if (arg0->mode < 14 && D_80000300 != 1) {
    arg0->mode += 14;
  }
  if (D_801CD4B8 != arg0->mode)
  {
    pending = *pendingp;
    if (pending == (-1))
    {
      D_801CD4BC = arg0->mode;
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
