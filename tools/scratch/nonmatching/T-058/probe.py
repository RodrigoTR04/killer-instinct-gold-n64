from pathlib import Path
import sys, subprocess, struct, json, re, os
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
ROOT=Path('tools/scratch/nonmatching/T-058')
base=Path('build/segments/main.bin').read_bytes()
flags=['-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude']
def probe(fn,s,label='test'):
 p=Path('/tmp/t058-%d.c'%os.getpid());o=Path('/tmp/t058-%d.o'%os.getpid())
 p.write_text('#include "common.h"\nextern f32 sinf(f32),cosf(f32);\n'+s)
 r=subprocess.run(['tools/ext/ido/5.3/cc',*flags,'-o',str(o),str(p)],capture_output=True,text=True)
 if r.returncode:return {'label':label,'error':r.stderr[-1200:]}
 try:
  code,masks,rels=elf_function(o,fn)
  off=int(fn[5:],16)-0x8000f960
  target=base[off:off+len(code)]
  diffs=[i*4 for i,(a,b,m) in enumerate(zip(struct.unpack('>'+str(len(code)//4)+'I',code),struct.unpack('>'+str(len(code)//4)+'I',target),masks)) if a&m!=b&m]
  return dict(label=label,bytes=len(code),words=len(diffs),offsets=diffs)
 except Exception as e:return dict(label=label,error=str(e))
def draft(fn):return (ROOT/'inputs'/(fn+'.txt')).read_text()
def run(fn,variants):
 rows=[]
 for label,s in variants:
  row=probe(fn,s,label);rows.append(row)
  if 'words' in row: print(fn,label,row['words'],row['bytes'],flush=True)
  else:print(fn,label,'ERROR',row['error'][:150],flush=True)
 ROOT.joinpath(fn+'.json').write_text(json.dumps(rows,indent=2)+'\n')
 return rows
if __name__=='__main__':
 fn=sys.argv[1];print(probe(fn,Path(sys.argv[2]).read_text()))
