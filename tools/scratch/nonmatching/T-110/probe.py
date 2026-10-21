"""Full-TU frontend draft measurement; no production files modified."""
from pathlib import Path
import importlib.util
import json
import sys
ROOT=Path(__file__).resolve().parents[4]
spec=importlib.util.spec_from_file_location('screen',ROOT/'tools/permuter/screen.py')
screen=importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
NAMES='801BFCBC 801C0800 801C08F8 801C11F0 801C1434 801C17D0 801C1990 801C1C34 801C224C 801C23C0 801C2ADC 801C2F5C 801C317C 801C3758 801C7A98 801C7F90 801C8004 801C80F0 801C8AE0 801C8C24 801C90D4 801C9698 801C9B14 801CAA00'.split()
def draft(n): return next((ROOT/'tools/scratch/nonmatching').glob('T-*/func_'+n+'.c'))
if __name__=='__main__':
 names=sys.argv[1:] or NAMES
 results=[]
 for n in names:
  r=screen.screen(('func_'+n,draft(n)))
  results.append(r)
  print(json.dumps(r),flush=True)
