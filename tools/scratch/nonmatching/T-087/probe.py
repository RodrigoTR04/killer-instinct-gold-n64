#!/usr/bin/env python3
import importlib.util, pathlib, subprocess, struct, json
ROOT=pathlib.Path(__file__).resolve().parents[4]
spec=importlib.util.spec_from_file_location('cmp',ROOT/'tools/scratch/flagprobe/compare.py'); cmp=importlib.util.module_from_spec(spec);spec.loader.exec_module(cmp)
rows={r['function']:r for r in json.loads((ROOT/'tools/progress/original-functions.json').read_text()).values() if r['area']=='ovl_7DF8'}
def probe(name,source,show=False):
 p=pathlib.Path('/tmp/t087-probe.c');o=p.with_suffix('.o');p.write_text('#include "common.h"\n'+source)
 r=subprocess.run([str(ROOT/'tools/ext/ido/5.3/cc'),'-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-I'+str(ROOT/'include'),str(p),'-o',str(o)],capture_output=True)
 if r.returncode:
  if show: print(r.stdout.decode()[-1500:],r.stderr.decode()[-1500:])
  return (99999,0)
 code,masks,_=cmp.elf_function(o,name); off=int(name[5:],16)-0x801ABB20;target=(ROOT/'build/segments/ovl_7DF8.bin').read_bytes()[off:off+rows[name]['bytes']]
 a=struct.unpack('>'+'I'*(len(code)//4),code);b=struct.unpack('>'+'I'*(len(target)//4),target)
 dif=[(i*4,hex(x),hex(y)) for i,(x,y) in enumerate(zip(a,b)) if x&masks[i]!=y&masks[i]]
 if show: print(dif);print(subprocess.check_output([str(ROOT/'tools/ext/binutils/bin/mips64-elf-objdump'),'-dr',str(o)],text=True))
 return len(dif)+abs(len(a)-len(b)),len(code)
if __name__=='__main__':
 import sys
 for f in sys.argv[1:]:
  p=pathlib.Path(f);print(p.stem,probe(p.stem,p.read_text(),True))
