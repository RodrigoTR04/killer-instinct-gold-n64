from pathlib import Path
import sys,re,json
sys.path.insert(0,'tools/scratch/nonmatching/T-096')
from probe import compile,source
from context import extent
OUT=Path('/tmp/kig-t098');OUT.mkdir(exist_ok=True)
fn='func_801B2EF4'
if __name__=='__main__':
 s=source(fn);(OUT/'base.c').write_text(s)
 print(compile(fn,s,'baseline',True))
 a,b,_=extent(s,fn); t=s[a:b]
 t=t.replace('    u8 alpha;','    u8 alpha;\n    s32 *counter = &D_801D30C0;')
 t=t.replace('    if (D_801D30C0++ < 10)','    arg1 = *counter;\n    if (arg1++ < 10)')
 t=t.replace('D_801D30C0, 10','*counter = arg1, 10').replace('    else\n    {','    else\n    {\n        *counter = arg1;')
 s=s[:a]+t+s[b:];(OUT/'pointer.c').write_text(s)
 r=compile(fn,s,'pointer',True);(OUT/'pointer.json').write_text(json.dumps(r,indent=2));print(r)
