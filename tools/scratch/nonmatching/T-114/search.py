from pathlib import Path
import sys,subprocess,importlib.util,re,json,shlex,time,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');P=R/'tools/ext/decomp-permuter'
spec=importlib.util.spec_from_file_location('strip',P/'strip_other_fns.py');strip=importlib.util.module_from_spec(spec);spec.loader.exec_module(strip)
rows=[]
for full in O.glob('*-full.c'):
 fn=full.name[:-7];s=full.read_text().replace('extern s32 func_801BF914(s32);','extern s32 func_801BF914(u32);');full.write_text(s)
 out=O/fn;out.mkdir(exist_ok=True)
 c=out/'context.c';c.write_text(re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)','',s))
 pp=subprocess.check_output(['gcc','-E','-P','-Iinclude',str(c)],text=True)
 (out/'base.c').write_text(strip.strip_other_fns(pp,fn))
 asm=next((R/'asm').glob('*/nonmatchings/*/'+fn+'.s'),None)
 if asm is None:asm=next((R/'asm').rglob(fn+'.s'))
 (out/'target.s').write_text((P/'prelude.inc').read_text()+'\n'+re.sub(r'^\s*\.late_rodata_alignment[^\n]*','',asm.read_text(),flags=re.M))
 subprocess.run([str(R/'tools/ext/binutils/bin/mips64-elf-as'),'-EB','-mips3','-32','-G','0','-Iinclude','-o',str(out/'target.o'),str(out/'target.s')],check=True)
 cmd=[R/'.venv/bin/python',R/'tools/ext/asm-processor/build.py',R/'tools/ext/ido/5.3/cc','--',R/'tools/ext/binutils/bin/mips64-elf-as','-EB','-mips3','-32','-G','0','-I',R/'include','--','-c','-G','0','-non_shared','-Xcpluscomm','-Wab,-r4300_mul','-O2','-mips2','-32','-I'+str(R/'include')]
 (out/'compile.sh').write_text('#!/bin/sh\nset -eu\nexec '+shlex.join(map(str,cmd))+' "$@"\n');(out/'compile.sh').chmod(0o755)
 (out/'settings.toml').write_text('func_name = '+json.dumps(fn)+'\ncompiler_type = "ido"\nobjdump_command = '+json.dumps(str(R/'tools/ext/binutils/bin/mips64-elf-objdump')+' -drz -m mips:4300')+'\n')
 rows.append((fn,out))
def run(item):
 fn,out=item;t=time.time()
 with (out/'search.log').open('w') as log:
  p=subprocess.run(['timeout','--signal=INT','--kill-after=15s','1800s',str(R/'.venv/bin/python'),str(P/'permuter.py'),str(out),'--stack-diffs','--stop-on-zero','--best-only','--better-only','-j','6'],stdout=log,stderr=subprocess.STDOUT)
 r=dict(function=fn,seconds=time.time()-t,exit=p.returncode);print(json.dumps(r),flush=True);return r
with concurrent.futures.ThreadPoolExecutor(max_workers=10) as pool:res=list(pool.map(run,rows))
(R/'tools/scratch/nonmatching/T-114/searches.json').write_text(json.dumps(res,indent=2)+'\n')
