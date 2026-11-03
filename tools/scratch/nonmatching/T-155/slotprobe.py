import sys, re, random, subprocess, tempfile
from pathlib import Path
sys.path.insert(0,'.')
import lib
cm=lib.cm
fn='func_801C4240'
src=open('d4240/c1.c').read()
m=re.search(r'\b'+fn+r'\([^)]*\)\s*\{\n',src); i0=m.end()
lines=src[i0:].split('\n')
decl=[]
for ln in lines:
    if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$',ln): decl.append(ln)
    else: break
n=len(decl); rest='\n'.join(lines[n:])
rnd=random.Random(7)
def build(o): return src[:i0]+'\n'.join(decl[k] for k in o)+'\n'+rest
def slots(o):
    with tempfile.TemporaryDirectory() as d:
        p=Path(d)/'x.c'; p.write_text(build(o))
        source,tu=cm.build_source(fn,p,True)
        obj=cm.compile_source(source,Path(d)/'c.c')
        pairs=cm.draft_raw(obj,fn)
    out={}
    for _,i,r in pairs:
        mm=re.match(r'swc1\s+\$f\d+,(\d+)\(sp\)',i)
        if mm: out.setdefault('swc1',[]).append(int(mm.group(1)))
    return out
for t in range(6):
    o=list(range(n)); rnd.shuffle(o)
    print([decl[k].strip().split()[-1].rstrip(';') for k in o], slots(o))
