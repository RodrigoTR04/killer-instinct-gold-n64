import re,itertools,pathlib,json,random
import tu,probe
from reconcile import reconcile
out=pathlib.Path(__file__).parent
rows={}
for n in ['8002AEE4','8002F45C','80015F6C','80017378']:
 fn='func_'+n;s=reconcile(fn,tu.draft(fn).read_text());_,pre=tu.ctx(fn);best=probe.probe(fn,pre+'\n'+s);base=best;bs=s;vs=[]
 if n=='8002AEE4':
  for typ in ['u32','u8','s16','s32']:
   for end in ['done=ready;','done++;','done = message->type == 10;','done = 10;']:
    vs.append(s.replace('s32 done=0;',typ+' done=0;').replace('done=1;',end))
  vs += [s.replace('while(!done)', 'while(done == 0)'),s.replace('case 10: done=1;', 'case 10: done = ready = 1;')]
 if n=='8002F45C':
  # Local order controls real live spill placement; no dummy locals/padding.
  pattern=r'T024AllocatedVoice \*voice;\s*s32 old;\s*T024KeyMap \*key;\s*s32 pan;'
  ds=['T024AllocatedVoice *voice;','s32 old;','T024KeyMap *key;','s32 pan;']
  vs += [re.sub(pattern,'\n'.join(p),s) for p in itertools.permutations(ds)]
  vs += [s.replace('s32 pan;',t+' pan;') for t in ['u32','s16','u8']]
 if n=='80015F6C':
  for stores in itertools.permutations(['D_8004ACD0[0] = 255;','D_8004ACD0[1] = 255;','D_8004ACD0[2] = 255;']):
   vs.append(re.sub(r'D_8004ACD0\[1\] = 255; D_8004ACD0\[0\] = 255; D_8004ACD0\[2\] = 255;', '\n'.join(stores),s))
  vs += [s.replace('D_8004ACD0[1] = 255; D_8004ACD0[0] = 255; D_8004ACD0[2] = 255;','D_8004ACD0[0] = D_8004ACD0[1] = D_8004ACD0[2] = 255;')]
 if n=='80017378':
  vs += [s.replace('model++;','++model;').replace('rot++;','++rot;')]
 count=0
 for v in vs:
  for style in range(4):
   c=v
   if style&1:c=re.sub(r';[^\S\n]+',';\n',c)
   if style&2:c=re.sub(r'\)\s*\{',')\n{',c)
   r=probe.probe(fn,pre+'\n'+c);count+=1
   if r[0]<best[0]:best=r;bs=c;print(fn,best,flush=True)
 (out/(fn+'.focused.c')).write_text(bs)
 rows[fn]={'old':base,'new':best,'probes':count}
(out/'focused.json').write_text(json.dumps(rows,indent=2)+'\n')
