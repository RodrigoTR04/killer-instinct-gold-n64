import sys,pathlib,struct,json,os,subprocess,re
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
out={}
for n in '2010 21B4 2358 24FC 26A0 2844 29E8 2EF4 310C 3324 353C 3754 396C'.split():
 fn='func_801B'+n;p=tu.draft(fn);_,pre=tu.ctx(fn);score=probe.probe(fn,pre+p.read_text());o=pathlib.Path('/tmp/t077-'+str(os.getpid())+'-'+fn+'.o');code,masks,_=probe.cmp.elf_function(o,fn);off=int(fn[5:],16)-0x801ABB20;target=(probe.ROOT/'build/segments/ovl_7DF8.bin').read_bytes()[off:off+probe.rows[fn]['bytes']];aa=struct.unpack('>'+'I'*(len(code)//4),code);bb=struct.unpack('>'+'I'*(len(target)//4),target);diff=[hex(i*4) for i,(a,b) in enumerate(zip(aa,bb)) if a&masks[i]!=b&masks[i]];out[fn]={'score':score,'offsets':diff}
 if n=='2010':pathlib.Path('/tmp/t077-final-A-disassembly.txt').write_text(subprocess.check_output([str(probe.ROOT/'tools/ext/binutils/bin/mips64-elf-objdump'),'-dr',str(o)],text=True))
pathlib.Path(__file__).with_name('remaining-offsets.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps(out,indent=2))
