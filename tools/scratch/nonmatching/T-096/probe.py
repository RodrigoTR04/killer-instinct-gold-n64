"""T-096 complete-TU diagnostics. Outputs and compiler products stay in /tmp."""
from pathlib import Path
import sys, importlib.util, subprocess, tempfile, struct, json, re
ROOT=Path(__file__).resolve().parents[4]
sys.path.insert(0,str(ROOT/'tools/permuter'))
import screen
FUNCTIONS=['801BF720','801BF914','801C4E38','801B6528','801B695C','801C5064','801C7998','801C6A80','801B2010','801B21B4','801B2358','801B24FC','801B26A0','801B2844','801B29E8','8002AA98','8002AAEC','8002F6F4','80017378']
WORK=Path('/tmp/kig-t096'); WORK.mkdir(exist_ok=True)
def draft(fn): return next((ROOT/'tools/scratch/nonmatching').glob('T-0*/'+fn+'.c'))
def source(fn):
 p=WORK/(fn+'.c')
 try: screen.measure(fn,draft(fn),source_output=p)
 except Exception:
  # Resolve only the three known alternate views and the audio return declaration.
  s=p.read_text()
  s=s.replace('extern s32 func_801BF720(s32);','extern s32 func_801BF720(u32);')
  s=s.replace('extern u8 D_802C8808[];','extern u8 D_802C8808[][512];')
  s=s.replace('memcpy(D_802C8808 +','memcpy((u8 *)D_802C8808 +')
  s=s.replace('extern void func_8002F6F4(s32, s32, void *);','extern s32 func_8002F6F4();')
  if fn == 'func_801C4E38':
   for sym in ['D_802D39A0','D_802D39A4','D_802D39A8']: s=s.replace('extern s32 '+sym+';', '')
   for sym in ['D_80291B5C','D_80291B74','D_80291BA0']: s=s.replace('extern s32 '+sym+'[];', 'extern s32 *'+sym+'[];')
  if fn == 'func_801C5064':
   s=s.replace('extern u8 D_802D399F;', '')
   start=s.index('void func_801C5064('); end=s.index('\n}', start)+2
   s=s[:start]+s[start:end].replace('D_802D399F', '((u8)D_802D399F)')+s[end:]
  p.write_text(s)
 return p.read_text()
def compile(fn,s,label='probe',dump=False):
 with tempfile.TemporaryDirectory(prefix='t096-') as d:
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
  return result
if __name__=='__main__':
 results={}
 for n in FUNCTIONS:
  fn='func_'+n; s=source(fn); r=compile(fn,s,'baseline',True); results[fn]=r; print(fn,r,flush=True)
 (WORK/'baseline.json').write_text(json.dumps(results,indent=2))
