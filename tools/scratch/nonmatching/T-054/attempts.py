from probe import *
# Shared declarations reproduce production types; no source TU is edited by probes.
DECLS='''extern void *D_8004A4C0[];
extern u8 D_8004AA28,D_8004AC88,D_8004A730[8];
extern s8 D_8004A5E0,D_8004A738,D_8004AC89,D_8004AC8A,D_8004AC8C;
extern u8 D_8004EA9E[];
extern f32 D_8004A740[],D_8004A800[],D_8004A860[],D_8004A8C0[],D_8004A920[],D_8004A7A0;
extern f32 D_8004AC80,D_8004AC84,D_8004ACE0,D_8004ACE4;
extern s32 D_8004ACF0,D_8004ACF8;
extern u8 *D_8004AA3C;
extern s32 (*D_8004AEAC)(s32,s32,s32,s32);
extern void (*D_8004AA30)(void),(*D_8004AA34)(T020Position *),(*D_8004AA38)();
extern void func_80019880(void),func_8001372C(T020Position *);
'''
def reconcile(s):
 # Only add declarations absent from the draft, preserving its existing declarations.
 add=[]
 for line in DECLS.splitlines():
  typ,rest=line.rsplit(' ',1) if False else ('','')
  # Decompose via known single-name declarations generated below.
 for name,decl in declarations.items():
  if name in s and not re.search(r'^extern [^;{}]*\b'+name+r'\b[^;{}]*;',s,re.M):add.append(decl)
 s=s.replace('extern u8 D_8004A730;', 'extern u8 D_8004A730[8];')
 s=re.sub(r'\bD_8004A730\s*=', 'D_8004A730[0] =',s)
 return '\n'.join(add)+'\n'+s
# Exact production declarations, one at a time to avoid duplicate/conflicting declarations.
declarations={}
for line in DECLS.splitlines():
 for name in re.findall(r'\b(?:D|func)_800[0-9A-F]+',line):
  if '(*' in line:
   if name=='D_8004AEAC': decl='extern s32 (*D_8004AEAC)(s32,s32,s32,s32);'
   elif name.startswith('func'): decl='extern void '+name+(' (T020Position *);' if name.endswith('1372C') else '(void);')
   else: decl='extern void (*'+name+')'+('(T020Position *);' if name.endswith('34') else '();')
  else:
   ty=re.match(r'extern (\w+)',line)[1]; star='*' if name=='D_8004AA3C' else ''
   if name=='D_8004A4C0':ty='void';star='*'
   arr='[8]' if name=='D_8004A730' else ('[]' if name in ['D_8004A4C0','D_8004EA9E','D_8004A740','D_8004A800','D_8004A860','D_8004A8C0','D_8004A920'] else '')
   decl='extern '+ty+' '+star+name+arr+';'
  if name.startswith('func_'):decl='extern void '+name+('(T020Position *);' if name.endswith('1372C') else '(void);')
  declarations[name]=decl
if __name__=='__main__':
 rows=[]
 for p in paths:
  s=reconcile(p.read_text());r=probe(s,p.stem);rows.append({'draft':str(p),**r});(ROOT/(p.stem+'-base.c')).write_text(s)
  print(p.stem,{k:v for k,v in r.items() if k!='offsets'},flush=True)
 (ROOT/'reconciled.json').write_text(json.dumps(rows,indent=2)+'\n')
