from pathlib import Path
import subprocess,sys,struct,json,re
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
ROOT=Path('tools/scratch/nonmatching/T-059')
GROUPS={'T-032':'25D58 24714 241BC 27E1C 216D4 253D0','T-026':'30440 39C08 3EF90 327E8','T-022':'1BB64 1E0B4 18F20 1D47C 1D080 1808C 193DC 18AE0 1B134 1B620 1AD04','T-033':'170C4 131A4 16910 17A68 17D6C','T-024':'297A4 2E150 2AB90 2A4F0 28230 29BE0'}
paths=[Path('tools/scratch/nonmatching')/task/('func_800'+n+'.c') for task,names in GROUPS.items() for n in names.split()]
base=Path('build/segments/main.bin').read_bytes()
flags=['-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude']
PRE='#include "common.h"\nextern f32 sinf(f32),cosf(f32);\ntypedef struct { u8 pad[0x28]; s16 x,y,z; } T020Position;\n'
def probe(s,fn):
 p=Path('/tmp/t059-probe.c');o=p.with_suffix('.o');p.write_text(PRE+s)
 r=subprocess.run(['tools/ext/ido/5.3/cc',*flags,'-o',str(o),str(p)],capture_output=True,text=True)
 if r.returncode:return {'error':r.stderr}
 c,m,_=elf_function(o,fn);off=int(fn[5:],16)-0x8000f960;t=base[off:off+len(c)]
 d=[i*4 for i,(a,b,mask) in enumerate(zip(struct.unpack('>%dI'%(len(c)//4),c),struct.unpack('>%dI'%(len(c)//4),t),m)) if a&mask!=b&mask]
 return {'bytes':len(c),'words':len(d),'offsets':d}
if __name__=='__main__':
 rows=[]
 for p in paths:
  r=probe(p.read_text(),p.stem);rows.append({'draft':str(p),**r});print(p.stem,{k:v for k,v in r.items() if k!='offsets'},flush=True)
 (ROOT/'baseline.json').write_text(json.dumps(rows,indent=2)+'\n')
