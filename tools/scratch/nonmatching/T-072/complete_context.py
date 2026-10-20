# Reuse later TU declarations before compiling a candidate; source bodies stay intact.
import re

def prepare(fn,text,s):
 if fn.endswith('15F6C'):
  decl='extern s32 func_8002F8F8(s32), func_8002F6F4(s32, s32, s32 *);'
  text=text.replace(decl,'')
  s=s.replace('extern void func_8002F8F8(void *);','').replace('extern void * func_8002F6F4(void *, s16, void **);','')
  s=decl+'\n'+s.replace('(void *)D_8004A264','D_8004A264').replace('(void *)D_80066C40','D_80066C40').replace('(void **)&D_8004A264','&D_8004A264')
 if fn.endswith('2B22C'):
  a=text.index('typedef struct T024DmaBuffer');b=text.index('\nvoid *func_8002B3A8',a);decl=text[a:b];text=text[:a]+text[b:]
  s=s.replace('extern T024Cache D_80068158;','').replace('D_80068158.', '((T024Cache *)&D_80068158)->').replace('u32 func_8002B22C(u32 address,s32 length,s32 unused)','s32 func_8002B22C(s32 address,s32 length,void *unused)')
  s=decl+'\n'+s
 if fn.endswith('287D4'):
  decl='typedef struct { float x,y,z; s16 active,timer; } T024Particle;\nextern T024Particle D_80061538[][20];'
  text=text.replace(decl,'')
  s=re.sub(r'typedef struct \{[^{}]*\}\s*T024MovingParticle;','',s).replace('extern T024MovingParticle D_80061538[][20];','').replace('T024MovingParticle','T024Particle').replace('p->speed','p->active')
  s=decl+'\n'+s
 if fn.endswith('2A4F0'):
  decl='typedef struct {\n    void *unused;\n    void *start;\n} T052SequenceEntry;\n\nextern T052SequenceEntry *D_80066C28;'
  text=text.replace(decl,'')
  s=s.replace('extern T024SeqFile *D_80066C28;','').replace('D_80066C28->','((T024SeqFile *)D_80066C28)->')
  s=decl+'\n'+s
 return text,s
