import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_8002F6F4';s=source(fn);a,b,br=extent(s,fn);body=s[a:b];jobs=[]
for member in ['event.id','start.id']:
 t=body.replace('s32 step;','');t=re.sub(r'\bstep\b',member,t);jobs.append(('step-'+member,t))
for order in [0,1]:
 t=body.replace('T024ChainEvent start;\n  T024ChainEvent event;','T024ChainEvent events[2];')
 t=re.sub(r'\bstart\b','events['+str(order)+']',t);t=re.sub(r'\bevent\b','events['+str(1-order)+']',t)
 jobs.append(('event-array-'+str(order),t))
for anchor in ['T024ChainEvent start;','T024ChainEvent event;']:
 t=body.replace('s32 step;','').replace(anchor,anchor+'\n s32 step;');jobs.append(('after-'+anchor,t))
for local in ['step','repeatTime']:
 t=body.replace('s32 '+local+';','struct { s32 value; } '+local+';');t=re.sub(r'\b'+local+r'\b(?!;)',local+'.value',t);jobs.append(('aggregate-'+local,t))
rows=[]
for label,t in jobs:
 r=compile(fn,s[:a]+t+s[b:],label,True);rows.append(r)
 if r.get('words',999)<2:
  p=OUT/(fn+'-stack-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
(OUT/'stack.json').write_text(json.dumps(rows,indent=2))
