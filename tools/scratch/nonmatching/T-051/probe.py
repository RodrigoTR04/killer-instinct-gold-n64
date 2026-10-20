from pathlib import Path
import subprocess,sys,struct,json
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
ROOT=Path('tools/scratch/nonmatching/T-051')
base=Path('build/segments/main.bin').read_bytes()
flags=['-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude']
def original(p):
 return subprocess.check_output(['git','show','HEAD:'+str(p)],text=True)
def probe(s,fn,tag='probe'):
 p=Path('/tmp/t051-'+tag+'.c');o=p.with_suffix('.o');p.write_text('#include "common.h"\nextern f32 sinf(f32),cosf(f32);\ntypedef struct { u8 pad[0x28]; s16 x,y,z; } T020Position;\n'+s)
 r=subprocess.run(['tools/ext/ido/5.3/cc',*flags,'-o',str(o),str(p)],capture_output=True,text=True)
 if r.returncode:return {'error':r.stderr}
 c,m,_=elf_function(o,fn);off=int(fn[5:],16)-0x8000f960;t=base[off:off+len(c)]
 d=[i*4 for i,(a,b,mask) in enumerate(zip(struct.unpack('>%dI'%(len(c)//4),c),struct.unpack('>%dI'%(len(c)//4),t),m)) if a&mask!=b&mask]
 return {'bytes':len(c),'words':len(d),'offsets':d}
if __name__=='__main__':
 rows=[]
 for task,names in [('T-033',['1178C','12B7C','1346C','15450']),('T-020',['16760']),('T-022',['1CBCC']),('T-032',['21B6C','249DC','26B38']),('T-035',['42198'])]:
  for n in names:
   p=Path('tools/scratch/nonmatching')/task/('func_800'+n+'.c');r=probe(original(p),p.stem,n);rows.append({'draft':str(p),**r});print(n,r if 'error' in r else {k:v for k,v in r.items() if k!='offsets'})
 (ROOT/'baseline.json').write_text(json.dumps(rows,indent=2)+'\n')
