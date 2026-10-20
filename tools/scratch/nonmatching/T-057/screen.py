from sweep import *
names=['801C51F8','801B2010','801B21B4','801B2358','801B24FC','801B26A0','801B2844','801B29E8','801B6A68','801C6A80','801B2EF4','801B310C','801B3324','801B353C','801B3754','801B396C']
rs=[]
for n in names:
 n='func_'+n;p=next((ROOT/'tools/scratch/nonmatching').glob('T-0[123]*/'+n+'.c'));r=probe(n,p.read_text());rs.append(dict(name=n,path=str(p.relative_to(ROOT)),score=r));print(n,r,flush=True)
(out/'baseline.json').write_text(json.dumps(rs,indent=2))
