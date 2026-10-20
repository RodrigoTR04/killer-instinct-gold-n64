from pathlib import Path
import subprocess,struct,sys,re,itertools
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
base=Path('build/segments/ovl_7DF8.bin').read_bytes()
for fn in ['801BF720','801BF914']:
 orig=Path(f'tools/scratch/nonmatching/T-023/func_{fn}.c').read_text().split('*/',1)[1]
 d="' '" if fn=='801BF720' else '27'
 cases=list(re.finditer(r"(case (?:'.'|\d+):) return ('.'|\d+);",orig))
 for mask,default,init,action in itertools.product(range(32),range(4),range(3),['break','goto done']):
  st=orig
  for i,m in reversed(list(enumerate(cases))):
   if mask&(1<<i):st=st[:m.start()]+m[1]+' result = '+m[2]+'; '+action+';'+st[m.end():]
  st=st.replace("    result = ' ';\n",'').replace('    result = 27;\n','')
  if init==0:st=st.replace('s32 result;',f's32 result = {d};')
  if init==1:st=st.replace('    switch (code)',f'    result = {d};\n    switch (code)')
  if init==2:st=st.replace('    return result;',f'    result = {d};\n    return result;')
  defs=['',f'default: return {d};',f'default: result = {d}; break;',f'default: result = {d}; goto done;']
  st=st.replace('    }\n', '        '+defs[default]+'\n    }\n')
  if 'goto done' in st:st=st.replace('    return result;', 'done:\n    return result;')
  p=Path('/tmp/t043-sweep.c');p.write_text('#include "common.h"\n'+st)
  out=Path('/tmp/t043-sweep.o')
  r=subprocess.run(['tools/ext/ido/5.3/cc','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(out),str(p)],capture_output=True)
  if r.returncode:continue
  code,masks,*_=elf_function(out,'func_'+fn)
  if len(code)!=(104 if fn=='801BF720' else 116):continue
  target=base[int(fn,16)-0x801abb20: int(fn,16)-0x801abb20+len(code)]
  diffs=[i for i,(a,b,m) in enumerate(zip(struct.unpack('>'+str(len(code)//4)+'I',code),struct.unpack('>'+str(len(code)//4)+'I',target),masks)) if (a&m)!=(b&m)]
  if not diffs:
   print(fn,mask,default,init,action,flush=True);Path(f'tools/scratch/nonmatching/T-043/{fn}-candidate.c').write_text(st);break
 else:print(fn,'NO MATCH',flush=True)
