#!/usr/bin/env python3
"""Compile pinned SM64 library sources only; never invokes make."""
import concurrent.futures,json,pathlib,subprocess
ROOT=pathlib.Path(__file__).resolve().parents[3]
BASE=ROOT/'tools/scratch/libultra'; SM=BASE/'sm64'; OUT=BASE/'build'
def build(p):
 rel=p.relative_to(SM); obj=OUT/rel.with_suffix('.o');obj.parent.mkdir(parents=True,exist_ok=True)
 defines=['-DVERSION_US','-DTARGET_N64','-D_LANGUAGE_C','-DF3D_OLD','-D_FINALROM']
 inc=['-I'+str(SM/x) for x in ['include','include/libc','lib/src']]
 if p.suffix=='.c':
  opt='-O3' if p.stem.startswith(('gu','al')) else '-O1'
  if p.parent.name=='math' or p.stem in ('string','ldiv'):opt='-O2'
  isa=['-mips2','-32']
  if p.stem.startswith('ll'):isa=['-mips3','-32'];opt='-O1'
  flags=['-G','0',opt,'-nostdinc','-non_shared','-Wab,-r4300_mul','-Xcpluscomm','-signed',*isa,*defines,*inc]
  cmd=[str(ROOT/'tools/ext/ido/5.3/cc'),'-c',*flags,str(p),'-o',str(obj)]
  r=subprocess.run(cmd,capture_output=True)
 else:
  flags=['-EB','-mips3','-32','--defsym','VERSION_US=1','--defsym','F3D_OLD=1']
  pp=subprocess.run(['cpp','-P','-D_LANGUAGE_ASSEMBLY',*defines[:2],'-DF3D_OLD','-D_FINALROM',*inc,str(p)],capture_output=True)
  r=pp if pp.returncode else subprocess.run([str(ROOT/'tools/ext/binutils/bin/mips64-elf-as'),*flags,'-I'+str(SM/'include'),'-o',str(obj)],input=pp.stdout,capture_output=True)
 return dict(source=str(rel),object=str(obj.relative_to(BASE)),flags=((' '.join(flags)) if p.suffix=='.c' else ('cpp -P -D_LANGUAGE_ASSEMBLY -DVERSION_US -DTARGET_N64 -DF3D_OLD -D_FINALROM '+' '.join(inc)+' | as '+' '.join(flags)+' -Ism64/include')).replace(str(SM)+'/','sm64/'),ok=r.returncode==0,error=r.stderr.decode(errors='replace') if r.returncode else '')
def main():
 OUT.mkdir(exist_ok=True)
 paths=sorted([p for p in (SM/'lib/src').rglob('*.c') if 'libgcc' not in p.parts]+list((SM/'lib/asm').glob('*.s')))
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool: rows=list(pool.map(build,paths))
 (OUT/'manifest.json').write_text(json.dumps(rows,indent=2)+'\n')
 print(f"Built {sum(r['ok'] for r in rows)}/{len(rows)} objects; failures recorded in build/manifest.json")
if __name__=='__main__':main()
