import re,json,pathlib,random
import tu,probe
from reconcile import reconcile
OUT=pathlib.Path(__file__).parent
names='8002AEE4 80017378 8002F45C 80015F6C 8001E0B4 8001AA90 80023EF0 80018F20 80024714 8002B22C 800287D4 80012390 800191F0 8002A4F0 8001BB64 8001D47C'.split()
def parts(s,fn):
 s=re.sub(r'/\*.*?\*/','',s,flags=re.S)
 m=re.search(r'\b'+fn+r'\s*\(',s); start=s.rfind('\n',0,m.start())+1
 return s[:start],s[start:]
def chunks(body):
 toks=re.findall(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[^{};]+|[{};]',body)
 out=[];pending='';depth=0
 for t in toks:
  if t in '{}':
   if pending.strip():out.append(pending.strip());pending=''
   out.append(t)
  elif t==';':
   pending+=';'
   # semicolons in for headers must remain; whitespace still safe
   out.append(pending.strip());pending=''
  else:pending+=' '.join(t.split())
 if pending.strip():out.append(pending.strip())
 return out
def render(cs,mode,rng):
 out=''
 for i,c in enumerate(cs):
  if i:
   prev=cs[i-1]
   sep= '\n' if mode==0 else ' '
   if mode==1:sep='\n' if prev.endswith(';') else ' '
   if mode==2:sep='\n' if c in '{}' or prev in '{}' else ' '
   if mode==3:sep='\n' if prev.endswith(';') or c in '{}' or prev in '{}' else ' '
   if mode>=4:sep='\n' if rng.random()<[.2,.5,.8][(mode-4)%3] else ' '
   out+=sep
  out+=c
 return out+'\n'
results={}
for n in names:
 fn='func_'+n;p=tu.draft(fn);s=reconcile(fn,p.read_text());path,pre=tu.ctx(fn);head,body=parts(s,fn);cs=chunks(body)
 base=probe.probe(fn,pre+'\n'+s);best=base;bs=s;label='baseline';seen=set();scores=[]
 rng=random.Random(71)
 for k in range(160):
  cand=head+render(cs,k if k<4 else 4+(k%3),rng)
  if cand in seen:continue
  seen.add(cand);r=probe.probe(fn,pre+'\n'+cand)
  scores.append(r[0])
  if r[0]<best[0]:best=r;bs=cand;label=str(k);print(fn,k,base,best,flush=True)
  if best[0]==0:break
 (OUT/(fn+'.best.c')).write_text(bs)
 results[fn]={'draft':str(p.relative_to(probe.ROOT)),'tu':str(path.relative_to(probe.ROOT)),'old':base,'new':best,'layout':label,'probes':len(scores),'errors':scores.count(99999)}
 (OUT/'results.json').write_text(json.dumps(results,indent=2)+'\n')
 print(fn,'DONE',results[fn],flush=True)
