import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
rows={};candidates=[]
for n in ['801B2010','801B21B4','801B2358','801B24FC','801B26A0','801B2844','801B29E8']:
 fn='func_'+n;p=ROOT/'tools/scratch/nonmatching/T-025'/(fn+'.c');t=p.read_text();start=t.index('    arg1 = *counter;');end=t.index('    guTranslate',start)
 t=t[:start]+'    /* Keep the counter block joined for IDO instruction scheduling. */\n    '+re.sub(r'\s+',' ',t[start:end]).strip()+'\n'+t[end:]
 temp=OUT/(fn+'-final-draft.c');temp.write_text(t);r=__import__('screen').measure(fn,temp);print(r,flush=True);rows[fn]=r
 if r['words']==0:candidates.append((fn,p,t[t.index('extern f32'):]))
(OUT/'promotion.json').write_text(json.dumps(rows,indent=2))
assert len(candidates)==7
p=ROOT/'src/ovl_7DF8/ovl_7DF8_5ED0.c';s=p.read_text()
for fn,draft,t in candidates:
 s,n=re.subn(r'#pragma GLOBAL_ASM\("[^"\n]*/'+fn+r'.s"\)',lambda m:t.rstrip(),s);assert n==1
p.write_text(s)
for fn,draft,t in candidates:draft.unlink()
