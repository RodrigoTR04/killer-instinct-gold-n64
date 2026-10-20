"""Compile candidates inside their owning TU; mask only ELF relocations."""
from pathlib import Path
import re,sys,json,struct,subprocess,importlib.util,os
ROOT=Path(__file__).resolve().parents[4]
spec=importlib.util.spec_from_file_location('cmp',ROOT/'tools/scratch/flagprobe/compare.py');cmp=importlib.util.module_from_spec(spec);spec.loader.exec_module(cmp)
SKIP={'8002AEE4','8002B1EC','80017378','8002AA98','8002AAEC','8002B9B4','8002A900','8002F45C'}
TUS=['main','main_1EB40','main_1BE80','main_1AB90','main_20220','main_20AE0','main_17140','main_1A880']
rows={r['function']:r for r in json.loads((ROOT/'tools/progress/original-functions.json').read_text()).values() if r['area']=='main'}
def targets():
 for tu in TUS:
  p=ROOT/'src/main'/f'{tu}.c'
  for fn in re.findall(r'/([\w]+)\.s',p.read_text()):
   if fn[5:] not in SKIP: yield fn,p,next((ROOT/'tools/scratch/nonmatching').glob('T-*/'+fn+'.c'))
def context(fn,tu,draft):
 s=tu.read_text();s=s[:s.index('#pragma GLOBAL_ASM("asm/nonmatchings/main/'+tu.stem+'/'+fn+'.s")')]
 return re.sub(r'#pragma GLOBAL_ASM\([^)]*\)','',s)+'\n'+draft

def probe(fn,source,verbose=False):
 p=Path('/tmp/t085-probe-%s.c'%os.getpid());o=p.with_suffix('.o');p.write_text(source)
 r=subprocess.run([str(ROOT/'tools/ext/ido/5.3/cc'),'-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-I'+str(ROOT/'include'),str(p),'-o',str(o)],capture_output=True,text=True)
 if r.returncode:
  if verbose: print(r.stderr)
  return None
 code,masks,_=cmp.elf_function(o,fn); row=rows[fn];off=int(row['vram'],16)-0x8000F960
 target=(ROOT/'build/segments/main.bin').read_bytes()[off:off+row['bytes']]
 a=struct.unpack('>%dI'%(len(code)//4),code);b=struct.unpack('>%dI'%(len(target)//4),target)
 dif=[i for i in range(max(len(a),len(b))) if i>=len(a) or i>=len(b) or a[i]&masks[i]!=b[i]&masks[i]]
 if verbose:
  print('diff offsets', [hex(i*4) for i in dif]);print(subprocess.check_output([str(ROOT/'tools/ext/binutils/bin/mips64-elf-objdump'),'-dr',str(o)],text=True))
 return len(dif),len(code)
if __name__=='__main__':
 for fn,tu,d in targets():
  if len(sys.argv)>1 and fn!=sys.argv[1]:continue
  print(fn,d,probe(fn,context(fn,tu,d.read_text()),'-v' in sys.argv),flush=True)
