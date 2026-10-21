"""Safe coordinate-storage probes. No build/source mutations; explicit --apply retains improvements."""
from pathlib import Path
import sys,re,json,itertools
sys.path.insert(0,str(Path(__file__).resolve().parent))
from probe import probe
from analyze import NAMES
OUT=Path('/tmp/kig-t106-coords');OUT.mkdir(exist_ok=True)
def splitargs(s):
 depth=0;args=[];start=0
 for i,c in enumerate(s):
  if c=='(':depth+=1
  elif c==')':depth-=1
  elif c==',' and depth==0:args.append(s[start:i].strip());start=i+1
 return args+[s[start:].strip()]
def calls(s):
 result=[]
 for m in re.finditer(r'    func_801BC1B0\(',s):
  end=s.index(';',m.end());result.append((m.start(),end,splitargs(s[m.end():end-1])))
 return result
def variants(s):
 cs=calls(s);a=cs[0][2];b=cs[1][2]
 strip=lambda x: re.sub(r'^\(f32\)\s*','',x).strip()
 x0,x1,y1=strip(a[11]),strip(b[11]),strip(b[12]);y0=strip(a[12]);
 if y0.startswith('(') and y0.endswith(')'):y0=y0[1:-1]
 names=list(dict.fromkeys([x0,x1,y1]));assert all(re.fullmatch(r'\w+',v) for v in names)
 for mode in ['array','pair','struct']:
  mapping={x0:'x[0]',x1:'x[1]',y1:'y[1]'}
  if x0==x1:mapping[x0]='x[0]'
  if mode=='pair':mapping={k:v.replace('x[0]','xy[0][0]').replace('x[1]','xy[1][0]').replace('y[1]','xy[1][1]') for k,v in mapping.items()};first='xy[0][1]';decl='s32 xy[2][2];'
  elif mode=='struct':mapping={k:v.replace('x[0]','xy.x0').replace('x[1]','xy.x1').replace('y[1]','xy.y1') for k,v in mapping.items()};first='xy.y0';decl='struct {s32 x0,y0,x1,y1;} xy;'
  else:first='y[0]';decl='s32 x[2], y[2];'
  t=s
  for v in names:t=re.sub(r'    s32 '+v+r';\n','',t)
  t=re.sub(r'\b('+'|'.join(names)+r')\b',lambda m:mapping[m[0]],t)
  t=t.replace(a[12],f'(f32) {first}',1)
  pos=t.index('    if (arg5 != 0)');t=t[:pos]+f'    {first} = {y0};\n'+t[pos:]
  pos=t.index('{',t.index('void func_'))+1;t=t[:pos]+'\n    '+decl+t[pos:]
  yield mode,t
if __name__=='__main__':
 rows=[]
 for n in NAMES:
  fn='func_'+n;p=Path('tools/scratch/nonmatching/T-023')/(fn+'.c');s=p.read_text();baseline=probe(fn,s);best=baseline;chosen=s;label='baseline'
  for name,t in variants(s):
   score=probe(fn,t)
   if score[0]<best[0]:best=score;chosen=t;label=name
  dest=OUT/p.name;dest.write_text(chosen)
  row=dict(function=fn,baseline=baseline,final=best,variant=label,candidate=str(dest));rows.append(row);print(row,flush=True)
 (OUT/'results.json').write_text(json.dumps(rows,indent=2))
