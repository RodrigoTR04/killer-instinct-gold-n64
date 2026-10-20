from probe import *
ROOT=Path('tools/scratch/nonmatching/T-059')
groups={'T-022':'1E0B4 18F20 1BB64 1D47C 1AD04','T-032':'24714 241BC 253D0','T-026':'30440','T-024':'2A4F0','T-033':'170C4 131A4'}
paths={n:Path('tools/scratch/nonmatching')/d/('func_800'+n+'.c') for d,ns in groups.items() for n in ns.split()}
paths = {n: ROOT / (n + "-base.c") if (ROOT / (n + "-base.c")).exists() else p for n,p in paths.items()}
rows=[]
def test(n,tag,s):
 r=probe(s,'func_800'+n); rows.append(dict(n=n,tag=tag,**r));
 (ROOT/(n+'-'+tag+'.c')).write_text(s)
 print(n,tag,r.get('words',r.get('error','')[:100]),r.get('bytes'),flush=True)
 return r
for n,p in paths.items():test(n,'base',p.read_text())
(ROOT/'results.json').write_text(json.dumps(rows,indent=2))
