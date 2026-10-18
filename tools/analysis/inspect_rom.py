#!/usr/bin/env python3
"""Read-only ROM survey and minimal MIPS III disassembler; stdlib only."""
import sys,struct,hashlib,re,math,collections,zlib
b=open(sys.argv[1],'rb').read()
base=0x7ffff400
if '--main' in sys.argv:
 sys.argv.remove('--main'); b=zlib.decompress(b[0xA94D82:0xAB5800],-15);base=0x8000F960
def u(o):return struct.unpack_from('>I',b,o)[0]
R=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra']
def dis(o):
 w=u(o);op=w>>26;s=(w>>21)&31;t=(w>>16)&31;d=(w>>11)&31;im=w&65535;si=im if im<32768 else im-65536;pc=base+o
 if w==0:return 'nop'
 if op in (2,3):return ('j' if op==2 else 'jal')+' %08X'%((pc&0xf0000000)|((w&0x3ffffff)<<2))
 if op==0:
  f=w&63;n={0:'sll',2:'srl',3:'sra',8:'jr',9:'jalr',16:'mfhi',18:'mflo',24:'mult',25:'multu',26:'div',27:'divu',32:'add',33:'addu',34:'sub',35:'subu',36:'and',37:'or',38:'xor',42:'slt',43:'sltu'}.get(f,'special_%02x'%f)
  if f==8:return n+' '+R[s]
  if f in (0,2,3):return f'{n} {R[d]},{R[t]},{(w>>6)&31}'
  return f'{n} {R[d]},{R[s]},{R[t]}'
 if op in (4,5,6,7):return f'{["beq","bne","blez","bgtz"][op-4]} {R[s]},{R[t]},0x{pc+4+si*4:08X}'
 if op==15:return f'lui {R[t]},0x{im:04X}'
 n={8:'addi',9:'addiu',10:'slti',11:'sltiu',12:'andi',13:'ori',14:'xori',32:'lb',33:'lh',35:'lw',36:'lbu',37:'lhu',40:'sb',41:'sh',43:'sw',47:'cache',49:'lwc1',53:'ldc1',57:'swc1',61:'sdc1'}.get(op)
 if n:return f'{n} {R[t]},0x{im:04X}({R[s]})' if op>=32 else f'{n} {R[t]},{R[s]},{si if op<12 else hex(im)}'
 return 'word 0x%08X'%w
if len(sys.argv)>2:
 a=int(sys.argv[2],0);z=int(sys.argv[3],0)
 for o in range(a,z,4):print(f'{o:08X} {base+o:08X} {u(o):08X} {dis(o)}')
else:
 print('size',hex(len(b)),'sha1',hashlib.sha1(b).hexdigest());print('first64',b[:64].hex())
 if base==0x7ffff400:print('IPL3 md5',hashlib.md5(b[64:4096]).hexdigest(),'sha1',hashlib.sha1(b[64:4096]).hexdigest())
 for o in range(0,len(b),0x10000):
  block=b[o:o+0x10000];size=len(block);c=collections.Counter(block);h=-sum((n/size)*math.log2(n/size) for n in c.values());print('block %06X entropy %.3f zeros %.3f'%(o,h,c[0]/size))
 for m in re.finditer(rb'[ -~]{8,}',b):
  if any(x in m.group().lower() for x in [b'os',b'rare',b'ultra',b'error',b'.c',b'.h',b'killer',b'2.0',b'copyright',b'assert',b'build',b'init']):print('string %06X'%m.start(),repr(m.group()[:200]))
 for magic in [b'RNC',b'Yay0',b'Yaz0',b'MIO0',b'\x11\x72',b'\x78\x9c',b'\x78\xda']:
  hits=[m.start() for m in re.finditer(re.escape(magic),b)];print('magic',repr(magic),'count',len(hits),'first',[hex(x) for x in hits[:30]])
