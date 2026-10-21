"""Compact original-assembly family comparison; generated products stay in /tmp."""
from pathlib import Path
import re, difflib, json
NAMES=['801BA088','801BA280','801BA470','801BA674','801BB024','801BB258','801BB594','801BADEC']
def instructions(n):
 p=next(Path('asm/nonmatchings/ovl_7DF8').glob('*/func_'+n+'.s'))
 return [m[1] for line in p.read_text().splitlines() if (m:=re.search(r'/\*.*?\*/\s+(.*)',line))]
def normalized(lines):
 return [re.sub(r'\$\w+','REG',re.sub(r'%[a-z]+\([^)]*\)|\.L\w+|0x[0-9A-Fa-f]+|(?<![\w])\d+','VALUE',line)) for line in lines]
if __name__=='__main__':
 base=instructions(NAMES[0]);out=[]
 for n in NAMES:
  ins=instructions(n);ops=[x.split()[0] for x in ins]
  out.append(dict(function='func_'+n,bytes=len(ins)*4,calls=[x for x in ins if x.startswith('jal')],normalized_similarity=round(difflib.SequenceMatcher(None,normalized(base),normalized(ins),autojunk=False).ratio(),3),stack=ins[0],float_conversions=ops.count('cvt.s.w')))
 print(json.dumps(out,indent=2))
