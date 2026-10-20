import re,json,pathlib,struct
import tu,probe
out=pathlib.Path(__file__).parent;rows=json.loads((out/'results.json').read_text());remaining={}
for fn,row in rows.items():
 p=probe.ROOT/row['draft'];s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn)
 # Restore conventional typedef endings without changing function-body boundaries.
 s=re.sub(r'}\n(T\w+;)',r'} \1',s)
 r=probe.probe(fn,pre+'\n'+s);assert r==tuple(row['new']),(fn,r,row['new'])
 if r[0]<row['old'][0]:
  s=re.sub(r'/\*.*?\*/\s*','',s,flags=re.S).strip()+'\n'
  cand='/* T-074 DRAFT: '+str(r[0])+' differing words; '+str(r[1])+' bytes. Not matching. */\n'+s
  assert probe.probe(fn,pre+'\n'+cand)==r
  p.write_text(cand)
 else:assert probe.probe(fn,pre+'\n'+p.read_text())==r
 # Record compact final evidence, excluding duplicate compiler artifacts.
 code,masks,_=probe.cmp.elf_function(pathlib.Path('/tmp/t074-'+fn+'.o'),fn)
 target=(probe.ROOT/'build/segments/ovl_7DF8.bin').read_bytes();off=int(fn[5:],16)-0x801ABB20;target=target[off:off+probe.rows[fn]['bytes']]
 a=struct.unpack('>'+'I'*(len(code)//4),code);b=struct.unpack('>'+'I'*(len(target)//4),target)
 remaining[fn]={'offsets':[hex(i*4) for i,(x,y) in enumerate(zip(a,b)) if x&masks[i]!=y&masks[i]],'compiled_bytes':len(code),'target_bytes':len(target)}
 row['final']=list(r)
 print(fn,r,flush=True)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n');(out/'remaining-offsets.json').write_text(json.dumps(remaining,indent=2)+'\n')
