"""Wrap simple statements (1-3 adjacent lines) in do { } while (0). usage: dowsweep.py fn draft out [jobs] [depth]"""
import sys, re, concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-173')
import msweep
fn,draft,out=sys.argv[1:4]
jobs=int(sys.argv[4]) if len(sys.argv)>4 else 6
depth=int(sys.argv[5]) if len(sys.argv)>5 else 2
lines=open(draft).read().split('\n')
def fstart(ls): return next(i for i,l in enumerate(ls) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
def simple(l):
    s=l.strip()
    return s.endswith(';') and not s.startswith(('return','break','continue','extern','typedef')) and '{' not in s and '}' not in s and not re.match(r'^(s32|u8|u32|f32|u16|s16|s8|T\w+|Frontend\w+|RenderState)\b[^=(]*;$',s) and not s.startswith('do ')
def cands(ls):
    s=fstart(ls); res={}
    n=len(ls)
    for i in range(s+1,n):
        for k in (1,2,3):
            seg=ls[i:i+k]
            if len(seg)<k or not all(simple(x) for x in seg): break
            ind=re.match(r'\s*',seg[0]).group(0)
            new=ls[:i]+[ind+'do { '+' '.join(x.strip() for x in seg)+' } while (0);']+ls[i+k:]
            res[f'w{i}_{k}']=new
    return res
cur=lines; best=msweep.measure(fn,'\n'.join(cur),'base'); print('base',best,file=sys.stderr)
for it in range(depth):
    cs=cands(cur)
    res={}
    with cf.ThreadPoolExecutor(jobs) as ex:
        futs={ex.submit(msweep.measure,fn,'\n'.join(v),k):k for k,v in cs.items()}
        for f in cf.as_completed(futs): res[futs[f]]=f.result()
    k,v=min(res.items(),key=lambda kv:kv[1])
    print('iter',it,'best',k,v,file=sys.stderr)
    if v<best:
        best=v; cur=cs[k]; open(out,'w').write('\n'.join(cur))
        if best[0]==0: break
    else: break
print('final',best)
