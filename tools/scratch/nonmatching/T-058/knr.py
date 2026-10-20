from search import *
def knr(fn):
 s=draft(fn); yield 'baseline',s
 m=re.search(r'\b'+fn+r'\(([^)]*)\)\s*{',s)
 if not m:return
 args=m[1].split(','); decl=[]; names=[]
 for arg in args:
  if arg.strip()=='void':continue
  z=re.search(r'(\w+)\s*(\[[^;]*\])?$',arg.strip())
  names.append(z[1]);decl.append(arg.strip()+';')
 for form in range(4):
  ds=decl[:]
  if form&1:ds=list(reversed(ds))
  if form&2:ds=[d.replace('float','double') for d in ds]
  yield f'K&R {form}',s[:m.start()]+fn+'('+','.join(names)+') '+''.join(ds)+' {'+s[m.end():]
for fn in sizes:test(fn,knr(fn))
