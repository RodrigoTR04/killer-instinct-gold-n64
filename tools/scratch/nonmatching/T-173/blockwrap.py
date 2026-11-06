"""Wrap balanced statements (if/else chains, blocks) in do{}while(0). usage: blockwrap.py fn draft [jobs]"""
import sys, re, concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-173')
import msweep
fn,draft=sys.argv[1:3]; jobs=int(sys.argv[3]) if len(sys.argv)>3 else 6
src=open(draft).read(); lines=src.split('\n')
s=next(i for i,l in enumerate(lines) if re.search(r'\b'+fn+r'\(',l) and not l.strip().endswith(';'))
cs={}
def depth(l): return l.count('{')-l.count('}')
n=len(lines)
for i in range(s+2,n):
    l=lines[i].strip()
    if not (l.startswith('if') or l.startswith('{') or l.startswith('for') or l.startswith('while')): continue
    # find end of statement: balanced, include following else
    d=0; j=i
    while j<n:
        d+=depth(lines[j]); 
        if d==0 and ('{' in ''.join(lines[i:j+1])):
            # check next nonblank line is else
            k=j+1
            while k<n and lines[k].strip()=='' : k+=1
            if k<n and lines[k].strip().startswith(('else','} else')) and not lines[j].strip().endswith('else'):
                j=k; d=depth(lines[j]); 
                if d==0 and lines[j].strip().endswith(';'): break
                continue
            break
        j+=1
    if j>=n: continue
    ind=re.match(r'\s*',lines[i]).group(0)
    new=lines[:i]+[ind+'do {']+lines[i:j+1]+[ind+'} while (0);']+lines[j+1:]
    cs[f'b{i}_{j}']=new
print(len(cs),file=sys.stderr)
res={}
with cf.ThreadPoolExecutor(jobs) as ex:
    futs={ex.submit(msweep.measure,fn,'\n'.join(v),k):k for k,v in cs.items()}
    for f in cf.as_completed(futs): res[futs[f]]=f.result()
for k,v in sorted(res.items(),key=lambda kv:kv[1])[:8]:
    print(k,v)
    if v[0]==0: open(draft.replace('.c','_bw.c'),'w').write('\n'.join(cs[k]))
