from probe import *
import concurrent.futures
results=[]
def run(n,label,c):
 fn='func_'+n;s=(WORK/(fn+'.c')).read_text();d=draft(fn).read_text(); candidate=c
 if d not in s:
  p=WORK/(fn+'-input-'+label+'.c');p.write_text(c)
  for pr,de in [(False,False),(True,False),(True,True)]:
   try:screen.measure(fn,p,pr,de,source_output=p.with_suffix('.ctx'));s=p.with_suffix('.ctx').read_text();d=s;c=s;break
   except Exception:pass
 try:r=compile(fn,s.replace(d,c),label,True)
 except Exception as e:r={'error':str(e)}
 results.append(dict(function=fn,label=label,**{k:v for k,v in r.items() if k!='label'}))
 print(n,label,r.get('words'),r.get('bytes'),r.get('error','')[-80:],flush=True)
 if 'words' in r:(WORK/(fn+'-'+label+'.c')).write_text(candidate)
