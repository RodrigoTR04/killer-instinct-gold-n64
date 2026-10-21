import sys,re
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from search import getdraft
OUT=ROOT/'tools/scratch/nonmatching/T-116';res={}
choices={'func_801C8004':'clean-improved','func_801BEEA4':'output-486-1.full','func_801C8AE0':'clean-improved','func_801C48E4':'clean-improved','func_801C7F90':'finalprobe'}
for fn,which in choices.items():
 r=next(r for r in ROWS if r['function']==fn);s=(WORK/(fn+'.'+which+'.c')).read_text();a,b=bodybounds(s,fn);t=s[a:b]
 if fn=='func_801C8004':t=t.replace('new_var','step')
 if fn=='func_801BEEA4':
  t=t.replace('  s32 i;','  s32 i;\n  s32 entryBytes;').replace('      slot = 8;','      entryBytes = sizeof(T023EntryEA4);').replace('&entries[i - 2], slot','&entries[i - 2], entryBytes')
 if fn=='func_801C8AE0':t=t.replace('new_var','lastNibble')
 if fn=='func_801C48E4':t=t.replace('new_var','firstParameter')
 u=s[:a]+t+s[b:];x=compile(fn,u,'retained-cleanup',True);print(fn,x,flush=True);res[fn]=x
 if x.get('words',1000)<r['words']:
  seed=(WORK/(fn+".seed.c")).read_text()
  da,db=bodybounds(seed,fn);ds=seed.rfind("\n",0,seed.rfind(fn,0,da))+1
  ua,ub=bodybounds(u,fn);us=u.rfind("\n",0,u.rfind(fn,0,ua))+1
  d=seed[:ds]+u[us:ub]+"\n"
  # Drop historical draft comments; retain declarations required for full TU checks.
  d=re.sub(r'/\*.*?\*/\s*','',d,flags=re.S).strip()+'\n'
  d='/* T-116 DRAFT: see T-116/REPORT.md for remaining instructions. */\n'+d
  (ROOT/r['draft']).write_text(d)
(OUT/'retained.json').write_text(json.dumps(res,indent=2)+'\n')
