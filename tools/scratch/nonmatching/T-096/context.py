"""Function order, linkage, prototypes and global storage diagnostics."""
from probe import *
from concurrent.futures import ThreadPoolExecutor

def extent(s,fn):
 m=re.search(r'(?m)^(?:void \*|[\w *]+)'+fn+r'\([^;{}]*\)\s*\{',s)
 if not m: raise ValueError(fn)
 a=m.start(); b=s.index('{',m.start()); level=1; i=b+1
 while level:
  level+=(s[i]=='{')-(s[i]=='}'); i+=1
 return a,i,b

def variants(fn,s):
 a,b,brace=extent(s,fn)
 body=s[a:b]; sig=s[a:brace].strip()
 yield 'static-linkage', s[:a]+'static '+s[a:]
 # Move target to TU end with original prototype; diagnostic placement only.
 yield 'target-last',s[:a]+sig+';\n'+s[b:]+'\n'+body+'\n'
 # Substitute other definitions with declarations while retaining source lines.
 other=s[:a]+sig+';\n'+s[b:]
 # Definition extraction by balanced braces, preserving typedefs and pragmas.
 pattern=r'(?m)^(?:[\w]+[ \t]+)+\*?([\w]+)\([^;{}]*\)\s*\{'
 for m in reversed(list(re.finditer(pattern,other))):
  pos=m.end()-1; depth=1; i=pos+1
  while depth:
   depth+=(other[i]=='{')-(other[i]=='}'); i+=1
  other=other[:pos]+';'+other[i:]
 yield 'declarations-only',other+'\n'+body
 # Ordinary prototypes without parameter types: ABI diagnostics, not retained.
 callees=set(re.findall(r'\b([A-Za-z_]\w*)\s*\(',body))-{'if','while','for','switch','sizeof',fn}
 for callee in sorted(callees):
  pat=r'(extern\s+[\w *]+\b'+callee+r')\([^;{}]*\);'
  t,n=re.subn(pat,r'\1();',s)
  if n: yield 'unprototyped-'+callee,t
 # Equivalent known-size and alignment declarations.
 globals=set(re.findall(r'\bD_[0-9A-F]+\b',body))
 for sym in sorted(globals):
  pat=r'(extern\s+[\w *]+\b'+sym+r')\[\];'
  for size in ['1','2','256']:
   t,n=re.subn(pat,r'\1['+size+'];',s)
   if n: yield sym+'-size-'+size,t
  pat=r'(extern\s+[\w *]+\b'+sym+r'(?:\[[^;]*\])?);'
  t,n=re.subn(pat,r'\1 __attribute__((aligned(8)));',s)
  if n: yield sym+'-align8',t

def main():
 rows={}
 for n in FUNCTIONS:
  fn='func_'+n; s=source(fn)
  baseline=compile(fn,s,'baseline',True); rows[fn]=[baseline]
  print(fn,baseline,flush=True)
  jobs=list(variants(fn,s))
  def run(item):
   name,src=item; r=compile(fn,src,name)
   if 'words' in r and r['words'] < baseline.get('words',999): (WORK/(fn+'-'+name+'.c')).write_text(src)
   return r
  with ThreadPoolExecutor(max_workers=4) as pool:
   for r in pool.map(run,jobs):
    rows[fn].append(r)
    if 'error' not in r: print(fn,r['label'],r['words'],r['bytes'],flush=True)
 (WORK/'context.json').write_text(json.dumps(rows,indent=2))
if __name__=='__main__': main()
