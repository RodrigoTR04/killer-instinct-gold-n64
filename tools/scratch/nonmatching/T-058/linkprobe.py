from probe import *
import os
# Resolve relocations with the real linker and current image symbol addresses.
syms={}
for elf in ['build/main.elf','build/kig.us.elf']:
 r=subprocess.run(['tools/ext/binutils/bin/mips64-elf-nm','-g','--defined-only',elf],capture_output=True,text=True)
 for line in r.stdout.splitlines():
  p=line.split()
  if len(p)==3:
   try:syms[p[2]]=int(p[0],16)
   except ValueError:pass
script='\n'.join('PROVIDE('+n+' = '+hex(v)+');' for n,v in syms.items())
def linked(fn,s,label='test',rodata=0x81000000):
 r=probe(fn,s,label)
 if 'error' in r:return r
 stem='/tmp/t058-'+str(os.getpid());p=Path(stem+'.ld');e=Path(stem+'.elf');b=Path(stem+'.bin')
 extra='\n'.join('PROVIDE('+n+' = 0x'+n[2:]+');' for n in set(re.findall(r'\bD_[0-9A-F]{8}\b',s)) if n not in syms)
 p.write_text('SECTIONS { .text '+fn[5:].replace('800','0x800',1)+' : SUBALIGN(4) { *(.text) } .rodata '+hex(rodata)+' : { *(.rodata) *(.rdata) } /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.mdebug*) } }\n'+script+'\n'+extra)
 z=subprocess.run(['tools/ext/binutils/bin/mips64-elf-ld','-T',str(p),'-o',str(e),stem+'.o'],capture_output=True,text=True)
 if z.returncode:r['link_error']=z.stderr[-1500:];return r
 z=subprocess.run(['tools/ext/binutils/bin/mips64-elf-objcopy','-O','binary','-j','.text',str(e),str(b)],capture_output=True,text=True)
 code=b.read_bytes()[:r['bytes']];off=int(fn[5:],16)-0x8000f960
 dif=[i for i in range(0,len(code),4) if code[i:i+4]!=base[off+i:off+i+4]]
 r['linked_words']=len(dif);r['linked_offsets']=dif
 return r
if __name__=='__main__':print(linked(sys.argv[1],Path(sys.argv[2]).read_text()))
