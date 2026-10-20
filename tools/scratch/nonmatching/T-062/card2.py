import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801B6528';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0;vs=[]
for rt,pt,mt,arity in itertools.product(['s32','u32','u8','s16','u16'],['void *','T029Card *','u32 *','const T029Card *'],['void *','Mtx *','u32 *','f32 *'],[3,4]):
 v=s.replace('s32 func_801B6528(',rt+' func_801B6528(').replace('void *arg1',pt+'arg1').replace('void *arg2',mt+'arg2')
 if arity==3:v=v.replace(', s32 arg3)',')')
 vs.append((str((rt,pt,mt,arity)),v))
for typ in ['s32','u32','s16','u16','s8','u8']:
 for scoped in [False,True]:
  v=s
  if scoped:v=v.replace('    s32 index;','').replace('if (D_802C8CE0 != 3) {','if (D_802C8CE0 != 3) {\n        '+typ+' index;').replace('    } else {','    } else {\n        '+typ+' index;')
  else:v=v.replace('s32 index;',typ+' index;')
  vs.append(('scope'+typ+str(scoped),v))
for ret in ['void','s32','u32','f32','f64','s64']:
 for pt in ['void *','Mtx *','u32 *','u8 *']:
  vs.append(('translate'+ret+pt,s.replace('extern void guTranslate(void *, f32, f32, f32);','extern '+ret+' guTranslate('+pt+', f32, f32, f32);')))
for fieldtype in ['u32','s16','u16','s8','u8']:
 for cast in ['', '(s32)', '(u32)']:
  v=s.replace('u8 pad[12]; s32 index;','u8 pad['+str(12+(4-{'u32':4,'s16':2,'u16':2,'s8':1,'u8':1}[fieldtype]))+']; '+fieldtype+' index;').replace('((T029Card *)arg1)->index',cast+'((T029Card *)arg1)->index');vs.append(('field'+fieldtype+cast,v))
for name,v in vs:
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,name,r,flush=True)
print('final',n,best)
