"""Record pool references in retained assembly and C, including empty TUs."""
import pathlib,re,json,yaml
out=[]
for im,base,lo,hi in [('main',0x8000f960,0x38e00,0x39e10),('ovl_7DF8',0x801abb20,0xe6c90,0xe9bd0)]:
 cfg=yaml.safe_load(pathlib.Path(f'kig.{im}.us.yaml').read_text())
 seg=cfg['segments'][0]['subsegments']
 entries=[]
 for e in seg:
  if isinstance(e,list) and len(e)>2:entries.append((e[0],e[1],e[2]))
  elif isinstance(e,dict) and 'start' in e:entries.append((e['start'],e['type'],e['name']))
 ranges={name:(start,entries[i+1][0]) for i,(start,typ,name) in enumerate(entries[:-1]) if typ=='.rodata'}
 for _,typ,tu in entries:
  if typ!='c':continue
  src=pathlib.Path(f'src/{im}/{tu}.c');text=src.read_text()
  paths=[src]+[pathlib.Path(p) for p in re.findall(r'GLOBAL_ASM\("([^"]+)"',text)]
  refs={}
  for p in paths:
   if not p.exists():continue
   for sym,a in re.findall(r'((?:D_|jtbl_)([0-9A-F]{8}))',p.read_text()):
    off=int(a,16)-base
    if lo<=off<hi:refs.setdefault(hex(off),[]).append(p.stem)
  out.append({'image':im,'tu':tu,'owned_range':ranges.get(tu),'pool_refs':{k:sorted(set(v)) for k,v in refs.items()}})
pathlib.Path('tools/scratch/nonmatching/T-091/inventory.json').write_text(json.dumps(out,indent=2))
