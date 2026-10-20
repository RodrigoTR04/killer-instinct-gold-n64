#!/usr/bin/env python3
"""Compile final audio TUs at O1/O2/O3 and compare complete padded .text.
Run from repo root after extract. Reports JSON diagnostics, never edits sources.
Only actual ELF relocation fields are masked. Linked make verification is final proof.
"""
from pathlib import Path
import re, subprocess, struct, tempfile, json
ref=Path('build/segments/main.bin').read_bytes()
units=re.findall(r'^build/src/main/main_(\w+)\.c\.o: CFLAGS := .* -O3 ',Path('Makefile').read_text(),re.M)
bounds=[int(x,16) for x in re.findall(r'\[0x([0-9A-F]+), (?:c|bin),',Path('kig.main.us.yaml').read_text())]
results=[]
for tu in units:
 start=int(tu,16);end=min(x for x in bounds if x>start)
 for opt in [1,2,3]:
  with tempfile.TemporaryDirectory() as tmp:
   obj=Path(tmp)/'p.o';cmd=['tools/ext/ido/5.3/cc','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul',f'-O{opt}','-mips2','-32','-Iinclude',f'src/main/main_{tu}.c','-o',str(obj)];r=subprocess.run(cmd,capture_output=True,text=True)
   if r.returncode:results.append(dict(tu=tu,opt=opt,error=r.stderr[-1000:]));continue
   data=obj.read_bytes();shoff=struct.unpack_from('>I',data,32)[0];esz,count,ni=struct.unpack_from('>HHH',data,46);secs=[struct.unpack_from('>10I',data,shoff+i*esz) for i in range(count)];names=data[secs[ni][4]:secs[ni][4]+secs[ni][5]]
   secnames=[names[sec[0]:names.index(0,sec[0])].decode() for sec in secs];ti=secnames.index('.text');t=secs[ti];code=data[t[4]:t[4]+t[5]];m=[0xffffffff]*(len(code)//4)
   for sec in secs:
    if sec[1]==9 and sec[7]==ti:
     for a in range(sec[4],sec[4]+sec[5],sec[9]):
      pos,info=struct.unpack_from('>II',data,a);kind=info&255
      if kind not in (4,5,6):raise ValueError(kind)
      m[pos//4]=0xfc000000 if kind==4 else 0xffff0000
   a=struct.unpack('>%dI'%(len(code)//4),code);b=struct.unpack('>%dI'%((end-start)//4),ref[start:end]);diff=sum(i>=len(a) or i>=len(b) or a[i]&m[i]!=b[i]&m[i] for i in range(max(len(a),len(b))))
   results.append(dict(tu=tu,opt=opt,size=len(code),original=end-start,diff=diff))
print(json.dumps(results,indent=2))
