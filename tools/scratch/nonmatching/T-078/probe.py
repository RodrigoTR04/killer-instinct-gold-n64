#!/usr/bin/env python3
"""Complete SDK-file O1/O2/O3 probes; outputs compact relocation-masked diagnostics."""
import importlib.util,json,re,struct,subprocess,tempfile,os
from pathlib import Path
ROOT=Path.cwd()
spec=importlib.util.spec_from_file_location('cmp',ROOT/'tools/scratch/flagprobe/compare.py'); cmp=importlib.util.module_from_spec(spec);spec.loader.exec_module(cmp)
SDK=Path(os.environ.get('SDK_ROOT', '/tmp/t075-libreultra'))
private={'alAudioFrame':'80039C08','_bnkfPatchInst':'80037780','__getTrackByte':'80038DE0','__readVarLen':'80038EA4','readVarLen':'800414F8','read32':'80041978','read16':'800419C8','_getRate':'800405E4','_pullSubFrame':'800407B4','_getVol':'80040A4C','_decodeChunk':'8003FB20','__CSPVoiceHandler':'8003846C','__CSPHandleMIDIMsg':'80037C3C','__CSPHandleMetaMsg':'80037A6C','__seqpVoiceHandler':'8003E1DC','__handleMIDIMsg':'8003D9BC','__handleMetaMsg':'8003D71C','alFxParamHdl':'80042198','alFxNew':'8003EF90'}
rows=json.loads((ROOT/'tools/progress/original-functions.json').read_text()); rows={r['function']:r for r in rows.values() if r['area']=='main'}
ref=(ROOT/'build/segments/main.bin').read_bytes()
result=[]
for file in ['bnkf','csplayer','cseq','synthesizer','seqplayer','drvrNew','load','env','seq','reverb']:
 for opt in [1,2,3]:
  with tempfile.TemporaryDirectory() as tmp:
   obj=Path(tmp)/'p.o'; cmd=[str(ROOT/'tools/ext/ido/5.3/cc'),'-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-DNDEBUG',f'-O{opt}','-mips2','-32','-I'+str(SDK/'include/2.0I'),'-I'+str(SDK/'include/2.0I/PR'),str(SDK/f'src/audio/{file}.c'),'-o',str(obj)]
   cmd=[str(ROOT/'.venv/bin/python'), str(ROOT/'tools/ext/asm-processor/build.py'), *(['--force', '--convert-statics', 'global'] if file!='reverb' else []), *(['-O2'] if opt==3 else []), cmd[0], '--', str(ROOT/'tools/ext/binutils/bin/mips64-elf-as'), '-EB', '-mips3', '-32', '-G', '0', '--', *cmd[1:]]
   run=subprocess.run(cmd,capture_output=True,text=True)
   if run.returncode:
    result.append(dict(file=file,opt=opt,error=run.stderr[-2500:]));continue
   subprocess.run(['cp',str(obj),f'/tmp/t078-{file}-O{opt}.o'])
   syms=subprocess.check_output([str(ROOT/'tools/ext/binutils/bin/mips64-elf-nm'),'--defined-only',str(obj)],text=True)
   for name in re.findall(r'^\w+ [tT] (\S+)$',syms,re.M):
    target=('func_80037A30' if file=='csplayer' else 'sdk_inline_setUspt') if name=='__setUsptFromTempo' else ('func_'+private[name] if name in private else name)
    if target not in rows:continue
    row=rows[target];code,masks,_=cmp.elf_function(obj,name);
    if not code:
     # Static symbol sizes recovered from mdebug are zero; use next text symbol.
     pairs=[(int(a,16),n) for a,n in re.findall(r'^(\w+) [tT] (\S+)$',syms,re.M)];start=next(a for a,n in pairs if n==name);end=min([a for a,n in pairs if a>start] or [start+row['bytes']]);
     alias=Path(tmp)/'alias.o';subprocess.run([str(ROOT/'tools/ext/binutils/bin/mips64-elf-objcopy'),'--redefine-sym',name+'=probe_static',str(obj),str(alias)],check=True)
     # Use common ELF parser after assigning inferred symbol size.
     data=bytearray(alias.read_bytes());shoff=struct.unpack_from('>I',data,32)[0];esz,count=struct.unpack_from('>HH',data,46);secs=[struct.unpack_from('>10I',data,shoff+i*esz) for i in range(count)]
     for sec in secs:
      if sec[1]!=2:continue
      strings=data[secs[sec[6]][4]:secs[sec[6]][4]+secs[sec[6]][5]]
      for pos in range(sec[4],sec[4]+sec[5],sec[9]):
       no=struct.unpack_from('>I',data,pos)[0]
       if strings[no:strings.find(0,no)]==b'probe_static':struct.pack_into('>I',data,pos+8,end-start)
     alias.write_bytes(data);code,masks,_=cmp.elf_function(alias,'probe_static')
    off=int(row['vram'],16)-0x8000F960; original=ref[off:off+row['bytes']]
    a=list(struct.unpack('>%dI'%(len(code)//4),code));b=list(struct.unpack('>%dI'%(len(original)//4),original))
    diff=sum(i>=len(a) or i>=len(b) or (a[i]&masks[i])!=(b[i]&masks[i]) for i in range(max(len(a),len(b))))
    result.append(dict(file=file,opt=opt,name=name,target=target,size=len(code),original=len(original),diff=diff))
 Path('/tmp/t078-results.json').write_text(json.dumps(result,indent=2))
 print(file,[(r['opt'],r.get('target'),r.get('diff', 'ERROR')) for r in result if r['file']==file and (r.get('target','').startswith('func_') or r.get('diff')==0 or 'error' in r)],flush=True)
