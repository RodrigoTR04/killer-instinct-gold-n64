import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-025/func_801B2B8C.c').read()
old="""        state->fade = arg1; p0 = (*arg0)++;
        p0->w0 = 0xFA000000;
    value = D_802C87D0 & 0xFF;
        p0->w1 = (value << 24) | (value << 16) | (value << 8) | (alpha & 0xFF);
        alpha = 0xFF;
        if ((s32)D_801D308C <= 0) D_801D308C += 1;
"""
assert old in s
new1="""        state->fade = arg1;
        do {
            p0 = (*arg0)++;
            p0->w0 = 0xFA000000;
            value = D_802C87D0 & 0xFF;
            p0->w1 = (value << 24) | (value << 16) | (value << 8) | (alpha & 0xFF);
            alpha = 0xFF;
            if ((s32)D_801D308C >= 1) {
                break;
            }
            D_801D308C += 1;
        } while (0);
"""
new2=new1.replace("p0 = (*arg0)++;\n            p0->w0 = 0xFA000000;","p1 = (*arg0)++;\n            p1->w0 = 0xFA000000;").replace("p0->w1 = (value","p1->w1 = (value")
cands=[('orig',s),('dowhile_p0',s.replace(old,new1)),('dowhile_p1',s.replace(old,new2))]
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,x) in zip(out,cands): print(r,k)
for k,x in cands: open(f'/tmp/w/r2b8c6_{k}.c','w').write(x)
