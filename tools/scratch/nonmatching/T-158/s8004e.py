import sys, itertools, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
exec(open('tools/scratch/nonmatching/T-158/s8004c.py').read().split("tail=")[0].split("import lib")[1])
tail="    if (conflict != 0) { func_801C7F90(); }\n}\n"
random.seed(3)
cands=[]
inits={'c':'conflict = 0;','u':'cur = D_80292710[0];','i':'i = 0;'}
for order in itertools.permutations('cui'):
  for ic in inc1:
    for vt in ('u8','s32','u32'):
      for sep in (0,1):
        for s in seconds:
          cur2='q' if sep else 'cur'
          sec=seconds[s]
          decls={'conflict':'s32 conflict;','i':'s32 i;','map':'FrontendButtonMap *map;','slot':'s32 slot;','used':'u8 used;','cur':'u8 *cur;','value':vt+' value;','q':'u8 *q;','button':'s32 button;'}
          if s=='ptrfor' and sep: continue
          names=['conflict','i','map','slot','used','cur','value','q','button']
          d=''.join(decls[n] for n in names)
          init='    '+' '.join(inits[c] for c in order)+'\n'
          loop="    for (;;) {\n"+bodies1['val']+inc1[ic]+"        if (i < 34) continue;\n        break;\n    }\n"
          src=pre+"void func_801C8004(void) {\n"+d+init+loop+sec+tail
          cands.append(((order,ic,vt,sep,s),src))
print(len(cands))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
res=sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])
for r,(k,s) in res[:8]: print(r,k)
