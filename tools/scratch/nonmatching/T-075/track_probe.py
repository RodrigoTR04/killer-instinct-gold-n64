import importlib.util,sys,re,random,contextlib,io
from pathlib import Path
p=Path('tools/scratch/nonmatching/T-055/sc.py').resolve();sp=importlib.util.spec_from_file_location('sc',p);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
s=Path('tools/scratch/nonmatching/T-075/track.c').read_text();h,b=s.split('u8 func_80038DE0',1);b='u8 func_80038DE0'+b;b=re.sub(r'/\*.*?\*/','',b,flags=re.S);parts=re.split(r'(?<=[;{}])\s*',b);r=random.Random(75);best=47
for i in range(250):
 b=''.join(x+ ('\n' if r.random()<.65 else ' ') for x in parts)
 Path('/tmp/t075-track.c').write_text(h+b)
 with contextlib.redirect_stdout(io.StringIO()):v=m.run('/tmp/t075-track.c','func_80038DE0')
 if v is not None and v<best:
  best=v;Path('tools/scratch/nonmatching/T-075/track.c').write_text(h+b);print(i,best,flush=True)
 if best==0:break
print('best',best)
