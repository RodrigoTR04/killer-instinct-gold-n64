import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
void func_801C8004(void) {
"""
L1={
'ptr':"    for (;;) {\n        value = *cur;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++; cur++;\n        if (i < 34) continue;\n        break;\n    }\n",
'ptr2':"    for (;;) {\n        value = *cur;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        cur++; i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'idx':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'idx2':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i >= 34) break;\n    }\n",
}
L2={
'goto':"""    map = D_80127C68;
    do {
        used = 0; slot = 0; {c} = map->b;
      next:
        button = *{c}; slot++; {c}++;
        if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
        used |= 1 << button;
        if (slot != 6) goto next;
        map++;
    }} while (map != (FrontendButtonMap *)&D_80127C74);
""",
'for':"""    map = D_80127C68;
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
}
tail="    if (conflict != 0) { func_801C7F90(); }\n}\n"
random.seed(int(sys.argv[1]))
cands=[]
for l1 in L1:
 for l2 in L2:
  for cshare in (0,1):
   if l2=='for' and cshare: continue
   for vt in ('u8','s32','u32'):
    for it in ('s32','u32'):
     for bt in ('s32','u32','u8'):
      for rep in range(8):
        c='cur' if cshare else 'q'
        names=['conflict','i','map','slot','used','cur','value','button']+([] if cshare or l2=='for' else ['q'])
        if 'idx' in l1 and cshare: names.remove('cur')
        if rep: random.shuffle(names)
        dd={'conflict':'s32 conflict;','i':f'{it} i;','map':'FrontendButtonMap *map;','slot':'s32 slot;','used':'u8 used;','cur':'u8 *cur;','value':f'{vt} value;','button':f'{bt} button;','q':'u8 *q;'}
        init={'ptr':"conflict = 0; cur = D_80292710[0]; i = 0;",'idx':"conflict = 0; i = 0;"}['ptr' if l1.startswith('ptr') else 'idx']
        init2=init if rep%2==0 else "i = 0; "+init.replace(" i = 0;","")
        s=pre+''.join('    '+dd[n]+'\n' for n in names)+"    "+init2+"\n"+L1[l1]+L2[l2].replace('{c}',c)+tail
        cands.append(((l1,l2,cshare,vt,it,bt,rep),s))
print(len(cands),flush=True)
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r8004_best.c','w').write(res[0][1][1])
