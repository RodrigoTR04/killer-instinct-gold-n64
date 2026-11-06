"""Hill-climb line joins/splits inside a function. usage: joinclimb.py fn draft out [jobs]"""
import sys, re
sys.path.insert(0,'tools/scratch/nonmatching/T-173')
import msweep
fn,draft,out=sys.argv[1:4]
jobs=int(sys.argv[4]) if len(sys.argv)>4 else 4
src=open(draft).read()
lines=src.split('\n')
start=next(i for i,l in enumerate(lines) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
def body_range(ls):
    s=next(i for i,l in enumerate(ls) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
    return s,len(ls)
def score(text,tag):
    return msweep.measure(fn,text,tag)
cur=lines; best=score('\n'.join(cur),'base')
print('base',best,file=sys.stderr)
improved=True
while improved:
    improved=False
    s,e=body_range(cur)
    cands={}
    for i in range(s+1,len(cur)-1):
        # join i with i+1
        if cur[i].strip()=='' or cur[i+1].strip()=='' : continue
        j=cur[:i]+[cur[i].rstrip()+' '+cur[i+1].strip()]+cur[i+2:]
        cands[f'j{i}']=j
        # split at ' ' after ';' if multiple statements on a line
    for i in range(s+1,len(cur)):
        l=cur[i]
        m=[x.end() for x in re.finditer(r';\s+(?=\S)',l)]
        for k,pos in enumerate(m):
            j=cur[:i]+[l[:pos].rstrip(),'    '+l[pos:].lstrip()]+cur[i+1:]
            cands[f's{i}_{k}']=j
    import concurrent.futures as cf
    res={}
    with cf.ThreadPoolExecutor(jobs) as ex:
        futs={ex.submit(score,'\n'.join(v),k):k for k,v in cands.items()}
        for f in cf.as_completed(futs): res[futs[f]]=f.result()
    k,v=min(res.items(),key=lambda kv:kv[1])
    print('best cand',k,v,file=sys.stderr)
    if v<best:
        best=v; cur=cands[k]; improved=True
        open(out,'w').write('\n'.join(cur))
        if best[0]==0: break
print('final',best)
