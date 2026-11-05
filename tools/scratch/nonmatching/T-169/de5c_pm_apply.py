import sys
from pathlib import Path
src = Path(sys.argv[1]).read_text()
i = src.index('void func_8001DE5C')
body = src[i:]
hdr = Path('tools/scratch/nonmatching/T-162/func_8001DE5C.c').read_text().split('void func_8001DE5C')[0]
Path(sys.argv[2]).write_text(hdr + body)
