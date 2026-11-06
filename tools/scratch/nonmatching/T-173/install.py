import sys,re
fn,draft,tu=sys.argv[1:4]
d=open(draft).read()
d=re.sub(r'^/\*.*?\*/\n','',d,flags=re.S) if d.startswith('/*') else d
d=d.replace('#include "frontend.h"\n','')
t=open(tu).read()
pat=re.compile(r'#pragma GLOBAL_ASM\("[^"\n]*/'+re.escape(fn)+r'\.s"\)\n')
assert len(pat.findall(t))==1
t=pat.sub(lambda m:d.lstrip('\n').rstrip('\n')+'\n',t)
open(tu,'w').write(t)
