"""T-122 complete-TU diagnostics. Outputs and compiler products stay in /tmp."""
from pathlib import Path
import sys, importlib.util, subprocess, tempfile, struct, json, re
ROOT=Path(__file__).resolve().parents[4]
sys.path.insert(0,str(ROOT/'tools/permuter'))
import screen
FUNCTIONS='801C1434 800131A4 8002E150 800297A4 8001808C 801BBE88 800253D0 801B2B8C 801BD640 800193DC 801B01EC 80017D6C 80018AE0 801B0CDC 801C3AA0 801C90D4'.split()
WORK=Path('/tmp/kig-t122'); WORK.mkdir(exist_ok=True)
def draft(fn): return next((ROOT/'tools/scratch/nonmatching').glob('T-0*/'+fn+'.c'))
def source(fn):
 p=WORK/(fn+'.c')
 for prefix,decl in [(False,False),(True,False),(True,True)]:
  try:
   r=screen.measure(fn,draft(fn),prefix,decl,source_output=p)
   return p.read_text()
  except Exception: pass
 raise RuntimeError(p.read_text()[-500:])
def compile(fn,s,label='probe',dump=False):
 with tempfile.TemporaryDirectory(prefix='t122-') as d:
  c=Path(d)/'candidate.c'; o=c.with_suffix('.o'); c.write_text(s)
  cmd=[str(ROOT/'.venv/bin/python'),str(ROOT/'tools/ext/asm-processor/build.py'),str(ROOT/'tools/ext/ido/5.3/cc'),'--',str(ROOT/'tools/ext/binutils/bin/mips64-elf-as'),'-EB','-mips3','-32','-G','0','-I','include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(o),str(c)]
  if label.startswith('static'):
   cmd.insert(2,'--convert-statics'); cmd.insert(3,'global')
  proc=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True)
  if proc.returncode: return {'label':label,'error':proc.stderr[-2000:]}
  code,masks,rels=screen.elf.elf_function(o,fn)
  row=next(r for r in json.loads((ROOT/'tools/progress/original-functions.json').read_text()).values() if r['function']==fn)
  base={'main':0x8000F960,'ovl_7DF8':0x801ABB20}[row['area']]; off=int(fn[5:],16)-base
  target=(ROOT/'build/segments'/(row['area']+'.bin')).read_bytes()[off:off+row['bytes']]
  a=struct.unpack('>'+ 'I'*(len(code)//4),code); b=struct.unpack('>'+'I'*(len(target)//4),target)
  bad=[i for i,(x,y) in enumerate(zip(a,b)) if x&masks[i]!=y&masks[i]]
  result={'label':label,'words':len(bad)+abs(len(a)-len(b)),'bytes':len(code),'offsets':[hex(i*4) for i in bad]}
  if dump:
   import rabbitizer
   result['instructions']=[{'offset':hex(i*4),'target':str(rabbitizer.Instruction(b[i])),'draft':str(rabbitizer.Instruction(a[i]))} for i in bad]
  if dump == 'all':
   import rabbitizer
   result['target_asm']=[str(rabbitizer.Instruction(x)) for x in b]
   result['draft_asm']=[str(rabbitizer.Instruction(x)) for x in a]
  return result
if __name__=='__main__':
 results={}
 for n in FUNCTIONS:
  fn='func_'+n; s=source(fn); r=compile(fn,s,'baseline',True); results[fn]=r; print(fn,r,flush=True)
 (WORK/'baseline.json').write_text(json.dumps(results,indent=2))
