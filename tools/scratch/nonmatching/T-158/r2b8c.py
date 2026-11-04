import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-025/func_801B2B8C.c').read()
head,body=s.split("s32 func_801B2B8C")
body="s32 func_801B2B8C"+body
cands=[]
for tick,fade,value in itertools.product(('arg1','arg3','L'),repeat=3):
    b=body
    decl=""
    names={'tick':tick,'fade':fade,'value':value}
    nm={}
    for r,v in names.items():
        if v=='L': nm[r]=r+'_l'; decl+=f" s32 {r}_l;"
        else: nm[r]=v
    b=b.replace("arg3 = state->timer; phase = (f64)arg3;",f"{nm['tick']} = state->timer; phase = (f64){nm['tick']};").replace("state->timer = ++arg3;",f"state->timer = ++{nm['tick']};")
    b=b.replace("arg1 = state->fade;",f"{nm['fade']} = state->fade;").replace("if (arg1++ < 10)",f"if ({nm['fade']}++ < 10)").replace("state->fade = arg1",f"state->fade = {nm['fade']}")
    # value is u32 local; optional alias
    if value!='L' or True:
        if value!='L':
            b=b.replace("u32 value; ","").replace("value",nm['value'])
        b=b.replace("    u8 alpha;\n","    u8 alpha;"+decl+"\n",1)
    cands.append(((tick,fade,value),head+b))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,sx) in res[:12]: print(r,k)
