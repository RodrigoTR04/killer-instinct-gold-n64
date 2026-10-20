"""Full production-TU probes; generated objects/logs live in /tmp."""
from pathlib import Path
import re,sys,json,struct,subprocess,importlib.util
ROOT=Path(__file__).resolve().parents[4]
spec=importlib.util.spec_from_file_location('cmp',ROOT/'tools/scratch/flagprobe/compare.py');cmp=importlib.util.module_from_spec(spec);spec.loader.exec_module(cmp)
rows={r['function']:r for r in json.loads((ROOT/'tools/progress/original-functions.json').read_text()).values() if r['area']=='main'}
NAMES='12B7C 131A4 1346C 1373C 16078 170C4 17A68 17D6C 1808C 18AE0 18F20 191F0 193DC 1AA90 1AD04 1B134 1BB64 1BDE0 15450 15594 1CD50 1D080 1D47C 1D7E4 1DE5C 23EF0 24028 241BC 244F0 245B4 24714 24B0C 21B6C 216D4'.split()
def location(fn):
 for p in (ROOT/'src/main').glob('main*.c'):
  if '/'+fn+'.s' in p.read_text():return p

def draft(fn):return next((ROOT/'tools/scratch/nonmatching').glob('T-*/'+fn+'.c'))
def check(fn,d,changes=(),verbose=False,fast=False):
 s=location(fn).read_text()
 for a,b in changes:s=s.replace(a,b)
 s=re.sub(r'#pragma GLOBAL_ASM\("[^"\n]*/'+fn+r'\.s"\)',lambda _:d,s)
 p=Path('/tmp/t093-'+fn+'.c');o=p.with_suffix('.o');p.write_text(s)
 cmd=[str(ROOT/'.venv/bin/python'),str(ROOT/'tools/ext/asm-processor/build.py'),str(ROOT/'tools/ext/ido/5.3/cc'),'--',str(ROOT/'tools/ext/binutils/bin/mips64-elf-as'),'-EB','-mips3','-32','-G','0','-I','include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(o),str(p)]
 if fast:
  p.write_text(re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', s))
  cmd=[str(ROOT/'tools/ext/ido/5.3/cc'),'-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude',str(p),'-o',str(o)]
 r=subprocess.run(cmd,capture_output=True,text=True)
 if r.returncode:
  Path('/tmp/t093-'+fn+'.err').write_text(r.stdout+r.stderr)
  if verbose:print(r.stdout+r.stderr)
  return None
 code,masks,_=cmp.elf_function(o,fn);row=rows[fn];off=int(row['vram'],16)-0x8000F960
 target=(ROOT/'build/segments/main.bin').read_bytes()[off:off+row['bytes']]
 a=struct.unpack('>%dI'%(len(code)//4),code);b=struct.unpack('>%dI'%(len(target)//4),target)
 dif=[i*4 for i,(x,y) in enumerate(zip(a,b)) if x&masks[i]!=y&masks[i]]
 if verbose:print(dif);print(subprocess.check_output([str(ROOT/'tools/ext/binutils/bin/mips64-elf-objdump'),'-dr',str(o)],text=True))
 return len(dif)+abs(len(a)-len(b)),len(code)
if __name__=='__main__':
 out={}
 for n in (sys.argv[1:] or NAMES):
  fn='func_800'+n;p=draft(fn);out[fn]=check(fn,p.read_text());print(fn,out[fn],flush=True)
 Path('/tmp/t093-baseline.json').write_text(json.dumps(out,indent=2))
