import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=source(fn);a,b,br=extent(s,fn);body=s[a:b];start=body.index('    arg1 = D_801D309C;');end=body.index('    guTranslate',start);jobs=[]
for name in ['arg1','arg3','count']:
 for mode in ['pre','post','separate','pointerpre','pointerpost']:
  for cache in [True,False]:
   head='    '+name+' = '+('*counter' if cache else 'D_801D309C')+';\n'
   sym='*counter' if cache else 'D_801D309C'
   pred=name+' < 1'
   if mode=='post':pred=name+'++ < 1'
   inc={'pre':sym+' = ++'+name,'post':sym+' = '+name,'separate':sym+' = '+name,'pointerpre':'++'+sym,'pointerpost':'('+sym+')++'}[mode]
   prefix='        ++'+name+';\n' if mode=='separate' else ''
   callarg=name if mode in ['separate','post'] else '('+inc+')'
   assign=prefix+('        '+inc+';\n' if mode in ['separate','post'] else '')
   t=body[:start]+head+'    if ('+pred+') {\n'+assign+'        position = func_801B19F0(-6.0f, -150.0f, '+callarg+', 1);\n    } else {\n'+prefix+'        '+inc+';\n        position = -150.0f;\n    }\n'+body[end:]
   if cache:t=t.replace('s32 alpha;','s32 alpha;\n s32 *counter = &D_801D309C;')
   if name=='count':t=t.replace('s32 alpha;','s32 alpha;\n s32 count;')
   # Pointer postfix produces old value in call, explicitly add one.
   if mode=='pointerpost':t=t.replace('('+inc+'), 1)', '('+inc+' + 1), 1)')
   jobs.append((name+'-'+mode+'-'+str(cache),t))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<14:
  p=OUT/(fn+'-family-'+label+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=4) as pool:rows=list(pool.map(run,jobs))
(OUT/'family.json').write_text(json.dumps(rows,indent=2))
