"""Retry standalone failures within a copy of their current owning TU."""
from pathlib import Path
import sys,subprocess,json,struct
sys.path.insert(0,'tools/scratch/flagprobe')
from compare import elf_function
rows=json.loads(Path('tools/scratch/nonmatching/T-046/screen.json').read_text());base=Path('build/segments/main.bin').read_bytes()
for row in rows:
 if 'error' not in row:continue
 p=Path(row['draft']);fn=p.stem
 owner=next((f for f in Path('src/main').glob('*.c') if '/'+fn+'.s"' in f.read_text()),None)
 if owner is None:continue
 source=owner.read_text();start=source.index('#pragma GLOBAL_ASM(',source.rfind('\n',0,source.index('/'+fn+'.s"')))
 end=source.index('\n',start)
 source=source[:start]+p.read_text()+source[end:]
 src=Path('/tmp/t046-context.c');obj=Path('/tmp/t046-context.o');src.write_text(source)
 r=subprocess.run(['.venv/bin/python','tools/ext/asm-processor/build.py','tools/ext/ido/5.3/cc','--','tools/ext/binutils/bin/mips64-elf-as','-EB','-mips3','-32','-G','0','-I','include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(obj),str(src)],capture_output=True,text=True)
 row['context_tu']=str(owner)
 if r.returncode:row['context_error']=r.stderr[-1500:];continue
 try:
  code,masks,_=elf_function(obj,fn);off=int(fn[5:],16)-0x8000f960;target=base[off:off+len(code)]
  diff=[i*4 for i,(a,b,m) in enumerate(zip(struct.unpack('>'+str(len(code)//4)+'I',code),struct.unpack('>'+str(len(code)//4)+'I',target),masks)) if a&m!=b&m]
  row.update(context_bytes=len(code),context_words=len(diff),context_offsets=diff[:10])
 except Exception as e:row['context_error']=str(e)
 print(fn,row.get('context_words',row.get('context_error','')),flush=True)
Path('tools/scratch/nonmatching/T-046/screen.json').write_text(json.dumps(rows,indent=2)+'\n')
