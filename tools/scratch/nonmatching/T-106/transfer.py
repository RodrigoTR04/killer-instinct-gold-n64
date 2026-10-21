from pathlib import Path
import sys,re,subprocess,itertools,json
sys.path.insert(0,str(Path(__file__).resolve().parent));from probe import probe
from coordinates import calls
from analyze import NAMES
OUT=Path('/tmp/kig-t106-transfer');OUT.mkdir(exist_ok=True)
def source(n):
 fn='func_'+n;s=subprocess.check_output(['git','show','HEAD:tools/scratch/nonmatching/T-023/'+fn+'.c'],text=True)
 scale=re.search(r'    u16 (\w+);',s)[1];s=re.sub(r'\b'+scale+r'\b','arg4->scale',s);s=s.replace('    u16 arg4->scale;','').replace('    arg4->scale = arg4->scale;','')
 # Inline pure calculation temporaries into coordinate expressions and call operands.
 cs=calls(s);strip=lambda x:re.sub(r'^\(f32\)\s*','',x).strip()
 x0,x1,y1=map(strip,[cs[0][2][11],cs[1][2][11],cs[1][2][12]])
 y0=strip(cs[0][2][12]);y0=y0[1:-1] if y0.startswith('(') else y0
 s=s.replace(cs[0][2][12],'(f32) firstY',1);pos=s.index('    if (arg5 != 0)');s=s[:pos]+'    firstY = '+y0+';\n'+s[pos:]
 pos=s.index('{',s.index('void func_'))+1;s=s[:pos]+'\n    s32 firstY;'+s[pos:]
 # Retain coordinates, increment and counters; substitute every other pure prebranch temporary.
 boundary=s.index('    if (arg5 != 0)');pre=s[:boundary];tail=s[boundary:]
 names=re.findall(r'    s32 (\w+);',pre)
 coords={x0,x1,y1,'firstY'}
 for v in names:
  if v in coords:continue
  m=re.search(r'    '+v+r' = ([^;]+);\n',pre)
  if not m:continue
  expr=m[1];pre=pre[:m.start()]+pre[m.end():];pre=pre.replace('    s32 '+v+';','');pre=re.sub(r'\b'+v+r'\b','('+expr+')',pre);tail=re.sub(r'\b'+v+r'\b','('+expr+')',tail)
 s=pre+tail
 # Put coordinates in draw order. Shared x is assigned to its second local after firstX.
 a=s.index('    '+x0+' =');b=s.index('    if (arg5')
 assignments={m[1]:m[0] for m in re.finditer(r'    (\w+) = [^;]+;\n',s[a:b])}
 s=s[:a]+''.join(assignments[v] for v in dict.fromkeys([x0,'firstY',x1,y1]))+s[b:]
 counter=re.search(r'extern s32 (D_\w+);',s)
 ptr=None
 if counter:
  glob=counter[1];ptr='counter';pos=s.index('    '+x0+' =');s=s[:pos]+'    counter = &'+glob+';\n'+s[pos:].replace(glob,'*counter')
  pos=s.index('{',s.index('void func_'))+1;s=s[:pos]+'\n    s32 *counter;'+s[pos:]
 return s,ptr
if __name__=='__main__':
 rows=[]
 for n in NAMES[:7]:
  fn='func_'+n;s,ptr=source(n);a=s.index('{',s.index('void func_'))+1;b=s.index('    counter =' if ptr else '    '+re.search(r'    (\w+) =',s[a:])[1]+' =',a)
  decls=re.findall(r'    s32 (\*?\w+);',s[a:b]);best=(99999,0);chosen=s
  for order in itertools.permutations(decls):
   t=s[:a]+'\n'+''.join('    s32 '+v+';\n' for v in order)+'\n'+s[b:];score=probe(fn,t)
   if score[0]<best[0]:best=score;chosen=t
   if score[0]==0:break
  (OUT/(fn+'.c')).write_text(chosen);row=dict(function=fn,score=best);rows.append(row);print(row,flush=True)
 (OUT/'results.json').write_text(json.dumps(rows,indent=2))
