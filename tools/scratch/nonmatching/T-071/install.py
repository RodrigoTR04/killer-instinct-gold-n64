import re,json,pathlib
import tu,probe
out=pathlib.Path(__file__).parent;rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 if row['new'][0]>=row['old'][0]:continue
 p=probe.ROOT/row['draft'];old=p.read_text();s=(out/(fn+'.best.c')).read_text()
 def split(t):
  m=re.search(r'[^\n]*\b'+fn+r'\s*\(',t);return t[:m.start()],t[m.start():]
 head,_=split(old);_,body=split(s)
 head=re.sub(r'/\*.*?\*/\s*','',head,flags=re.S).replace('#include "common.h"','').strip()
 cand=head+'\n\n'+body
 _,pre=tu.ctx(fn);assert probe.probe(fn,pre+'\n'+cand)==tuple(row['new']),fn
 if row['new'][0]==0:
  path=probe.ROOT/row['tu'];t=path.read_text();pat=r'#pragma GLOBAL_ASM\("[^"]*/'+fn+r'\.s"\)'
  t,n=re.subn(pat,cand,t);assert n==1;path.write_text(t);p.unlink()
 else:p.write_text('/* T-071 DRAFT: '+str(row['new'][0])+' differing words; layout-sensitive scheduling. */\n'+cand)
 print(fn,'installed',flush=True)
