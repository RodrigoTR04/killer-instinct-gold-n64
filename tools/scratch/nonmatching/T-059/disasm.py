from probe import *
import rabbitizer
n=sys.argv[1]; start=int('800'+n,16)-0x8000f960
for i in range(0,int(sys.argv[2]) if len(sys.argv)>2 else 748,4): print('%03x'%i,str(rabbitizer.Instruction(struct.unpack_from('>I',base,start+i)[0])))
