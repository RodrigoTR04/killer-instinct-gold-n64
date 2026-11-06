"""Exhaustive pairs of do{}while(0) single-line wraps (and singles). usage: dowpairs.py fn draft outprefix [jobs]"""
import sys, re, itertools, concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-173')
import msweep
fn,draft,outp=sys.argv[1:4]; jobs=int(sys.argv[4]) if len(sys.argv)>4 else 8
lines=open(draft).read().split('\n')
s=next(i for i,l in enumerate(lines) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
def simple(l):
    t=l.strip()
    return t.endswith(';') and not t.startswith(('return','break','continue','extern','typedef','do ')) and '{' not in t and '}' not in t and not re.match(r'^(s32|u8|u32|f32|u16|s16|s8|T\w+|Frontend\w+|RenderState)\b[^=(]*;$',t)
idx=[i for i in range(s+1,len(lines)) if simple(lines[i])]
def wrap(ls,i):
    ind=re.match(r'\s*',ls[i]).group(0)
    ls=list(ls); ls[i]=ind+'do { '+ls[i].strip()+' } while (0);'; return ls
cs={}
for i in idx: cs[(i,)]=wrap(lines,i)
for i,j in itertools.combinations(idx,2): cs[(i,j)]=wrap(wrap(lines,i),j)
print(len(cs),file=sys.stderr)
res={}
with cf.ThreadPoolExecutor(jobs) as ex:
    futs={ex.submit(msweep.measure,fn,'\n'.join(v),'_'.join(map(str,k))):k for k,v in cs.items()}
    for f in cf.as_completed(futs): res[futs[f]]=f.result()
for k,v in sorted(res.items(),key=lambda kv:kv[1])[:6]:
    print(k,v)
    if v[0]==0: open(outp+'_'+'_'.join(map(str,k))+'.c','w').write('\n'.join(cs[k]))
