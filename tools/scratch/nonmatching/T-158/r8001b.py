import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read()
head,body=base.split('void func_8001BDE0')
body='void func_8001BDE0'+body
v={}
v['base']=body
v['A']=body.replace("f32 temp_f24;","f32 temp_f24; f32 new_var3;").replace("temp_f24 = D_800489F0;\n        arg2 = D_800489F4;","new_var3 = D_800489F4; temp_f24 = D_800489F0;\n        arg2 = new_var3;")
v['B']=body.replace("if (threshold < temp_f0_2) {","if ((temp_f0 = threshold) < temp_f0_2) {")
v['AB']=v['A'].replace("if (threshold < temp_f0_2) {","if ((temp_f0 = threshold) < temp_f0_2) {")
cands=list(v.items())
out=lib.run('func_8001BDE0',[head+s for k,s in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'/tmp/w/b8001_{k}.c','w').write(head+s)
