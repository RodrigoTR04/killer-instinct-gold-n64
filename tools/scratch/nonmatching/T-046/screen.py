"""Screen main float/switch drafts with production flags and ELF relocation masks."""
from pathlib import Path
import sys, subprocess, struct, re, json
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
base=Path('build/segments/main.bin').read_bytes()
rows=[]
for task in ['T-020','T-022','T-024','T-026','T-032','T-033','T-035']:
 for p in sorted(Path('tools/scratch/nonmatching',task).glob('func_800*.c')):
  s=p.read_text()
  if not re.search(r'\bswitch\b|\d\.\d',s): continue
  fn=p.stem
  src=Path('/tmp/t046-screen.c');obj=Path('/tmp/t046-screen.o')
  src.write_text('#include "common.h"\nextern f32 sinf(f32), cosf(f32);\n'+s)
  r=subprocess.run(['tools/ext/ido/5.3/cc','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(obj),str(src)],capture_output=True,text=True)
  row={'draft':str(p)}
  if r.returncode:row['error']=r.stderr[:700]
  else:
   try:
    code,masks,_=elf_function(obj,fn)
    addr=int(fn[5:],16);off=addr-0x8000f960
    target=base[off:off+len(code)]
    diff=[i*4 for i,(a,b,m) in enumerate(zip(struct.unpack('>'+str(len(code)//4)+'I',code),struct.unpack('>'+str(len(code)//4)+'I',target),masks)) if a&m!=b&m]
    row.update(bytes=len(code),words=len(diff),offsets=diff[:10])
   except Exception as e:row['error']=str(e)
  rows.append(row)
Path('tools/scratch/nonmatching/T-046/screen.json').write_text(json.dumps(rows,indent=2)+'\n')
for row in sorted(rows,key=lambda r:r.get('words',10000)):print(row)
