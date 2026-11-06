"""Wrap every balanced line range of the function body in do { } while (0). usage: rangewrap.py fn draft out [jobs]"""
import sys, re, concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-173')
import msweep
fn,draft,outp=sys.argv[1:4]; jobs=int(sys.argv[4]) if len(sys.argv)>4 else 8
lines=open(draft).read().split('\n')
s=next(i for i,l in enumerate(lines) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
# body starts after first '{'
b0=next(i for i in range(s,len(lines)) if '{' in lines[i])
e=len(lines)-1
while not lines[e].strip().startswith('}'): e-=1
def stmt_start(l):
    t=l.strip()
    return t!='' and not t.startswith(('}','else','{')) and not re.match(r'^(s32|u8|u32|f32|u16|s16|s8|T\w+|Frontend\w+|RenderState)\b[^=(]*(=[^;]*)?;$',t) or t.startswith(('if','for','while','do'))
cands={}
n=len(lines)
for i in range(b0+1,e):
    if lines[i].strip()=='' or lines[i].strip().startswith(('}','else')): continue
    if re.match(r'^\s*(s32|u8|u32|f32|T\w+)\b[^=(]*;$',lines[i]): continue
    d=0
    for j in range(i,e):
        d+=lines[j].count('{')-lines[j].count('}')
        if d<0: break
        t=lines[j].strip()
        if d==0 and t.endswith(('}',';')) and not t.startswith('else') :
            # ensure next line is not else
            k=j+1
            while k<e and lines[k].strip()=='': k+=1
            if k<e and lines[k].strip().startswith('else'): continue
            if 'return' in ' '.join(lines[i:j+1]) and False: pass
            ind=re.match(r'\s*',lines[i]).group(0)
            new=lines[:i]+[ind+'do {']+lines[i:j+1]+[ind+'} while (0);']+lines[j+1:]
            cands[(i,j)]=new
print(len(cands),file=sys.stderr)
res={}
with cf.ThreadPoolExecutor(jobs) as ex:
    futs={ex.submit(msweep.measure,fn,'\n'.join(v),'r%d_%d'%k):k for k,v in cands.items()}
    for f in cf.as_completed(futs): res[futs[f]]=f.result()
for k,v in sorted(res.items(),key=lambda kv:kv[1])[:8]:
    print(k,v)
    if v[0]==0: open(outp+'_%d_%d.c'%k,'w').write('\n'.join(cands[k]))
