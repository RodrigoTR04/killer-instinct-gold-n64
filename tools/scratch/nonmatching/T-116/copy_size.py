import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
fn='func_801BEEA4';s=(WORK/(fn+'.output-486-1.full.c')).read_text();res=[]
for init,name in itertools.product(['8','sizeof(T023EntryEA4)'],['slot','entryBytes']):
 t=s
 if name!='slot':t=t.replace('  s32 i;','  s32 i;\n  s32 entryBytes;').replace('      slot = 8;','      entryBytes = '+init+';').replace('&entries[i - 2], slot','&entries[i - 2], entryBytes')
 x=compile(fn,t,init+name,True);res.append(x);print(x,flush=True)
 if x.get('words')==16 and name!='slot':(WORK/(fn+'.copy-size.c')).write_text(t)
(ROOT/'tools/scratch/nonmatching/T-116/copy-size.json').write_text(json.dumps(res,indent=2)+'\n')
