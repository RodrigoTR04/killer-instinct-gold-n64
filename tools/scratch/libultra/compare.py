#!/usr/bin/env python3
"""Compare the excluded inventory against rebuilt ELF symbols, never export ROM data."""
import collections,csv,hashlib,json,pathlib,struct
from build import ROOT,BASE

def elf(path):
 b=path.read_bytes(); shoff=struct.unpack_from('>I',b,32)[0]; ent,n,si=struct.unpack_from('>HHH',b,46)
 ss=[struct.unpack_from('>10I',b,shoff+i*ent) for i in range(n)]
 def data(s):return b[s[4]:s[4]+s[5]]
 def string(blob,o):return blob[o:blob.index(b'\0',o)].decode()
 sn=data(ss[si]); ti=next((i for i,s in enumerate(ss) if string(sn,s[0])=='.text'),None)
 if ti is None:return []
 text=bytearray(data(ss[ti])); masks={};symbols=[]
 for s in ss:
  if s[1]==9 and s[7]==ti:
   for pos in range(s[4],s[4]+s[5],s[9]):
    off,info=struct.unpack_from('>II',b,pos);kind=info&255
    if kind==10:
     sy=ss[s[6]]; sp=sy[4]+(info>>8)*sy[9]; _,value,_,_,_,idx=struct.unpack_from('>IIIBBH',b,sp)
     assert idx==ti, 'external PC16 relocation unsupported'
     word=struct.unpack_from('>I',text,off)[0]; addend=word&65535; addend=addend if addend<32768 else addend-65536
     struct.pack_into('>I',text,off,(word&0xffff0000)|((value//4+addend-off//4)&65535)); continue
    if kind not in (4,5,6):raise ValueError(f'{path}: unsupported text relocation {kind}')
    masks[off]=0xfc000000 if kind==4 else 0xffff0000
  if s[1]==2:
   strings=data(ss[s[6]])
   for pos in range(s[4],s[4]+s[5],s[9]):
    no,val,size,info,other,idx=struct.unpack_from('>IIIBBH',b,pos)
    if idx==ti and no and (info&15 in (0,2)):
     name=string(strings,no)
     if not name.startswith(('.', '$')):symbols.append((val,size,name))
 result=[]
 for val,size,name in sorted(symbols):
  end=val+size if size else min([v for v,_,_ in symbols if v>val]+[len(text)])
  if end<=val:continue
  result.append(dict(name=name,offset=val,raw=text[val:end],masks=[masks.get(o,0xffffffff) for o in range(val,end,4)],inferred=not size,text_size=len(text),text=bytes(text),rel=masks))
 return result

def main():
 manifest=json.loads((BASE/'build/manifest.json').read_text());refs=collections.defaultdict(list)
 for obj in manifest:
  if obj['ok']:
   for sym in elf(BASE/obj['object']):refs[sym['name']].append(dict(sym,**obj))
 inventory=[]
 for seg in ('boot','main'):
  for row in csv.DictReader((ROOT/f'tools/analysis/data/{seg}_functions.csv').open()):inventory.append(dict(row,segment=seg))
 status=[r for r in csv.DictReader((ROOT/'tools/progress/status.csv').open()) if 'libultra' in r['note']]
 rom=(ROOT/'baserom.us.z64').read_bytes()
 assert hashlib.sha1(rom).hexdigest()=='ba52e91b44450c548467044b26951353dc491e04'
 main=(ROOT/'build/segments/main.bin').read_bytes()
 expected=next(r for r in json.loads((ROOT/'build/segments/manifest.json').read_text()) if r['name']=='main')
 assert hashlib.sha1(main).hexdigest()==expected['sha1']
 rows=[]
 for st in status:
  targets=[r for r in inventory if r['name']==st['name_or_vram'] or (r['start'].lower()==st['name_or_vram'].split(':')[-1].lower() and (':' not in st['name_or_vram'] or r['segment']==st['name_or_vram'].split(':')[0]))]
  assert len(targets)==1,(st,targets)
  t=targets[0];addr=int(t['start'],16);size=int(t['size'],16);seg=t['segment'];name=t['name']
  data=rom if seg=='boot' else main;off=addr-0x7ffff400 if seg=='boot' else addr-0x8000f960
  target=data[off:off+size];candidates=[]
  for ref in refs[name]:
   raw=ref['raw'];note='';n=len(raw)
   if ref['inferred']:
    n=min(size,ref['text_size']-ref['offset']); raw=ref['text'][ref['offset']:ref['offset']+n]
    ref=dict(ref,masks=[ref['rel'].get(o,0xffffffff) for o in range(ref['offset'],ref['offset']+n,4)])
   # Symbol size omits inter-function alignment; infer assembly extents from next label.
   if n<=size and target[n:]==bytes(size-n):
    a=struct.unpack('>%dI'%(n//4),target[:n]);b=struct.unpack('>%dI'%(n//4),raw)
    equal=all((x&m)==(y&m) for x,y,m in zip(a,b,ref['masks']))
    result=('MATCH' if target[:n]==raw else 'MATCH_MASKED') if equal else 'NO_MATCH'
    note=f'body={n}; padding={size-n}; object_offset=0x{ref["offset"]:X}'
    if not equal:note+='; differing unmasked words='+str(sum((x&m)!=(y&m) for x,y,m in zip(a,b,ref['masks'])))
   else:result='NO_MATCH';note=f'object extent={n}; inventory extent={size}; size/padding mismatch'
   candidates.append(({'MATCH':0,'MATCH_MASKED':1,'NO_MATCH':2}[result],ref['source'],result,note,ref))
  if candidates:
   _,source,result,note,ref=min(candidates,key=lambda r:(r[0],r[1]));flags=ref['flags']
  else:source='';flags='';result='NOT_FOUND';note='No named text symbol in pinned SM64-US lib sources'
  rows.append(dict(segment=seg,vram=f'0x{addr:08X}',name=name,bytes=size,result=result,sm64_source=source,flags=flags,note=note))
 with (BASE/'results.csv').open('w') as f:
  w=csv.DictWriter(f,fieldnames=['segment','vram','name','bytes','result','sm64_source','flags','note']);w.writeheader();w.writerows(rows)
 placements={}
 for row in rows:
  for ref in refs[row['name']]:
   if ref['source']!=row['sm64_source']:continue
   base=int(row['vram'],16)-ref['offset'];key=(row['segment'],base,ref['source'])
   text=ref['text'];n=len(text);data=rom if row['segment']=='boot' else main
   off=base-(0x7ffff400 if row['segment']=='boot' else 0x8000f960);target=data[off:off+n]
   equal=len(target)==n and all((a&ref['rel'].get(i*4,0xffffffff))==(b&ref['rel'].get(i*4,0xffffffff)) for i,(a,b) in enumerate(zip(struct.unpack('>%dI'%(n//4),target),struct.unpack('>%dI'%(n//4),text))))
   placements[key]=dict(segment=row['segment'],base=f'0x{base:08X}',end=f'0x{base+n:08X}',source=ref['source'],text_bytes=n,masked_match=equal)
 (BASE/'build/placements.json').write_text(json.dumps([placements[k] for k in sorted(placements)],indent=2)+'\n')
 for result in ('MATCH','MATCH_MASKED','NO_MATCH','NOT_FOUND'):
  subset=[r for r in rows if r['result']==result];print(result,len(subset),sum(r['bytes'] for r in subset))
if __name__=='__main__':main()
