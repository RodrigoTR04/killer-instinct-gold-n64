import pathlib,re,subprocess,sys,struct
sys.path.insert(0,str(pathlib.Path(__file__).parent))
import probe,tu

def check(fn,draft, changes=()):
 source,_=tu.ctx(fn);text=source.read_text()
 for a,b in changes:text=text.replace(a,b)
 text=re.sub(r'#pragma GLOBAL_ASM\("[^"\n]*/'+fn+r'\.s"\)',lambda _:draft,text)
 p=pathlib.Path('/tmp/t087-full-'+fn+'.c');p.write_text(text);o=p.with_suffix('.o')
 cmd=[str(probe.ROOT/'.venv/bin/python'),str(probe.ROOT/'tools/ext/asm-processor/build.py'),str(probe.ROOT/'tools/ext/ido/5.3/cc'),'--',str(probe.ROOT/'tools/ext/binutils/bin/mips64-elf-as'),'-EB','-mips3','-32','-G','0','-I','include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(o),str(p)]
 r=subprocess.run(cmd,capture_output=True,text=True)
 if r.returncode:print(r.stdout,r.stderr);return None
 code,masks,_=probe.cmp.elf_function(o,fn);off=int(fn[5:],16)-0x801ABB20;target=(probe.ROOT/'build/segments/ovl_7DF8.bin').read_bytes()[off:off+probe.rows[fn]['bytes']]
 a=struct.unpack('>'+str(len(code)//4)+'I',code);b=struct.unpack('>'+str(len(target)//4)+'I',target)
 return sum(x&masks[i]!=y&masks[i] for i,(x,y) in enumerate(zip(a,b)))+abs(len(a)-len(b)),len(code)
if __name__=='__main__':
 for f in sys.argv[1:]:
  p=pathlib.Path(f);fn=re.search(r'func_801[0-9A-F]+',p.name)[0];print(fn,check(fn,p.read_text()))
