import pathlib,subprocess,json
hints={
'main_1BE80':'\nD_80048D70 = 0x80048D70; // type:f32 force_migration:True function_owner:func_8002BBD0\nD_80048EDC = 0x80048EDC; // type:f32 force_migration:True function_owner:func_8002BBD0\n',
'main_1E7F0': ''.join(f'\nD_{a:X} = 0x{a:X}; // force_migration:True function_owner:func_8002E150\n' for a in [0x80048EE0,0x80048F10,0x80048F38,0x80048F58]),
'ovl_7DF8_2380':'\nD_802927E0 = 0x802927E0; // type:f32 force_migration:True function_owner:func_801ADEA0\n',
}
candidates=[('main','main_1BE80',0x39410,0x39580),('main','main_1E7F0',0x39580,0x39650),('ovl_7DF8','ovl_7DF8_2380',0xe6cc0,0xe6cd0),('ovl_7DF8','ovl_7DF8_13FF0',0xe7160,0xe7ca0),('ovl_7DF8','ovl_7DF8_1B790',0xe8da0,0xe93f0),('ovl_7DF8','ovl_7DF8_1BD90',0xe93f0,0xe9a40)]

import re
for tu,owner in [('ovl_7DF8_3F60','func_801B1210'),('ovl_7DF8_5ED0','func_801B2B8C'),('ovl_7DF8_116E0','func_801BE660')]:
 missing=sorted(set(re.findall(r"undefined reference to `([^']+)'",pathlib.Path(f'/tmp/t091-{tu}.log').read_text())))
 hints[tu]=''.join(f'\n{sym} = 0x{sym.split("_")[-1]}; // force_migration:True function_owner:{owner}\n' for sym in missing)
candidates[3:3]=[('ovl_7DF8','ovl_7DF8_3F60',0xe6cd0,0xe6e40),('ovl_7DF8','ovl_7DF8_5ED0',0xe6e40,0xe7030),('ovl_7DF8','ovl_7DF8_116E0',0xe7030,0xe70d0)]
results=json.loads(pathlib.Path('tools/scratch/nonmatching/T-091/results.json').read_text())
for im,tu,start,end in candidates:
 sym=pathlib.Path(f'symbol_addrs.{im}.us.txt'); symold=sym.read_text(); sym.write_text(symold + hints.get(tu,''))
 p=pathlib.Path(f'kig.{im}.us.yaml'); old=p.read_text(); lines=old.splitlines(True)
 # Locate enclosing asm fragment using parsed yaml positions.
 import yaml
 entries=yaml.safe_load(old)['segments'][0]['subsegments']; spans=[]
 for e in entries:
  off=e[0] if isinstance(e,list) else e.get('start')
  if isinstance(off,int):spans.append((off,e))
 owner=max((v for v in spans if v[0]<=start),key=lambda x:x[0]); nextoff=min(v[0] for v in spans if v[0]>owner[0])
 if not isinstance(owner[1],dict) or owner[1].get('type')!='data':raise Exception(owner)
 replacement=[]
 if owner[0]<start:replacement.append('      - '+ '{start: 0x%X, type: data, name: %s, linker_section_order: .rodata}\n'%(owner[0],owner[1]['name']))
 replacement.append('      - [0x%X, .rodata, %s]\n'%(start,tu))
 if end<nextoff:replacement.append('      - {start: 0x%X, type: data, name: t091_after_%s, linker_section_order: .rodata}\n'%(end,tu))
 idx=next(i for i,l in enumerate(lines) if 'name: '+owner[1]['name']+',' in l)
 lines[idx:idx+1]=replacement;p.write_text(''.join(lines))
 log=pathlib.Path(f'/tmp/t091-{tu}.log')
 with log.open('w') as out:r=subprocess.run('make clean && make extract && make -j4 all',shell=True,stdout=out,stderr=subprocess.STDOUT)
 if r.returncode:
  p.write_text(old);sym.write_text(symold)
 results.append([im,tu,hex(start),hex(end),'done' if not r.returncode else 'reverted',str(log)])
 pathlib.Path('tools/scratch/nonmatching/T-091/results.json').write_text(json.dumps(results,indent=2))
 print(tu,results[-1][4],flush=True)
