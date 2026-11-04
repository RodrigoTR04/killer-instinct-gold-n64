import sys, itertools, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
"""
bodies1={
 'val':"        value = *cur;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n",
 'dir':"        if (*cur != 0 && *cur >= D_802926F8[0][i]) { conflict = 1; }\n",
 'val2':"        value = *cur;\n        if (value != 0) { if (value >= D_802926F8[0][i]) { conflict = 1; } }\n",
 'cmp':"        value = *cur;\n        if (value != 0 && D_802926F8[0][i] <= value) { conflict = 1; }\n",
}
inc1={'ic':"        i++; cur++;\n",'ci':"        cur++; i++;\n"}
seconds={
 'ptrgoto':"""    map = D_80127C68;
    do {
        used = 0; slot = 0; q = map->b;
      next:
        button = *q; slot++; q++;
        if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
        used |= 1 << button;
        if (slot != 6) goto next;
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
""",
 'ptrfor':"""    map = D_80127C68;
    do {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            button = map->b[slot];
            if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
            used |= 1 << button;
        }
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
""",
 'ptrdo':"""    map = D_80127C68;
    do {
        used = 0; slot = 0; q = map->b;
        do {
            button = *q; slot++; q++;
            if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
            used |= 1 << button;
        } while (slot != 6);
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
""",
}
tail="    if (conflict != 0) { func_801C7F90(); }\n}\n"
decl_names={'conflict':'s32 conflict;','i':'s32 i;','map':'FrontendButtonMap *map;','slot':'s32 slot;','used':'u8 used;','cur':'u8 *cur;','value':'u8 value;','q':'u8 *q;','button':'s32 button;'}
cands=[]
random.seed(5)
for b1 in bodies1:
  for ic in inc1:
    for s in seconds:
      for rep in range(6):
        names=list(decl_names); 
        if rep: random.shuffle(names)
        names=[n for n in names if n!='value' or 'value' in bodies1[b1]]
        names=[n for n in names if n not in ('q',) or 'q =' in seconds[s]]
        decl=''.join(decl_names[n] for n in names)
        init="    conflict = 0; cur = D_80292710[0]; i = 0;\n"
        loop="    for (;;) {\n"+bodies1[b1]+inc1[ic]+"        if (i < 34) continue;\n        break;\n    }\n"
        src=pre+"void func_801C8004(void) {\n"+decl+init+loop+seconds[s]+tail
        cands.append(((b1,ic,s,tuple(names)),src))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
res=sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])
seen=set()
for r,(k,s) in res:
    if k[:3] in seen: continue
    seen.add(k[:3]); print(r,k[:3])
open('tools/scratch/nonmatching/T-158/c/best_c.c','w').write(res[0][1][1])
