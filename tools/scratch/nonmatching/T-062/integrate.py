import sys,re,pathlib
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu
fn=sys.argv[1];p=tu.draft(fn);t,_=tu.ctx(fn);s=p.read_text();s=re.sub(r'/\* DRAFT.*?\*/\s*','',s,count=1,flags=re.S);s=s.replace('#include "common.h"','');text=t.read_text();text=re.sub(r'#pragma GLOBAL_ASM\("[^"\n]*/'+fn+r'\.s"\)',lambda _:s.strip(),text);t.write_text(text);p.unlink();print(t,p)
