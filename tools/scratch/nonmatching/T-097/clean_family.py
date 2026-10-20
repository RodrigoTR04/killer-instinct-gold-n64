import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=(OUT/(fn+'-family2-call-store-_counter.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];rows=[]
start=body.index('    arg1 = *counter;');end=body.index('    guTranslate',start)
for mode in range(4):
 t=body[:start]+re.sub(r'\s+',' ',body[start:end]).strip()+'\n'+body[end:]
 if mode&1:t=t.replace('s32 alpha;\n s32 *counter','s32 alpha; s32 *counter')
 if mode&2:t=t.replace('T025Gfx2010 *env;\n    if','T025Gfx2010 *env; if')
 r=compile(fn,s[:a]+t+s[b:],str(mode),True);print(r,flush=True);rows.append(r)
 if r.get('words')==0:(OUT/('family-clean-'+str(mode)+'.c')).write_text(s[:a]+t+s[b:])
(OUT/'family-clean.json').write_text(json.dumps(rows,indent=2))
