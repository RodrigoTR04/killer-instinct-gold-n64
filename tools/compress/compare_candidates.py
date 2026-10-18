#!/usr/bin/env python3
"""Compare gzip levels and all zlib level/memLevel/strategy combinations.

Run verify_all.py --json /tmp/kig-t008/verification.json first.
Output contains only stream metadata and Huffman code lengths.
"""
import sys,json,pathlib,zlib,subprocess
from rarezip import build
binary = build()
from deflate_info import inspect
r=pathlib.Path('baserom.us.z64').read_bytes(); rows=json.load(open('/tmp/kig-t008/verification.json')); report=[]
for e in [rows[0],rows[1],rows[3],rows[-2],rows[-1]]:
 o=r[e['start']+2:e['stream_end']];d=zlib.decompress(o,-15); results={}
 for l in range(1,10):
  b=subprocess.check_output([str(binary),'-n',f'-{l}','-c'],input=d)[10:-8]
  results['gzip124-'+str(l)]={'size':len(b),'match':b==o,'first_difference':next((i for i,(a,b) in enumerate(zip(o,b)) if a!=b),None if o==b else min(len(o),len(b)))}
 matches=[]; best=(0,None)
 for l in range(1,10):
  for m in range(1,10):
   for strategy in range(5):
    z=zlib.compressobj(l,zlib.DEFLATED,-15,m,strategy); b=z.compress(d)+z.flush()
    i=next((i for i,(a,b) in enumerate(zip(o,b)) if a!=b),min(len(o),len(b)))
    if i>best[0]:best=(i,(l,m,strategy,len(b)))
    if o==b:matches.append((l,m,strategy))
 blocks=inspect(o)
 report.append(dict(name=e['name'],gzip=results,zlib_matches=matches,zlib_best_prefix=best,blocks=blocks))
 print(e['name'],'blocks',[(b['type'],b['expanded_end'],b['tokens']) for b in blocks],'zlib',matches,'best',best)
pathlib.Path('/tmp/kig-t008/experiments.json').write_text(json.dumps(report,indent=2))
