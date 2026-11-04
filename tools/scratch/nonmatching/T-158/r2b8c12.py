import sys, itertools, re, tempfile
from pathlib import Path
import concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
cm=lib.cm
code=open('tools/scratch/nonmatching/T-158/r2b8c3.py').read().split("cands=[]")[0]
exec(code)
def asm_of(src):
    with tempfile.TemporaryDirectory(prefix='a158-') as d:
        p=Path(d)/'draft.c'; p.write_text(src)
        source,tu=cm.build_source('func_801B2B8C',p,True)
        o=cm.compile_source(source,Path(d)/'c.c')
        pairs=cm.draft_raw(o,'func_801B2B8C')
    return [cm.canon(cm.apply_relocs(i,r)) for _,i,r in pairs]
def regs(a):
    A1=A2=V=None
    for l in a:
        m=re.match(r'lui (\w+),%hi\(0x801d308c\)',l)
        if m: A1=m.group(1)
        m=re.match(r'lui (\w+),%hi\(0x801d3094\)',l)
        if m: A2=m.group(1)
    fr=next((abs(int(re.search(r'-?\d+$',x).group())) for x in a if x.startswith('addiu sp,sp,')),0)
    return A1,A2,fr
keys=list(itertools.product((1,0),(1,0),(6,5,4,3,2),(1,0),(1,0),(1,0)))
def run(k):
    try:
        return k,regs(asm_of(variant(*k)))
    except SystemExit:
        return k,None
with cf.ThreadPoolExecutor(12) as ex:
    res=list(ex.map(run,keys))
for k,r in res:
    if r and r[0]=='a2' and r[1]=='a3': print(k,r)
print(len(res))
