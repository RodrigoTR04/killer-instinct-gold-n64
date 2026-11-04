import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-158/w_2b8c_dw.c').read()
tail_old="""if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255; p0 = (*arg0)++; p0->w0 = 0xB900031D; p0->w1 = 0x0F0A4000;
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    p0 = (*arg0)++; p0->w0 = 0x06000000; p0->w1 = (u32)&D_801D3030;"""
assert tail_old in s
def tail(a,b,c,layout):
    if layout==0:
        return f"""if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255; {a} = (*arg0)++; {a}->w0 = 0xB900031D; {a}->w1 = 0x0F0A4000;
    {b} = (*arg0)++; {b}->w0 = 0xFB000000; {b}->w1 = (alpha + D_801D3094) & 0xFF;
    {c} = (*arg0)++; {c}->w0 = 0x06000000; {c}->w1 = (u32)&D_801D3030;"""
    if layout==1:
        return f"""if (D_801D3094 < 0) {{ D_802C87D0 = D_801D3094 + 255; }} else {{ D_802C87D0 = 255; }}
    {a} = (*arg0)++;
    {a}->w0 = 0xB900031D; {a}->w1 = 0x0F0A4000;
    {b} = (*arg0)++;
    {b}->w0 = 0xFB000000; {b}->w1 = (alpha + D_801D3094) & 0xFF;
    {c} = (*arg0)++;
    {c}->w0 = 0x06000000; {c}->w1 = (u32)&D_801D3030;"""
cands=[]
for names in [('p0','p0','p0'),('p0','p1','p0'),('p1','p0','p1'),('p0','p1','p1'),('p1','p1','p0'),('p0','p1','p2'),('p2','p2','p2'),('p1','p1','p1'),('p0','p0','p1')]:
    for layout in (0,1):
        t=tail(*names,layout)
        x=s.replace(tail_old,t)
        if 'p2' in names: x=x.replace("    T025Gfx2B8C *p0;\n","    T025Gfx2B8C *p0; T025Gfx2B8C *p2;\n")
        cands.append(((names,layout),x))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,x) in sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1])): print(r,k)
