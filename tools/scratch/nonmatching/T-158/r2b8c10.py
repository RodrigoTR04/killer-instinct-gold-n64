import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-158/w_2b8c_dw.c').read()
tail_old="""p0 = (*arg0)++; p0->w0 = 0xB900031D; p0->w1 = 0x0F0A4000;
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    p0 = (*arg0)++; p0->w0 = 0x06000000; p0->w1 = (u32)&D_801D3030;"""
assert tail_old in s
def blk(i): return f"{{ T025Gfx2B8C *q{i} = (*arg0)++;"
variants={
'blockscoped':"""{ T025Gfx2B8C *q2 = (*arg0)++; q2->w0 = 0xB900031D; q2->w1 = 0x0F0A4000; }
    { T025Gfx2B8C *q3 = (*arg0)++; q3->w0 = 0xFB000000; q3->w1 = (alpha + D_801D3094) & 0xFF; }
    { T025Gfx2B8C *q4 = (*arg0)++; q4->w0 = 0x06000000; q4->w1 = (u32)&D_801D3030; }""",
'blockscoped2':"""{ T025Gfx2B8C *q2 = (*arg0)++; q2->w0 = 0xB900031D; q2->w1 = 0x0F0A4000;
    T025Gfx2B8C *q3 = (*arg0)++; q3->w0 = 0xFB000000; q3->w1 = (alpha + D_801D3094) & 0xFF;
    T025Gfx2B8C *q4 = (*arg0)++; q4->w0 = 0x06000000; q4->w1 = (u32)&D_801D3030; }""",
'first_p1':"""p1 = (*arg0)++; p1->w0 = 0xB900031D; p1->w1 = 0x0F0A4000;
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    p1 = (*arg0)++; p1->w0 = 0x06000000; p1->w1 = (u32)&D_801D3030;""",
'blk_only_last':"""p0 = (*arg0)++; p0->w0 = 0xB900031D; p0->w1 = 0x0F0A4000;
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    { T025Gfx2B8C *q4 = (*arg0)++; q4->w0 = 0x06000000; q4->w1 = (u32)&D_801D3030; }""",
'blk_first':"""{ T025Gfx2B8C *q2 = (*arg0)++; q2->w0 = 0xB900031D; q2->w1 = 0x0F0A4000; }
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    p0 = (*arg0)++; p0->w0 = 0x06000000; p0->w1 = (u32)&D_801D3030;""",
}
cands=[('base',s)]+[(k,s.replace(tail_old,v)) for k,v in variants.items()]
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,x) in zip(out,cands): print(r,k)
for k,x in cands: open(f'/tmp/w/r2b8c10_{k}.c','w').write(x)
