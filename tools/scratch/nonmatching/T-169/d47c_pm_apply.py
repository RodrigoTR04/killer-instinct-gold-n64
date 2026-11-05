import re, sys
from pathlib import Path
src = Path(sys.argv[1]).read_text()
i = src.index('void func_8001D47C')
body = src[i:]
for junk in ['      if (i && i)\n      {\n      }\n']:
    body = body.replace(junk, '')
hdr = Path('tools/scratch/nonmatching/T-022/func_8001D47C.c').read_text().split('void func_8001D47C')[0]
out = Path(sys.argv[2]); out.write_text(hdr + body)
print(out)
