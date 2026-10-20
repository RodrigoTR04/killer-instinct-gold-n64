from probe import *
import rabbitizer
s=Path(sys.argv[1]).read_text();fn=sys.argv[2] if len(sys.argv)>2 else re.findall(r'void (func_800[0-9A-F]+)\(',s)[-1];print(probe(s,fn))
c,m,_=elf_function(Path('/tmp/t059-probe.o'),fn);off=int(fn[5:],16)-0x8000f960
for i in range(0,len(c),4):
 a=struct.unpack_from('>I',c,i)[0];b=struct.unpack_from('>I',base,off+i)[0]
 if a&m[i//4]!=b&m[i//4]:print('%03x'%i,str(rabbitizer.Instruction(b)), '|',str(rabbitizer.Instruction(a)))
