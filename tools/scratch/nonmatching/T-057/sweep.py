import pathlib,sys,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent))
from probe import probe,ROOT
out=pathlib.Path(__file__).parent
results=[]
def sweep(name, variants):
 p=next((ROOT/'tools/scratch/nonmatching').glob('T-0[123]*/'+name+'.c'))
 src=p.read_text(); baseline=probe(name,src);best=baseline;bs=src;count=0
 for label,s in variants(src):
  score=probe(name,s);count+=1
  if score[0]<best[0]:
   best=score;bs=s;print(name,label,score,flush=True);(out/(name+'.best.c')).write_text(bs)
 results.append(dict(name=name,baseline=baseline,best=best,count=count))
 (out/('results-'+pathlib.Path(sys.argv[0]).stem+'.json')).write_text(json.dumps(results,indent=2))
 return bs

def gfx(s):
 # Independent store ordering, declaration ordering, and command word types.
 pairs=list(re.finditer(r'(\s*\w+->w[01] = [^;]+;)(\s*\w+->w[01] = [^;]+;)',s))
 for bits in itertools.product([0,1],repeat=len(pairs)):
  t=s
  for m,b in reversed(list(zip(pairs,bits))):
   if b:t=t[:m.start()]+m[2]+m[1]+t[m.end():]
  yield 'stores'+str(bits),t
 for ty in ['s32','u32','unsigned long','long']:
  yield 'wordtype'+ty,re.sub(r'\{ [su]32 w0, w1;', '{ '+ty+' w0, w1;',s)
 for expr in ['0x01030040U','(0x103 << 16) | 0x40','0x01030000 + 0x40']:
  yield 'constant'+expr,s.replace('0x01030040',expr)
 if '*p0, *p1, *p2, *p3, *p4;' in s:
  for order in itertools.permutations(range(5)):
   yield 'decl'+str(order),s.replace('*p0, *p1, *p2, *p3, *p4;',', '.join('*p'+str(i) for i in order)+';')
 for i in range(11):
  for access in ['index','add','bytes']:
   for v in ['p'+str(i),'command'+str(i),'env']:
    if access=='index':t=re.sub(r'\b'+v+r'->w([01])',lambda m:'((u32 *)'+v+')['+m[1]+']',s)
    elif access=='add':t=s.replace('(*arg0)++','(*arg0 += 1) - 1')
    else:t=re.sub(r'\b'+v+r'->w([01])',lambda m:'*(u32 *)((u8 *)'+v+' + '+str(int(m[1])*4)+')',s)
    yield access+v,t

if __name__=='__main__':
 for n in ['func_801C51F8','func_801B6A68']:
  b=sweep(n,gfx)
