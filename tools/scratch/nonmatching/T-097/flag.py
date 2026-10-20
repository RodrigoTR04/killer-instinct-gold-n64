import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801C6A80';s=(OUT/(fn+'-cached-flag.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];jobs=[]
for var in ['arg0','temp_v0','temp_t9','var_v0']:
 t=body.replace('if (*flag == 0)',f'if (({var} = *flag) == 0)').replace('*flag += 1;',f'*flag = {var} + 1;')
 jobs.append(('value-'+var,t))
for anchor in ['s32 temp_v0;','u32 var_v0;','u8 temp_t9;','u32 *phase = &D_802921D4;']:
 t=body.replace('    u8 *flag = &D_802D3984;','').replace(anchor,anchor+'\n u8 *flag = &D_802D3984;');jobs.append(('decl-'+anchor,t))
for point in ['if (arg1 < 0xF0U) {','if (temp_v0 >= 0xB) {']:
 t=body.replace('    u8 *flag = &D_802D3984;','').replace(point,point+'\n u8 *flag = &D_802D3984;');jobs.append(('scope-'+point,t))
for expr in ['*flag = *flag + 1;','++*flag;','(*flag)++;','D_802D3984 = *flag + 1;']:
 jobs.append(('update-'+expr,body.replace('*flag += 1;',expr)))
for typ in ['const u8 *','volatile u8 *','u8 * const']:
 jobs.append(('pointer-'+typ,body.replace('u8 *flag',typ+'flag')))
for join in ['all','condition','declarations']:
 t=body
 if join=='all':t=re.sub(r'\n\s*',' ',t)
 if join=='condition':t=t.replace('if (*flag == 0) {\n                *flag += 1;', 'if (*flag == 0) { *flag += 1;')
 if join=='declarations':t=t.replace('u8 temp_t9;\n    u8 *flag','u8 temp_t9; u8 *flag')
 jobs.append(('layout-'+join,t))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<4:
  p=OUT/(fn+'-flag-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=3) as pool:rows=list(pool.map(run,jobs))
(OUT/'flag.json').write_text(json.dumps(rows,indent=2))
