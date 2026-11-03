import sys, itertools
sys.path.insert(0,'.')
import lib
H = """extern void osViBlack(s32);
extern s32 D_80000300, D_801CD4B8, D_801CD4BC;
typedef struct VideoMode { u8 data[0x50]; } VideoMode;
extern VideoMode D_800066D0[];
extern void osViSetMode(), osViSetSpecialFeatures(u32);
"""
cands=[]
for na, cmpo, nxt, pend, ptrstyle, tail in itertools.product([0,1],[0,1],[0,1],[0,1],[0,1,2],[0,1]):
    L=["void func_801ADA04(RenderState *arg0)","{","  s32 mode = arg0->mode;"]
    if na: L.append("  s32 needs_adjustment;")
    if nxt: L.append("  s32 next;")
    if pend: L.append("  s32 pending;")
    if ptrstyle: L.append("  s32 *pendingp = &D_801CD4BC;")
    rd = "*pendingp" if ptrstyle else "D_801CD4BC"
    if na:
        L.append("  needs_adjustment = mode < 14;")
        cond = "needs_adjustment != 0"
    else: cond = "mode < 14"
    L.append("  if (%s)"%cond); L.append("  {")
    if nxt:
        L += ["    next = mode + 14;","    if (D_80000300 != 1)","    {","      arg0->mode = next;","      mode = next;","    }"]
    else:
        L += ["    if (D_80000300 != 1)","    {","      mode += 14;","      arg0->mode = mode;","    }"]
    L.append("  }")
    L.append("  if (%s)"%("D_801CD4B8 != mode" if cmpo==0 else "mode != D_801CD4B8"))
    L.append("  {")
    if pend:
        L.append("    pending = %s;"%rd); p="pending"
    else: p=rd
    L += ["    if (%s == (-1))"%p,"    {","      %s = mode;"%("D_801CD4BC" if ptrstyle!=2 else "*pendingp"),"      return;","    }","    %s = %s;"%("D_801CD4BC" if ptrstyle!=2 else "*pendingp",p),"    osViSetMode(&D_800066D0[%s]);"%p,"    osViBlack(1);","    osViSetSpecialFeatures(0xAA);","    osViBlack(1);","    D_801CD4B8 = arg0->mode;","    %s = -1;"%("D_801CD4BC" if ptrstyle!=2 else "*pendingp"),"  }","}"]
    cands.append(((na,cmpo,nxt,pend,ptrstyle),"\n".join(L)+"\n"))
res=lib.run('func_801ADA04',[H+s for _,s in cands],prefix=False)
rows=sorted([(r,c) for (c,_),r in zip(cands,res) if r and c[0]==0],key=lambda t:(t[0][1],t[0][0]))
for r,c in rows[:6]: print(r,c)
