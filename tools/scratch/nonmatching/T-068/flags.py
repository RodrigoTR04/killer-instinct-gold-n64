import os,re,sys,json,struct,subprocess
from pathlib import Path
import probe,tu
flags=['-Xcpluscomm -Wab,-r4300_mul -O2 -mips2','-Xcpluscomm -Wab,-r4300_mul -O2 -mips1','-Xcpluscomm -Wab,-r4300_mul -O1 -mips2','-Wab,-r4300_mul -O2 -mips2']
results={}
for off in ['13FF0','190B0','1BD90']:
 p=probe.ROOT/('src/ovl_7DF8/ovl_7DF8_'+off+'.c');s=re.sub(r'#pragma GLOBAL_ASM\([^)]*\)','',p.read_text());s=s.replace('#include "common.h"','')
 names=re.findall(r'^\w[^\n;]*\b(func_[0-9A-F]+)\([^;]*?\)\s*\{',s,re.M)
 results[off]={}
 for flag in flags:
  os.environ['PROBE_FLAGS']=flag
  rows={n:probe.probe(n,s) for n in names if n in probe.rows}
  results[off][flag]=rows
  bad={n:r for n,r in rows.items() if r[0]}
  print(off,flag,'matched',len(rows)-len(bad),'/',len(rows),'failures',bad,flush=True)
Path(__file__).with_name('flags.json').write_text(json.dumps(results,indent=2)+'\n')
