#!/usr/bin/env python3
# sweep.py FN TEMPLATE [N]: template alternatives written {{a||b||c}}; compiles every combination in TU context.
import sys,re,itertools,pathlib
sys.path.insert(0,str(pathlib.Path(__file__).parent))
import probe,tu
fn,tp=sys.argv[1],pathlib.Path(sys.argv[2]).read_text()
parts=re.split(r'\{\{(.*?)\}\}',tp,flags=re.S)
alts=[p.split('||') for p in parts[1::2]]
_,pre=tu.ctx(fn)
res=[]
for combo in itertools.product(*alts):
    s=parts[0]+''.join(c+parts[2*i+2] for i,c in enumerate(combo))
    r=probe.probe(fn,pre+'\n'+s)
    res.append((r,combo,s))
    if r[0]==0: print('MATCH',combo); pathlib.Path(sys.argv[2]+'.match.c').write_text(s); break
res.sort(key=lambda x:x[0])
for r,c,s in res[:int(sys.argv[3]) if len(sys.argv)>3 else 5]: print(r,c)
pathlib.Path(sys.argv[2]+'.best.c').write_text(res[0][2])
