import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read()
head,body=base.split('void func_8001BDE0')
body='void func_8001BDE0'+body
old="temp_f24 = D_800489F0;\n        arg2 = D_800489F4;"
assert old in body
body=body.replace("f32 temp_f24;","f32 temp_f24; f32 new_var3; f32 new_var4;")
cands=[]
alts={
'o1':"temp_f24 = D_800489F0; new_var3 = D_800489F4; arg2 = new_var3;",
'o2':"new_var3 = D_800489F4; temp_f24 = D_800489F0; arg2 = new_var3;",
'o3':"new_var3 = D_800489F4; arg2 = new_var3; temp_f24 = D_800489F0;",
'o4':"new_var4 = D_800489F0; new_var3 = D_800489F4; temp_f24 = new_var4; arg2 = new_var3;",
'o5':"new_var4 = D_800489F0; new_var3 = D_800489F4; arg2 = new_var3; temp_f24 = new_var4;",
'o6':"new_var4 = D_800489F0; temp_f24 = new_var4; new_var3 = D_800489F4; arg2 = new_var3;",
'o7':"temp_f24 = D_800489F0; new_var3 = D_800489F4; arg2 = new_var3;",
'o8':"new_var3 = D_800489F4; temp_f24 = D_800489F0; threshold = threshold; arg2 = new_var3;",
}
for k,a in alts.items(): cands.append((k,head+body.replace(old,a)))
# also: scale local instead of arg2
b2=body.replace("arg2) - temp_f24","new_var3) - temp_f24")
for k,a in alts.items():
    s=b2.replace(old,a.replace("arg2 = new_var3;",""))
    cands.append((k+'_noarg',head+s))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'/tmp/w/b8001c_{k}.c','w').write(s)
