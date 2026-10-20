import re,json,pathlib,subprocess,struct
import probe,tu
from reconcile import reconcile
from complete_context import prepare
out=pathlib.Path(__file__).parent
rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 tu_path=probe.ROOT/row['tu'];text=tu_path.read_text();candidate=out/(fn+'.best.c');s=candidate.read_text() if candidate.exists() else reconcile(fn,tu.draft(fn).read_text());pat=r'#pragma GLOBAL_ASM\("[^"]*/'+fn+r'\.s"\)'
 text,s=prepare(fn,text,s)
 text,n=re.subn(pat,lambda m:s,text);assert n==1
 p=pathlib.Path('/tmp/t072-full-'+fn+'.c');o=p.with_suffix('.o');p.write_text(text)
 cmd=['.venv/bin/python','tools/ext/asm-processor/build.py','tools/ext/ido/5.3/cc','--','tools/ext/binutils/bin/mips64-elf-as','-EB','-mips3','-32','-G','0','-I','include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-Iinclude','-o',str(o),str(p)]
 r=subprocess.run(cmd,capture_output=True,text=True)
 if r.returncode:print(fn,r.stderr[-2000:],flush=True);row['full_tu_error']=r.stderr[-2000:];continue
 row.pop('full_tu_error',None)
 code,masks,_=probe.cmp.elf_function(o,fn);off=int(fn[5:],16)-0x8000F960;target=(probe.ROOT/'build/segments/main.bin').read_bytes()[off:off+probe.rows[fn]['bytes']]
 a=struct.unpack('>%dI'%(len(code)//4),code);b=struct.unpack('>%dI'%(len(target)//4),target)
 dif=[i*4 for i,(x,y) in enumerate(zip(a,b)) if x&masks[i]!=y&masks[i]]
 score=(len(dif)+abs(len(a)-len(b)),len(code));row['full_tu']=score;row['offsets']=dif
 print(fn,score,'expected',row['new'],flush=True)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
